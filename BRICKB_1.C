#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<process.h>
#include<stdlib.h>

char grid[50][120],name[20],lifechar=3;
int m=20,n=41,paddlesize=11,paddlestart=15,start=0,i,lag=100,life=3;
int x1,y1,x2,y2,xdiff=1,ydiff=1;
char ball=4,upwall=220,ltwall=221,rtwall=222,dnwall=223,brick=219,brick2=177,brick3=176;
int diffc,gamestart=0,scoreb1=250,scoreb2=500,scoreb3=1000,lscore=2000;
float score=0;

struct hscore
 {
  char name[20];
  float score;
 }htemp,t,h[20];

 void highscores()
 {
  int i=0;
  FILE *fp;
  fp=fopen("high.DAT","rb");
  if(fp==NULL)
   {
    puts("Cannot open file!");
    exit(1);
   }
  clrscr();
  printf("\n\n\n\t\t\t\tHIGH SCORES\n\n");
  while((fread(&htemp,sizeof(htemp),1,fp)==1)&&i<10)
   {
    printf("\n\t\t\t%d. %s : %0.0f",i+1,htemp.name,htemp.score);
    i++;
   }
  fclose(fp);
  getch();
 }

void modhscore()
{
 int i=0,j,k,m;
 FILE *fp,*ft;
  fp=fopen("high.DAT","rb");
  ft=fopen("temp.DAT","wb");
  if(fp==NULL)
   {
    puts("Cannot open file!");
    exit(1);
   }
  if(ft==NULL)
   {
    puts("Cannot open file!");
    exit(1);
   }
    for(m=0;m<20;m++)
    {
     h[m].score=0;
     strcpy(h[m].name,"                    ");
    }
   while(fread(&htemp,sizeof(htemp),1,fp)==1)
    {
     h[i]=htemp;
     i++;
    }
    h[11].score=score;
    strcpy(h[11].name,name);
    for(j=0;j<20;j++)
    for(k=j+1;k<20;k++)
    if(h[j].score<h[k].score)
    {
     t=h[j];
     h[j]=h[k];
     h[k]=t;
    }
    i=0;
    while(i<20)
     {
      fwrite(&h[i],sizeof(h[i]),1,ft);
      i++;
     }
  fclose(fp);
  fclose(ft);
  remove("high.DAT");
  rename("temp.DAT","high.DAT");
}


void instructions()
{
	char cont;
	clrscr();
	printf("\n\nCONTROLS\n\n");
	printf("A- Move paddle left\n");
	printf("D- Move paddle right\n\n\n");
	printf("OBJECTIVES\n\n");
	printf("1.Make sure the ball doesn't hit the ground.\n");
	printf("2.You have 3 lives.\n");
	printf("3.There are 3 difficulties- Easy, Medium and Hard.\n");
	printf("4.The game will stop if all the brick finshes or all the lives are lost.\n\n\n");
	printf("SCORING SYSTEM\n\n");
	printf("125/250/500: Hit a brick once \n");
	printf("250/500/1000: Hit a brick twice\n");
	printf("500/1000/2000: Completely destroy a brick\n");
	printf("\n\n\t\t\tPress y to continue.");
    while(1)
    {
    cont=getch();
    if(cont=='y'||cont=='Y')
     break;
    }

}


void intro()
{
  char cont;
  clrscr();
  printf("\n\n\n\n");
  printf("\t\t ____    _____    _____    _____   _  __    \n  "  );delay(200);
  printf("\t\t|  _ \\  |  __ \\  |_   _|  / ____| | |/ / \n "  );delay(200);
  printf("\t\t| |_) | | |__) |   | |   | |      | ' /    \n "  );delay(200);
  printf("\t\t|  _ <  |  _  /    | |   | |      |  <     \n "  );delay(200);
  printf("\t\t| |_) | | | \\ \\   _| |_  | |____  | . \\ \n "  );delay(200);
  printf("\t\t|____/  |_|  \\_\\ |_____|  \\_____| |_|\\_\\ \n ");delay(200);
  printf("\t ____    _____    ______              _  __  ______   _____ \n");delay(200);
  printf("\t|  _ \\  |  __ \\\  |  ____|     /\\     | |/ / |  ____| |  __ \\ \n");delay(200);
  printf("\t| |_) | | |__) | | |__       /  \\    | ' /  | |__    | |__) |\n" );delay(200);
  printf("\t|  _ <  |  _  /  |  __|     / /\\ \\   |  <   |  __|   |  _  /\n");delay(200);
  printf("\t| |_) | | | \\ \\  | |____   / ____ \\  | . \\  | |____  | | \\ \\ \n");delay(200);
  printf("\t|____/  |_|  \\_\\ |______| /_/    \\_\\ |_|\\_\\ |______| |_|  \\_\\ \n");delay(200);
  printf("\n\n\t\t\tPress y to continue.");
  while(1)
  {
   cont=getch();
   if(cont=='y'||cont=='Y')
    break;
  }
 }

void paddleleft()
 {
    if((paddlestart-1)==0)
     return;

    if(start==0)
     {
      grid[x1][y1]=' ';
      y1--;
      grid[x1][y1]=ball;
     }

	grid[m-3][paddlestart-1]=223;
	grid[m-3][paddlestart+paddlesize-1]=' ';
	paddlestart--;


 }

void paddleright()
 {
       if((paddlestart+paddlesize)==(n-1))
     return;

       if(start==0)
	{
	  grid[x1][y1]=' ';
	  y1++;
	  grid[x1][y1]=ball;
	}


	grid[m-3][paddlestart]=' ';
	grid[m-3][paddlestart+paddlesize]=223;
	paddlestart++;


 }

void printgrid()
 {
	int i,j;
	for(i=0;i<m;i++)
	 {
		printf("\n\t\t");
		for(j=0;j<n;j++)
		 {
			printf("%c",grid[i][j]);
		 }
	 }
	printf("\n\t\tScore:%0.0f\n\t\tLives:",score);
	for(i=0;i<life;i++)
	 {
	  printf("%c",lifechar);
	 }
 }

void reset()
 {
  start=0;
  paddlestart=15;
  paddlesize=11;

  for(i=1;i<n-1;i++)
     {
	grid[m-3][i]=' ';
     }

  for(i=0;i<paddlesize;i++)
     {
	grid[m-3][paddlestart+i]=223;
     }

  xdiff=1;
  ydiff=1;
  x1=m-4;
  y1=paddlestart+(paddlesize/2);
  grid[x1][y1]=ball;
 }

void difficulty()
 {
  clrscr();
  printf("\n\n\n\n\t\t\t1.Easy");
  printf("\n\n\t\t\t2.Medium");
  printf("\n\n\t\t\t3.Hard");
  printf("\n\n\t\t\tChoose option:");
  scanf("%d",&diffc);
  switch(diffc)
   {
    case 1:lag=150;
	   scoreb1=125;
	   scoreb2=250;
	   scoreb3=500;
	   lscore=1000;
	   return;
    case 2:lag=100;
	   scoreb1=250;
	   scoreb2=500;
	   scoreb3=1000;
	   lscore=2000;
	   return;
    case 3:lag=50;
	   scoreb1=500;
	   scoreb2=1000;
	   scoreb3=2000;
	   lscore=4000;
	   return;
   }

  }



void creategrid()
 {
	int i,j,k;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		 {                       //initializes spaces
			grid[i][j]=' ';
		 }
    }

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		 {
			if(i==0)
			 grid[i][j]=upwall;
			if((j==0)&&(i!=m-1)&&(i!=0))           //borders
			 grid[i][j]=ltwall;
			if((j==n-1)&&(i!=m-1)&&(i!=0))
			 grid[i][j]=rtwall;
			if(i==m-1)
			 grid[i][j]=dnwall;

		 }
    }


    for(i=2;i<m/2;i+=2)
	{
		for(j=1;j<n;j+=5)
		 {
			for(k=j;k<j+4;k++)
			  {                          //brick initialization line 1
			   grid[i][k]=219;
		      }

		 }
    }


    for(i=0;i<paddlesize;i++)
     {
	grid[m-3][paddlestart+i]=223;                          //paddle
     }

    grid[x1][y1]=ball;
 }

void ballmovement()
 {
   int i=0,j,k,l,flag=0;

   if(start==0)
    return;

   for(k=1;k<m/2;k++)
    {
     for(l=1;l<n-1;l++)
      {
       if(grid[k][l]==brick||grid[k][l]==brick2||grid[k][l]==brick3)
	 {
	  flag=1;
	  break;
	 }
      }
    }
   if(flag==0)
    {
     char cont;
     sleep(1);
     clrscr();
     score=score+life*lscore;
     gamestart=0;
     printf("\n\n\n\n\n\t\t\tYOU WON!\n\t\t\tGAME OVER.");
     printf("\n\n\t\t\tFinal Score:%0.0f",score);
     printf("\n\n\t\t\tPress y to continue.");
    while(1)
    {
    cont=getch();
    if(cont=='y'||cont=='Y')
     break;
    }
     printf("\n\n\t\t\tEnter your name:");
     scanf("%s",&name);
     modhscore();
     getch();
     return;
    }

   if(grid[x1-xdiff][y1-ydiff]==upwall||grid[x1-xdiff][y1-ydiff]==dnwall)
      xdiff=xdiff*-1;

   if(grid[x1-xdiff][y1-ydiff]==ltwall||grid[x1-xdiff][y1-ydiff]==rtwall)
     {
       ydiff=ydiff*-1;
       if(grid[x1-xdiff][y1-ydiff]==upwall||grid[x1-xdiff][y1-ydiff]==dnwall)
	 xdiff=xdiff*-1;
     }

   if(grid[x1-xdiff][y1-ydiff]==brick)
      {
       while(1)
       {
	i++;
	if(grid[x1-xdiff][y1-ydiff-i]==' '||grid[x1-xdiff][y1-ydiff-i]==ltwall)
	   break;
       }
       for(j=1;j<5;j++)
	{
	 grid[x1-xdiff][y1-ydiff-i+j]=brick2;
	}
	xdiff=xdiff*-1;
	score=score+scoreb1;
	return;
      }

     if(grid[x1-xdiff][y1-ydiff]==brick2)
      {
       while(1)
       {
	i++;
	if(grid[x1-xdiff][y1-ydiff-i]==' '||grid[x1-xdiff][y1-ydiff-i]==ltwall)
	   break;
       }
       for(j=1;j<5;j++)
	{
	 grid[x1-xdiff][y1-ydiff-i+j]=brick3;
	}
	xdiff=xdiff*-1;
	score=score+scoreb2;
	return;
      }

     if(grid[x1-xdiff][y1-ydiff]==brick3)
      {
       while(1)
       {
	i++;
	if(grid[x1-xdiff][y1-ydiff-i]==' '||grid[x1-xdiff][y1-ydiff-i]==ltwall)
	   break;
       }
       for(j=1;j<5;j++)
	{
	 grid[x1-xdiff][y1-ydiff-i+j]=' ';
	}
	xdiff=xdiff*-1;
	score=score+scoreb3;
	return;
      }
   if(grid[x1][y1]==dnwall)
    {
     grid[x1-xdiff][y1-ydiff]=ball;
     return;
    }

   if(x1==m-2)
    {
      printf("\t\tLIFE LOST");
      sleep(3);
      life--;
      if(life==0)
       {
	char cont;
	clrscr();
	gamestart=0;
	printf("\n\n\n\n\n\n\t\t\tGAME OVER.");
	printf("\n\n\t\t\tFinal Score:%0.0f",score);
	printf("\n\n\t\t\tPress y to continue.");

    while(1)
    {
    cont=getch();
    if(cont=='y'||cont=='Y')
     break;
    }
	printf("\n\n\t\t\tEnter your name:");
	scanf("%s",&name);
	modhscore();
	getch();
	return;
       }
      grid[x1][y1]=' ';
      reset();
      return;
    }

   x2=x1;
   y2=y1;
   x1=x1-xdiff;
   y1=y1-ydiff;
   grid[x1][y1]=ball;
   grid[x2][y2]=' ';

 }


main()
 {

	char ch;
	int i,choice;
	intro();
    do{
	x1=m-4;
	y1=paddlestart+(paddlesize/2);
	x2=x1-xdiff;
	y2=y1-ydiff;
	creategrid();
	score=0;
	life=3;
	gamestart=0;
	start=0;
	clrscr();
	printf("\n\n\n\n\n\t\t\t1.Play");
	printf("\n\n\t\t\t2.Instructions");
	printf("\n\n\t\t\t3.Change Difficulty");
	printf("\n\n\t\t\t4.Highscores");
	printf("\n\n\t\t\t5.Exit");
	printf("\n\n\t\t\tChoose option:");
	scanf("%d",&choice);

	switch(choice)
	 {
	  case 1:gamestart=1;
		 break;

	  case 2:instructions();
		 break;

	  case 3:difficulty();
		 break;

	  case 4:highscores();
		 break;

	  case 5:exit(0);
		 break;
	 }

	while(gamestart)
	 {
	   clrscr();


	   if(kbhit())
	    {
		ch=getch();
		switch(ch)
		 {
			case 27:exit(0);
				break;

			case 32:start=1;
				randomize();
				if(random(2))
				 ydiff=ydiff*-1;
				break;

			case 'd':   for(i=0;i<3;i++)
					  {
					   paddleright();
					  }
					 break;

			case 'a':   for(i=0;i<3;i++)
					  {
					   paddleleft();
					  }
					 break;

			case 'q':gamestart=0;
				 break;
			  }

		 }
		else
		 {
		   printgrid();
		   ballmovement();
		   delay(lag);
		 }
	   }

       }while(1);

 }


