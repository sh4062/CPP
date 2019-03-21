cc = gcc
main : server.o client.o
 

client.o: client.cc 
		gcc  client.cc -o client.o
server.o: server.cc
		gcc  server.cc -o server.o  #加-c 指定生成为可重链接.o文件
clean:
	rm -rf *.o