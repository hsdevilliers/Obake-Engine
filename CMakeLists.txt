cmake_minimum_required(VERSION 3.3)
project(OBAKE)

include_directories(include)


#add_executable(OBAKE ${SOURCE_FILES})

#LINK_DIRECTORIES("ddd/lib/*")

#find_package(PkgConfig REQUIRED)
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#INCLUDE_DIRECTORIES(ddd/include/SDL)
#TARGET_LINK_LIBRARIES(OBAKE ${SDL2_LIBRARIES})



#mingw32, libSDL2main, libSDL2, opengl32, glew32

# configure the SDL (cf. "SDL2-2.0.3\i686-w64-mingw32\lib\pkgconfig\sdl2.pc")
# C++ flags
set(SDL2_Flags "-mwindows -Wl,--no-undefined -static-libgcc")
# library paths
set(SDL2_ROOT     "D:/Work/OBAKE/Resources/SDL2/SDL2-2.0.4/i686-w64-mingw32")
set(GLEW_ROOT     "D:/Work/OBAKE/Resources/glew-1.13.0")

set(SDL2_Includes "${SDL2_ROOT}/include")
set(SDL2_LibDir   "${SDL2_ROOT}/lib")
set(GLEW_Includes "${GLEW_ROOT}/include")
set(GLEW_LibDir   "${GLEW_ROOT}/lib/Release/Win32")#D:\Work\OBAKE\Resources\glew-1.13.0\lib\Release\Win32

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug")

# imported targets for CMake (cf. https://cmake.org/Wiki/CMake/Tutorials/Exporting_and_Importing_Targets)
add_library(SDL2     STATIC IMPORTED)
add_library(SDL2main STATIC IMPORTED)
add_library(glew32   STATIC IMPORTED)
set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2.a")
set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2main.a")
set_property(TARGET glew32   PROPERTY IMPORTED_LOCATION "${GLEW_LibDir}/glew32.lib")

#INCLUDE_DIRECTORIES(GLEW_Includes)
# the libs to link against
# note: as always with gcc, the order is important...
set(SDL2_Libs mingw32 SDL2 SDL2main m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid glew32 opengl32)

# configure the project
# include the SDL flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${SDL2_Flags}")

file(GLOB SOURCE_FILES "src/*.cpp" "*.cpp")
# define the target
add_executable(OBAKE ${SOURCE_FILES})
# include the SDL headers
target_include_directories(OBAKE SYSTEM PRIVATE ${SDL2_Includes} ${GLEW_Includes})
# link against the SDL (and its dependencies)
target_link_libraries(OBAKE ${SDL2_Libs})