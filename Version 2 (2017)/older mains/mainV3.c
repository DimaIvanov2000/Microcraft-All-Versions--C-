/************************************************************

    MICROCRAFT
    (AKA ASCIICRAFT)

    Written by Dima Ivanov

    Microcraft is a small-scale, primitive adaptation of Minecraft in a
    console window using C.

************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include<time.h>

/********** Functions **********/

/* Initialization */
void initialize();

/* World / File Handling */
void loadWorld(char[]);
void saveWorld(char[]);
void unloadWorld(void);
void standardGen(void);

/* Preliminary User Interface */
int title(void);
void titleAnim(void);
int mainMenu(void);
void changeSettings(void);
void displayHelp(void);
int selectWorld(void);
void createWorld(void);
void deleteWorld(char[]);

/* In-Game Display */
void displayWorld(void);
void displayInventory(void);

/* Main Game Handling */
void play(void);

/* Other */
void SetColor(int);
void cprintf(int,char[]);
void cprinti(int,int);
//void borderprintf();

/********** Structures **********/

struct block
{
    char name[50];
    char ch;
    int col;
    int hardness;
    int solid;
    int drop;
};

/********** Global Variables **********/
struct block blocks[32];
int loadedWorld[3][2][256][256]={0};
int player[4]={128,128,0,0};
char pRotChars[4]={'^','>','v','<'}; //191 192 217 218
//char pRotChars[3][3]={{218,'^',191},{'<','O','>'},{192,'v',217}};

/********** Main Function **********/
int main(void)
{
    int i,j;
    int option;
    int temp;

    //deleteWorld("effefeeffefsefe");

    srand((unsigned int) time(NULL));

//    system("cls");
//    cprintf(8,"\n\t##################################################\n\n");
//    cprintf(15,"");
//    cprintf(14,"\n\n\tAny Key to Continue");
//    cprintf(8,"\n\n\t##################################################\n\n");
//    getch();

    initialize();
    standardGen();
    //saveWorld("lolxd");
    unloadWorld();
    //loadWorld("lolxd");

    titleAnim();
    while(title()==1)
    {
        do
        {
            temp=mainMenu();
            switch(temp)
            {
                case 1:
                    if(selectWorld()==1)
                    {
                        play();
                        temp=0;
                    }
                    break;
                case 2:
                    displayHelp();
                    break;
                case 3:
                    changeSettings();
                    break;
            }
        }
        while(temp!=0);
    }

    setColor(15);
    return 0;
}

/********** Function Declarations **********/

void initialize(void)
{
    int i=0,j=0;
    char c;
    char curLine[50]={0};
    FILE*bInfo=fopen("config//blockInfoV2.txt","r");

    while(!feof(bInfo))
    {
        fscanf(bInfo,"%s",curLine);
        for(i=0;i<50;i++)
        {
            blocks[j].name[i]=curLine[i];
            if(curLine[i]==0)
            {
                break;
            }
        }
        printf("%i: ",j);
        for(i=0;i<50;i++)
        {
            printf("%i ",curLine[i]);
            curLine[i]=0;
        }
        printf("\n\n");
        fscanf(bInfo,"%s",curLine);
        blocks[j].ch=((curLine[0]-48)*100)+((curLine[1]-48)*10)+(curLine[2]-48);
        blocks[j].col=((curLine[4]-48)*10)+(curLine[5]-48);
        blocks[j].hardness=curLine[7]-48;
        blocks[j].solid=curLine[9]-48;
        //printf("%i %i   %i\n",curLine[11],curLine[12],((curLine[11]-48)*10)+curLine[12]-48);
        blocks[j].drop=((curLine[11]-48)*10)+(curLine[12]-48);
        for(i=0;i<50;i++)
        {
            printf("%i ",curLine[i]);
            curLine[i]=0;
        }
        printf("\n\n");
        j++;
    }
    getch();
    fflush(bInfo);
    fclose(bInfo);
}

void loadWorld(char name[])
{
    //-95 is +2 at start (a)
    int b;
    int i,j,k,l;
    int currPlace=0;
    int coeff=0;
    char nName[40]={0};
    strcat(nName,"worlds//");
    strcat(nName,name);
    strcat(nName,".txt");
    //-95 is +2 at start (a)
    FILE*w=fopen(nName,"r");
    for(i=0;i<2;i++)
    {
        player[i]=0;
        b=fgetc(w);
        j=0;
        do
        {
            player[i]+=(b-65)*(int)pow(26,j);
            j++;
            b=fgetc(w);
        }
        while(b!=10);
    }

    for(i=0;i<3;i++)
    {
        for(j=0;j<2;j++)
        {
            for(k=0;k<256;k++)
            {
                b=fgetc(w);
                while(b!=10&&b!=-1)
                {
                    if(b>=97&&b<=122)
                    {
                        coeff*=26;
                        coeff+=b-97;
                    }
                    else if(b>=65&&b<=90)
                    {
                        if(coeff==0)
                        {
                            coeff=1;
                        }
                        for(l=1;l<=coeff;l++)
                        {
                            loadedWorld[i][j][currPlace][k]=b-65;
                            currPlace++;
                        }
                        coeff=0;
                    }
                    b=fgetc(w);
                }
                currPlace=0;
            }
        }
    }
    fflush(w);
    printf("%i",fclose(w));
    getch();
}

void saveWorld(char name[])
{
//    char worldDirName[50]={0};
//    char playerDirName[50]={0};
//    char invDirName[50]={0};
//    strcat()word
//    mkdir(name,0700);

//    char dirName[50];
//    sprintf(nName,"worlds//%s.txt",name);
//
//    FILE*w=fopen(nName,"w");
//
//
//
//    fflush(w);
//    fclose(w);

    int i,j,k;
    int iar,num,cur;
    int temp;

    char nName[40]={0};
    strcat(nName,"worlds//");
    strcat(nName,name);
    strcat(nName,".txt");
    FILE* w=fopen(nName,"w");
    for(i=0;i<2;i++)
    {
        temp=player[i];
        j=1;
        do
        {
            fputc(65+(temp%(int)pow(26,j)),w);
            temp-=temp%(int)pow(26,j);
            temp/=26;
            j++;
        }
        while(temp!=0);
        fputc(10,w);
    }

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
            if(iar>1)
            {
                fputc((iar%26)+97,w);
            }
            fputc(cur+65,w);
            fputc(10,w);
        }
    }
    fflush(w);
    fclose(w);
}

void unloadWorld(void)
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

void standardGen(void)
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

int title(void)
{
	int i,j;
	char input;

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
	do
    {
        input=getch();
    }
    while(input!=27&&input!=8&&input!=13);
    if(input==13)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void titleAnim(void)
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

int mainMenu(void)
{
    int i;
    char input;
    int selection=0;
    char options[3][15]={"Play!","Help","Settings"};

    do
    {
        system("cls");
        cprintf(8,"\n\t##################################################\n\n");
        for(i=0;i<3;i++)
        {
            if(selection==i)
            {
                cprintf(10,"\t > ");
            }
            else
            {
                cprintf(15,"\t   ");
            }
            printf("%s\n",options[i]);
        }
        cprintf(14,"\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back to Title");
        cprintf(8,"\n\n\t##################################################\n\n");
        input=getch();
        switch(input)
        {
        case 72:
            if(selection>0)
            {
                selection--;
            }
            break;
        case 80:
            if(selection<2)
            {
                selection++;
            }
            break;
        case 13:
            return selection+1;
            break;
        }
    }
    while(input!=27&&input!=8);
    return 0;
}

void changeSettings(void)
{
    return 0;
}

void displayHelp(void)
{
    int i;
    char input;
    int selection=0;
    char options[5][20]={"Controls","Premise","Detailed Guide","Features","Crafting Recipes"};
    char subOptionsGuide[6][25]={"Breaking and Placing","Inventory Management","Crafting","Appliances","Dimensions","Blocktionary"};

    do
    {
        system("cls");
        cprintf(8,"\n\t##################################################\n\n");
        for(i=0;i<5;i++)
        {
            if(selection==i)
            {
                cprintf(10,"\t > ");
            }
            else
            {
                cprintf(15,"\t   ");
            }
            printf("%s\n",options[i]);
        }
        cprintf(14,"\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back");
        cprintf(8,"\n\n\t##################################################\n\n");
        input=getch();
        switch(input)
        {
        case 72:
            if(selection>0)
            {
                selection--;
            }
            break;
        case 80:
            if(selection<4)
            {
                selection++;
            }
            break;
        case 13:
            switch(selection)
            {
                case 0:
                    system("cls");
                    cprintf(8,"\n\t##################################################\n\n");
                    cprintf(15,"\t ^\n\t< >   Move\n\t v\n\n\t W\n\tA D   Reorient\n\t S\n\n\t E   Break\n\t Q   Place\n\t R   Open Inventory");
                    cprintf(14,"\n\n\tAny Key to Continue");
                    cprintf(8,"\n\n\t##################################################\n\n");
                    getch();
                    break;
                case 1:
                    system("cls");
                    cprintf(8,"\n\t##################################################\n\n");
                    cprintf(15,"\tMicrocraft is a small-scale adaptation of\n\tMinecraft. The \"objective\" of the game is thus\n\tpractically identical: collect resources, craft\n\titems with the materials you collect and process,\n\tand use these items to shape the world around you\n\tto your desires. For further detail on various\n\ttopics, visit the \"Detailed Guide\" tab. For more\n\tinformation on features in or planned for the\n\tgame, visit the \"Features\" tab.");
                    cprintf(14,"\n\n\tAny Key to Continue");
                    cprintf(8,"\n\n\t##################################################\n\n");
                    getch();
                    break;
                case 2:
                    selection=0;
                    do
                    {
                        system("cls");
                        cprintf(8,"\n\t##################################################\n\n");
                        for(i=0;i<6;i++)
                        {
                            if(selection==i)
                            {
                                cprintf(10,"\t > ");
                            }
                            else
                            {
                                cprintf(15,"\t   ");
                            }
                            printf("%s\n",subOptionsGuide[i]);
                        }
                        cprintf(14,"\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back");
                        cprintf(8,"\n\n\t##################################################\n\n");
                        input=getch();
                        switch(input)
                        {
                        case 72:
                            if(selection>0)
                            {
                                selection--;
                            }
                            break;
                        case 80:
                            if(selection<5)
                            {
                                selection++;
                            }
                            break;
                        case 13:
                            switch(selection)
                            {
                                case 0:
                                    system("cls");
                                    cprintf(8,"\n\t##################################################\n\n");
                                    cprintf(15,"\tPressing E will break the block towards which your\n\tcharacter is facing. Blocks may yield items other\n\tthan themselves (e.g. stone yields cobblestone,\n\tgrass yields dirt, etc.) If you do not have the\n\tappropriate tool level (i.e. wood, stone, iron,\n\tdiamond. This mostly applies to stone and other\n\tores), blocks will take longer to break and will\n\tnot yield an item. Higher tool levels also\n\tincrease the durability of tools. Tools will\n\tdegrade quicker when used on inappropriate blocks\n\t(e.g. shovel on wood, pickaxe on dirt, etc.).\n\n\tPressing E will Place a block in the space the\n\tcharacter is facing towards, given that said space\n\tis empty. Appliances may only be used if placed\n\tdown.");
                                    cprintf(14,"\n\n\tAny Key to Continue");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    getch();
                                    break;
                                case 1:
                                    system("cls");
                                    cprintf(8,"\n\t##################################################\n\n");
                                    cprintf(15,"\tlol not done yet");
                                    cprintf(14,"\n\n\tAny Key to Continue");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    getch();
                                    break;
                                case 2:
                                    system("cls");
                                    cprintf(8,"\n\t##################################################\n\n");
                                    cprintf(15,"\tlol not done yet");
                                    cprintf(14,"\n\n\tAny Key to Continue");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    getch();
                                    break;
                                case 3:
                                    system("cls");
                                    cprintf(8,"\n\t##################################################\n\n");
                                    cprintf(15,"\tlol not done yet");
                                    cprintf(14,"\n\n\tAny Key to Continue");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    getch();
                                    break;
                                case 4:
                                    system("cls");
                                    cprintf(8,"\n\t##################################################\n\n");
                                    cprintf(15,"\tlol not done yet");
                                    cprintf(14,"\n\n\tAny Key to Continue");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    getch();
                                    break;
                                case 5:
                                    system("cls");
                                    cprintf(8,"\n\t##################################################\n\n");
                                    cprintf(15,"\tlol not done yet");
                                    cprintf(14,"\n\n\tAny Key to Continue");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    getch();
                                    break;
                            }
                            break;
                        }
                    }
                    while(input!=27&&input!=8);
                    input=0;
                    selection=0;
                    break;
                case 3:
                    system("cls");
                    cprintf(8,"\n\t##################################################\n\n");
                    cprintf(15,"\tFeatures Currently Implemented:\n\t - This section is not complete im lazy lol");
                    cprintf(14,"\n\n\tAny Key to Continue");
                    cprintf(8,"\n\n\t##################################################\n\n");
                    getch();
                    break;
                case 4:
                    system("cls");
                    cprintf(8,"\n\t##################################################\n\n");
                    cprintf(15,"\tnot done get out of here");
                    cprintf(14,"\n\n\tAny Key to Continue");
                    cprintf(8,"\n\n\t##################################################\n\n");
                    getch();
                    break;
            }
            break;
        }
    }
    while(input!=27&&input!=8);
    return;
}

int selectWorld(void)
{
    int i,j;
    int selection=-1;
    char input;
    char c;
    char wName[31];
    int wNum=0;

    FILE*wInfo=fopen("config//worldInfo.txt","r");
    do
    {
        system("cls");
        cprintf(8,"\n\n\t##################################################\n\n");
        //fgets(wName,31,wInfo);
        if(selection==-1)
        {
            cprintf(10,"\t > [Create New World]\n\n");
        }
        else
        {
            cprintf(15,"\t   [Create New World]\n\n");
        }
        j=0;
        c=fgetc(wInfo);
        while(c!=-1)
        {
            i=0;
            while(c!=10)
            {
                wName[i]=c;
                i++;
                c=fgetc(wInfo);
            }
            wName[i]=0;
            c=fgetc(wInfo);
            if(j==selection)
            {
                cprintf(10,"\t > ");
            }
            else
            {
                cprintf(15,"\t   ");
            }
            printf("%s\n",wName);
            j++;
        }
        rewind(wInfo);
        cprintf(14,"\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back");
        cprintf(8,"\n\n\t##################################################\n\n");
        input=getch();
        switch(input)
        {
        case 72:
            if(selection>-1)
            {
                selection--;
            }
            break;
        case 80:
            if(selection<j-1)
            {
                selection++;
            }
            break;
        case 13:
            if(selection>-1)
            {
                wNum=selection;
                selection=0;
                do
                {
                    system("cls");
                    cprintf(8,"\n\n\t##################################################\n\n");
                    if(selection==0)
                    {
                        cprintf(10,"\t > Play World\n");
                        cprintf(15,"\t   Delete World\n");
                    }
                    else
                    {
                        cprintf(15,"\t   Play World\n");
                        cprintf(10,"\t > Delete World\n");
                    }
                    cprintf(14,"\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back");
                    cprintf(8,"\n\n\t##################################################\n\n");
                    input=getch();
                    switch(input)
                    {
                        case 72:
                            if(selection>0)
                            {
                                selection--;
                            }
                            break;
                        case 80:
                            if(selection<1)
                            {
                                selection++;
                            }
                            break;
                        case 13:
                            if(selection==0)
                            {
                                for(i=0;i<wNum;i++)
                                {
                                    fgets(wName,31,wInfo);
                                }
                                c=fgetc(wInfo);
                                i=0;
                                while(c!=10)
                                {
                                    wName[i]=c;
                                    i++;
                                    c=fgetc(wInfo);
                                }
                                wName[i]=0;
                                loadWorld(wName);
                                fclose(wInfo);
                                return 1;
                            }
                            else
                            {
                                selection=0;
                                do
                                {
                                    system("cls");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    if(selection==0)
                                    {
                                        cprintf(10,"\t > Cancel\n");
                                        cprintf(15,"\t   Delete World\n");
                                    }
                                    else
                                    {
                                        cprintf(15,"\t   Cancel\n");
                                        cprintf(12,"\t > Delete World\n");
                                    }
                                    cprintf(14,"\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back");
                                    cprintf(8,"\n\n\t##################################################\n\n");
                                    input=getch();
                                    switch(input)
                                    {
                                        case 72:
                                            if(selection>0)
                                            {
                                                selection--;
                                            }
                                            break;
                                        case 80:
                                            if(selection<1)
                                            {
                                                selection++;
                                            }
                                            break;
                                        case 13:
                                            if(selection==1)
                                            {
                                                rewind(wInfo);
                                                for(i=0;i<wNum;i++)
                                                {
                                                    fgets(wName,31,wInfo);
                                                }
                                                c=fgetc(wInfo);
                                                i=0;
                                                while(c!=10)
                                                {
                                                    wName[i]=c;
                                                    i++;
                                                    c=fgetc(wInfo);
                                                }
                                                wName[i]=0;
                                                fclose(wInfo);
                                                deleteWorld(wName);
                                                FILE*wInfo=fopen("config//worldInfo.txt","r");
                                            }
                                            break;
                                    }
                                }
                                while(input!=27&&input!=8&&input!=13);
                                if(!(input==13&&selection==1))
                                {
                                    input=0;
                                    selection=0;
                                }
                            }
                            break;
                    }
                }
                while(input!=27&&input!=8&&input!=13);

                input=0;
                selection=-1;
                break;
            }
            else
            {
                createWorld();
            }
        }
    }
    while(input!=27&&input!=8);
    fflush(wInfo);
    fclose(wInfo);
    return 0;
}

void createWorld()
{
    int i;
    char input;
    int selection=0;
    char worldGenTypes[3][20]={"Standard","Noise","Experimental"};

    int placeInName=0;
    char name[31]={0};

    FILE*wInfo=fopen("config//worldInfo.txt","a");
    do
    {
        system("cls");
        cprintf(8,"\n\n\t##################################################\n\n\t");
        cprintf(15,"Name: ");
        if(placeInName==30)
        {
            cprintf(14,name);
        }
        else
        {
            cprintf(15,name);
            printf("%c",220);
        }
        cprintf(14,"\n\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back");
        cprintf(8,"\n\n\t##################################################\n\n");
        input=getch();
        if(input==8&&placeInName>0)
        {
            placeInName--;
            name[placeInName]=0;
        }
        else if(input>=32&&placeInName<30)
        {
            name[placeInName]=input;
            placeInName++;
        }
        else if(input==27)
        {
            return;
        }
    }
    while(input!=27&&!(input==13&&placeInName>0));
    do
    {
        system("cls");
        cprintf(8,"\n\n\t##################################################\n\n\t");
        cprintf(11,"Name: ");
        printf("%s",name);
        printf("\n");
        for(i=0;i<3;i++)
        {
            if(selection==i)
            {
                cprintf(10,"\n\t > ");
            }
            else
            {
                cprintf(15,"\n\t   ");
            }
            printf("%s",worldGenTypes[i]);
        }
        cprintf(14,"\n\n\tArrow Keys - Move Cursor\n\tEnter - Confirm\n\tEsc - Back");
        cprintf(8,"\n\n\t##################################################\n\n\t");
        input=getch();
        switch(input)
        {
            case 72:
            if(selection>0)
            {
                selection--;
            }
            break;
        case 80:
            if(selection<2)
            {
                selection++;
            }
            break;
        case 13:
            switch(selection)
            {
            case 0:
                standardGen();
                break;
            case 1:
                standardGen();
                break;
            case 2:
                standardGen();
                break;
            }
            player[0]=128;
            player[1]=128;
            saveWorld(name);
            i=0;
            while(name[i]!=0)
            {
                fputc(name[i],wInfo);
                i++;
            }
            fputc(10,wInfo);
            fclose(wInfo);
            return;
            break;
        }
    }
    while(input!=27&&input!=13);
    fflush(wInfo);
    fclose(wInfo);
    return;
}

void deleteWorld(char wName[])
{
    int i=0,j;
    int correct;
    char c;
    char fullName[50]={0};
    strcat(fullName,"worlds//");
    strcat(fullName,wName);
    strcat(fullName,".txt");

    FILE*wInfo=fopen("config//worldInfo.txt","r");
    FILE*temp=fopen("config//temp.txt","w");

    c=fgetc(wInfo);
    while(c!=-1)
    {
        correct=1;
        j=0;
        while(c!=10)
        {
            if(c!=wName[j])
            {
                correct=0;
            }
            c=fgetc(wInfo);
            j++;
        }
        if(correct==1&&wName[j]==0)
        {
            break;
        }
        c=fgetc(wInfo);
        i++;
    }
    rewind(wInfo);

    j=0;
    c=fgetc(wInfo);
    while(c!=-1)
    {
        while(c!=10)
        {
            if(j!=i)
            {
                fputc(c,temp);
            }
            c=fgetc(wInfo);
        }
        if(j!=i)
        {
            fputc(10,temp);
        }
        j++;
        c=fgetc(wInfo);
    }
    fflush(wInfo);
    fclose(wInfo);
    fflush(temp);
    fclose(temp);

    printf("%i",remove(fullName));
    printf("%i",remove("config//worldInfo.txt"));
    printf("%i",rename("config//temp.txt","config//worldInfo.txt"));
    getch();
}

void displayWorld(void)
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

void displayInventory(void)
{

}

void play(void)
{
    char input;
    do
    {
        displayWorld();
        printf("\n\n%i , %i",player[0],player[1]);
        input=getch();
        switch(input)
        {
        case 'w':
            player[1]--;
            break;
        case 's':
            player[1]++;
            break;
        case 'a':
            player[0]--;
            break;
        case 'd':
            player[0]++;
            break;
        case 'i':
            player[2]=0;
            break;
        case 'l':
            player[2]=1;
            break;
        case 'k':
            player[2]=2;
            break;
        case 'j':
            player[2]=3;
            break;
        }
    }
    while(input!=27);
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

void cprintf(int c,char*s) //saves a lot of lines of code in display, arguements are color then string
{
    //self-explanatory
    setColor(c);
    printf(s);
}

void cprinti(int c,int i) //saves some of lines of code in display, arguements are color then integer
{
    //self-explanatory
    setColor(c);
    printf("%i",i);
}

//void borderprintf(int indent,int size,char s[]) //arguements are indent size, line size, and the string itself
//{
//    int i,j;
//    int place=0;
//
//    for(i=0;s[place]!=32&&s[place+i]!=0;i++){}
//    if((place%size)+i>size)
//    {
//        printf("\n");
//    }
//    for(j=0;j<=i;j++)
//    {
//        printf("%c",s[place+i]);
//    }
//
//}
