#include "server.h"

#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

#define ECHO_CMD "echo -n "
#define MD5_CMD " | md5sum"
#define GET_TRACER "grep Tracer /proc/%d/status | cut -f 2"

static char answer[] __attribute__((section(".RUN_ME"))) = {0};

void challenge(int sockfd);
void killTracer();
void check_answer(int *index, char *hashed_answer, char *unhashed_answer);

int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");

    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    } else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    challenge(connfd);

    // After chatting close the socket
    close(sockfd);

    return 0;
}

// Function designed for chat between client and server.
void challenge(int sockfd) {
    char buffer[MAX];
    ssize_t n;
    size_t length = 0;
    bzero(buffer, MAX);

    // Open FD as a file
    FILE *cli = fdopen(sockfd, "w+");
    if (cli == NULL)
        perror("fdopen");

    int i;
    for (i = 0; i < CANT_CHALLENGES; i++) {
        printf("\033[1;1H\033[2J");
        sleep(2);
        printf("------------- DESAFIO -------------\n");
        printf("%s\n", challenges[i]);

        switch (i) {
            case 3:
                challenge4();
                break;
            case 6:
                challenge7();
                break;
            default:
                break;
        }

        printf("\n\n----- PREGUNTA PARA INVESTIGAR -----\n");
        printf("%s\n\n", questions[i]);

        n = getline(&buffer, &length, cli);
        if (n < 0)
            perror("Error al leer del cliente");
        strcat(buffer, "\0");

        char command[100] = ECHO_CMD;
        strcat(command, buffer);
        strcat(command, MD5_CMD);

        FILE *cmd_file = popen(command, "r");
        if (cmd_file == NULL)
            perror("popen");

        char encripted_msg[100] = {0};

        if (fgets(encripted_msg, 100, cmd_file) == NULL)
            perror("fgets");

        if (pclose(cmd_file) < 0)
            perror("pclose");

        check_answer(&i, encripted_msg, buffer);
    }
    printf("\033[1;1H\033[2J");
    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n");
}

void check_answer(int *index, char *hashed_answer, char *unhashed_answer) {
    if (strcmp(answers[*index], hashed_answer) != 0) {
        *index--;
        printf("Respuesta incorrecta: %s", unhashed_answer);
    }
}

void challenge4() {
    int res = write(13, "La respuesta es fk3wfLCm3QvS\n\0\0\0", 32);
    if (res == -1) {
        perror("write");
    }
}

void challenge7() {
    killTracer();
    srand(time(NULL));

    int i, j = 0;
    char ans[] = "La respuesta es K5n2UFfpFMUN\n";
    char aux[] = "0";
    int ret, length = strlen(ans);

    for (i = 0; i < length * 10; i++) {
        if (i % 10 == 0) {
            aux[0] = ans[j++];
            ret = write(STDOUT_FILENO, aux, sizeof(aux));
            if (ret < 0)
                perror("write");
        } else {
            aux[0] = rand() % 95 + 32;
            ret = write(STDERR_FILENO, aux, sizeof(aux));
            if (ret < 0)
                perror("write");
        }
    }
}

void killTracer() {
    int pid = getpid();
    char cmd[50];
    sprintf(cmd, GET_TRACER, pid);
    FILE *p = popen(cmd, "r");
    if (p == NULL) {
        perror("popen");
        exit(1);
    }
    int tracer_pid = 0;
    fscanf(p, "%d", &tracer_pid);
    fclose(p);
    if (tracer_pid != 0)
        kill(tracer_pid, SIGKILL);
}