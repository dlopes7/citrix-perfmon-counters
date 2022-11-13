cmake_minimum_required(VERSION 3.22)
project(citrix_counters)

set(CMAKE_CXX_STANDARD 20)

set(CITRIX_XML ${CMAKE_CURRENT_SOURCE_DIR}/citrix.xml)
set(CITRIX_RC ${CMAKE_CURRENT_SOURCE_DIR}/citrix_counters.rc)

add_custom_command(
        OUTPUT ${CITRIX_RC}
        DEPENDS ${CITRIX_XML}
        COMMENT "Generating resources because the XML file was updated"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ctrpp citrix.xml -o citrix_counters.h -rc citrix_counters.rc
        VERBATIM
)

add_custom_target(citrix_counters_resources DEPENDS ${CITRIX_RC})
add_executable(citrix_counters
        main.cpp  # Entry point
        ${CITRIX_RC} # Resource file where the counter names are defined
        ICASessionInstance.cpp ICASessionInstance.h
        CitrixProvider.cpp CitrixProvider.h
        Random.cpp Random.h
        )
