#include <stdio.h>
#include <unistd.h> // For usleep
#include <string.h>
#include <math.h>   // For sin()
#include <stdlib.h>
#include <signal.h> 
#include <sys/ioctl.h>


#define MS_PER_FRAME 85000
#define FREQ 0.35
#define SECOND 1000000 //Microseconds

void sigBitchHandler(int sig); //well it's sigWINCH but why not calling it bitch?
void sigIntHandler(int sig); 
int cornerCheck(int x,int y);


typedef struct 
{
    int x;
    int y;

    int dx;
    int dy;
}Logo;

struct winsize window;

int main(void)
{


    
    printf("\033[?25l"); 
    setvbuf(stdout,NULL, _IONBF,0);
    

    //Installing SIGINT Handler
    signal(SIGINT,sigIntHandler);
    //Installing Sigbitch
    signal(SIGWINCH,sigBitchHandler);

    printf("To exit press Ctrl+C");
    usleep(SECOND * 1.5);

    Logo logo = {5,5,1,1};
    
    
    const char *text = "DVD";
    
    long color_timer = 0; 

    while(1)
    {    

        printf("\033[H\033[J"); 
        printf("\033[%d;%dH", logo.y, logo.x);


        
        if(logo.x <= 1 || logo.x >= (window.ws_col-strlen(text))) 
        {
            logo.dx *= -1;
        }
        if(logo.y <=1 || logo.y >= window.ws_row) 
        {
           logo.dy *= -1; 
        }


        for(int i = 0; i < 3; i++) 
        {

            int r = (sin(FREQ * i + color_timer * 0.2 + 0) * 127) + 128;
            int g = (sin(FREQ * i + color_timer * 0.2 + 2) * 127) + 128;
            int b = (sin(FREQ * i + color_timer * 0.2 + 4) * 127) + 128;

            printf("\033[38;2;%d;%d;%dm%c", r, g, b, text[i]);
        }
        
        printf("\033[0m"); // Reset color logic
//        fflush(stdout);    overwritten by setvbuf 

        
        logo.y += logo.dy;
        logo.x += logo.dx;

        color_timer++;
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

int cornerCheck(int x,int y)
{

    

}