// include the header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {

    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in address;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0) {
        perror("socket failed");
        exit(1);
    } else {
        printf("TCP Server Socket created successfully\n");
    }

    memset(&address, '\0', sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip);

    connect(sock, (struct sockaddr*)&address, sizeof(address));
    printf("Connected to the server\n");

    bzero(buffer, 1024);
    strcpy(buffer, "Hello from client");
    printf("Client: %s\n", buffer);
    send(sock, buffer, sizeof(buffer), 0);
    
    bzero(buffer, 1024);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);
    
    close(sock);
    printf("Connection closed from server\n");
    

    return 0;
}