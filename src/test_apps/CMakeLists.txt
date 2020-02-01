set(APPS
    stand_up)

foreach(app ${APPS})
    add_executable(${app} src/${app}.c)
    target_link_libraries(${app} PUBLIC
                            servo_controller
                            leg_control
                            bcm2835
                            ncurses)
    target_include_directories(${app} PUBLIC
                                "include"
                                "${PROJECT_SOURCE_DIR}/src/libraries/servo_controller/include"
                                "${PROJECT_SOURCE_DIR}/src/libraries/leg_control/include"
                                )
endforeach()

install(TARGETS ${APPS} DESTINATION bin)