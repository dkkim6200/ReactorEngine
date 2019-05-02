# ReactorEngine

## Introduction
Reactor Engine is a 3D Game Engine developed by Daekun Kim. It uses C++ as a main lanaguage. The goal is to create a multi-platform and platform-independent game engine, like Unity 3D or Unreal Engine. I know it would be hard, but I want to give it a try!

This engine implements a component-based architecture.

## Feature list
- [x] 3D Graphics
    - [x] OpenGL
    - [x] Texture loading
        - [x] BMP
        - [ ] PNG, JPEG
    - [x] Mesh loading
        - [x] OBJ
        - [ ] FBX
        - [ ] Bezier patches
    - [ ] Material
        - [x] Shaders (vertex and fragment)
    - [ ] Lighting
    - [ ] Animation
- [x] GLFW integration (Window, input, OpenGL context)
- [x] Event messaging system
    - [x] Pub/sub with callbacks
- [ ] Math libray
    - Vector3
    - Vector2
    - Matrix
    - Quaternion
- [ ] Custom containers (for ease of debugging and simplicity)
    - [ ] Linked List
    - [ ] Stack
    - [ ] Queue
    - [ ] Hash Table
- [ ] Input
    
## To-do list
- [ ] Level Editor
- [ ] Physics Engine
- [ ] Serialization / Deserialization
- [ ] Debugger logging/assertions
- [ ] Custom introspection
- [ ] Scripting API
    - Possible Language: Python (I know how to use it), Lua (Heard that it can be easily used on iOS)
    
## References
- Simple Engine Library
    - https://bitbucket.org/rgaul/sel/src/default/

Copyright (c) Daekun Kim 2016-2019
