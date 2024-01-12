cmake_minimum_required(VERSION 3.10)
project(VULCAN)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)
add_executable(VULCAN ${SOURCES} ${HEADERS})
include_directories(include)


#SFML dependency
set(SFML_DIR lib/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1)
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
target_include_directories(VULCAN PRIVATE ${SFML_DIR}/include)
target_link_libraries(VULCAN PRIVATE sfml-graphics sfml-system)


#TGUI dependency
set(TGUI_AV lib/TGUI-0.9.5)
set(TGUI_DIR ${TGUI_AV}/build)
find_package(TGUI 0.9.5 REQUIRED)
target_link_libraries(VULCAN PRIVATE tgui)


#GUI module, which depends on SFML and TGUI
file(GLOB GUI_SOURCES src/GUI/*.cpp)
file(GLOB GUI_HEADERS include/GUI/*.hpp)
add_library(GUILib ${GUI_SOURCES} ${GUI_HEADERS})
target_include_directories(GUILib PUBLIC include/GUI)
target_include_directories(GUILib PUBLIC ${TGUI_AV}/include)
target_link_libraries(GUILib PUBLIC sfml-graphics sfml-system)
target_include_directories(GUILib PUBLIC include)
target_link_libraries(GUILib PRIVATE tgui)


#plotter module, which depends on SFML
file(GLOB plotter_SOURCES lib/plotter/src/*.cpp)
file(GLOB plotter_HEADERS lib/plotter/include/*.hpp)
add_library(plotterLib ${plotter_SOURCES} ${plotter_HEADERS})
target_include_directories(plotterLib PUBLIC lib/plotter/include)
target_link_libraries(plotterLib PUBLIC sfml-graphics)
target_link_libraries(VULCAN PRIVATE GUILib plotterLib)



# Copy content of the common folder in the build folder (themes and input files)
set(SOURCE_DIR common)
set(DESTINATION_DIR .)
file(COPY ${SOURCE_DIR}/ DESTINATION ${DESTINATION_DIR})






