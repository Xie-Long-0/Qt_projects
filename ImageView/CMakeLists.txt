cmake_minimum_required(VERSION 3.18)

project(ImageView VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 向编译器添加编译选项
if (MSVC)
    add_compile_options(/W3 /utf-8)
else()
    add_compile_options(-Wall -utf-8)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# 源文件列表
set(SOURCES
    main.cpp
    widget.cpp
    ImageView.cpp
)

# 头文件列表
set(HEADERS
    widget.h
    ImageView.h
)

# UI 文件列表
set(UIS
    widget.ui
)

# 生成可执行文件
add_executable(ImageView ${SOURCES} ${HEADERS} ${UIS})

# 链接Qt库
target_link_libraries(ImageView PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 添加 Widgets 模块的头文件路径
target_include_directories(ImageView SYSTEM PUBLIC
    ${Qt${QT_VERSION_MAJOR}Widgets_INCLUDE_DIRS}
)
