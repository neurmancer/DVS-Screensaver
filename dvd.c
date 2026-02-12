#include <stdio.h>
#include <unistd.h> // For usleep
#include <string.h>
#include <math.h>   // For sin()
#include <stdlib.h>

int main(int argc, char** argv)
{
    setvbuf(stdout,NULL, _IONBF,0);
    int height;
    int width;
    if(argc>1)
    {
        width = atoi(argv[1]);
        height = atoi(argv[2]);

    }
    else
    {
        width=230;
        height=65;
    }
    printf("\033[?25l"); 

    int ballX = 3;
    int ballY = 5;
    int vertical = 1;
    int velocity = 1;
    
    long color_timer = 0; 

    while(1)
    {
        printf("\033[H\033[J"); 

        printf("\033[%d;%dH", ballY, ballX);

        const char *text = "DVD";
        

        for(int i = 0; i < 3; i++) {
            double freq = 0.35;

            int r = (sin(freq * i + color_timer * 0.2 + 0) * 127) + 128;
            int g = (sin(freq * i + color_timer * 0.2 + 2) * 127) + 128;
            int b = (sin(freq * i + color_timer * 0.2 + 4) * 127) + 128;

            printf("\033[38;2;%d;%d;%dm%c", r, g, b, text[i]);
        }
        
        printf("\033[0m"); // Reset color logic
//        fflush(stdout);    overwritten by setvbuf 

        if(ballX <= 0 || ballX >= (width-3)) {
            velocity *= -1;
        }
        if(ballY <=1 || ballY >= height) {
           vertical *= -1; 
        }
        
        ballY += vertical;
        ballX += velocity;

        color_timer++;

        usleep(90780); //I pulled that up from my ass so deal with it. 
    }
    return 0;
}
