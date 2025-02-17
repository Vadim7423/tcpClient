cmake_minimum_required(VERSION 3.16)

project(testQtClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH ${QT_CMAKE_DIR})

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(apptestQtClient
    main.cpp
)

qt_add_qml_module(apptestQtClient
    URI testQtClient
    VERSION 1.0
    QML_FILES
        Main.qml
        ui/ConnectionRow.qml
        ui/VoltMetersList.qml
        ui/VoltMeter.qml
        ui/StatusesRow.qml
    SOURCES
        tcp/tcp_client.h
        tcp/boost_tcp_client.h tcp/boost_tcp_client.cpp
        client_handler.h client_handler.cpp
        app.h app.cpp
        model/volt_meteers_model.h model/volt_meteers_model.cpp
        model/range.h model/range.cpp model/channel.h model/channel.cpp
        protocol/protocol.h
        protocol/client_protocol.h protocol/client_protocol.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apptestQtClient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apptestQtClient
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptestQtClient
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apptestQtClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
