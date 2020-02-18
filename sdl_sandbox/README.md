# SDL Sandbox

This folder contains a series of small functions used for testing the functionality of SDL2. Most
of the code is based on [LazyFoo's SDL tutorial](http://lazyfoo.net/tutorials/SDL/)

## File Overview

* `main.cpp`: contains main. Calls test functions.
* `exercises.h`: contains declarations for all exercises available.
* `exerciseN.cpp`: contains definition for a single exercise.
* `setup.h`: declarations for utility functions to set up and tear down SDL.
* `sdl.h`: re-exports SDL libraries with C linkage.

## Notes About Running

No matter what, there seems to be a leak of ~49kB from four contexts on my system. Since the values
are constant and all originate from within SDL itself, I'm assuming that these are one off leaks 
that don't affect anything and that will be reclaimed by the operating system anyway.

## Notes About SDL Functions

1. I'm pretty sure that setting `srcrect` and `dstrect` allows for slicing out parts of the overall 
texture, which I need for rendering tilesets. Leaving `srcrect` as null takes the entire texture, 
while a null `dstrect` applies the texture to the entire rendering target. The texture will be
stretched to fit. 
