##############################################################################
# Files
##############################################################################

add_executable(demo_sigslots_manager sigslots_manager.cpp)
target_link_libraries(demo_sigslots_manager ${PROJECT_NAME})
install(TARGETS demo_sigslots_manager RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(demo_sigslots sigslots.cpp)
target_link_libraries(demo_sigslots ${PROJECT_NAME})
install(TARGETS demo_sigslots RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
