#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
//#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9229
// the smaller packet size and smaller node size means more granular control and validation
// validating changes in output in larger volumes will lose ordering at the CPU level
// Sporadic checks with long node chaining data creates 2d network map with bilateral ids, making electronic cash
#define TARGIT 8
// TODO - call for each instance that wants computation
// REVIEW - implicit but should bind both the socket and a buffer counter to socket if possible
typedef struct {
  char* (*inner)(struct sockaddr*, int*, char*, socklen_t, ssize_t);
  int* eta;
  struct sockaddr* arg;
  socklen_t addr_size;
  ssize_t recv_len;
  char* buffer;
} Arg;
char* inner (struct sockaddr* arg, int* eta, char* buffer, socklen_t addr_size, ssize_t recv_len) {
  printf("Waiting for message...\n");
  addr_size = sizeof(&arg);
  recv_len = recvfrom(*eta, buffer, TARGIT, 0, arg, &addr_size);

  if (recv_len > 0) {
    buffer[recv_len] = '\0'; // Null-terminate the received data
    printf("Received: %s\n", buffer);
    // Echo message back to client
    sendto(*eta, buffer, recv_len, 0, arg, addr_size);
    printf("returning...");
    return buffer;
  } else {
    printf("recvfrom error\n");
  }
}

char* call (Arg* arg) {
  //void inner (struct sockaddr* arg, int* eta, char* buffer, socklen_t addr_size, ssize_t recv_len) {
  return arg->inner(arg->arg, arg->eta, arg->buffer, arg->addr_size, arg->recv_len);
}

Arg* createInner (char* (*inner)(struct sockaddr*, int*, char*, socklen_t, ssize_t)) {
  Arg* args = (Arg*)malloc(sizeof(Arg));
  args->arg = (struct sockaddr*)malloc(sizeof(struct sockaddr_in));
  args->eta = (int*)malloc(sizeof(int));
  args->buffer = (char*)malloc(sizeof(char) * TARGIT);
  args->addr_size = sizeof(struct sockaddr_in);
  args->recv_len = 0;
  args->inner = inner;
  struct sockaddr_in array;//, arg;
  //char buffer[TARGIT]
  //socklen_t addr_size;
  //ssize_t recv_len;
  if ((*args->eta = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("cannot create socket");
    return args;
  }
  memset(&array, 0, sizeof(array));
  array.sin_family = AF_INET;
  array.sin_port = htons(PORT);
  array.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(*args->eta, (struct sockaddr *)&array, sizeof(array)) < 0) {
    perror("bind fail");
    return args;
  }
  printf("UDP listen on port %d", PORT);
  return args; 
}
/*
int tar () {
  int eta;
  struct sockaddr_in array, arg;
  //create the socket
  if ((eta = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    return 0;
  }
  memset(&array, 0, sizeof(array));
  array.sin_family = AF_INET;
  array.sin_port = htons(PORT);
  // REVIEW docs
  array.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(eta, (struct sockaddr *)&array, sizeof(array)) < 0) {
    perror("binding socket to address failed");
  }
  printf("UDP gitarray service for gitarg listening on port %d for updates...\n", PORT);
  // TODO - build cost for return validation
  // TODO - add semi-permenant or permenant ID to socket location to return chain or "lace" (trace) of encryption 
  // seeded tar then gains value by network address length or accumulates tar value and the transfer of keys, changeable values in those keys are the "tokens"
  return eta;
  // NOTE - the tar really is the data stored here if the integers match, so a check for matches at location with the 2d bilateral ids, makes the electronic cash
}
*/

/*
int main () {
  Arg* arg = createInner(inner);
  while (1) {
    call(arg);    
  }
  
  return 0;
}
*/
