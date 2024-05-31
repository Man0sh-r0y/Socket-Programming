#include <stdio.h>          // Standard I/O library for functions like printf and perror
#include <stdlib.h>         // Standard library for functions like exit and atoi
#include <string.h>         // String handling library for functions like memset and strcpy
#include <sys/socket.h>     // Library for socket functions
#include <sys/types.h>      // Library for data types used in socket programming
#include <netinet/in.h>     // Library for Internet address family
#include <arpa/inet.h>      // Library for functions like inet_addr and htons

int main(int argc, char **argv) // Main function with command line arguments
{
    if (argc != 2) // Check if the correct number of arguments is provided
    {
        printf("Usage: %s <port>\n", argv[0]); // Print usage message
        exit(0); // Exit the program if the number of arguments is incorrect
    }

    char *ip = "127.0.0.1"; // IP address to bind the server to (localhost)
    int port = atoi(argv[1]); // Convert the port number from a string to an integer

    int sockfd; // Socket file descriptor
    struct sockaddr_in server_addr, client_addr; // Structures to hold server and client addresses
    char buffer[1024]; // Buffer to hold data
    socklen_t addr_size; // Variable to hold the size of the address
    int n; // Variable for return values

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket
    if (sockfd < 0) // Check if the socket was created successfully
    {
        perror("[-]socket error"); // Print an error message if socket creation failed
        exit(1); // Exit the program
    }

    memset(&server_addr, '\0', sizeof(server_addr)); // Clear the server address structure
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr.s_addr = inet_addr(ip); 

    n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // Bind the socket to the IP address and port
    if (n < 0) // Check if binding was successful
    {
        perror("[-]bind error"); // Print an error message if binding failed
        exit(1); // Exit the program
    }

    bzero(buffer, 1024); // Clear the buffer
    addr_size = sizeof(client_addr); // Set the size of the client address structure
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_size); // Receive data from a client
    printf("[+]Data recv: %s\n", buffer); // Print the received data

    bzero(buffer, 1024); // Clear the buffer again
    strcpy(buffer, "Welcome to the UDP Server."); // Copy a welcome message into the buffer
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr)); // Send the welcome message to the client
    printf("[+]Data send: %s\n", buffer); // Print the sent message

    return 0; // Return 0 to indicate successful execution
}
