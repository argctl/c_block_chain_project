#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 9229
#define BUFSIZE 8
typedef struct {
  void (*inner)(struct sockaddr*, int*, char*, socklen_t, ssize_t);
  struct sockaddr* arg;
  int* eta;
  char* buffer;
  socklen_t addr_size;
  ssize_t recv_len;
} Arg;
void inner (struct sockaddr* arg, int* eta, char* buffer, socklen_t addr_size, ssize_t recv_len) {
  printf("Waiting for message...\n");
  addr_size = sizeof(&arg);
  recv_len = recvfrom(*eta, buffer, BUFSIZE, 0, arg, &addr_size);

  if (recv_len > 0) {
    buffer[recv_len] = '\0'; // Null-terminate the received data
    printf("Received: %s\n", buffer);
    // Echo message back to client
    sendto(*eta, buffer, recv_len, 0, arg, addr_size);
  } else {
    printf("recvfrom error\n");
  }
}

void call (Arg* arg) {
  //void inner (struct sockaddr* arg, int* eta, char* buffer, socklen_t addr_size, ssize_t recv_len) {
  return arg->inner(arg->arg, arg->eta, arg->buffer, arg->addr_size, arg->recv_len);
}

Arg* createInner (void (*inner)(struct sockaddr*, int*, char*, socklen_t, ssize_t)) {
  Arg* args = (Arg*)malloc(sizeof(Arg));
  args->arg = (struct sockaddr*)malloc(sizeof(struct sockaddr_in));
  args->eta = (int*)malloc(sizeof(int));
  args->buffer = (char*)malloc(sizeof(char) * BUFSIZE);
  args->addr_size = sizeof(struct sockaddr_in);
  args->recv_len = 0;
  args->inner = inner;
  struct sockaddr_in array;//, arg;
  //char buffer[BUFSIZE]
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
  send('G');
  return args; 
}
int main() {
    Arg* arg = createInner(inner);
    //Args *args = outer();
    /*
    int eta;
    struct sockaddr_in array, arg;
    char buffer[BUFSIZE];
    socklen_t addr_size;
    ssize_t recv_len;

    // Create socket
    if ((eta = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket");
        return 0;
    }

    // Configure settings in address struct
    memset(&array, 0, sizeof(array));
    array.sin_family = AF_INET;
    array.sin_port = htons(PORT);
    array.sin_addr.s_addr = htonl(INADDR_ANY); // Use any available address

    // Bind socket with address struct
    if (bind(eta, (struct sockaddr *)&array, sizeof(array)) < 0) {
        perror("bind failed");
        return 0;
    }

    printf("UDP Server listening on port %d\n", PORT);
    */

    // Listen for incoming datagrams
    while (1) {
      call(arg);
      //inner((struct sockaddr *)&arg, &eta, buffer, addr_size, recv_len);
      //inner(args->arg, args->eta, args->buffer, args->addr_size, args->recv_len);
        /*
        printf("Waiting for message...\n");
        addr_size = sizeof(arg);
        recv_len = recvfrom(eta, buffer, BUFSIZE, 0, (struct sockaddr *)&arg, &addr_size);

        if (recv_len > 0) {
            buffer[recv_len] = '\0'; // Null-terminate the received data
            printf("Received: %s\n", buffer);

            // Echo message back to client
            sendto(eta, buffer, recv_len, 0, (struct sockaddr *)&arg, addr_size);
        } else {
            printf("recvfrom error\n");
        }
      */
    }

    //close(args->eta);
    return 0;
}
