#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "util.h"


int main(int argc, char *argv[])
{
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    //char buffer[500];
    char *buffer = malloc(500 * sizeof(char));

    const int PORT = 26200;

    if (argc < 3) {
        fprintf(stderr,"Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);

    /*
     * Step 1 Create socket.
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");

    /* gethostbyname() takes host domain name and resolves it to an address */
    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    /* 0 out the server address stuct and set members */
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)server->h_addr_list, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    const char *space = " ";
    //char *wordToken;
    char *wordToken = malloc(500 * sizeof(char));
    int count = 0;

    for (;;)
    {
        //int length;
        printf("Enter next command> ");
        fgets(buffer, 500, stdin);
        //length = strlen(buffer);
        char buffSave[500];
        strcpy(buffSave, buffer);
        //printf("buffer is %s \n", buffer);

        wordToken = strtok(buffer, space);
        //printf("buffer is %s - %s\n", buffSave, wordToken);
        //printf("wordtoken starts at -> %s ", wordToken);
        writen(sockfd, wordToken, 500 * sizeof(char));
        //wordToken = strtok(NULL, space);
        //printf("next 1-> %s \n", wordToken);
        if (strcmp(wordToken, "get") == 0)
        {
            wordToken = strtok(NULL, space);
            writen(sockfd, wordToken, 500 * sizeof(char));

            readn(sockfd, buffer, 50 * sizeof(char));
            count = atoi(buffer);

            //printf("count is -> %d\n", count);

            readn(sockfd, buffSave, 500 * sizeof(char));
            printf("%s\n", buffSave);

            readn(sockfd, buffSave, 500 * sizeof(char));
            printf("%s\n", buffSave);

            //printf("before for loop\n");

            for (int i = 0; i < (count + 1); i++)
            {
                readn(sockfd, buffSave, 500 * sizeof(char));
                printf("%s\n", buffSave);
            }

            //printf("after for loop\n");

            //readn(sockfd, buffSave, 500 * sizeof(char));
            //printf("%s\n", buffSave);

        }
        else if (strcmp(wordToken, "put") == 0)
        {
            wordToken = strtok(NULL, space);
            writen(sockfd, wordToken, 500 * sizeof(char));
        }
        else if (strcmp(wordToken, "delete") == 0)
        {
            wordToken = strtok(NULL, space);
            writen(sockfd, wordToken, 500 * sizeof(char));
        }
        else if (strcmp(wordToken, "save\n") == 0)
        {
            printf("save is here\n");
            break;
        }
        

    }




}