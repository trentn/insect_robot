set(SERVO_CONTROLLER_SOURCES 
        src/servo_controller.c)
add_library(servo_controller ${SERVO_CONTROLLER_SOURCES})

set(LEG_CONTROL_SOURCES 
        src/leg_control.c)
add_library(leg_control ${LEG_CONTROL_SOURCES})

set(KINEMATICS_SOURCES 
        src/kinematics.c)
add_library(kinematics ${KINEMATICS_SOURCES})

target_include_directories(servo_controller PUBLIC "include")
target_include_directories(leg_control PUBLIC "include")
target_include_directories(kinematics PUBLIC "include")
