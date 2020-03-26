set(SOURCES 
        src/leg_control.c)

add_library(leg_control ${SOURCES})

target_link_directories(leg_control PUBLIC	
                            "${PROJECT_SOURCE_DIR}/src/libraries/servo_controller/include")

target_include_directories(leg_control PUBLIC
                            "include"
                            "${PROJECT_SOURCE_DIR}/src/libraries/servo_controller/include")
