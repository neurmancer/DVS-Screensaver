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

void sigIntHandler(int sig); 

int main(void)
{

    struct winsize window;
    
    printf("\033[?25l"); 
    setvbuf(stdout,NULL, _IONBF,0);
    

    //Installing SIGINT Handler
    signal(SIGINT,sigIntHandler);

    printf("To exit press Ctrl+C");
    usleep(SECOND * 1.5);

    int ballX = 5;
    int ballY = 5;
    int dy = 1;
    int dx = 1;
    
    const char *text = "DVD";
    
    long color_timer = 0; 

    while(1)
    {
        if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&window) == -1) { perror("The terminal size couldn't have been obtained");return(-1);} 
        
        printf("\033[H\033[J"); 

        printf("\033[%d;%dH", ballY, ballX);


        
        if(ballX <= 1 || ballX >= (window.ws_col-strlen(text))) 
        {
            dx *= -1;
        }
        if(ballY <=1 || ballY >= window.ws_row) 
        {
           dy *= -1; 
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

        
        ballY += dy;
        ballX += dx;

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