cmake_minimum_required(VERSION 3.9)

project(cptar VERSION 1.0.0 DESCRIPTION "c++ bindings libtar")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

set(SOURCE_FILES src/Tar.cpp src/TarException.cpp)

option(BUILD_SHARED_LIB "builld shared version" ON)

if(BUILD_SHARED_LIB)
    message("builld shared version")
    add_library( ${PROJECT_NAME} SHARED  ${SOURCE_FILES})
else()
    message("builld static version")
    add_library( ${PROJECT_NAME}  ${SOURCE_FILES})
endif()



target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)


set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1)



install(TARGETS ${PROJECT_NAME} EXPORT CptarConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(EXPORT CptarConfig DESTINATION share/Cptar/cmake)

export(TARGETS ${PROJECT_NAME} FILE CptarConfig.cmake)
