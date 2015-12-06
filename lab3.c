#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *visiter1Func();// 1ый посититель
void *visiter2Func();// 2ой посититель
void *visiter3Func();// 3ий посититель
void *ownerFunc();// владелец

int nbotle_refr = 10; //колличество бутылок в холодильнике
int visit[3][2]; //состояния поситителей + коллличество выпитых им бутылок
bool ownerdo=0; //состояние владельца
int i;  

pthread_mutex_t refr; 
pthread_t vis1,vis2,vis3, owner;	

int main()
{
	initscr();
	printw("\n");
	pthread_create(&owner, NULL, ownerFunc, NULL);	
        pthread_create(&vis1, NULL, visiter1Func, NULL);
	pthread_create(&vis2, NULL, visiter2Func, NULL);
	pthread_create(&vis3, NULL, visiter3Func, NULL); 
	
	visit[1][2]=0; //количество выпитых буьылок 0
	visit[2][2]=0;
	visit[3][2]=0;
       
	//цикл печати информации о состоянии
	while(1)
	{
		

		for(i=1; i<=3; i++)
		{
			printw("\n");
			//печать имени посетителя
			if(i==1) printw("	Homer Simpson ");
			if(i==2) printw("	Fred Flintston ");
			if(i==3) printw("	Barney Rubble ");

			//печать состояния
			printw("drank %d bottles. Now he ", visit[i][2]);
			if(visit[i][1]==1) printw("stands in line to refrigerator.");
			if(visit[i][1]==2) printw("takes a bottle of beer.");
			if(visit[i][1]==3) printw("drinks beer.");
			if(visit[i][1]==4) printw("sleeps.");
			
			printw("\n\n\n");
				
		}
		if(ownerdo==1)   printw("	Owner finds the bottle and puts 5 new bottle\n	*Visitor can not use the fridge\n\n");
		if(ownerdo==0)   printw("	Owner reads a book\n\n");
		printw("        Bottles in the fridge = %d\n", nbotle_refr );		
		refresh();		
		napms(1000);
		clear();
		if(nbotle_refr==0) { printw("The bear ran out. GAME OVER"); refresh();  napms(60000); endwin();}
		
	}
	return 0;
}
	


void *ownerFunc()
{
	pthread_mutex_init(&refr, NULL);
	srand(time(NULL));//инициализация ф-ии rand значением ф-ии time 
	//цикл функционирования хозяина	
	while(1)
	{
		//с веротяностью 1/25 владелец зайдет, посчитает бутылки и добавит 3 новых 
		if(rand()%25 +1 == 1) 
		{
			ownerdo=1;//владелец открыл холодильник и снял все lock
			pthread_mutex_init(&refr, NULL);
			pthread_mutex_lock(&refr);
			napms(30000); 
			pthread_mutex_unlock(&refr);
			nbotle_refr+=3;	
			ownerdo=0;//занимается своими делами
		}
		napms(1000);	
	}
}


void *visiter1Func()
{
	//цикл функционирования 1ого поситителя
	while(1)
	{
		visit[1][1]=1;//посититель встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		visit[1][1]=2;//посититель берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца то закрывает mutex
		if(ownerdo==0)
		pthread_mutex_unlock(&refr);  
		
		
		visit[1][1]=3;//пьет пиво 20 секунд
		napms(20000);
 		nbotle_refr--;
		visit[1][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(visit[1][2]==10) {visit[1][1]=4; napms(120000);} //если выпито 10 бутылок спит 120 секунд
	}
}

void *visiter2Func()
{
	//цикл функционирования 2ого поситителя
	while(1)
	{
		visit[2][1]=1;//посититель встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		visit[2][1]=2;//посититель берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца то закрывает mutex
		if(ownerdo==0)
		pthread_mutex_unlock(&refr);  
		
		
		visit[2][1]=3;//пьет пиво 20 секунд
		napms(20000); 
                nbotle_refr--;
		visit[2][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(visit[2][2]==10) {visit[2][1]=4; napms(120000);} //если выпито 10 бутылок спит 120 секунд
	}
}

void *visiter3Func()
{
	//цикл функционирования 3ого поситителя
	while(1)
	{
		visit[3][1]=1;//посититель встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		visit[3][1]=2;//посититель берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца то закрывает mutex
		if(ownerdo==0)
		pthread_mutex_unlock(&refr);  
		
		
		visit[3][1]=3;//пьет пиво 20 секунд
		napms(20000);
		nbotle_refr--; 
		visit[3][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(visit[3][2]==10) {visit[3][1]=4; napms(120000);} //если выпито 10 бутылок спит 120 секунд
	}
}
