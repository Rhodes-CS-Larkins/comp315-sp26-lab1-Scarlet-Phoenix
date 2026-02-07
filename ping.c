/*
 * ping.c - UDP ping/pong client code
 *          author: <your name>
 */
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "util.h"

#define PORTNO "1266"


int main(int argc, char **argv) {
  int ch, errors = 0;
  int nping = 1;                        // default packet count
  char *ponghost = strdup("localhost"); // default host
  char *pongport = strdup(PORTNO);      // default port
  int arraysize = 100;                  // default packet size
//  int verbose = 0;

  while ((ch = getopt(argc, argv, "h:n:p:")) != -1) {
    switch (ch) {
    case 'h':
      ponghost = strdup(optarg);
      break;
    case 'n':
      nping = atoi(optarg);
      break;
    case 'p':
      pongport = strdup(optarg);
      break;
    case 's':
      arraysize = atoi(optarg);
      break;
    //case 'v':
     // verbose = 1;
     // break;
    default:
      fprintf(stderr, "usage: ping [-h host] [-n #pings] [-p port] [-s size]\n");
    }
  }

  // UDP ping implemenation goes here
  printf("nping: %d arraysize: %d errors: %d ponghost: %s pongport: %s\n",
      nping, arraysize, errors, ponghost, pongport);

  char arr[arraysize]; //= 200; 
  for (size_t cur = 0; cur < arraysize; cur++){
    arr[cur] = (char)200;
  }
  struct sockaddr_in saddr; 
  bzero(&saddr, sizeof(saddr));
  int sockfd; 


 // int len; 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if(connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
  {
      printf("\n Error : Connect Failed \n");
      exit(0);
  }
  char recvbuf[arraysize]; 
  for (int cur = 0; cur < nping; cur++)
  {
    
    sendto(sockfd, arr, arraysize, 0, (struct sockaddr*)NULL, sizeof(saddr));
    printf("client:sent \n");
    recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)NULL, NULL);
    printf("client:recieved\n");
  }
  printf("client:finished\n");



  return 0;
}
