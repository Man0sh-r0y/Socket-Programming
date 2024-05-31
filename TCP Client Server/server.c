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

    int server_socket, client_socket;

    struct sockaddr_in server_address, client_address; 
    // This sockaddr_in structure is defined in the header file <arpa/inet.h> 
    // And I've defined the structure variable server_address and client_address

    socklen_t addr_size; // the variable `addr_size` is the type of socklen_t (an unsigned integral type) 
    // socklen_t describes the length of a socket address. 
    // This is an integer type of at least 32 bits.

    char buffer[1024]; 
    // this char array of size 1024 is used to store data received from or to be sent to the client. 
    //It acts as a temporary storage for messages exchanged between the server and the client.

    int n;

    server_socket = socket(AF_INET, SOCK_STREAM, 0); // creates a new socket for network communication.
    // AF_INET: It is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses). 
    // SOCK_STREAM: It specifies the socket type. `SOCK_STREAM` indicates that this is a TCP socket, which provides reliable, two-way, connection-based byte streams.
    // 0: Specifies the protocol. When set to 0, the system chooses the default protocol for the given socket type, which is TCP for SOCK_STREAM

    printf("Server Socket: %d\n", server_socket);

    if(server_socket < 0) { // if socket() returns -1, then socket creation failed
        perror("socket failed"); // it prints an error message
        exit(1); // terminate the program with a non-zero status which indicates an error
    } else {
        printf("TCP Server Socket created successfully\n"); // socket creation successful
    }

    memset(&server_address, '\0', sizeof(server_address)); // memset is used to fill a block of memory with a specific value and '\0' means NULL character
    server_address.sin_family = AF_INET; // It sets the address family to AF_INET, which is used for IPv4 addresses.
    server_address.sin_port = htons(port); // It sets the port number for the socket. And htons(port) converts the port number from host byte order to network byte order (big-endian). htons stands for "host to network short"
    server_address.sin_addr.s_addr = inet_addr(ip); // It sets the IP address for the server.
    // `inet_addr(ip)` converts the IP address in the ip string from the standard dot notation ("127.0.0.1") to a format suitable for the sin_addr.s_addr field of the `sockaddr_in` structure

    n = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    // After the creation of the socket, the bind function binds the socket to the address and port number 
    // (struct sockaddr*)&server_address: It's a pointer to the sockaddr_in structure that contains the address to which the socket will be bound. 
    // It needs to be cast to a struct sockaddr* as the bind function expects this type.


    if(n < 0) { // if bind() returns -1, then bind failed
        perror("bind failed");
        exit(1);
    } else { // bind succesfull
        printf("Socket binded successfully to IP: %s and Port: %d\n", ip, port);
    }

    listen(server_socket, 5); 
    // It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection.
    // 5: This parameter is the backlog parameter, which defines the maximum length of the queue of pending connections. Here, it is set to 5.
    // the backlog parameter specifies the number of pending connections the queue will hold.
    // When multiple clients connect to the server, the server then holds the incoming requests in a queue. 
    // The clients are arranged in the queue, and the server processes their requests one by one as and when queue-member proceeds. 
    // The nature of this kind of connection is called queued connection.

    printf("Listening for connections...\n");

    while (1) // It will continuously accept incoming connections.
    {
        addr_size = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addr_size);
        // accept() waits for an incoming connection request and returns a new socket file descriptor for the connection.

        if(client_socket < 0) {
            perror("accept failed");
            exit(1);
        } else {
            printf("\nConnection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

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