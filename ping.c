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
  struct addrinfo hints, *gadderinfo, *p; 
  hints.ai_family = AF_INET;      
  hints.ai_socktype = SOCK_DGRAM; 
  hints.ai_protocol = IPPROTO_UDP; // instructions specify IVP4 and UDP
  hints.ai_flags = AI_PASSIVE; 
  int sockfd; 

  int addrinfret = getaddrinfo(ponghost, pongport, &hints, &gadderinfo);

  if (addrinfret != 0){
    printf("ping: GETADDRINFO RETURNED VALUE OTHER THAN 0\n"); 
  }




 // int len; 
 
 for (p = gadderinfo; p != NULL; p = p->ai_next){
   sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
   if (sockfd != -1){
    break;
   }
 }
 //freeaddrinfo(gadderinfo);
 
 // sockfd = socket(gadderinfo->ai_family, gadderinfo->ai_socktype, gadderinfo->ai_protocol);
  printf("ping: attempting connect  on port %s\n", pongport); 

  if (sockfd == -1){
   printf("no usable socket found."); 
   return 1;
  }



 /* if(connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
  {
      printf("\n Error : Connect Failed \n");
      exit(0);
  }
  */
  char recvbuf[arraysize];
  struct sockaddr_storage their_addr;
  //socklen_t socklen_A
  //printf("ping: startign loop\n");
  
  //printf("aaa\n");
  //perror("the loop should start now.");i
  ssize_t sendcheck;
  ssize_t recvcheck;
  int validateResultPong = 0;
  double tottime = 0;
  double timeAtSend = 0;
  double timeAtRecieve = 0;
  double nTime = 0; 
  for (int i = 0; i  < nping; i++)   
  {
  
  //  socklen_t addr_len = gadderinfo->ai_addrlen;

  //  printf("client:attempting send"); 
    timeAtSend = get_wctime();
     sendcheck = sendto(sockfd, arr, sizeof(arr), 0, gadderinfo->ai_addr,gadderinfo->ai_addrlen);
    
    if (sendcheck == -1){
     //  printf("ping:sent \n");
   //  }else{
       printf("ping:send error occured.\n");
     }

    socklen_t  recvsocklen = sizeof(their_addr); 
    recvcheck =  recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*)&their_addr, &recvsocklen);
    timeAtRecieve = get_wctime();
    if (recvcheck != -1) { 
     // printf("ping:recieved\n");

      //validate section. 
      for (int j = 0; j < sizeof(recvbuf); j++){
       // printf("%d\n", (int) recvbuf[j]);
        if (recvbuf[j] != (char) 201){
          validateResultPong = 1;
        }
      }
      tottime += (timeAtRecieve - timeAtSend); 
      nTime = (timeAtRecieve - timeAtSend);
      printf("ping[%d] : round-trip time: %lf ms\n", i, nTime);
      

    }else{
      printf("ping: recieve error occured.\n");
    }
    
  }
 if (validateResultPong == 1) {
    printf("ping: returned buffs from server did not have 201\n"); 
  }else{
    printf("no errors detected");
  }
  printf("time to send %d packets of %d bytes %lf ms (%lf avg per packet)\n", nping, arraysize, tottime, (tottime / nping));
  printf("client:finished\n");



  return 0;
}
