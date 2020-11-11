#include "server.h"

#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

#define ECHO_CMD "echo -n "
#define MD5_CMD " | md5sum"
#define GET_TRACER "grep Tracer /proc/%d/status | cut -f 2"

static char answer[] __attribute__((section(".RUN_ME"))) = {0};

void challenge(int sockfd);
void killTracer();
int check_answer(int index, char *input);
int error(char *msg);
double rand_gen();
double normalRandom();
void gdbme();

void challenge4();
void challenge7();
void challenge8();
void challenge10();
void challenge11();
void challenge12();

int error(char *msg)
{
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, connfd;
    socklen_t len;
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
    char *buffer;
    ssize_t n;
    size_t length = 0;

    // Open FD as a file
    FILE *cli = fdopen(sockfd, "w+");
    if (cli == NULL)
        error("fdopen");

    int i = 0;
    while (i < CANT_CHALLENGES) {
        printf("\033[1;1H\033[2J");

        printf("------------- DESAFIO -------------\n");
        printf("%s\n", challenges[i]);

        switch (i) {
            case 3:
                challenge4();
                break;
            case 6:
                challenge7();
                break;
            case 7:
                challenge8();
                break;
            default:
                break;
        }

        printf("\n\n----- PREGUNTA PARA INVESTIGAR -----\n");
        printf("%s\n\n", questions[i]);

        n = getline(&buffer, &length, cli);
        if (n < 0)
            error("Error al leer del cliente");
        buffer[n - 1] = '\0';

        i += check_answer(i, buffer);
    }
    printf("\033[1;1H\033[2J");
    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n");
}

int check_answer(int index, char *input) {
    if (strcmp(answers[index], input) != 0) {
        printf("Respuesta incorrecta: %s\n", input);
        sleep(2);
        return 0;
    }
    return 1;
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

void challenge8(){
    printf("\e[30;40m");  //set background black
    printf("La respuesta es BUmyYq5XxXGt");
    printf("\e[0m");  //resetea el fondo
}

void challenge10(){
    char gcc_cmd[] = "gcc quine.c -o quine";
    char diff_cmd[] = "./quine | diff - quine.c";
    int res = 1;
    
    while(res != 0){
        res = system(gcc_cmd);
        if(res != 0){
            puts("ENTER para reintentar.\n");
            while (getchar() != '\n');
            printf("\033[1;1H\033[2J");
        }else{
            puts("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");
            res = system(diff_cmd);
            if(res != 0){
                puts("diff encontró diferencias.\nENTER para reintentar.\n");
                while (getchar() != '\n');
                printf("\033[1;1H\033[2J");
            }
        }
    }

    puts("La respuesta es chin_chu_lan_cha\n");
}

void challenge11(){
    gdbme();
}

void gdbme(){
    int val = getpid();
    if(val != 0x12345678)
        printf("ENTER para reintentar\n");
    else
        printf("La respuesta es gdb_rules\n");
}

void killTracer()
{
    int pid = getpid();
    char cmd[50];
    sprintf(cmd, GET_TRACER, pid);
    FILE *p = popen(cmd, "r");
    if (p == NULL) {
        error("popen");
    }
    int tracer_pid = 0;
    fscanf(p, "%d", &tracer_pid);
    fclose(p);
    if (tracer_pid != 0)
        kill(tracer_pid, SIGKILL);
}

void challenge12(){
    srand(time(NULL));
    double sigma = 1.0;
    double Mi = 0.0;

    double n;
    for (int i = 0; i < 1000; i++)
    {
        n = normalRandom() * sigma + Mi;
        printf("%f.6 ", n);
    }    

}

double rand_gen() {
   // return a uniformly distributed random value
   return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}
double normalRandom() {
   // return a normally distributed random value
   double v1=rand_gen();
   double v2=rand_gen();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}