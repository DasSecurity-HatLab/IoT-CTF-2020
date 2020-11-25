#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

extern char *getenv();

char *memstr(char *haystack, char *needle, int size)
{
	char *p;
	char needlesize = strlen(needle);

	for (p = haystack; p <= (haystack-needlesize+size); p++)
	{
		if (memcmp(p, needle, needlesize) == 0)
			return p; /* found */
	}
	return NULL;
}
int readflag(){
    FILE *f=0;
    char buf[1024]="";
    f= fopen("/flag","r");
    fread(buf,1024,1,f);
    fclose(f);
    printf("Content-type: text/html\n\n");
    printf("%s",buf);
    return 0;
}

main()
{
	char	*cookie;
	char  *p;
  char  *p2;
  int   len;
  char  *session;
  cookie = getenv("HTTP_COOKIE");
  //printf("%s",cookie);
  if(cookie){
      p=strstr(cookie,"SESSION=");
      if(p){
          
          session=p+8;
          session[30]=0;
          //printf("Content-type: text/html\n\n");
          //printf("%s",session);
          FILE *f=0;
          char buf[50]="/tmp/sess_";
          char buf2[1024]="";
          strcat(buf,session);
          //printf("%s",buf);
          f= fopen(buf,"rb");
          if (f){
              fread(buf2,1024,1,f);
              fclose(f);
              //printf("%s",buf2);
              p=0;
              p=memchr(buf2,58,1024);//:  
              //printf("%s",p);
              //exit(0);
              if(p){
                 p2=memchr(p+1,59,1024);//;
                 //printf("%s",p2);
                 if(p2){
                    char* user=0;
                    user=p+1;
                    user[p2-p-1]=0;
                    //printf("%s",user);
                    if(!strcmp(user,"admin")){
                       readflag();
                       return 0;
                    }
                    
                 }
              }
          }
          
          
      }
  }
  printf("Content-type: text/html\n\n");
  printf("{\"ret\":-1,\"auth first\"}");
  return 0;
}
