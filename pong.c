/*
 * pong.c - UDP ping/pong server code
 *          author: <Charles Reed>
 */
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "util.h"

#define PORTNO "1266"


/*void *get_in_addr (struct sockaddr *sa) 
{
  return &(((struct sockaddr_in*)sa)->sin_addr);
}*/


int main(int argc, char **argv) {
  int ch;
  int nping = 1;                    // default packet count
  char *pongport = strdup(PORTNO);  // default port

  while ((ch = getopt(argc, argv, "h:n:p:")) != -1) {
    switch (ch) {
    case 'n':
      nping = atoi(optarg);
      break;
    case 'p':
      pongport = strdup(optarg);
      break;
    default:
      fprintf(stderr, "usage: pong [-n #pings] [-p port]\n");
    }
  }
 // pongport = strdup("127.0.0.1");
// char recvBuf;
 int sockfd;// len; 
 int rv; 
 //struct sockaddr_in servaddr, clientaddr;
 struct addrinfo servaddr, hints, *servinfo, *p; 
 memset(&servaddr, 0, sizeof(servaddr));
 hints.ai_family = AF_INET; 
 hints.ai_socktype = SOCK_DGRAM; 
 hints.ai_protocol = IPPROTO_UDP; 
 hints.ai_flags = AI_PASSIVE; 
 

  if (( rv = getaddrinfo(NULL, pongport, &hints, &servinfo)) != 0){
    return 1;
  }
  for (p = servinfo; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd == -1) continue;

    int y = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(y));

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(sockfd);
        continue;
    }

    break;
  }
  freeaddrinfo(servinfo); 
  printf("pong: listening on port %s\n", pongport);
  //printf("%d", nping);
  //int counter = 0; 
  struct sockaddr their_addr; 
  socklen_t addr_len = sizeof(their_addr);
  //char s[AF_INET];
  



  //while(1){
  for (int curr = 0; curr < nping; curr++){
    char buf[1024];                     
   // struct sockaddr_storage their_addr;
    //socklen_t addr_len = sizeof(their_addr);
    ssize_t numbytes = recvfrom(sockfd, buf, sizeof(buf)-1, 0,
                                (struct sockaddr *)&their_addr, &addr_len);
    printf("pong[%d] : recieved packet from %s\n", curr, their_addr.sa_data);
         //inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof s)); 
    //inet_ntop(AF_INET, &((struct sockaddr_in *) their_addr.ai_addr), ipAddress, INET_ADDRSTRLEN) );   

    if (numbytes == -1) {
        perror("pong: recvfromerror\n");
        return(1);
    }//else{
      //counter++;
    //  if (counter >= nping){
      //  counter = 0; 
      //}
    //}
    for (ssize_t i = 0; i < sizeof(buf); i++) {
        buf[i] = (char)201; 
    }


    sendto(sockfd, buf, sizeof(buf), 0,
           (struct sockaddr *)&their_addr, addr_len);
}



  //sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

  return 0;
}

