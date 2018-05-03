cmake_minimum_required(VERSION 3.11)

project(picotest_examples LANGUAGES C)

add_executable(traverse)
target_include_directories(traverse 
    PRIVATE
        ../include
)
target_sources(traverse 
    PRIVATE
        traverse.c
)

add_executable(logger)
target_include_directories(logger 
    PRIVATE
        ../include
)
target_sources(logger 
    PRIVATE
        logger.c
)

add_executable(matcher)
target_include_directories(matcher 
    PRIVATE
        ../include
)
target_sources(matcher 
    PRIVATE
        matcher.c
)