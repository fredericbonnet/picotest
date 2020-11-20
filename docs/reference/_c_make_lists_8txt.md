<a id="_c_make_lists_8txt"></a>
# File CMakeLists.txt

![][C++]

**Location**: `examples/CMakeLists.txt`





## Source

```cpp
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

add_executable(filter)
target_include_directories(filter 
    PRIVATE
        ../include
)
target_sources(filter
    PRIVATE
        filter.c
)

add_executable(tags)
target_include_directories(tags 
    PRIVATE
        ../include
)
target_sources(tags
    PRIVATE
        tags.c
)

add_executable(fixtures)
target_include_directories(fixtures 
    PRIVATE
        ../include
)
target_sources(fixtures
    PRIVATE
        fixtures.c
)

add_executable(hooks)
target_include_directories(hooks 
    PRIVATE
        ../include
)
target_sources(hooks
    PRIVATE
        hooks.c
)
```

[C++]: https://img.shields.io/badge/language-C%2B%2B-blue (C++)