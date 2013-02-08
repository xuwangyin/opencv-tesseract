cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)

project(opencv-tesseract)

set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++0x ")

add_executable(opencv-tesseract opencv-tesseract.cpp)

# find opencv package
find_package( OpenCV REQUIRED )

# includes
set(LEPTONICA_INCLUDE_PATH "/usr/include/leptonica")
set(TESSERACT_INCLUDE_PATH "/usr/local/include/tesseract")
include_directories(${OpenCV_INCLUDE_DIRS} ${LEPTONICA_INCLUDE_PATH} ${TESSERACT_INCLUDE_PATH})

# libraries
set(LEPTONICA_LIBS "lept")
set(TESSERAC_LIBS "tesseract")
set(LIBS ${LIBS} ${OpenCV_LIBS} ${LEPTONICA_LIBS} ${TESSERAC_LIBS})
target_link_libraries(opencv-tesseract ${LIBS})
