/*
	Dima Ivanov's C Programs:
	
	Microcraft (2016 Version)
	
	A small-scale, two-dimensional recreation of Markus Persson's Minecraft.
	
	Functional Features include:
	
	- Random world generation
	- Player Movement
	- Several Block Types
	- 
*/

#include<stdio.h>

void playerAction();
	void mine();
	void place();
	void use();
void generateMap();
void displayMap();
void displayInv();

int map[256][256]={0};
int player[3]={128,128,0};
int inventory[5]={0};
char playerIcons[]={'v','^','>','<'};
char icons[]={176,178,177,' ',' ',' '};
int blockInfo[]={0};
int end=0;

main()
{
	char lol;
	generateMap();
	displayMap();
	while(end==0)
	{
		if(kbhit()) 
		{
			playerAction(getch());
			displayMap();
		}
	}
}

void generateMap()
{
	srand((unsigned) time(NULL));
	int i,j;
	for(i=0;i<=255;i++)
	{
		for(j=0;j<=255;j++)
		{
			if(rand()%4==0)
			{
				map[i][j]=2;
			}
			else
			{
				map[i][j]=1;
			}
		}
	}
}

void displayMap()
{
	int i,j;
	system("cls");
	for(i=-5;i<=5;i++)
	{
		printf("\t");
		for(j=-5;j<=5;j++)
		{
			if(i==0&&j==0)
			{
				printf("%c",playerIcons[player[2]]);
			}
			else if(player[0]+j>=0&&player[0]+j<=255&&player[1]+i>=0&&player[1]+i<=255)
			{
				printf("%c",icons[map[player[0]+j][player[1]+i]]);
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n   ");
	for(i=0;i<=4;i++)
	{
		printf("|%c %i| ",icons[i+1],inventory[i]);
	}
}

void playerAction(id)
{
	switch(id)
	{
		//looking around
		case 'k':
			player[2]=0;
			break;
		case 'i':
			player[2]=1;
			break;
		case 'l':
			player[2]=2;
			break;
		case 'j':
			player[2]=3;
			break;
		//moving character
		case 's':
			if(player[1]<255) player[1]++;
			break;
		case 'w':
			if(player[1]>0) player[1]--;
			break;
		case 'd':
			if(player[0]<255) player[0]++;
			break;
		case 'a':
			if(player[0]>0) player[0]--;
			break;
		//other actions
		case 'f':
			mine();
			break;
		case 'h':
			place();
			break;
		case 'r':
			use();
			break;
		case 't':
			end=1;
			break;
	}
}

void mine()
{
	switch(player[2])
	{
		case 0:
			if(player[1]<255&&map[player[0]][player[1]+1]!=0)
			{
				inventory[map[player[0]][player[1]+1]-1]++;
				map[player[0]][player[1]+1]=0;
			}
			break;
		case 1:
			if(player[1]>0&&map[player[0]][player[1]-1]!=0)
			{
				inventory[map[player[0]][player[1]-1]-1]++;
				map[player[0]][player[1]-1]=0;
			}
			break;
		case 2:
			if(player[0]<255&&map[player[0]+1][player[1]]!=0)
			{
				inventory[map[player[0]+1][player[1]]-1]++;
				map[player[0]+1][player[1]]=0;
			}
			break;
		case 3:
			if(player[0]>0&&map[player[0]-1][player[1]]!=0)
			{
				inventory[map[player[0]-1][player[1]]-1]++;
				map[player[0]-1][player[1]]=0;
			}
			break;
	}
}

void place()
{
	
}

void use()
{
	
}
