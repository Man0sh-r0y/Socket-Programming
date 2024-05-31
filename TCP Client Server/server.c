// include the header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {

    char *ip = "127.0.0.1"; // the ip address of the server
    int port = 5566; // the port number of the server

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket < 0) {
        perror("socket failed");
        exit(1);
    } else {
        printf("TCP Server Socket created successfully\n");
    }

    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if(n < 0) {
        perror("bind failed");
        exit(1);
    } else {
        printf("TCP Server Socket binded successfully to IP: %s and Port: %d\n", ip, port);
    }

    listen(server_socket, 5);
    printf("Listening for connections...\n");

    while (1)
    {
        addr_size = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addr_size);
        if(client_socket < 0) {
            perror("accept failed");
            exit(1);
        } else {
            printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

            bzero(buffer, 1024);
            recv(client_socket, buffer, sizeof(buffer), 0);
            printf("Client: %s\n", buffer);

            bzero(buffer, 1024);
            strcpy(buffer, "Hello from server");
            send(client_socket, buffer, strlen(buffer), 0);
            printf("Server: %s\n", buffer);
            send(client_socket, buffer, strlen(buffer), 0);

            close(client_socket);
            printf("Connection closed from client\n");
        }
    }
    

    return 0;
}