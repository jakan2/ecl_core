##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_containers)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_config
    ecl_errors
    ecl_exceptions
    ecl_formatters
    ecl_converters
    ecl_mpl
    ecl_type_traits
    ecl_utilities
    )
catkin_package(
        INCLUDE_DIRS include
	CATKIN_DEPENDS 
            ecl_config
            ecl_errors
            ecl_exceptions
            ecl_formatters
            ecl_converters
            ecl_mpl
            ecl_type_traits
            ecl_utilities
        )
include_directories(SYSTEM include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



