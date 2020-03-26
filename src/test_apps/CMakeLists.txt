set(APPS
    inv_kin_test)

# order of libraries listed matters: https://stackoverflow.com/questions/51725564/cmake-doesnt-link-c-and-c-static-libraries-undefined-reference-to-function

foreach(app ${APPS})
    add_executable(${app} src/${app}.c)
    target_link_libraries(${app} PUBLIC
                            leg_control
                            servo_controller
                            kinematics
                            bcm2835
                            ncurses
                            m)
    target_include_directories(${app} PUBLIC
                                "include"
                                "${PROJECT_SOURCE_DIR}/src/libraries/include"
                                )
endforeach()

install(TARGETS ${APPS} DESTINATION bin)