# TCP Client Server Program

## Server Program `(server.c)`

At first setting up the IP Address and Port for the Server

```c
char *ip = "127.0.0.1"; 
int port = 5566; 
```

### IP Address: `127.0.0.1`

* **Loopback Address:** `127.0.0.1` is a special-purpose IPv4 address known as the loopback address. It is used to establish an IP connection to the same machine or computer being used by the end-user.
* **Local Testing:** This address is commonly used for local testing and development because it does not require a network connection. Any data sent to `127.0.0.1` is looped back to the local machine, allowing developers to test network applications without needing an external network.

### Port Number: `5566`

A port number is a 16-bit number (ranging from 0 to 65535) used by TCP and UDP protocols to distinguish different services or applications running on the same machine. You can choose any port number except the reserved port number (Like `port 80` is for HTTP etc.)
