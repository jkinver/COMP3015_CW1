# COMP3015_CW1

## Visual Studio Version:
Visual Studio 2022

## Operating System:
Windows 10

## How does it work?
There are four primary files that allow this program to function: main, scenebasic_uniform, the vertex shader, and the fragment shader. main is the simplest of the four, as it only runs the program itself. scenebasic_uniform is what contains the majority of the code. It defines the object (.obj) files to be loaded; how OpenGL should draw the object(s); how the GL lighting should be configured; what textures should be loaded onto the object(s); and the model, view, and projection matrices that enable the object to be rendered and visible in the viewport. scenebasic_uniform has a main file to run the above (.cpp) and a header file to use include statements for relevant files and to define the base class’ variables and methods.
The vertex and fragments shaders are what define information regarding colour and lighting and implement the different models of lighting, such as “cel shading” and fog effects. Only basic lighting is implemented in this project, due mostly to time constraints and illness, but it is demonstrated nonetheless. Generally, the vertex shader takes information that the fragment shader cannot gather alone and sends it across, such that the fragment shader may use that information to better shade a scene – per-fragment shading regards individual pixels, rather than vertices in the space.

## What’s it worth?
Briefly, a note on what marking band seems most fitting from my perspective as the student. The 40-50 mark range is satisfied completely, according to the rubric, and hence I believe my mark should push into the 50 – 60 range. The presence of multiple lights and textures may lend me points too, but the lack of a skybox (instead, I’ve opted for a plane) prevents breaching into the 60 – 70 range.

## Unlisted YouTube video:
https://youtu.be/nkQmhyuFh5Y

## GitHub Repository Link:
https://github.com/jkinver/COMP3015_CW1 


 

