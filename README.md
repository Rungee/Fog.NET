# About

Fog.NET is C++/CLI wrapper of [Fog-Framework](http://code.google.com/p/fog/) that
is a high performance 2d vector graphics library which contains platform independent SVG engine and UI toolkit (optional). 

# Configuration & Compilation
1. Download Fog-Framework from http://code.google.com/p/fog/
2. Extract it into a directory with name Fog at the same level as Fog.NET. Fog directory should contain following folders: Build, Documentaion, Src, Util
3. Configure Fog (cmake) in order to create Visual Studio Solution.
4. Configure Fog Project in the following way: 
   4.1. General -> Output directory: Bin\$(Configuration)\$(PlatformShortName)\
   4.2. C/C++ -> Additional Include Directory: ../Src
   4.3. Linker-> Advanced -> Import Library: Bin/$(Configuration)/$(PlatformShortName)/$(ProjectName).$(PlatformShortName).lib
5. Build
6. To run C# Demo application one needs to copy Fog.x86.dll or Fog.x64.dll into the directory with *.exe from Build\Bin\Debug(Release)


# License

Fog.NET is free and is released under MIT License. Please see [License](https://github.com/Rungee/Fog.NET/blob/master/LICENSE.md) for more information.
