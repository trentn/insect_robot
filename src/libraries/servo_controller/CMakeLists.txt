set(SOURCES 
        src/servo_controller.c)
add_library(servo_controller ${SOURCES})

target_include_directories(servo_controller PUBLIC
                            "include")