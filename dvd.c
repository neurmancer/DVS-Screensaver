#include <stdio.h>
#include <unistd.h> // For usleep
#include <string.h>
#include <math.h>   // For sin()
#include <stdlib.h>
#include <signal.h> 
#include <sys/ioctl.h>
#include <time.h>

#define MS_PER_FRAME 85000
#define SECOND 1000000 //Microseconds

void sigBitchHandler(int sig); //well it's sigWINCH but why not calling it bitch?
void sigIntHandler(int sig); 
enum Corner cornerCheck(int x,int y,int text_len,struct winsize win);


enum Corner { NO_CORNER, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

typedef struct 
{
    int x;
    int y;

    int dx;
    int dy;

    int lastX;
    int lastY;
}Logo;
 
struct winsize window;

int main(int argc,char *argv[])
{
    char *text;
    int textSize = 0;
    if (argc == 2)
    {
        text = (char *)malloc(strlen(argv[1])+1);
        strcpy(text,argv[1]);
        textSize = strlen(argv[1]);
        if (textSize > 32)
        {
            printf("Text is too long dude :/ \n");
            return(-1);
        }
    }
    
    else
    {
        text = (char *)malloc(sizeof(char)*4);
        strcpy(text,"DVD");
        textSize = 3;
    }
    

    printf("\033[?25l"); 
    setvbuf(stdout,NULL, _IONBF,0);
    srand(time(NULL));

    //Installing SIGINT Handler
    signal(SIGINT,sigIntHandler);
    //Installing Sigbitch
    signal(SIGWINCH,sigBitchHandler);

    ioctl(STDOUT_FILENO,TIOCGWINSZ,&window);

    printf("To exit press Ctrl+C");
    usleep(SECOND * 1.5);

    float FREQ = 0.35;
    Logo logo = {0,0,1,1};

    
    long color_timer = 0;


    logo.x = (rand() % window.ws_col-(textSize+5)) + 3;
    logo.y = (rand() % window.ws_row-10)+1;

    logo.lastX = logo.x;
    logo.lastY = logo.y;

    printf("\033[2J");
    
    int cornerPanicCounter = 0;
    int cornerFlag = 0;
    while(1)
    {    
        if (cornerFlag) { printf("\033[H\033[J"); }
        else { printf("\033[%d;%dH\033[K", logo.lastY, logo.lastX); } 


        printf("\033[%d;%dH", logo.y, logo.x);
        logo.lastX = logo.x;
        logo.lastY = logo.y;

        int corner = cornerCheck(logo.x,logo.y,textSize,window);
        if (corner)
        {
            printf("\a\a\a");
            FREQ = 0.75;
            logo.dx*=5;
            logo.dy*=3;
            cornerPanicCounter = 50;
            cornerFlag = 1;
        }
        if(logo.x <= 1 || logo.x >= (window.ws_col-textSize)) 
        {
            logo.dx *= -1;
        }
        if(logo.y <=1 || logo.y >= window.ws_row) 
        {
           logo.dy *= -1; 
        }


        for(int i = 0; i < textSize; i++) //Tried to make it dynamic 
        {

            int r = (sin(FREQ * i + color_timer * 0.2 + 0) * 127) + 128;
            int g = (sin(FREQ * i + color_timer * 0.2 + 2) * 127) + 128;
            int b = (sin(FREQ * i + color_timer * 0.2 + 4) * 127) + 128;

            printf("\033[38;2;%d;%d;%dm%c", r, g, b, text[i]);
        }
;
        
        printf("\033[0m"); // Reset color logic
//        fflush(stdout);    overwritten by setvbuf 

        
        logo.y += logo.dy;
        logo.x += logo.dx;

        color_timer++;
        if (cornerPanicCounter != 0) {cornerPanicCounter--;}
        
        else if(cornerPanicCounter == 0 && cornerFlag == 1)
        {
            cornerFlag = 0;
            FREQ = 0.35;
            logo.dx /= 5;
            logo.dy /= 3;
        }
        usleep(MS_PER_FRAME); //I pulled that up from my ass so deal with it. 
    }
    return 0;
}

void sigIntHandler(int sig)
{
    printf("\033[H\033[J"); 
    printf("\033[?25h");
    exit(0);
}

void sigBitchHandler(int sig)
{
    if (sig == SIGWINCH)
    {
        if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&window) == -1) { perror("The terminal size couldn't have been obtained");}
    }
    

}



enum Corner cornerCheck(int x, int y, int text_len, struct winsize win) {
    int right  = x + text_len - 1;
    int bottom = y;  // again, single line

    if (x <= 1 && y <= 1)               return TOP_LEFT;
    if (right >= win.ws_col-1 && y <= 1)  return TOP_RIGHT;
    if (x <= 1 && bottom >= win.ws_row) return BOTTOM_LEFT;
    if (right >= win.ws_col-1 && bottom >= win.ws_row) return BOTTOM_RIGHT;

    return NO_CORNER;
}

void textWriter(char *text,int textSize)
{

}