#include <stdio.h>
#include <unistd.h> // For usleep
#include <string.h>
#include <math.h>   // For sin()
#include <stdlib.h>
#include <signal.h> 

#define MS_PER_FRAME 85000
#define FREQ 0.35

void sigIntHandler(int sig); 

int main(int argc, char** argv)
{
    printf("\033[?25l"); 
    setvbuf(stdout,NULL, _IONBF,0);
    int height;
    int width;
    
    //Installing SIGINT Handler
    signal(SIGINT,sigIntHandler);

    printf("To exit press Ctrl+C");
    sleep(1);

    if(argc>2)
    {
        width = atoi(argv[1]);
        height = atoi(argv[2]);

    }
    else
    {
        width=230;
        height=65;
    }


    int ballX = 5;
    int ballY = 5;
    int dy = 1;
    int dx = 1;
    
    long color_timer = 0; 

    while(1)
    {
        printf("\033[H\033[J"); 

        printf("\033[%d;%dH", ballY, ballX);

        const char *text = "DVD";
        
        if(ballX <= 1 || ballX >= (width-strlen(text))) 
        {
            dx *= -1;
        }
        if(ballY <=1 || ballY >= height) 
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