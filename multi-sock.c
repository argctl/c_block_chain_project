#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int create_socket_and_bind(int port) {
    int sock;
    struct sockaddr_in address;
    int reuse = 1;

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Set SO_REUSEADDR to allow multiple bindings to the same port
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("Setting SO_REUSEADDR failed");
        close(sock);
        return -1;
    }

    // Set SO_REUSEPORT to allow multiple bindings to the same port (if supported)
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
        perror("Setting SO_REUSEPORT failed");
        close(sock);
        return -1;
    }

    // Set up the address structure
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all local interfaces

    // Bind the socket to the specified port
    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(sock);
        return -1;
    }

    printf("Socket bound to port %d\n", port);
    return sock;
}

int main() {
    int port = 9229;

    // Create and bind the first socket
    int sock1 = create_socket_and_bind(port);
    if (sock1 < 0) {
        return -1;
    }

    // Create and bind the second socket
    int sock2 = create_socket_and_bind(port);
    if (sock2 < 0) {
        close(sock1);
        return -1;
    }

    // Both sockets are now bound to the same port
    printf("Both sockets are successfully bound to port %d\n", port);

    // Close sockets before exiting
    close(sock1);
    close(sock2);

    return 0;
}
