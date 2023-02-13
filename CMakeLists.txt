cmake_minimum_required(VERSION 3.14)
project(20f-flt-pln)
set (EXE_NAME flight_planner)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "input01.txt")
set(input02 "input02.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

if(MINGW OR CYGWIN)
    add_definitions(-O3)
endif()
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS_DEBUG "-O3")
add_executable(${EXE_NAME} main.cpp City.cpp City.h DSList.h DSVector.h SString.cpp SString.h Stack.h FlightPlanner.cpp FlightPlanner.h AList.h Flight.cpp Flight.h DesiredFlight.cpp DesiredFlight.h Test.cpp FlightPlan.cpp FlightPlan.h)

