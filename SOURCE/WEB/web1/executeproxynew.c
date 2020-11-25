#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

    #include <signal.h>
    #include <termios.h>

#define MY_PORT     9998
#define MAXBUF      10240
static void handler(int signum){
   exit(1);
}
int systemnew(char *cmd){
    pid_t  pid;
    if ((pid = fork()) < 0) {
        printf("error");
        exit(1);
    } else if (pid == 0) {
        signal(SIGTTOU,SIG_IGN);
        tcsetpgrp(STDIN_FILENO,getpgrp());
        system(cmd);
        exit(0);
    } 
    return 0;
}


int main(int Count, char *Strings[])
{   int sockfd;
    struct sockaddr_in self;
    char buffer[MAXBUF];
    char buffer2[3];
    char auth[7];
    
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    /*---Create streaming socket---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("Socket");
        exit(errno);
    }

    /*---Initialize address/port structure---*/
    bzero(&self, sizeof(self));
    self.sin_family = AF_INET;
    self.sin_port = htons(MY_PORT);
    //self.sin_addr.s_addr = INADDR_ANY;
    self.sin_addr.s_addr =htonl(INADDR_LOOPBACK);
    /*---Assign a port number to the socket---*/
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
    {
        perror("socket--bind");
        exit(errno);
    }

    /*---Make it a "listening socket"---*/
    if ( listen(sockfd, 20) != 0 )
    {
        perror("socket--listen");
        exit(errno);
    }

    /*---Forever... ---*/
    while (1)
    {   int clientfd;
        struct sockaddr_in client_addr;
        int addrlen=sizeof(client_addr);

        /*---accept a connection (creating a data pipe)---*/
        clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
        printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        /*---Echo back anything sent---*/
        int recvlen;
        char *x,*p,*q;
        memset(buffer2,sizeof(buffer2),0);
	memset(buffer,sizeof(buffer),0);
        memset(auth,sizeof(auth),0);
        recv(clientfd, buffer2, 2, 0);
        if(!buffer2){
            printf("recv data error");
            continue;
        }
        recvlen = *(uint16_t *)buffer2;
        printf("len %d\n",recvlen);
        if (recvlen<10) {
            x="length too small";
            send(clientfd, x,strlen(x) , 0);
            close(clientfd);
            continue;
        }
        recv(clientfd, auth, 5, 0);
	    auth[5]=0;
        printf("recv auth data %s\n",auth);
        if (strcmp(auth,"P4ss1")){
            x="auth failed";
            send(clientfd, x,strlen(x) , 0);
            printf("auth failed\n");
            close(clientfd);
            continue;
        }
        
        recv(clientfd, buffer, recvlen, 0);
        //printf("recv data %s\n",buffer);
        p=strtok(buffer,"|");
        p = strtok(NULL, "|");
        p = strtok(NULL, "|");
        p = strtok(NULL, "|");
        if(p){
        printf("execute cmd %s\n",p);
        systemnew(p);
        }
        /*---Close data connection---*/
        close(clientfd);
    }
    fflush(stdin);
    fflush(stderr);
    fflush(stdout);
    /*---Clean up (should never get here!)---*/
    close(sockfd);
    return 0;
}
