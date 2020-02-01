set(SUBDIRS
        servo_controller
        leg_control)

foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
endforeach()