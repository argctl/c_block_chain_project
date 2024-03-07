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
  // TODO - add semi-permenant or permenant ID to socket location to return chain or "lace" (trace) of encryption 
  // seeded tar then gains value by network address length or accumulates tar value and the transfer of keys, changeable values in those keys are the "tokens"
  return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  // NOTE - the tar really is the data stored here if the integers match, so a check for matches at location with the 2d bilateral ids, makes the electronic cash
}
int main () {
  struct sockaddr_in i, o;
  int _socket_ = sizeof(i), recv_len;
  char buffer[TARGIT];
  
}
