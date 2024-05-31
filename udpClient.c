#include <stdio.h>          // Standard I/O library for functions like printf and perror
#include <stdlib.h>         // Standard library for functions like exit and atoi
#include <string.h>         // String handling library for functions like memset, bzero, and strcpy
#include <sys/socket.h>     // Library for socket functions
#include <sys/types.h>      // Library for data types used in socket programming
#include <netinet/in.h>     // Library for Internet address family
#include <arpa/inet.h>      // Library for functions like inet_addr and htons

int main(int argc, char **argv) // Main function with command line arguments
{
    // Check if the correct number of arguments is provided
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]); // Print usage message
        exit(0); // Exit the program if the number of arguments is incorrect
    }

    char *ip = "127.0.0.1"; // IP address to bind the server to (localhost)
    int port = atoi(argv[1]); // Convert the port number from a string to an integer

    int sockfd; // Socket file descriptor
    struct sockaddr_in addr; // Structure to hold the address information
    char buffer[1024]; // Buffer to hold data
    socklen_t addr_size; // Variable to hold the size of the address

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket
    memset(&addr, '\0', sizeof(addr)); // Clear the address structure
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(port); 
    addr.sin_addr.s_addr = inet_addr(ip); 

    bzero(buffer, 1024); // Clear the buffer
    strcpy(buffer, "Hello, World!"); // Copy the message into the buffer
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr)); // Send the message to the server
    printf("[+]Data send: %s\n", buffer); // Print the sent message

    bzero(buffer, 1024); // Clear the buffer again
    addr_size = sizeof(addr); // Set the size of the address structure
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size); // Receive data from the server
    printf("[+]Data recv: %s\n", buffer); // Print the received data

    return 0;
}
