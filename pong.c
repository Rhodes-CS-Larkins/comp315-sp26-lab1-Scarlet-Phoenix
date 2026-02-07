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

 

  // pong implementation goes here.
  printf("nping: %d pongport: %s\n", nping, pongport);

  struct addrinfo  hints, *servinfo, *p;
  int sadderinfo; 
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM; 
  hints.ai_protocol = IPPROTO_UDP; 
  int sockfd;
//  int bindret;
  
  sadderinfo = getaddrinfo(NULL, pongport, &hints, &servinfo);
/*
  for(p = servinfo; p!= NULL; p = p->ai_next)
  {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("server: socket\n");
      continue;
    }
    if ((bind(sockfd, p->ai_addr, p->ai_addrlen)) == -1){
      perror("server: bind\n");
      continue;
  }
*/
  //bind(sockfd, p->ai_addr, p->ai_addrlen);
  //sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol); 
/*   for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -2) {
            perror("server: socket");
            continue;
        }
   }

  bindret = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

*/
  printf("pong: sadderinfo: %d", sadderinfo);
  printf("waiting for connections.");
  while(1){
    for (p = servinfo; p != NULL; p = p->ai_next) {
      if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -2){
        perror("Server: didn't bind to socket");
        continue;

      }
      if ((bind(sockfd, p->ai_addr, p->ai_addrlen)) == -1){
        perror("pong: bind error");
        close(sockfd);
        continue;
      }
    } 



    // int newsock = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size
    for (int i = 0; i < nping; i++){
      char *cbuf; 
      recv(sockfd, &cbuf, sizeof(cbuf), 0); 
      printf("pong[%d]: recieved packet from %d", i,sockfd );
      for (int v = 0; v < sizeof(cbuf); v++)
      {
         cbuf[v]++;
        }
      send(sockfd, &cbuf, sizeof(cbuf), 0);
    }
  }
  return 0;
}

