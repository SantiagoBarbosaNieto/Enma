# Enma 
This is an implementation of a game engine following the [Game Engine](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) series from The Cherno ([YouTube](https://www.youtube.com/c/TheChernoProject), [GitHub](https://github.com/TheCherno))

## Setup
Currently there is no release for this application. For the project setup, VisualStudio Community is required and to generate the solution just run the Setup.bat script from the folder Scripts. It should generate the solution ready to run. 

## What is it really? 
Enma is currently a simple 2D renderer that supports batch rendering for both quads and textures. It is not much of a game engine, since there are not many tools implemented to facilitate game creation with it. But one could definitely  create a game with this 2D renderer as it is, so I'll still call it a game engine.

![Enma_SandboxShowcase_5mb](https://github.com/SantiagoBarbosaNieto/Enma/assets/60375386/fa3c28ac-cc00-4d1e-a9be-cb1dca7428a9)

## Interesting features
- #### Layers
The app is coded as a layered app. The application can have multiple layers implemented to handle different things. For example, the game engine itself is made out of two main layers. the renderer that is the default layer, and an extra implemented imgui layer on top of it for debug and input purposes.

- #### Rendering API
The game engine is coded with a layer of abstraction from the rendering API. Currently it only has support for OpenGL, but twith the abstraction layer, giving support to other rendering libraries such as vulkan would be possible (but not easy at all! the abstraction of rendering to still get the control vulkan gives is hard)

- #### Rendering
It currently supports rendering quads and textures, with modifiable position, color tint, rotation, size, and tiling size. It makes batches of multiple quads for a single draw call.

- #### Sandbox App
It is really easy to create an application on top of the game engine to utilize all of its features:
You just have to create the application and start implementing layers to it.
  
  ![image](https://github.com/SantiagoBarbosaNieto/Enma/assets/60375386/ebba270b-5335-4b61-b8e5-8b269955f429)

  


- #### Profiling
Has a custom profiling functionality integrated! Using EM_PROFILE_FUNCTION() and EM_PROFILE_SCOPE you can gather information of either a function or an entire scope, give it a name, and later see it all visually within a chrome browser.
![image](https://github.com/SantiagoBarbosaNieto/Enma/assets/60375386/e5eeb2ca-d18f-40a2-af7b-9680bcba6126)

![image](https://github.com/SantiagoBarbosaNieto/Enma/assets/60375386/df67abc2-6679-46c0-906d-a7800e2cbf8a)




