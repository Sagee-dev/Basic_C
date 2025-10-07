#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main(){ 

  struct addrinfo hints, *host;
  int r, sockfd;
  const int size = 1024;
  char buffer[size];
  
  /* configure the remote address */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  r = getaddrinfo(0,"8080",&hints, &host);
  if(r !=0){
  perror("get_addr");
  exit(1);
  }

/*create the socket*/
sockfd = socket(host->ai_family,host->ai_socktype,host->ai_protocol);
if(sockfd==-1){
perror("socket");
exit(1);
}

/* a UDP server requires something to be sent before a respose can be generated */
r=sendto(sockfd,
"\n",
1,
0,
host->ai_addr,
host->ai_addrlen);

r=recvfrom(
sockfd,
buffer,
size,
0,
host->ai_addr,
&host->ai_addrlen);

buffer[r] = '\0';
printf("%s",buffer);
/*done cleanup*/
return 0;
}
