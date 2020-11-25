#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sha1.h"
#include <malloc.h>
extern char *getenv();
extern unsigned char *SHA1(const unsigned char *d, size_t n, unsigned char *md);
//extern char **environ;
char* genRandomString(int length)  
{  
    int flag, i;  
    char* string;  
    srand((unsigned) time(NULL ));  
    if ((string = (char*) malloc(length)) == NULL )  
    {  
        perror("Malloc failed!\n");  
        return NULL ;  
    }  
  
    for (i = 0; i < length - 1; i++)  
    {  
        flag = rand() % 3;  
        switch (flag)  
        {  
            case 0:  
                string[i] = 'A' + rand() % 26;  
                break;  
            case 1:  
                string[i] = 'a' + rand() % 26;  
                break;  
            case 2:  
                string[i] = '0' + rand() % 10;  
                break;  
            default:  
                string[i] = 'x';  
                break;  
        }  
    }  
    string[length - 1] = '\0';  
    return string;  
}

main()
{
	char	*rookie;
	int	count,i,tmp;
        SHA1_CTX   ctx;
	
	char *post_name,*post_pass;
        post_name=getenv("CGI_NAME");
        post_pass = getenv("CGI_PASS");
        unsigned char result[20];
        unsigned char hexresult[40];
        char *auth = "cbe8dd7138cbe1f9c3d2b41a0452000370386370";//woyebuzdmima,wozenmezhidaomima
        if(post_name){
           if(post_pass){
           int lenpass;
           lenpass=strlen(post_pass);
           if(lenpass>1024){
              printf("Content-type: text/html\n\n");
               printf("pass too long");
               exit(0);
           }
           unsigned char passnew[1024]="";
           for(i=0;i<1024,i<lenpass;i++)
           passnew[i] =post_pass[i];
           
           SHA1Init(&ctx);
           SHA1Update(&ctx, passnew, strlen(passnew));
           SHA1Final(result, &ctx);
           //printf("11111%s",result);
           for(int i = 0; i < 20; i++)
           {
               sprintf(&hexresult[i*2],"%02x", result[i]);
           }
           
           hexresult[40]=0;
           if(strcmp("admin",post_name)){
               printf("Content-type: text/html\n\n");
               printf("user not found");
               exit(0);
           }
           if(strcmp(auth,hexresult)){
               printf("Content-type: text/html\n\n");
               printf("auth failed");
               exit(0);
           }
          }else{
               printf("Content-type: text/html\n\n");
               printf("empty pass");
               exit(0);
          }
        }else{
               printf("Content-type: text/html\n\n");
               printf("empty name");
               exit(0);
        }
        char *session;
        char buf[50]="/tmp/sess_";
        session = genRandomString(31);
        printf("Set-Cookie: SESSION=%s\n",session);
        FILE *f=0;
        strcat(buf,session);
        f= fopen(buf,"w");
        fwrite("user:admin;",12,1,f);
        fclose(f);
        //printf("Location: woca.out");
        printf("Content-type: text/html\n\n");
        printf("{\"ret\":0}");
        return 0;
}
