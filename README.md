# VULCAN
Pedagogical neutronics simulator with a primary focus on Criticality.
![image](https://github.com/AlexisFxValencia/VULCAN/assets/84465552/96ce3cb3-a13e-45e3-b849-450883b0d2ed)


# To use it on Linux
- Download on github the lastest lin64 release
- copy the archive in a VULCAN folder and cd there.
- tar -xvf <archive_name>
- ./VULCAN

# To use it on Windows
- Download on github the latest win64 release.
- Unzip it.
- Launch VULCAN.exe


# Manual
There is no manual yet but a word file (in french) to help you use it for explaning neutronics and criticality to your students or the public : 
Dossier_pedagogique_neutronics_simulator.docx

# Compilation
## Compilation (and run) on Linux
- git clone https://github.com/AlexisFxValencia/VULCAN.git
- cd VULCAN
- ./extract_libs.sh
It will unzip the dependencies in the lib folder

I copied for you the built version of SFML 2.5.1 for Linux in the lib folder (not the source files because there are too many dependencies). I copied for you the tgui 0.9.5 source code (SFML is its only dependency) which is used for generating the GUI (buttons, menubar...). You therefore have to build TGUI : 
- ./build_tgui.sh

The previous steps need only to be executed once. 
Now to compile VULCAN and launch it :
- ./build_and_run.sh


### Debug with VScode
prerequisite : same previous steps as compilation and run on Linux.

- ./build_and_run.sh -d
- there is a launch.json already written in the folder with a debug configuration.



## Compilation on Windows
- git clone https://github.com/AlexisFxValencia/VULCAN.git

you need the compiled versions of SFML 2.5.1 and TGUI 0.9.5 for windows 64 bit. I could not copy them here for you because they are to big.
- As for now (2024) the following links work :
     -  https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip
     -  https://github.com/texus/TGUI/releases/download/v0.9.5/TGUI-0.9.5-VisualStudio-64bit-for-SFML-2.5.1.zip
- put the downloaded zip files in the lib folder and extract them there.
- replace the content of VULCAN CMakeLists by the content of CMakeLists_windows.
- mkdir build && cd build
- cmake ..
- open build/VULCAN.sln with visual studio (community 2022) and build a Release version from it. It should create a Release folder in the build folder.
- Visual studio won't be able to launch the executable unless you right click on VULCAN in the solution explorer and set it as the startup project (otherwise ALL_BUILD is the startup project...)
- copy the content of the common folder ("input_files" and "themes") in the build/Release folder
- copy the content of the bin folders of SFML and TGUI (the .dll) next to the executable (without -d in their name is enough for a release version of the executable)
- execute build/VULCAN.exe in a terminal or click on play in visual studio.

