# GDShader Lab

Tools, utils and documentations for porting shaders from other systems to GoDot GDShaders.

## Introduction

[Godot](https://github.com/godotengine/godot) is a great open-source game engine capable to great extents. It can create both 2D and 3D games, with wide community support on addons and assets.

No game graphics development can avoid the topic of [Shading](https://en.wikipedia.org/wiki/Shading). Like any game engine, godot provides its own [shader framework](https://docs.godotengine.org/en/stable/tutorials/shaders/introduction_to_shaders.html). A shading [language](https://docs.godotengine.org/en/stable/tutorials/shaders/shader_reference/shading_language.html#doc-shading-language) close to GLSL ES 3.0 is designed with the intent to make writing shaders easier and more approachable for most game developers.

While this is a noble goal, and it does work well for anyone who would like to write their shaders from scratch, it unfortunately creates a natural barrier for anyone who would like to switch to an open-source solution but would like to reuse previous work done else where. This is mainly because GLSL is **not** used a lot in the gaming industry.

Due to the prominent use of DirectX in the gaming industry in the previous decades, Microsoft's [HLSL](https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl) has became the de facto standard language for writing game shaders. Both of the most commercially used game engines, [Unity Engine](https://unity.com/) and [Unreal Engine](https://www.unrealengine.com/en-US), use HLSL variants as their shading language. [Slang](https://shader-slang.org/), the effort for a cross-platform shading language sponsored by [Khronos group](https://www.khronos.org/), is also adapting a language similar to HLSL in design.

Fortunately, the industry has moved forward from its closed past. With industry leaders like Microsoft and Khronos group building new open standards and tools (e.g. [spirv-cross](https://github.com/KhronosGroup/SPIRV-Cross) and [dxc](https://github.com/microsoft/DirectXShaderCompiler)), the porting process can now be assisted greatly by them. This repo serves as a collection of guides and documents about the use of these tools to port shaders to GoDot, as well as providing environments and missing tools to facilitate such goals.

