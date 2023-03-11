include_guard(DIRECTORY)

if(NOT CHORUSKIT_CMAKE_MODULES_DIR)
    set(CHORUSKIT_CMAKE_MODULES_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

if(NOT CHORUSKIT_SHARED_LIBRARY_PATTERN)
    if(WIN32)
        set(CHORUSKIT_SHARED_LIBRARY_PATTERN "*.dll")
    elseif(APPLE)
        set(CHORUSKIT_SHARED_LIBRARY_PATTERN "*.dylib")
    else()
        set(CHORUSKIT_SHARED_LIBRARY_PATTERN "*.so*")
    endif()
endif()