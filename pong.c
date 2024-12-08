#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 16

int main() {
    int sockfd;
    struct sockaddr_in myaddr, cliaddr;
    char buffer[BUFFER_SIZE];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&myaddr, 0, sizeof(myaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        socklen_t len = sizeof(cliaddr);
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "PING") == 0) {
            strcpy(buffer, "PONG");
            sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
            printf("PONG sent\n");
        }
    }

    close(sockfd);

    return 0;
}
