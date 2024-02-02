# VULCAN
Pedagogical neutronics simulator with a primary focus on Criticality.


## Compilation for Linux
- git clone it
- cd VULCAN

dependencies : I could copy the source code of the dependency to be sure to have the good version
- unzip the lib/external libraries and compile them with cmake.
     - for SFML : mkdir build && cd build and cmake .. is enough
     - for TGUI : cmake -S . -B build -D TGUI_BACKEND=SFML_GRAPHICS -D TGUI_SHARED_LIBS=FALSE

back to vulcan :
- mkdir build && cd build
- cmake ..



## Compilation for Windows
you need the compiled versions of SFML 2.5.1 and TGUI 0.9.5 for windows 64 bit.
- for example :
     -  https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip
     -  https://github.com/texus/TGUI/releases/download/v0.9.5/TGUI-0.9.5-VisualStudio-64bit-for-SFML-2.5.1.zip
- put them in the lib folder and extract them there.
- replace the content of the CMakeLists by the content of CMakeLists_windows.
- mkdir build && cd build
- cmake ..
- open build/VULCAN.sln with visual studio (community 2022) and build a Release version from it. It should create a Release folder in the build folder.
- visual studio won't be able to launch the executable so you whould have an error message. Is is allright.
- copy the content of the common folder ("input_files" and "themes") inthe build/Release folder
- copy the content of the bin folders of SFML and TGUI next to the executable (not with -d for the release version)
- execute build/VULCAN.exe

