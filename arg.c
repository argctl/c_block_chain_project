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
int main () {
  int eta = tar(); 
  struct sockaddr_in array, arg;
  ssize_t recv_len;
  char buffer[TARGIT];
  if (bind(eta, (struct sockaddr *)&array, sizeof(array)) < 0) {
    perror("binding socket to address failed");
  }
  socklen_t addr_size;
  printf("program exit");
  while (1) {
    printf("waiting for update...");
    addr_size = sizeof(arg);
    recv_len = recvfrom(eta, buffer, TARGIT, 0, (struct sockaddr *)&arg, &addr_size);
    if (recv_len > 0) {
      buffer[recv_len] = '\0';
      printf("Received: %s\n", buffer);
      sendto(eta, buffer, recv_len, 0, (struct sockaddr *)&arg, addr_size);
    } else {
      printf("recvfrom error\n");
    }
  }
  close(eta);
  return 0;
}
