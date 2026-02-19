# DVD-CLI-Screensaver
Just a **shitty but fun** retro bouncing DVD screensaver imitation for CLI. (tbh at this point I can't call it 'shitty anymore but it stays for the vibe)

Because who needs a life when you can watch a rainbow rectangle defile your terminal till hit corner (spoiler I never checked if it hits or not...(update from V3 It fucking does hit the corner))

# Table Of Content

* [**Features**](#features-current-version-v3)

* [In Development(Empty)](#in-development-features)

* [Compile&Run](#compile--run)


## Features (Current Version V3)

> - Bouncing "DVD" text 
>
> - Psychedelic truecolor rainbow cycling because why a plain white text when you can get epilepsy seizures 
>
> - Hides cursor/Brings backs when program terminated with Ctrl+C (yeah don't kill terminal for nothing lol)
>
> - Dynamic window size detection 
>
> - Better dynamic window handling with SIGWINCH(this was for you nerds)
>
> - Random starting point for each run
>
> - Corner detection 
>
> - Reduced Jitter and optimized CLI clearing 
>
> - I added a cursed version as another file without trail clearing so it leaves everything on screen perfectly cursed.
> 
> - Custom text input via CLI explained in Compile&Run
>
> - - custom text feature via CLI arguments (./filename.o "I am gay" (c'mon it's RGB so you have to use it like that))

## **In Development Features**

 


## Compile & Run

```bash

cc dvd.c -o dvd -lm     #lm for lib math yk.

./dvd #For default DVD text

./dvd "YOUR TEXT" #For text(it has cap of 32 letters fyi)  
#Ctrl+C for exit 
```
