#include <stdio.h>
#include <math.h>

void draw();
void ghostMove();
void ghostMoveRandom();
void playerMove();
int check();

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

int junctionMap[17][2]={{1,1},{1,11},{3,1},{3,3},{3,6},{3,9},{3,11},{6,3},{6,9},{7,3},{7,9},{9,1},{9,3},{9,9},{9,11},{11,1},{11,11}};

int player[2]={7,6};
int ghosts[4][3]={{4,6,0},{4,6,0},{4,6,0},{4,6,0}};
int dots;
int score;
int end;
char icons[]={' ','O','@','*','o',' ',' ',' ',' ','#','!'};

main()
{
	srand((unsigned int) time(NULL));
	
	dots=62;
	score=0;
	end=0;
//	printf("%i",board[1][1]);
//	getch();
	while(end==0)
	{
		system("cls");
		draw();
		playerMove();
		end=check();
		if(check()==0)
		{
			ghostMove();
			end=check();
		}
	}
	system("cls");
	draw();
	
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
				if(end==0)
				{
					printf("O ");
				}
				else
				{
					printf("! ");
				}
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
		player[1]=11;
	}
	else if(board[player[0]][player[1]]==6)
	{
		player[1]=1;
	}
}

void ghostMoveRandom(i)
{
	int ok=0;
	while(ok==0)
	{
		int choice=rand()%4;
		
		switch(choice)
		{
			case 0:
				if(board[ghosts[i][0]-1][ghosts[i][1]]<7&&choice!=ghosts[i][2])
				{
					ghosts[i][0]--;
					ok++;
				}
				break;
			case 1:
				if(board[ghosts[i][0]+1][ghosts[i][1]]<7&&choice!=ghosts[i][2])
				{
					ghosts[i][0]++;
					ok++;
				}
				break;
			case 2:
				if(board[ghosts[i][0]][ghosts[i][1]-1]<7&&choice!=ghosts[i][2])
				{
					ghosts[i][1]--;
					ok++;
				}
				break;
			case 3:
				if(board[ghosts[i][0]][ghosts[i][1]+1]<7&&choice!=ghosts[i][2])
				{
					ghosts[i][1]++;
					ok++;
				}
				break;
		}
		ghosts[i][2]=choice;
	}
}

void ghostMove()
{
	int i;
	int j;
	for(i=0;i<4;i++)
	{
		int okay=0;
		for(j=0;j<17;j++)
		{
			if(ghosts[i][0]==junctionMap[j][0]&&ghosts[i][1]==junctionMap[j][1])
			{
				ghostMoveRandom(i);
				okay++;
				break;
			}
		}
		if(okay==0)
		{
			switch(ghosts[i][2])
			{
				case 0:
					if(board[ghosts[i][0]-1][ghosts[i][1]]<7)
					{
						ghosts[i][0]--;
					}
					break;
				case 1:
					if(board[ghosts[i][0]+1][ghosts[i][1]]<7)
					{
						ghosts[i][0]++;
					}
					break;
				case 2:
					if(board[ghosts[i][0]][ghosts[i][1]-1]<7)
					{
						ghosts[i][1]--;
					}
					break;
				case 3:
					if(board[ghosts[i][0]][ghosts[i][1]+1]<7)
					{
						ghosts[i][1]++;
					}
					break;
			}
		}
		if(board[ghosts[i][0]][ghosts[i][1]]==5)
		{
			ghosts[i][1]=11;
		}	
		else if(board[ghosts[i][0]][ghosts[i][1]]==6)
		{
			ghosts[i][1]=1;
		}
	}
	
}

int check()
{
	int i;
	int collision=0;
	
	for(i=0;i<4;i++)
	{
		if(ghosts[i][0]==player[0]&&ghosts[i][1]==player[1])
		{
			collision=1;
		}
	}
	
	return collision;
}
