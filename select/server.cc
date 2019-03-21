// #include <sys/select.h>
// #include <sys/time.h>

// int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,const struct timeval *timeout)
//maxfdp1指定待测试的描述字个数，它的值是待测试的最大描述字加1
//中间的三个参数readset、writeset和exceptset指定我们要让内核测试读、写和异常条件的描述字
//timeout告知内核等待所指定描述字中的任何一个就绪可花多少时间
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h> //互联网地址族 sockaddr_in
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#define IPADDR "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define SIZE 10

typedef struct server_context_st
{
    int cli_cnt;      /*客户端个数*/
    int clifds[SIZE]; /*客户端的个数*/
    fd_set allfds;    /*句柄集合*/
    int maxfd;        /*句柄最大值*/
} server_context_st;
static server_context_st *s_srv_ctx = NULL;
//Init
static int server_init()
{
    s_srv_ctx = (server_context_st *)malloc(sizeof(server_context_st));
    if (s_srv_ctx == NULL)
    {
        return -1;
    }
    memset(s_srv_ctx, 0, sizeof(server_context_st));
    int i = 0;
    for (; i < SIZE; i++)
    {
        s_srv_ctx->clifds[i] = -1;
    }
    return 0;
}
//create
int create_server_proc(const char *ip, int port)
{
    int fd;
    struct sockaddr_in ser_addr;
    fd = socket(AF_INET, SOCK_STREAM, 0); //ip版本,通信类型,协议比如udptcp
    if (fd == -1)
    {
        fprintf(stderr, "create socket fail,erron:%d,reason:%s\n", errno, strerror(errno));
        return -1;
    }
    int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1)
    {
        return -1;
    }
    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &ser_addr.sin_addr);
    ser_addr.sin_port = htons(port);
    if (bind(fd, (sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
    {
        perror("bind error!");
        return -1;
    }
    listen(fd, LISTENQ);
    return fd;
}
static int accept_client_proc(int srvfd)
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;

    printf("accpet clint proc is called.\n");

ACCEPT:
    clifd = accept(srvfd,(struct sockaddr*)&cliaddr,&cliaddrlen);

    if (clifd == -1) {
        if (errno == EINTR) {
            goto ACCEPT;
        } else {
            fprintf(stderr, "accept fail,error:%s\n", strerror(errno));
            return -1;
        }
    }

    fprintf(stdout, "accept a new client: %s:%d\n",
            inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);

    //将新的连接描述符添加到数组中
    int i = 0;
    for (i = 0; i < SIZE; i++) {
        if (s_srv_ctx->clifds[i] < 0) {
            s_srv_ctx->clifds[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }

    if (i == SIZE) {
        fprintf(stderr,"too many clients.\n");
        return -1;
    }
 }

static int handle_client_msg(int fd, char *buf) 
{
    assert(buf);
    printf("recv buf is :%s\n", buf);
    write(fd, buf, strlen(buf) +1);
    return 0;
}

static void recv_client_msg(fd_set *readfds)
{
    int i = 0, n = 0;
    int clifd;
    char buf[MAXLINE] = {0};
    for (i = 0;i <= s_srv_ctx->cli_cnt;i++) {
        clifd = s_srv_ctx->clifds[i];
        if (clifd < 0) {
            continue;
        }
        /*判断客户端套接字是否有数据*/
        if (FD_ISSET(clifd, readfds)) {
            //接收客户端发送的信息
            n = read(clifd, buf, MAXLINE);
            if (n <= 0) {
                /*n==0表示读取完成，客户都关闭套接字*/
                FD_CLR(clifd, &s_srv_ctx->allfds);
                close(clifd);
                s_srv_ctx->clifds[i] = -1;
                continue;
            }
            handle_client_msg(clifd, buf);
        }
    }
}
static void handle_client_proc(int srvfd)
{
    int  clifd = -1;
    int  retval = 0;
    fd_set *readfds = &s_srv_ctx->allfds;
    struct timeval tv;
    int i = 0;

    while (1) {
        /*每次调用select前都要重新设置文件描述符和时间，因为事件发生后，文件描述符和时间都被内核修改啦*/
        FD_ZERO(readfds);
        /*添加监听套接字*/
        FD_SET(srvfd, readfds);
        s_srv_ctx->maxfd = srvfd;

        tv.tv_sec = 30;
        tv.tv_usec = 0;
        /*添加客户端套接字*/
        for (i = 0; i < s_srv_ctx->cli_cnt; i++) {
            clifd = s_srv_ctx->clifds[i];
            /*去除无效的客户端句柄*/
            if (clifd != -1) {
                FD_SET(clifd, readfds);
            }
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd : s_srv_ctx->maxfd);
        }

        /*开始轮询接收处理服务端和客户端套接字*/
        retval = select(s_srv_ctx->maxfd + 1, readfds, NULL, NULL, &tv);
        if (retval == -1) {
            fprintf(stderr, "select error:%s.\n", strerror(errno));
            return;
        }
        if (retval == 0) {
            fprintf(stdout, "select is timeout.\n");
            continue;
        }
        if (FD_ISSET(srvfd, readfds)) {
            /*监听客户端请求*/
            accept_client_proc(srvfd);
        } else {
            /*接受处理客户端消息*/
            recv_client_msg(readfds);
        }
    }
}

//de
static void server_uninit()
{
    if (s_srv_ctx)
    {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}
int main()
{
    int ser_fd;
    if (server_init() < 0)
        return -1;
    ser_fd = create_server_proc(IPADDR, PORT);
    if (ser_fd < 0)
    {
        fprintf(stderr, "socket create or bind fail.\n");
        server_uninit();
        return -1;
    }
    handle_client_proc(ser_fd);
    server_uninit();
    return 0;
}