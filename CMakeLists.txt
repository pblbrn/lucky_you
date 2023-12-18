# Set cmake version
cmake_minimum_required(VERSION 3.10)

# Set Name of project and language
project(lucky_you LANGUAGES CXX)


# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Bluetooth TextToSpeech Core Widgets)
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDDEVICE REQUIRED libsystemd)
# Create executable using the specified src
INCLUDE_DIRECTORIES(${APP_INCLUDE_DIRS} src)
add_executable(${PROJECT_NAME}
    src/lucky_you.h src/lucky_you.cpp src/lucky_you.ui
    src/server.h src/server.cpp
    src/speak.h src/speak.cpp
    src/batterystatus.h src/batterystatus.cpp
    src/threaddata.h
    src/mugshot.h src/mugshot.cpp
    src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Bluetooth
    Qt::Core
    Qt::Widgets
    Qt6::TextToSpeech
)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDDEVICE_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDDEVICE_LIBRARIES}  ${OpenCV_LIBRARIES})

# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /W3>
)




