
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10012
#define BUF_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server;
    char buffer[BUF_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Prepare server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    // server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  //ip a 
    inet_pton(AF_INET, "192.168.1.1", &server.sin_addr);

    // Connect to server
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    while (1)
    {
        printf("Enter message: ");

        fgets(buffer, BUF_SIZE, stdin);

        // Send message to server
        send(sock, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUF_SIZE);

        // Receive response from server
        read(sock, buffer, BUF_SIZE);

        printf("Echo from server: %s", buffer);
    }

    close(sock);

    return 0;
}
