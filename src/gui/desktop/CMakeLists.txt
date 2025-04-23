cmake_minimum_required(VERSION 3.16)

project(game_5 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(NOT DEFINED CMAKE_PREFIX_PATH)
    if(WIN32)
        file(GLOB USER_QT_PATHS "$ENV{USERPROFILE}/Qt/6.*/gcc_*")
    else()
        file(GLOB USER_QT_PATHS "$ENV{HOME}/Qt/6.*/gcc_*")
    endif()
    foreach(path ${USER_QT_PATHS})
        if(EXISTS "${path}/lib/cmake/Qt6")
            list(APPEND CMAKE_PREFIX_PATH "${path}")
            message(STATUS "Using guessed Qt path: ${path}")
            break()
        endif()
    endforeach()
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)



set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
set(SRC_DIR ${ROOT_DIR}/src)
set(BUILD_DIR ${ROOT_DIR}/build)
set(LIB_SRC_DIR ${SRC_DIR}/brick_game)
set(FIRST tetris)
set(SECOND s-snake)
set(FIRST_DIR ${LIB_SRC_DIR}/${FIRST})
set(SECOND_DIR ${LIB_SRC_DIR}/snake)


set(PROJECT_SOURCES
    gui.cpp
    gamewindow.cpp
    gamewindow.h
    gamewindow.ui
    Colors_c.tpp
    gridscene_.h
    gridscene_.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(game_5
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
      add_executable(game_5
          ${PROJECT_SOURCES}
      )
endif()

target_link_libraries(game_5 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


add_library(gamelib STATIC IMPORTED)

if(TE_TRIS)
    target_include_directories(game_5 PRIVATE ${FIRST_DIR})
    set_target_properties(gamelib PROPERTIES
        IMPORTED_LOCATION "${BUILD_DIR}/${FIRST}.a"
        INTERFACE_INCLUDE_DIRECTORIES "${FIRST_DIR}"
    )
    target_compile_definitions(game_5 PUBLIC TE_TRIS)
elseif(S_SNAKE)
    target_include_directories(game_5 PRIVATE ${SECOND_DIR})
    set_target_properties(gamelib PROPERTIES
        IMPORTED_LOCATION "${BUILD_DIR}/${SECOND}.a"
        INTERFACE_INCLUDE_DIRECTORIES "${SECOND_DIR}"
    )
    target_compile_definitions(game_5 PUBLIC S_SNAKE)
endif()

target_link_libraries(game_5 PRIVATE gamelib)



target_compile_options(game_5 PUBLIC
    -Wall
    -Wextra
    -Werror
    -O2         # Optimization
    -D_POSIX_C_SOURCE=201706L
)

if(APPLE)
    set_target_properties(game_5 PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
    )
elseif(WIN32)
    set_target_properties(game_5 PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()


# include(GNUInstallDirs)
# install(TARGETS game_5
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game_5)
endif()
