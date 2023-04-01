cmake_minimum_required(VERSION 3.24)
project(WFC_Image_Generator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(WFC_Image_Generator main.cpp src/view/PatternWidget.cpp src/view/PatternWidget.h src/model/Generator.cpp src/model/Generator.h src/view/MainWidget.cpp src/view/MainWidget.h src/view/InputImgPreview.cpp src/view/InputImgPreview.h src/model/Utils/vec2D.h src/model/Utils/Direction.h src/model/Rule/Rule.cpp src/model/Rule/Rule.h)
target_link_libraries(WFC_Image_Generator
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

