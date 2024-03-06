#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 9229
// the smaller packet size and smaller node size means more granular control and validation
// validating changes in output in larger volumes will lose ordering at the CPU level
// Sporadic checks with long node chaining data creates 2d network map with bilateral ids, making electronic cash
#define TARGIT 8
// TODO - call for each instance that wants computation
// REVIEW - implicit but should bind both the socket and a buffer counter to socket if possible
int tar () {
  // TODO - build cost for return validation
  return 0;
}
int main () {
  struct sockaddr_in i, o;
  int _socket_ = sizeof(i), recv_len;
  char buffer[
  
}
