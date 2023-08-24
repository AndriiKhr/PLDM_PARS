
# set minimum cmake version
cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

# project name and language
project(pldm_pars LANGUAGES C)

# add header files
include_directories(inc)

# add source files
add_executable ( pldm_pars  src/main.c 
                            src/pars.c
                            src/json.c )
