#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define XZACIATOK   20
#define XKONIEC     50
#define XDLZKA      (XKONIEC-XZACIATOK)

#define YZACIATOK   3
#define YKONIEC     18
#define YDLZKA      (YKONIEC-YZACIATOK)

#define DELAY_1     10000000
#define DELAY       150000000
#define SNAKE_MAX_DLZKA 1000

#define VPRAVO      77
#define VLAVO       75
#define DOHORA      72
#define DODOLA      80
#define ESC         27



int snake_dlzka=3;
int clanok[SNAKE_MAX_DLZKA];
int zivot=3+1;


void vytv_hranic(void);
void vypis(void);
void papo(void);
void doprava(void);
void dolava(void);
void dole(void);
void hore(void);
void chod(void);
void ukoncenie(void);
void koment(void);
void game_over(void);
void ulozit(void);
void sekanie(void);




typedef struct{
  int x;
  int y;
  int smer;
} struktura;
struktura hlava,bod,telo[SNAKE_MAX_DLZKA],jedlo;




void gotoXY(int x, int y)
{
    COORD XY;
    XY.X=x;
    XY.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}



void delay(int pocet)
{
    int k;
    //printf("\n\n\tNacitavam");
    for(int i=0; i<pocet; i++)
    {
        for(int j=0; j<DELAY_1;j++)
            k=j;
    //printf(". ");
    }
}



void nacitavanie(int pocet)
{
    int k;
    printf("Nacitavam");
    for(int i=0; i<pocet; i++)
    {
        for(int j=0; j<DELAY;j++)
            k=j;
    printf(". ");
    }
}



void sekanie(void)
{
    for(int i=2 ; i<snake_dlzka ; i++)
    {
       if(hlava.x==telo[i].x&&hlava.y==telo[i].y)
       {
           snake_dlzka=i-1;
       }
    }
}


///==================================================================================///

int main(void)
{
    vypis();
    vytv_hranic();
    papo();
    zaciatok();
    chod();
    return 0;
}



void chod(void)
{
    int priemet,a;

    do
    {
        system("cls");
        fflush(stdin);
        koment();
        papo();
        if(hlava.smer==VPRAVO)
            doprava();
        else if(hlava.smer==VLAVO)
            dolava();
        else if(hlava.smer==DOHORA)
            hore();
        else if(hlava.smer==DODOLA)
            dole();
        vytv_hranic();
        sekanie();

        delay(7);
        if(zivot<1)
            game_over();
    }while(!kbhit());
    a=getch();
    if(a == ESC)
        ukoncenie();
    priemet=getch();
    if( (hlava.smer==VPRAVO&&priemet!=VPRAVO&&priemet!=VLAVO) || (hlava.smer==VLAVO&&priemet!=VLAVO&&priemet!=VPRAVO) || (hlava.smer==DOHORA&&priemet!=DODOLA&&priemet!=DOHORA) || (hlava.smer==DODOLA&&priemet!=DOHORA&&priemet!=DODOLA) )
    {
        hlava.smer=priemet;
        chod();
    }
    chod();
}







void zaciatok(void)
{
    hlava.smer=VPRAVO;
    hlava.x=35;
    hlava.y=7;
    gotoXY(hlava.x,hlava.y);
    printf(">");
    for(int i=0; i<snake_dlzka ; i++)
    {
        telo[i].x = hlava.x-(1+i);
        telo[i].y = hlava.y;
        gotoXY(telo[i].x,telo[i].y);
        printf("*");
    }
}








void vypis(void)
{
    printf("\n\tVitajte v hernon studia A.M.O.R\n\n\tPre pokracovanie stlacte klavesnicu....");
    getch();
    system("cls");
    jedlo.x=0;
    jedlo.y=0;
    printf("\n\tHerne instrukcie :");
    printf("\n\n->\tpre navigovanie snakea, pouzivajte sipky ");
    printf("\n\n->\tpre ukoncenie stlacte klavesnicu ESC");
    printf("\n\n->\tpre pokracovanie stlacte klavesnicu...");

    if(getch()==27)
        exit(0);
    system("cls");
}





void vytv_hranic(void)
{
    /// x-ova osa
    gotoXY(XZACIATOK,YZACIATOK);
    for(int i=0; i<=XDLZKA; i++)
    {
        printf("%c",'!');
    }

    gotoXY(XZACIATOK,YKONIEC);
    for(int i=0; i<=XDLZKA; i++)
    {
        printf("%c",'!');
    }

    ///y-ova osa
    for(int i=0; i<YDLZKA; i++)
    {
        gotoXY(XZACIATOK,YZACIATOK+1+i);
        printf("%c",'!');
    }

    for(int i=0; i<YDLZKA; i++)
    {
        gotoXY(XKONIEC,YZACIATOK+1+i);
        printf("%c",'!');
    }

    if(hlava.x>=XKONIEC || hlava.x<=XZACIATOK || hlava.y>= YKONIEC || hlava.y<= YZACIATOK)
    {
        zivot--;
        snake_dlzka=3;
        zaciatok();
    }
}




void papo(void)
{
    if( (hlava.x==jedlo.x)&&(hlava.y==jedlo.y) )
    {
        jedlo.x = (rand()%(XDLZKA-2))+(XZACIATOK+1);
        jedlo.y = (rand()%(YDLZKA-2))+(YZACIATOK+1);
        gotoXY(jedlo.x , jedlo.y);
        printf("#");
        snake_dlzka++;
    }
    else if (jedlo.x==0 || jedlo.y==0)
    {
        jedlo.x = (rand()%(XDLZKA-2))+(XZACIATOK+1);
        jedlo.y = (rand()%(YDLZKA-2))+(YZACIATOK+1);
        gotoXY(jedlo.x , jedlo.y);
        printf("#");
    }
    else
    {
        gotoXY(jedlo.x , jedlo.y);
        printf("#");
    }
}



void koment(void)
{
    gotoXY(XZACIATOK, YZACIATOK-1);
    printf("Dlzka = %d", snake_dlzka);
    gotoXY(XKONIEC-7, YZACIATOK-1);
    printf("Zivoty: %d", zivot);
}





void ukoncenie(void)
{
    system("cls");
    printf("\n\n\tKoniec hry\n\tDakujeme ze ste vyuzili sluzby skupiny A.M.O.R");
    exit(0);
}



void game_over(void)
{
    int channel;
    gotoXY(XZACIATOK+(XKONIEC-XZACIATOK)/2-9,YKONIEC+2);
    printf("GAME OVER !");
    gotoXY(XZACIATOK+(XKONIEC-XZACIATOK)/2-9,YKONIEC+3);
    nacitavanie(9);
    system("cls");
    zle_game:
    printf("\n\n\t\tGame OVER\n\n\tzvolte jednu z moznosti:\n->\t#1 pre hranie znovu\n->\t#2 pre ukoncenie\n->\t#3 pre ulozenie\n\t");
    scanf("%d",&channel);

    if(channel==1)
    {
        snake_dlzka=3;
        chod();
    }
    else if(channel==2)
    {
        //printf("dsadjkasdsa");
        ukoncenie();
        //return 0;
    }

    else if(channel==3)
        ulozit();
    else
    {
        printf("\n\n\n\t\tZadali ste nespravne cislo\n");
        nacitavanie(9);
        system("cls");
        printf("\n\n\t\tZadali ste nespravne cislo");
        goto zle_game;
    }
}



void ulozit(void)
{
    FILE *fw;
    char meno[100];
    if((fw=fopen("udaje.TXT","a+")) == NULL)
    {
        printf("\n\n\tNepoadilo sa otvorit");
    }
    system("cls");
    printf("Zadajte meno:\t\t");
    scanf("%s",meno);
    fprintf(fw,"%s %d",meno,snake_dlzka);
    printf("\n\n\t");
    fclose(fw);
    nacitavanie(9);
    ukoncenie();
}




void doprava(void)
{
    bod.x=hlava.x;
    bod.y=hlava.y;
    hlava.x++;
    hlava.y;
    gotoXY(hlava.x,hlava.y);
    printf(">");

    telo[0].x=bod.x;
    telo[0].y=bod.y;
    gotoXY(telo[0].x,telo[0].y);
    printf("*");

    for(int i=snake_dlzka ; i>0 ; i--)
    {
        telo[i].x=telo[i-1].x;
        telo[i].y=telo[i-1].y;
        gotoXY(telo[i].x,telo[i].y);
        printf("*");
    }
}

void dolava(void)
{
    bod.x=hlava.x;
    bod.y=hlava.y;
    hlava.x--;
    hlava.y;
    gotoXY(hlava.x,hlava.y);
    printf("<");

    telo[0].x=bod.x;
    telo[0].y=bod.y;
    gotoXY(telo[0].x,telo[0].y);
    printf("*");

    for(int i=snake_dlzka ; i>0 ; i--)
    {
        telo[i].x=telo[i-1].x;
        telo[i].y=telo[i-1].y;
        gotoXY(telo[i].x,telo[i].y);
        printf("*");
    }
}


void dole(void)
{
    bod.x=hlava.x;
    bod.y=hlava.y;
    hlava.x;
    hlava.y++;
    gotoXY(hlava.x,hlava.y);
    printf("V");

    telo[0].x=bod.x;
    telo[0].y=bod.y;
    gotoXY(telo[0].x,telo[0].y);
    printf("*");

    for(int i=snake_dlzka ; i>0 ; i--)
    {
        telo[i].x=telo[i-1].x;
        telo[i].y=telo[i-1].y;
        gotoXY(telo[i].x,telo[i].y);
        printf("*");
    }
}


void hore(void)
{
    bod.x=hlava.x;
    bod.y=hlava.y;
    hlava.x;
    hlava.y--;
    gotoXY(hlava.x,hlava.y);
    printf("A");

    telo[0].x=bod.x;
    telo[0].y=bod.y;
    gotoXY(telo[0].x,telo[0].y);
    printf("*");

    for(int i=snake_dlzka ; i>0 ; i--)
    {
        telo[i].x=telo[i-1].x;
        telo[i].y=telo[i-1].y;
        gotoXY(telo[i].x,telo[i].y);
        printf("*");
    }
}

