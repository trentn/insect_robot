set(SUBDIRS
        servo_controller
        leg_control
        kinematics)

foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
endforeach()