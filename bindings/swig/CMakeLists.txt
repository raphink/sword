#####################################################################################################
#
# A system to, hopefully, build the Sword bindings which are asked for.  Currently I only know and
# therefore only support Python & Perl bindings.  YMMV for it, please submit patches or suggestions.
# I will try to get them integrated into the system if I can.  If there are bindings that you need
# other than the Python|Perl/Swig bindings, then you should probably speak up now.

MESSAGE(STATUS "\n-- CONFIGURING SWIG BINDINGS")
#####################################################################################################
# SWIG
# We need to find the SWIG executable in order to be able to do this, right?
FIND_PACKAGE(SWIG)

IF(NOT SWIG_FOUND)
	MESSAGE(FATAL_ERROR "Swig: no")
ELSE(NOT SWIG_FOUND)
	MESSAGE(STATUS "Swig: yes")
	
	#INCLUDE(${SWIG_USE_FILE})
	
	#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
	#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}../../include)
	#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/..)
	#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../..)
	
	SET(CMAKE_SWIG_FLAGS "-w-451,-402;-shadow;-c++")
	
	MACRO(SWORD_SWIG_GENERATE LANG)
		ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Sword.cxx
			COMMAND ${SWIG_EXECUTABLE} ${CMAKE_SWIG_FLAGS} -${LANG} -o "${CMAKE_CURRENT_BINARY_DIR}/Sword.cxx"
				"-I${CMAKE_SOURCE_DIR}/bindings/swig" ${SWIG_INCLUDES} "${CMAKE_SOURCE_DIR}/bindings/swig/sword.i"
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
	ENDMACRO(SWORD_SWIG_GENERATE)
	
	GET_DIRECTORY_PROPERTY(cmake_include_directories INCLUDE_DIRECTORIES)
	SET(SWIG_INCLUDES)
	FOREACH(directory ${cmake_include_directories})
		SET(SWIG_INCLUDES ${SWIG_INCLUDES} "-I${directory}")
	ENDFOREACH(directory ${cmake_include_directories})
	
	IF(SWORD_BINDINGS MATCHES ".*Python.*")
		ADD_SUBDIRECTORY(python)
	ENDIF(SWORD_BINDINGS MATCHES ".*Python.*")
	
	IF(SWORD_BINDINGS MATCHES ".*Perl.*")
		ADD_SUBDIRECTORY(perl)
	ENDIF(SWORD_BINDINGS MATCHES ".*Perl.*")
ENDIF(NOT SWIG_FOUND)
