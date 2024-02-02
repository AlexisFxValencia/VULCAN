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
- put them in the lib folder.
- replace the content of the CMakeLists by the content of CMakeLists_windows.
- mkdir build && cd build
- cmake ..
- open the .sln file with visual studio (community 2022) and build a Release version. It should create a Release folder in the build folder.
- copy the content of the common folder ("input_files" and "themes") inthe build/Release folder
- copy the content of the bin folders of SFML and TGUI next to the executable (not with -d for the release version)

