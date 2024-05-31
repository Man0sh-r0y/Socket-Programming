// include the header files
#include<stdio.h> // Provides functions like printf and perror.
#include<stdlib.h> // Provides functions like exit and memory management functions.
#include<string.h> // Provides functions like memset, bzero, and strcpy.
#include<unistd.h> // Provides access to the close function and other system calls.
#include<arpa/inet.h> // Provides functions and definitions for manipulating IP addresses and port numbers (struct sockaddr_in, inet_addr, htons, etc.).

int main() {

    char *ip = "127.0.0.1"; // the ip address of the server
    // `127.0.0.1` is a special-purpose IPv4 address known as the loopback address. 
    // It is used to establish an IP connection to the same machine or computer being used by the end-user.
    // This address is commonly used for local testing and development because it does not require a network connection. 
    // Any data sent to `127.0.0.1` is looped back to the local machine, allowing developers to test network applications without needing an external network.

    int port = 5566; // the port number of the server
    // A port number is a 16-bit number (ranging from 0 to 65535) to distinguish different services or applications running on the same machine. 
    // You can choose any port number except the reserved port number (Like `port 80` is for HTTP etc.)

    int client_socket; // It's a Socket File Descriptor
    // A file descriptor is an unsigned integer used by a process to identify an open file.
    // socket file descriptor is a unique integer identifier that the operating system assigns to a socket when it is created. 
    // This identifier is used by the program to reference the socket in subsequent network communication operations.
    //  The file descriptor is passed to other socket functions like bind, listen, accept, connect, send, and recv to perform various network operations.
    
    struct sockaddr_in client_address;
    // This sockaddr_in structure is defined in the header file <arpa/inet.h> 
    // And I've defined the structure variable server_address and client_address

    socklen_t addr_size; // address of client socket
    // the variable `addr_size` is the type of socklen_t (an unsigned integral type) 
    // socklen_t describes the length of a socket address. 
    // This is an integer type of at least 32 bits.

    char buffer[1024];
    // this char array of size 1024 is used to store data received from or to be sent to the client. 
    // It acts as a temporary storage for messages exchanged between the server and the client.

    client_socket = socket(AF_INET, SOCK_STREAM, 0); // creates a new socket for network communication.
    // AF_INET: It is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses). 
    // SOCK_STREAM: It specifies the socket type. `SOCK_STREAM` indicates that this is a TCP socket, which provides reliable, two-way, connection-based byte streams.
    // 0: Specifies the protocol. When set to 0, the system chooses the default protocol for the given socket type, which is TCP for SOCK_STREAM

    if(client_socket < 0) { // if socket() returns -1, then socket creation failed
        perror("socket failed"); // it prints an error message
        exit(1); // terminate the program with a non-zero status which indicates an error
    } else {
        printf("TCP Socket created successfully\n"); // socket creation successful
        // A TCP socket is a software concept that allows applications to connect to a Transmission Control Protocol/Internet Protocol (TCP/IP) network. 
    }

    memset(&client_address, '\0', sizeof(client_address));// memset is used to fill a block of memory with a specific value and '\0' means NULL character
    client_address.sin_family = AF_INET; // It sets the address family to AF_INET, which is used for IPv4 addresses.
    client_address.sin_port = htons(port); // It sets the port number for the socket. And htons(port) converts the port number from host byte order to network byte order (big-endian). htons stands for "host to network short"
    client_address.sin_addr.s_addr = inet_addr(ip); // It sets the IP address for the server.
    // `inet_addr(ip)` converts the IP address in the ip string from the standard dot notation ("127.0.0.1") to a format suitable for the sin_addr.s_addr field of the `sockaddr_in` structure

    connect(client_socket, (struct sockaddr*)&client_address, sizeof(client_address)); // establish connection with the server

    printf("Connected to the server\n");

    bzero(buffer, 1024); // this bzero() clears the buffer to ensure it does not contain any leftover data.
    strcpy(buffer, "Hello from client"); // Response message is copied into buffer using strcpy.
    printf("Message sent to Server: %s\n", buffer);
    send(client_socket, buffer, sizeof(buffer), 0); // send() function send the data in the buffer to the server and the parameter `0` defines no special behavior
    
    bzero(buffer, 1024); // again clears the buffer
    recv(client_socket, buffer, sizeof(buffer), 0); // recv() reads data from the client_socket and stores the recieved data into the buffer and the parameter `0` defines no special behaviour
    printf("Message recieved from Server: %s\n", buffer);
    
    close(client_socket);
    printf("Connection closed !\n");
    

    return 0;
}