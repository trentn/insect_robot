set(SOURCES 
        src/kinematics.c)
        
add_library(kinematics ${SOURCES})

target_include_directories(kinematics PUBLIC
                            "include")