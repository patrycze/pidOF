#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
int j,i,k=0;
struct stat sb;
ssize_t r, bufsiz;
char *linkname;
int b,c;
char *line;
int length = strlen(argv[1])+1;
line = malloc(length);
char *toComm;
char *dirname2;
const char *comm = "comm";
char *dirname = "../../../../../proc/";
int a = strlen(dirname);
DIR *dirp, *dirp2;
struct dirent *dp, *dp2;
if ((dirp = opendir(dirname)) == NULL) {
	perror("couldn't open 'proc'");
        return 0;
    }

do {
int errno = 0;
        if ((dp = readdir(dirp)) != NULL) {
        	//if (strcmp(dp->d_name, argv[1]) == 0) {
			b = strlen(dp->d_name);
			dirname2 = malloc(a+b+1);
			strcpy(dirname2,dirname);
			strcat(dirname2,dp->d_name);
			//printf("%s\n", dirname2);
			if((dirp2 = opendir(dirname2)) == NULL)
			{
				//perror("couldn't open ");
				//printf("%s\n",dp->d_name);
				continue;
			}
			do {
				if((dp2 = readdir(dirp2)) != NULL) {
					if(strcmp(dp2->d_name, comm) == 0)
					{
						FILE *f;
						line = malloc(50);
						c = strlen(dp2->d_name);
						toComm = malloc(a+b+c+1);
						strcpy(toComm,dirname2);
						strcat(toComm,"/");
						strcat(toComm,dp2->d_name);
						f = fopen(toComm,"r");
						fgets(line,length,f);
						//printf("%s\n", toComm);
						if(strcmp(line,argv[1]) == 0)
						{
							bufsiz = sb.st_size + 1;
							if (sb.st_size == 0)
               							bufsiz = PATH_MAX;

							linkname = malloc(bufsiz);
	
							if (linkname == NULL) {
            							perror("malloc");
               							exit(EXIT_FAILURE);
           						}

							r = readlink(line,linkname, bufsiz);
							//if (r == -1) {
            						//	perror("readlink");
               						//	exit(EXIT_FAILURE);
           						//}
							strcat(linkname,"\0");
							if(strlen(linkname)>0)
            						{
                                				printf("Sending SIGINT to %s \n",dp2->d_name);
                                				kill(atoi(dp2->d_name),SIGINT);
           						}
							else
							{
								printf("%s \n",line);
								printf("%s \n", dp->d_name);
							}
						} 
					} 
				} 
			}while(dp2 != NULL);

			//} while(dp2 != NULL);
         		//printf("found %s\n", dp->d_name);
	      	//}	//closedir(dirp);
	 }
} while(dp != NULL);



return 0;
}
