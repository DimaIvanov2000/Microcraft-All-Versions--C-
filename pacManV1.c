#include <stdio.h>
#include <math.h>

void draw();
void ghostMove();
void playerMove();
void check();

int board[13][13]={
{9,9,9,9,9,9,9,9,9,9,9,9,9},
{9,4,3,3,3,3,3,3,3,3,3,4,9},
{9,3,9,9,9,9,9,9,9,9,9,3,9},
{9,3,3,3,3,3,3,3,3,3,3,3,9},
{9,9,9,3,9,9,7,9,9,3,9,9,9},
{9,9,9,3,9,7,7,7,9,3,9,9,9},
{5,0,0,3,9,9,9,9,9,3,0,0,6},
{9,9,9,3,3,3,0,3,3,3,9,9,9},
{9,9,9,3,9,9,9,9,9,3,9,9,9},
{9,3,3,3,3,3,3,3,3,3,3,3,9},
{9,3,9,9,9,9,9,9,9,9,9,3,9},
{9,4,3,3,3,3,3,3,3,3,3,4,9},
{9,9,9,9,9,9,9,9,9,9,9,9,9},
};
player[2]={7,6};
int ghosts[4][3]={1};
int dots;
int score;
char icons[]={' ','O','@','*','o',' ',' ',' ',' ','#'};

main()
{
	srand((unsigned int) time(NULL));
	
	dots=62;
	score=0;
	while(1)
	{
		system("cls");
		draw();
		playerMove();
		ghostMove();
	}
	
}

void draw()
{
	int i;
	int j;
	int k;
	
	for(i=0;i<13;i++)
	{
		printf("\t");
		for(j=0;j<13;j++)
		{
			if(player[0]==i&&player[1]==j)
			{
				printf("O ");
			}
			else
			{
				int ghost=0;
				for(k=0;k<4;k++)
				{
					if(ghosts[k][0]==i&&ghosts[k][1]==j)
					{
						ghost++;
					}
				}
				if(ghost==0)
				{
					printf("%c ",icons[board[i][j]]);
				}
				else
				{
					printf("@ ");
				}
			}
		}
		printf("\n");
	}
	printf("\nScore: %i\n\n",score);
}

void playerMove()
{
	char move;
	char ok=0;
	while(ok==0)
	{
		move=getch();
		
		switch(move)
		{
			case 'w':
				if(board[player[0]-1][player[1]]<7)
				{
					player[0]--;
					ok++;
				}
				break;
			case 'a':
				if(board[player[0]][player[1]-1]<7)
				{
					player[1]--;
					ok++;
				}
				break;
			case 's':
				if(board[player[0]+1][player[1]]<7)
				{
					player[0]++;
					ok++;
				}
				break;
			case 'd':
				if(board[player[0]][player[1]+1]<7)
				{
					player[1]++;
					ok++;
				}
				break;
		}
	}
	if(board[player[0]][player[1]]==3)
	{
		board[player[0]][player[1]]=0;
		score+=10;
		dots--;
	}
	else if(board[player[0]][player[1]]==4)
	{
		board[player[0]][player[1]]=0;
		score+=50;
		dots--;
	}
	else if(board[player[0]][player[1]]==5)
	{
		player[0]=6;player[1]=11;
	}
	else if(board[player[0]][player[1]]==6)
	{
		player[0]=6;player[1]=1;
	}
}

void ghostMove()
{
	int i;
	int j;
	
	for(i=0;i<4;i++)
	{
		int ok=0;
		
		switch(ghosts[i][2])
		{
			case 0:
				if(board[ghosts[i][0]-1][ghosts[i][1]]<7)
				{
					ghosts[i][0]--;
					ok++;
				}
				break;
			case 1:
				if(board[ghosts[i][0]+1][ghosts[i][1]]<7)
				{
					ghosts[i][0]++;
					ok++;
				}
				break;
			case 2:
				if(board[ghosts[i][0]][ghosts[i][1]-1]<7)
				{
					ghosts[i][1]--;
					ok++;
				}
				break;
			case 3:
				if(board[ghosts[i][0]][ghosts[i][1]+1]<7)
				{
					ghosts[i][1]++;
					ok++;
				}
				break;
		}
		while(ok==0)
		{
			int choice=rand()%4;
			
			switch(choice)
			{
				case 0:
					if(board[ghosts[i][0]-1][ghosts[i][1]]<7)
					{
						ghosts[i][0]--;
						ok++;
					}
					break;
				case 1:
					if(board[ghosts[i][0]+1][ghosts[i][1]]<7)
					{
						ghosts[i][0]++;
						ok++;
					}
					break;
				case 2:
					if(board[ghosts[i][0]][ghosts[i][1]-1]<7)
					{
						ghosts[i][1]--;
						ok++;
					}
					break;
				case 3:
					if(board[ghosts[i][0]][ghosts[i][1]+1]<7)
					{
						ghosts[i][1]++;
						ok++;
					}
					break;
			}
			ghosts[i][2]=choice;
		}
	}
}
