cc = gcc
main : server.o client.o
 

client.o: client.c 
		gcc  client.c -o client.o
server.o: server.c
		gcc  server.c -o server.o  #加-c 指定生成为可重链接.o文件
clean:
	rm -rf *.o