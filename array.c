#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void array (char* ctl) {
  int arg;
  const char *tar = ctl;
  struct sockaddr_in serverAddress;
  if ((arg = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failure");
    //return 1;
    exit(1); 
  } 
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9229);
  serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  ssize_t bytes = sendto(arg, tar, strlen(tar), 0, (const struct sockaddr *) &serverAddress, sizeof(serverAddress));
  /*
  if (bytes < 0) {
    return 1;
  } else {
    return 0;
  }
  */
  close(arg);
}

/*
int main () {
  char *tar = "G1G2G3G4";
  array(tar);
  
  return 0;

}
*/
