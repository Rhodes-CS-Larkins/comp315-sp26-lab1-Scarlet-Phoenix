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
 bzero(&servaddr, sizeof(servaddr)); 
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

    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(sockfd);
        continue;
    }

    break;
  }
  freeaddrinfo(servinfo); 
  printf("pong: listening on port %s\n", pongport);
  printf("%d", nping);
  while(1){
    char buf[1024];                     // fixed-size buffer — adjust as needed
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof(their_addr);

    ssize_t numbytes = recvfrom(sockfd, buf, sizeof(buf)-1, 0,
                                (struct sockaddr *)&their_addr, &addr_len);
    printf("recieved %u\n",(int) numbytes); 

    if (numbytes == -1) {
        perror("pong: recvfromerror\n");
        continue;
    }
    for (ssize_t i = 0; i < numbytes; i++) {
        buf[i]++;
    }


    sendto(sockfd, buf, numbytes, 0,
           (struct sockaddr *)&their_addr, addr_len);
}



  //sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

  return 0;
}

