#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main(){
struct addrinfo hints, *server;
struct sockaddr client;
socklen_t client_size;
int r,socketfd;
const char *buffer = "UDP SERVER: Hello DON_R \n";
const int size = 1024;
char input[size];

/* Configure the server*/
memset(&hints,0,sizeof(hints));
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_DGRAM;
hints.ai_flags = AI_PASSIVE;
r = getaddrinfo(0,"8080",&hints,&server);
if(r<0){
perror("Failed");
exit(1);
}

/* create the socket */
socketfd = socket(server->ai_family,server->ai_socktype,server->ai_protocol);
if(socketfd==-1){
perror("socket_fd");
exit(1);
}

r=bind(socketfd, server->ai_addr, server->ai_addrlen);
if(r==-1){
perror("Bind");
exit(1);
}
puts("UDP Server is Listening...");
/* no need to listen or accepts UDP Server */

client_size = sizeof(struct sockaddr);

r=recvfrom(
socketfd,
input,
size,
0,
&client,
&client_size);

if(r==-1){
  perror("failed");
  exit(1);
}

r = sendto(
socketfd,
buffer,
strlen(buffer),
0,
&client,
client_size);

if(r==-1){
perror("sendto");
}
return 0;
}


