Name: Ian Meadows

## Cool Thing Done:
- I figured out how to make things transparent so for the Complex Objects there is a trasparent texture applied to them and there is also a trasparent color applied to them.


## building
- To build use make.
- To clean use make clean
- note: I got the make file from a friend that found it online. I modified it to work with OpenGL


## running
- Run the hw4 file that is generated. ./hw6

## Exit
- To exit use the ESC key

## View
- to alternate between view modes use 'p' or 'P' keys
- To rotate the view around use the arrow keys
- To move when in First person mode use the w,a,s,d keys
- note: up and down viewing is limited to 90 degrees up and down to fix vector swapping


## references
- I used code from gears.c, ex7.c, ex8.c, ex9.c, ex13, ex14, and ex15
- I used information from: https://learnopengl.com/Getting-started/Camera
    to produce a first person camera


I spent around 5-6 hours on this assignment





note: might segfault when closing or opening, but I can't get it to continuously reproduce
    - this could be a makefile bug when building the project after updating a file in the 
    project. To fix this call make clean and rebuild the project