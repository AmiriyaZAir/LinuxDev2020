cmake_minimum_required (VERSION 3.15.3)

set (PROJECT Window)

project (${PROJECT})

add_executable (${PROJECT} ${PROJECT}.c )


set (LIBRARIES
		ncursesw
		pcre2-8)

foreach (LIBRARY ${LIBRARIES})
	find_library (${LIBRARY}_LIB ${LIBRARY})
endforeach ()

if (WITHOUT_UTF)
	add_definitions (-DUTF_ENCODING=0)
else ()
	add_definitions (-DUTF_ENCODING=1)
endif ()

target_link_libraries (${PROJECT} ${LIBRARIES})
