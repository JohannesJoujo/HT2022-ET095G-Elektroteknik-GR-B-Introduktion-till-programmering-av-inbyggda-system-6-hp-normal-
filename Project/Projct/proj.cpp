#include "C12832.h"
#include "mbed.h"
#include "RGBLed.h"
#include <cstdio>

bool gameover;
void input();
void logic();
void draw();
void setup();
void scored();
void printsnake();
void Gameover();
void presstoplay();
//used for directions in if statement
int rr=0, dd=0, u=0,ll=0;
//three same bitmaps for head, tail and food
static char jagj[]= {
   0xFF,
   0xFF,
   0xFF
};
static char jagjj[]= {
   0xFF,
   0xFF,
   0xFF
};
static char jagjjj[]= {
   0xFF,
   0xFF,
   0xFF
};
Bitmap jag = {3,3,1,jagj};
Bitmap jag2 = {3,3,1,jagjj};
Bitmap jag3 = {3,3,1,jagjjj};


AnalogOut port(p18);
C12832 lcd(p5,p7,p6,p8,p11);
DigitalIn d(p12);
DigitalIn l(p13);
InterruptIn center(p14);
DigitalIn up(p15);
DigitalIn r(p16);
//to use for coordinates for food and head
int x,y,fruitx,fruity,score;
enum directions {stop=0};
directions dir;
bool start=false;

RGBLed myRGBled(p23,p24,p25); //RGB PWM pins
AnalogIn ain(p19);
LocalFileSystem local("local");
int tailx[1000], taily[1000];

double tim = 1.001;
int value;

int main()
{
   center.rise(&setup);
   while (!start) {
    presstoplay();
   }
   while(!gameover) {
     draw();
       input();
       logic();
   }
}

// starts the game by setting gameover to false and the snakehead, food position
// + resetting the score every tyme player wants to play again
void setup()
{
   gameover=false;
   start=true;
   dir=stop;
   x=64;
   y=16;
   fruitx=rand() % 126;
   fruity=rand() % 30;
   score=0;
}
//shows the snake + food
void draw()
{

   lcd.cls();
   for(int i =0; i<32; i++) {

       for (int j=0; j<128; j++) {
           if(i == y && j == x) {
               lcd.locate(x,y);
               lcd.print_bm(jag,x,y);
               for(int n=1; n<score; n++) {
                   lcd.print_bm(jag3,tailx[n],taily[n]);
               }
               lcd.copy_to_lcd();
                wait(ain.read()/20);

           } else if (i == fruity && j== fruitx) {
               lcd.locate(fruitx,fruity);
               lcd.print_bm(jag2,fruitx,fruity);
               for(int n=1; n<score; n++) {
                   lcd.print_bm(jag3,tailx[n],taily[n]);
               }
               lcd.copy_to_lcd();
                //wait(ain.read()/20);
           }
       }

   }

}
//switches direction of the snake head when the joystick is toogled
void input()
{
   lcd.locate(x,y);
   lcd.cls();
   lcd.print_bm(jag,x,y);
   lcd.print_bm(jag2,fruitx,fruity);

   lcd.copy_to_lcd();

   if(r == 1 && x<=118 || rr==1) {
       rr = 1;
       dd=0;
       u=0;
       ll=0;
       x++;
       printsnake();
   }

   if(up == 1 && y>=1 ||u==1) {
       u = 1;
       rr = 0;
       dd=0;
       ll=0;
       y--;
       printsnake();
   }

   if(d == 1 && y<=28 || dd==1) {
       dd = 1;
       rr = 0;
       u=0;
       ll=0;
       y++;
       printsnake();
   }

   if(l == 1&& x>=1 || ll==1) {
       ll = 1;
       rr = 0;
       dd=0;
       u=0;
       x--;
       printsnake();
   }
   lcd.copy_to_lcd();
}


void logic()
{
    //logic for the tail to follow the snakehead
   int prevx=tailx[0];
   int prevy=taily[0];
   int prev2x, prev2y;
   tailx[0]=x;
   taily[0]=y;
   for (int i =1; i<score; i++) {
       prev2x=tailx[i];
       prev2y=taily[i];
       tailx[i]=prevx;
       taily[i]=prevy;
       prevx=prev2x;
       prevy=prev2y;

        //if the head touches the tail you lose
       if(tailx[i] == x && taily[i] == y) {
           gameover=true;
           Gameover();
       }
   }


 //if you go outside the lcd screen you lose
   if(x < 0 || x > 125) {
       gameover= true;
       Gameover();
   }
   if(y < 0 || y > 29) {
       gameover= true;
       Gameover();
   }
   //when the head meets the food call score function
   if(x==fruitx && y== fruity) {
       scored();
   } else if(x==fruitx && y==fruity+1) {
       scored();
   } else if (x==fruitx && fruity==y+2) {
       scored();
   } else if(x==fruitx+1 && y==fruity) {
       scored();
   } else if (x==fruitx+1 && fruity==y+1) {
       scored();
   } else if (x==fruitx+1 && fruity==y+2) {
       scored();
   }else if (x==fruitx+2 && fruity==y) {
       scored();
   }
   else if (x==fruitx+2 && fruity==y+2) {
       scored();
   }
   else if (x==fruitx+2 && fruity==y+2) {
       scored();
   }

   else if(x+1==fruitx && y==fruity+1) {
       scored();
   } else if (x+1==fruitx && fruity==y+2) {
       scored();
   } else if(x+2==fruitx+1 && y==fruity) {
       scored();
   } else if (x+2==fruitx+1 && fruity==y+1) {
       scored();
   } else if (x+1==fruitx+1 && fruity==y+2) {
       scored();
   }else if (x+1==fruitx+2 && fruity==y) {
       scored();
   }
   else if (x+2==fruitx+2 && fruity==y+2) {
       scored();
   }
   else if (x+2==fruitx+2 && fruity==y+2) {
       scored();
   }

}

// score function adds a score and switches the food to a random position
void scored()
{
   score++;

   if(score==5||score==10||score==15||score==20|| score==50||score==100) {
       myRGBled.setColor(RGBLed::GREEN);
       wait(0.001);
       myRGBled.setColor(RGBLed::BLACK);
       wait(0.001);
       myRGBled.setColor(RGBLed::GREEN);
       wait(0.001);
       myRGBled.setColor(RGBLed::BLACK);

   }
   fruitx=rand() % 128;
   fruity=rand() % 30;
}
// copy_to_lcd
void printsnake()
{
   lcd.cls();
   lcd.locate(x,y);
   lcd.print_bm(jag,x,y);
   lcd.print_bm(jag2,fruitx,fruity);
   lcd.copy_to_lcd();
}
// when the player loses they can see score and a message to play again, if they beat top score it saves in a file
void Gameover(){
if(gameover){
    lcd.cls();
    FILE* File1 = fopen("/local/datafile.txt","r");
    fscanf(File1,"%d",&value);
    fclose(File1);
    if(score > value){
    lcd.locate(0,0);
    lcd.printf("New high score is : %d", score);
    lcd.locate(0,19);
    lcd.printf("Press center to play again");
    FILE* File2 = fopen("/local/datafile.txt","w");
    fprintf(File1,"%d ", score);
    fclose(File2);
    wait(0.3);
    }else{
    lcd.locate(0,0);
    lcd.printf("Score: %d", score);
    lcd.locate(0,10);
    lcd.printf("Top score is : %d", value);
    lcd.locate(0,19);
    lcd.printf("Press center to play again");
    wait(0.3);
    }
    gameover=false;
    start=false;
    dir=stop;
    ll = 0;
    rr = 0;
    dd=0;
    u=0;
}

}
//shows the first time player logs in and want to play
void presstoplay(){
    FILE* File4 = fopen("/local/datafile.txt","r");
    fscanf(File4,"%d",&value);
    lcd.locate(0,0);
    lcd.printf("Top score is : %d", value);
    fclose(File4);
    lcd.locate(0,15);
    lcd.printf("Press center to play");
    wait(0.1);
}
