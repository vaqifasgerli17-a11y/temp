cmake_minimum_required(VERSION 3.16)
project(temp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bu iki sətir C++ obyektlərinin QML-ə keçməsi üçün MOC xətasını həll edir:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Lazım olan Qt komponentlərini tapırıq
find_package(Qt6 REQUIRED COMPONENTS Gui Qml Quick QuickControls2 SerialPort)

# Əvvəlcə executable-ı yaradırıq
qt_add_executable(apptemp
    main.cpp
    serialmanager.h
    serialmanager.cpp
)

# QML resurs fayllarını əlavə edirik
qt_add_qml_module(apptemp
    URI temp
    VERSION 1.0
    QML_FILES Main.qml
)

# Kitabxanaları layihəyə bağlayırıq (executable yarandıqdan SONRA)
target_link_libraries(apptemp
    PRIVATE Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::SerialPort
)

include(GNUInstallDirs)
install(TARGETS apptemp
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
