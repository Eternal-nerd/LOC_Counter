cmake_minimum_required(VERSION 3.5)
project(LOC_Counter)

# set standard:
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add source files:
set(SOURCES
	src/main.cpp
)

# add headers
set(HEADERS
)

# add executable:
add_executable(LOC_Counter ${SOURCES} ${HEADERS})

# add libs
#target_link_libraries(LOC_Counter PRIVATE Vulkan::Vulkan SDL3::SDL3)

# Specify the output directory for the binary
set_target_properties(LOC_Counter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)



