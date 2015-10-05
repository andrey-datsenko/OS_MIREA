#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

main()
{
	
	pid_t pid;
	switch(pid=fork())
	{
		case -1:exit(1);
		case 0: {
			char name[20]; 
			FILE *CHILD; 
			sprintf(name, "file_%d.txt", getppid());
			CHILD=fopen(name, "w"); 
			fprintf(CHILD, "%d %d", getppid(), getpid());
			fclose(CHILD);
			exit(2);}
		default: {
			 char name2[20];
			 FILE *PARENTS;
			 sprintf(name2, "file_%d.txt", pid);
			 PARENTS=fopen(name2, "w"); 
			 fprintf(PARENTS, "%d" , getpid());
			 fclose(PARENTS);
			 wait();
			 printf("\nGood\n\n");}
	}
}
