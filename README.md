# DVD-CLI-Screensaver
Just a **shitty but fun** retro bouncing DVD screensaver imitation for CLI. (tbh at this point I can't call it 'shitty anymore but it stays for the vibe)

Because who needs a life when you can watch a rainbow rectangle defile your terminal till hit corner (spoiler I never checked if it hits or not...(update from 2.01Beta I'll do check tomorrow, I swear I'll do, one stranger that starred this repo))

# Table Of Content

* [**Features**](#features-curret-version-v201beta)

* [In Development](#in-development-features)

* [Compile&Run](#compile--run)


## Features (Curret version V2.01Beta)

> Bouncing "DVD" text 
>
> Psychedelic truecolor rainbow cycling because why a plain white text when you can get epilepsy seizures 
>
> Hides cursor/Brings backs when program terminated with Ctrl+C (yeah don't kill terminal for nothing lol)
>
> Dynamic window size detection 
>
> Better dynamic window handling with SIGWINCH(this was for you nerds) **DONE**


## In Development Features

- Corner detection and something will trigger when it hits to corner which I haven't thought of yet *Currnetly In Dev*

- custom text feature via CLI arguments 

- Maybe toggle for plain white text/RGB or BOLD/Normal via CLI arguments idk...it's 1.25AM here



## Compile & Run

```bash

cc dvd.c -o dvd -lm     #lm for lib math yk.

./dvd  
#Ctrl+C for exit 
```
