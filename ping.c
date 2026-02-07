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
 // for (int i = 0; i < sizeof(arr); i++){
    //arr[i] = 200; 
  //}
 
  //if (verbose) printf("ping: attempting to alloc and memset arr\n");
 /* char *arr = malloc(arraysize * sizeof(char)); 
  if (arr == NULL){
    perror("Failed to alloc array"); 
    exit(1);
  }
  memset(arr, 200, arraysize);
  */
  for (size_t cur = 0; cur < arraysize; cur++){
    arr[cur] = (char)200;
  }
  printf("set char array to 200\n");
  int sockfd; 
 // int numbytes; 
  int sadderinfo;
  struct addrinfo hints, *servinfo, *p; // int rv;
//  char s[INET6_ADDRSTRLEN];
  hints.ai_family = AF_INET; 
  hints.ai_socktype = SOCK_DGRAM; 
  hints.ai_protocol = IPPROTO_UDP; 
 if ((sadderinfo = getaddrinfo(ponghost, pongport, &hints, &servinfo)) == -1)
 {
   perror("ping: addrinfo"); 
   return 1;
 }
  printf("ping: set addrinfo, attempting to call socket\n"); 
 // sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
 for (p = servinfo; p != NULL; p = p->ai_next) {
   if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
     printf("Client: connected.\n");
     continue;
   }
  if (sockfd == -1) {
    perror("Socket not found.");
    exit(1);
  }
 }
  printf("Client: Trying to send to %d.\n", sadderinfo); 
//  int totalTimeCounter = 0;
 // int localTimeCounter = 0;
  char recvArr[arraysize]; 
  for (int pingnum = 0; pingnum < nping; pingnum++)
  {
//    localTimeCounter = 0; 
    send(sockfd, arr, sizeof(arr), 0);
    recv(sockfd, recvArr, sizeof(arr), 0);
    for (int i = 0; i < arraysize; i++)
    {
      if ((int)recvArr[i] != 201){
        perror("ping: array did not arrive back with size 201"); 
        break;
      }
    }






  }



  return 0;
}
