cmake_minimum_required(VERSION 3.22)
project(citrix_counters)

set(CMAKE_CXX_STANDARD 20)

set(CITRIX_XML ${CMAKE_CURRENT_SOURCE_DIR}/citrix.xml)
set(CITRIX_RC ${CMAKE_CURRENT_SOURCE_DIR}/src/citrix_counters.rc)

add_custom_command(
        OUTPUT ${CITRIX_RC}
        DEPENDS ${CITRIX_XML}
        COMMENT "Generating resources because the XML file was updated"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ctrpp citrix.xml -o src/citrix_counters.h -rc src/citrix_counters.rc
        VERBATIM
)

add_custom_target(citrix_counters_resources DEPENDS ${CITRIX_RC})
add_executable(citrix_counters
        ${CITRIX_RC} # Resource file where the counter names are defined
        src/main.cpp
        src/provider.cpp
        src/session.cpp
        src/random.cpp
        )
