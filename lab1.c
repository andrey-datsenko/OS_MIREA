#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	switch(pid=fork())
	{
		case -1:exit(1);
		case 0: {
			printf("CHILD:   Я дочерний процесс. PID =%d\n", getpid());
			char name[20]; 
			FILE *CHILD; 
			sprintf(name, "file_%d.txt", getpid());
			CHILD=fopen(name, "w"); 
			fprintf(CHILD, "%d %d", getppid(), getpid());
			fclose(CHILD);
			printf("CHILD:   Я создал файл 'file_%d.txt' и записал в него PID и PPID\n\n", getpid());
			exit(2);}
		default: {
			 printf("PARENTS: Я родительский процесс. PID =%d, CHILD PID=%d\n", getpid(), pid);
			 char name2[20];
			 FILE *PARENTS;
			 sprintf(name2, "file_%d.txt", getpid());
			 PARENTS=fopen(name2, "w"); 
			 fprintf(PARENTS, "%d" , getpid());
			 fclose(PARENTS);
			
			 printf("PARENTS: Я создал файл 'file_%d.txt' и записал в него PID\n", getpid());
			 printf("PARENTS: Жду завершения потомка\n");
			 wait(NULL);
			 printf("\nВсе good\n");}
	}
	return 0;
}
