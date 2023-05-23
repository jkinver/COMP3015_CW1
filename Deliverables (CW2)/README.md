# COMP3015 CW2

## Visual Studio Version:
Visual Studio 2022

## Operating System:
Windows 10

## How does it work?
Similarly to its first iteration, there are four primary files: main.cpp, scenebasic_uniform.cpp (and its header), the vertex shader, and the fragment shader. As before, main.cpp runs the program. scenebasic_uniform (the header and the cpp file) works to identify which OBJ files to load, how to draw them through OpenGL, how the lighting should be configured, and how to use the MVP (model-view-projection) format to display the result. Unlike last time, however, there are no textures loaded into this program, as the more advanced technique that was used was Edge Detection. This makes it so that the loaded model, and the plane above which it is suspended, are completely blacked out with only the outlines of their triangle components visible. The contrast is very noticeable. Additionally, there exists a simple function, with extra variables defined from the header, to enable the camera to rotate about the object loaded. This again makes it slightly more advanced than the original version.
The vertex and fragment shaders are what do most of the heavy lifting, so to speak. There are additional functions from last time to enable edge detection. And, as much as cel shading was heavily desired, time constraints and programming problems once again opposed. Multiple lights have returned, although it is difficult to discern given the edge detection, and these prove my capability for coding the project - normally, it is written with a single light in mind, so it is evident that a base understanding is present.
The vertex shader passes information on to the fragment shader, a little more so than last time, and allows the fragment shader to draw per-pixel rather than per-vertex. Arguably, a vertex shader would be more appropriate here with regards to efficiency, but having both is again more evidence of knowledge, which is inherently useful. 

## What's it worth?
Once again, a brief outline shall be detailed regarding thoughts on marking. The range in which this project falls is lower, this time. Once again, time constraints proved troublesome, as too did mental health struggles, leading to a project that only serves as a baseline. Regardless, it is at least complex enough for a pass. The lack of any features beyond edge detection and camera rotation (and beyond that which already were present) lands a solid 40 when combined with the video explanation of the project. With any luck, the robustness of the code alongside a sufficiently detailed description, as well as the detail of GitHub's commits will take it to around 45, but this cannot be known for sure until it is officially marked. 

## Unlisted YouTube video:
https://youtu.be/E2QL38t2J20

## GitHub repo link:
https://github.com/jkinver/COMP3015_CW1 
