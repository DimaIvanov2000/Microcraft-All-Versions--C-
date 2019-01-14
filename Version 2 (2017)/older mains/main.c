#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
//functions

void initialize();

void loadWorld();
void saveWorld();
void unloadWorld();

void standardGen();

void displayWorld();
void displayInventory();
void displayHelp();

void title();
void titleAnim();

void SetColor();

//structures

struct block
{
    char name[20];
    char ch;
    int col;
    int hardness;
    int solid;
    int drop;
};

//variables
struct block blocks[32];
int loadedWorld[3][2][256][256]={0};
int player[4]={128,128,0,0};
char pRotChars[4]={'^','>','v','<'};

//main code

int main(void)
{
    int i,j;
    char input;
    int option
    srand(time(NULL));
    initialize();
    standardGen();
    titleAnim();
    do
    {
       input=getch();
       switch(input)
       {
           case

       }
    }
    while(input!=27);


//    do
//    {
//        displayWorld();
//        printf("\n\n%i , %i",player[0],player[1]);
//        input=getch();
//        switch(input)
//        {
//        case 'w':
//            player[1]--;
//            break;
//        case 's':
//            player[1]++;
//            break;
//        case 'a':
//            player[0]--;
//            break;
//        case 'd':
//            player[0]++;
//            break;
//        case 'i':
//            player[2]=0;
//            break;
//        case 'l':
//            player[2]=1;
//            break;
//        case 'k':
//            player[2]=2;
//            break;
//        case 'j':
//            player[2]=3;
//            break;
//        }
//    }
//    while(input!=27);


    setColor(15);
    return 0;
}

//function declarations

void initialize()
{
    int i=0,j=0;
    char c;
    FILE* bInfo=fopen("config//blockInfo.txt","r");
    do
    {
        c=fgetc(bInfo);
        j=0;
        while(c!=47)
        {
            blocks[i].name[j]=c;
            c=fgetc(bInfo);
            j++;
        }
        blocks[i].ch+=100*(fgetc(bInfo)-48);
        blocks[i].ch+=10*(fgetc(bInfo)-48);
        blocks[i].ch+=fgetc(bInfo)-48;
        fgetc(bInfo);
        blocks[i].col+=10*(fgetc(bInfo)-48);
        blocks[i].col+=fgetc(bInfo)-48;
        fgetc(bInfo);
        blocks[i].hardness+=fgetc(bInfo)-48;
        fgetc(bInfo);
        blocks[i].solid+=fgetc(bInfo)-48;
        fgetc(bInfo);
        blocks[i].drop+=10*(fgetc(bInfo)-48);
        blocks[i].drop+=fgetc(bInfo)-48;
        i++;
        c=fgetc(bInfo);
    }
    while(c!=-1);
    fclose(bInfo);
}

void loadWorld(char name[])
{
    //-95 is +2 at start (a)
    int b;
    int i,j,k,l,m;
    int n=0;
    char nName[40]={0};
    strcat(nName,"worlds//");
    strcat(nName,name);
    strcat(nName,".txt");
    //-95 is +2 at start (a)
    FILE* w=fopen(nName,"r");
    b=fgetc(w);
    for(m=0;m<6;m++)
    {
        l=0;
        while(b!=-1&&b!=10)
        {
            j=0;
            k=1;
            while(b>=97)
            {
                j+=(b-97)*k;
                k*=26;
                b=fgetc(w);
            }
            if(j==0)
            {
                j=1;
            }
            for(i=0;i<j;i++)
            {
                loadedWorld[m/2][m%2][(l+j-1)/256][(l+j-1)%256]=b-65;
            }
            l+=j;
            b=fgetc(w);
        }
    }
    fclose(w);
}

void saveWorld(char name[])
{

    int i,j,k;
    int iar,num,cur;


    char nName[40]={0};
    strcat(nName,"worlds//");
    strcat(nName,name);
    strcat(nName,".txt");
    FILE* w=fopen(nName,"w");
    for(i=0;i<6;i++)
    {
        for(j=0;j<256;j++)
        {
            cur=loadedWorld[i/2][i%2][j][0];
            iar=1;
            for(k=1;k<256;k++)
            {
                num=loadedWorld[i/2][i%2][j][k];
                if(num==cur)
                {
                    iar++;
                }
                else
                {
                    if(iar>25)
                    {
                        fputc((iar/26)+97,w);
                    }
                    if(iar>1)
                    {
                        fputc((iar%26)+97,w);
                    }
                    fputc(cur+65,w);
                    cur=num;
                    iar=1;
                }
            }
            if(iar>25)
            {
                fputc((iar/26)+97,w);
            }
            fputc((iar%26)+97,w);
            fputc(cur+65,w);
            fputc(10,w);
        }
        fputc(10,w);
    }
    fclose(w);
}

void unloadWorld()
{
    int i,j,k;
    for(k=0;k<6;k++)
    {
        for(j=0;j<256;j++)
        {
            for(i=0;i<256;i++)
            {
                loadedWorld[k/2][k%2][j][i]=0;
            }
        }
    }
}

void standardGen()
{
    int i,j,k,l;
    unloadWorld();
    for(j=0;j<256;j++)
    {
        for(i=0;i<256;i++)
        {
            if(rand()%16==0)
            {
                loadedWorld[0][0][j][i]=3;
            }
            else
            {
                loadedWorld[0][0][j][i]=1;
            }
        }
    }
    for(j=0;j<256;j++)
    {
        for(i=0;i<256;i++)
        {
            if(rand()%64==0)
            {
                for(l=-2;l<=2;l++)
                {
                    for(k=-2;k<=2;k++)
                    {
                        if(fabs((double)(k*l))!=4&&loadedWorld[0][1][j+l][i+k]!=5)
                        {
                            loadedWorld[0][1][j+l][i+k]=7;
                        }
                    }
                }
                loadedWorld[0][1][j][i]=5;
            }
        }
    }
}

void displayWorld()
{
    int i,j;
    int col=0;
    system("cls");
    for(j=-5;j<=5;j++)
    {
        for(i=-5;i<=5;i++)
        {
            if(i==0&&j==0)
            {
                setColor(15);
                printf("%c",pRotChars[player[2]]);
            }
            else
            {
                if(player[0]+i>=0&&player[0]+i<256&&player[1]+j>=0&&player[1]+j<256)
                {
                    if(loadedWorld[0][1][player[1]+j][player[0]+i]==0)
                    {
                        setColor(blocks[loadedWorld[0][0][player[1]+j][player[0]+i]].col);
                        printf("%c",blocks[loadedWorld[0][0][player[1]+j][player[0]+i]].ch);
                    }
                    else
                    {
                        setColor(blocks[loadedWorld[0][1][player[1]+j][player[0]+i]].col);
                        printf("%c",blocks[loadedWorld[0][1][player[1]+j][player[0]+i]].ch);
                    }
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void displayInventory()
{

}

void displayHelp()
{

}

void title()
{
	int i,j;

	int title[4][50]={
	{220,220,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,32,220,32,32,220,220,220,32,220,220,220,32,32,32,220,220,32,32,220,220},
	{219,32,219,32,219,32,32,219,32,32,219,32,32,32,219,220,219,32,219,32,219,32,219,32,32,32,219,220,219,32,219,220,219,32,219,220,32,32,32,219,32,32,32,32,223,223,220,220,223,223},
	{219,32,219,32,219,32,32,219,32,32,219,32,32,32,219,223,220,32,219,32,219,32,219,32,32,32,219,223,220,32,219,32,219,32,219,32,32,32,32,219,32,32,32,32,32,219,219,219,219,32},
	{223,32,223,32,223,32,223,223,223,32,223,223,223,32,223,32,223,32,223,223,223,32,223,223,223,32,223,32,223,32,223,32,223,32,223,32,32,32,32,223,32,32,32,32,32,223,32,32,223,32}
	};

	system("cls");
	setColor(14);
	printf("\n\t##################################################\n\t");
	setColor(11);
	for(i=0;i<4;i++)
	{
		for(j=0;j<50;j++)
		{
			printf("%c",title[i][j]);
		}
		printf("\n\t");
	}
	setColor(14);
	printf("##################################################\n");
}

void titleAnim()
{
    int i,j,k;
    int x,y;
    int e=0;

	int title[4][50]={
	{220,220,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,220,220,220,32,32,220,32,32,220,220,220,32,220,220,220,32,32,32,220,220,32,32,220,220},
	{219,32,219,32,219,32,32,219,32,32,219,32,32,32,219,220,219,32,219,32,219,32,219,32,32,32,219,220,219,32,219,220,219,32,219,220,32,32,32,219,32,32,32,32,223,223,220,220,223,223},
	{219,32,219,32,219,32,32,219,32,32,219,32,32,32,219,223,220,32,219,32,219,32,219,32,32,32,219,223,220,32,219,32,219,32,219,32,32,32,32,219,32,32,32,32,32,219,219,219,219,32},
	{223,32,223,32,223,32,223,223,223,32,223,223,223,32,223,32,223,32,223,223,223,32,223,223,223,32,223,32,223,32,223,32,223,32,223,32,32,32,32,223,32,32,32,32,32,223,32,32,223,32}
	};
	int vis[4][50]={0};

    setColor(14);
	for(i=0;i<=25;i++)
    {
        if(kbhit())
        {
            getch();
            return;
        }
        system("cls");
        printf("\n\t");
        for(j=0;j<50;j++)
        {
           if(fabs((double)(25-j))>=25-i)
           {
               printf("#");
           }
           else
           {
               printf(" ");
           }
        }
        printf("\n\n\n\n\n\t");
        for(j=0;j<50;j++)
        {
           if(fabs((double)(25-j))>=25-i)
           {
               printf("#");
           }
           else
           {
               printf(" ");
           }
        }
    }
	for(k=0;k<200;k++)
    {
        if(kbhit())
        {
            getch();
            return;
        }
        system("cls");
        x=rand()%50;
        y=rand()%4;
        while(vis[y][x]==1)
        {
            x=rand()%50;
            y=rand()%4;
        }
        vis[y][x]=1;
        setColor(14);
        printf("\n\t##################################################\n\t");
        setColor(3);
        for(i=0;i<4;i++)
        {
            for(j=0;j<50;j++)
            {
                if(vis[i][j]==1)
                {
                    printf("%c",title[i][j]);
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n\t");
        }
        setColor(14);
        printf("##################################################\n");
    }
    setColor(10);
}

void setColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
