# VULCAN
Pedagogical neutronics simulator with a primary focus on Criticality.
![image](https://github.com/AlexisFxValencia/VULCAN/assets/84465552/96ce3cb3-a13e-45e3-b849-450883b0d2ed)

# To use it on Windows
Download on github the win64 release.

Unzip it.

Execute then  VULCAN.exe

# To use it on Linux
to be completed...

# Manual
There is no manual yet but a word file (in french) to help you use it for explaning neutronics and criticality to your students or the public : 
Dossier_pedagogique_neutronics_simulator.docx

# Compilation
## Compilation on Linux
- git clone it
- cd VULCAN

dependencies : I copied the source code of the dependency for you to be sure to have the good version
- unzip the lib/external libraries and compile them with cmake.
     - for SFML : mkdir build && cd build and cmake .. is enough
     - for TGUI : cmake -S . -B build -D TGUI_BACKEND=SFML_GRAPHICS -D TGUI_SHARED_LIBS=FALSE

back to vulcan :
- mkdir build && cd build
- cmake ..



## Compilation on Windows
you need the compiled versions of SFML 2.5.1 and TGUI 0.9.5 for windows 64 bit. I could not copy them here for you because they are to big.
- As for now (2024) the following links work :
     -  https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip
     -  https://github.com/texus/TGUI/releases/download/v0.9.5/TGUI-0.9.5-VisualStudio-64bit-for-SFML-2.5.1.zip
- put the downloaded zip files in the lib folder and extract them there.
- replace the content of VULCAN CMakeLists by the content of CMakeLists_windows.
- mkdir build && cd build
- cmake ..
- open build/VULCAN.sln with visual studio (community 2022) and build a Release version from it. It should create a Release folder in the build folder.
- Visual studio won't be able to launch the executable so you should have an error message. Is is allright.
- copy the content of the common folder ("input_files" and "themes") in the build/Release folder
- copy the content of the bin folders of SFML and TGUI (the .dll) next to the executable (without -d in their name is enough for a release version of the executable)
- execute build/VULCAN.exe

