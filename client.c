#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int error(char*);
void my_listen(int);

int main(int argc, char* argv[]) {
    if (argc < 3)
        error("Not enough arguments...");
    else if (argc > 3)
        error("Too much arguments...");

    int socketfd, port;
    struct sockaddr_in server;
    char* ip_addr;

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        error("Failed to open socket...");

    port = atoi(argv[2]);
    ip_addr = argv[1];
    if (strcmp(ip_addr, "localhost") == 0)
        strcpy(ip_addr, "127.0.0.1");

    bzero(&server, sizeof(server));
    server.sin_addr.s_addr = inet_addr(ip_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(socketfd, (struct sockaddr*)&server, sizeof(server)) != 0)
        error("Failed to connect with server...");
    else
        printf("Connection with server established!\n");

    my_listen(socketfd);

    printf("Closing socket...Bye\n");
    close(socketfd);
    return 0;
}

int error(char* msg) {
    perror(msg);
    return -1;
}

void my_listen(int socketfd) {
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, stdin)) != -1) {
        write(socketfd, line, nread);
        sleep(1);
    }
    free(line);
}