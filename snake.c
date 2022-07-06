#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include<windows.h>
#define height 30
#define width 30
int X,Y,fruitX,fruitY,score,gameover,flag;
int tailX[100],tailY[100],CountTail=0;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void setup()
{
	X=width/2;
	Y=height/2;
	label1:
		fruitX=rand()%30;
		if(fruitX==0)
			goto label1;
	label2:
		fruitY=rand()%30;
		if(fruitY==0)
			goto label2;
	score=0;
	gameover=0;  // if game gets over then gameover will be 1
}
void draw()
{
	int i,j,k;
	system("cls"); //to refresh the screen,function of stdlib.h
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(i==0 || i==height-1 || j==0 || j==width-1)
				printf("#");
			else
			{
				if(i==X && j==Y)
					printf("O");
				else if(i==fruitX && j==fruitY)
					printf("F");
				else
				{
					int si=0;  //si=snake increament
					for(k=0;k<CountTail;k++)
					{
						if(i==tailX[k] && j==tailY[k])
						{
							printf("o");
							si=1;
						}
					}
					if(si==0)
						printf(" ");
				}
			}
		}
		printf("\n");
	}
}
void input()
{
	char ch;
	if(kbhit())
	{
		ch=getch();
		switch(ch)
		{
			case 'a': flag=1;
					  break;
			case 's': flag=2;
					  break;
			case 'w': flag=3;
					  break;
			case 'd': flag=4;
					  break;
			case 'x': gameover=1;
					  break;
		}
	}
}
void makeLogic()
{
	int i;
	usleep(1000); //sleep(5) takes 5sec pause and usleep(5000000) takes 5sec pause. usleep accepts argument in microsecond
	int prevX = tailX [0];
	int prevY = tailY [0];
	int prev2X, prev2Y;
	tailX[0] = X;
	tailY[0] = Y;
	for(i = 1;i < CountTail ; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch(flag)
	{
		case 1: Y--;
				break;
		case 2: X++;
				break;
		case 3: X--;
				break;
		case 4: Y++;
				break;
		default: break;
	}
	if(X<0 || X>width || Y<0 || Y>height)
		gameover=1;
	for(i=0;i<CountTail;i++)    // check if snake head(X,Y) touching tail portion or not
	{
		if(X==tailX[i] && Y==tailY[i])
			gameover=1;
	}
	if(X==fruitX && Y==fruitY)
	{
		label3:
		fruitX=rand()%30;
		if(fruitX==0 || fruitX==29)
			goto label3;
		label4:
		fruitY=rand()%30;
		if(fruitY==0 || fruitY==29)
			goto label4;
		score+=1;
		CountTail++;
	}
}
void hard()
{
    setup();
	while(!gameover)
	{
		draw();
		input();
		makeLogic();
		sleep(0.99999);
		printf("\nSCORE: %d",score);
	}
}
void easy()
{
    setup();
	while(!gameover)
	{
		draw();
		input();
		makeLogic();
		sleep(1);
		printf("\nSCORE: %d",score);
	}
}
int main()
{
	int  c,d;

	  printf("==============================================\n");
        printf("Press 1 for easy mode\n");
        printf("Press 2 for hard mode\n");
        printf("Which mode you want to play please enter:\n");
        scanf("%d",&d);
        switch(d)
        {
        case 1:
            easy();
            break;
        case 2:
            hard();
            break;
        }


	  printf("==============================================\n");
       do{
            printf("Press 1 for continue again\n");
            printf("Press 2 for exit\n");
		     scanf("%d",&c);
        switch(c)
        {
            case 1:
            main();
            break;
        case 2:
            exit(0);
		}
        }while(1);
	return 0;
}