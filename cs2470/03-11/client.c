#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 1024

int
main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket failed");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) < 0) {
        perror("Invalid addr");
        exit(1);
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        exit(1);
    }

    const char* msg = "GET / HTTP/1.0\r\n\r\n";
    if (send(sock, msg, strlen(msg), 0) < 0) {
        perror("Send failed");
        exit(1);
    }

    char buffer[MAX_BUFFER] = { 0 };
    while (1) {
        int bytes_recvd = recv(sock, buffer, MAX_BUFFER - 1, 0);
        if (bytes_recvd < 0) {
            perror("Recv failed.");
            break;
        }
        else if (bytes_recvd == 0) {
            printf("\nServer closed connection.\n");
            break;
        }
        else {
            buffer[bytes_recvd] = 0;
            printf("%s", buffer);
        }
    }
    printf("\n");

    close(sock);
    return 0;
}
