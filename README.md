# DVD-Screensaver
Just a **shitty but fun** retro bouncing DVD screensaver imitation for CLI. 
Because who needs a life when you can watch a rainbow rectangle defile your terminal till hit corner (spoiler I never checked if it hits or not)?


## Features (I added)

- Bouncing "DVD" text 
- Psychedelic truecolor rainbow cycling because why a plain white text when you can get epilepsy seizures 
- Hides cursor/Brings backs when terminated with Ctrl+C
- Optional width/height args if your terminal isn’t built like a cinema screen



## Compile & Run

```bash

cc dvd.c -o dvd -lm 

./dvd   #for defult size(230x65)
./dvd  width height #for custom borders 
#Ctrl+C for exit 
