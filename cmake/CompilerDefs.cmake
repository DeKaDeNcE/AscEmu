MACRO( IS_ARCH_64BIT )
	IF( NOT WIN32 )
		
		IF( CMAKE_SYSTEM_PROCESSOR MATCHES "[xX]64" OR CMAKE_SYSTEM_PROCESSOR MATCHES "[xX]86_64" OR CMAKE_SYSTEM_PROCESSOR MATCHES "[aA][mM][dD]64" )
			SET( IS_64BIT TRUE )
		ELSE()
			SET( IS_64BIT FALSE )
		ENDIF()
		
	ELSE( NOT WIN32 )

		IF( CMAKE_GENERATOR MATCHES Win64* )
			SET( IS_64BIT TRUE )
		ELSE( CMAKE_GENERATOR MATCHES Win64* )
			SET( IS_64BIT FALSE )
		ENDIF( CMAKE_GENERATOR MATCHES Win64* )
		
	ENDIF( NOT WIN32 )
	
ENDMACRO( IS_ARCH_64BIT )

IF( WIN32 )
	IF( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
		SET( CMAKE_INSTALL_PREFIX "C:/Ascemu" CACHE PATH "Install path prefix" FORCE )
	ENDIF( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
    
    add_definitions( -DWIN32 )
ENDIF( WIN32 )

SET( GLOBAL_DEFINES "-DHAVE_CONFIG_H")

IF( CMAKE_GENERATOR MATCHES Visual*)
	SET( GLOBAL_DEFINES ${GLOBAL_DEFINES} "/MP")
ENDIF()

IF(CMAKE_GENERATOR MATCHES Visual*)
	SET(GLOBAL_DEFINES ${GLOBAL_DEFINES} "/bigobj")
ENDIF()

IS_ARCH_64BIT()

#check platform version.
IF( IS_64BIT )
	SET( GLOBAL_DEFINES ${GLOBAL_DEFINES} -"DX64")
	IF(CMAKE_GENERATOR MATCHES NMake*)
		SET( GLOBAL_DEFINES ${GLOBAL_DEFINES} "-bigobj")
	ENDIF()
ENDIF()

#mac osx
IF( APPLE )
	SET( GLOBAL_DEFINES ${GLOBAL_DEFINES} "-DHAVE_DARWIN")
	SET( IS_MAC TRUE)
ELSEIF(UNIX)
	#mac has unix defined too but if 'if(APPLE)' fails, then it's not apple.
	
	#check for freebsd
	IF( ( CMAKE_SYSTEM_NAME  STREQUAL "FreeBSD" ) OR ( CMAKE_SYSTEM_NAME STREQUAL kFreeBSD ) )
		SET( GLOBAL_DEFINES ${GLOBAL_DEFINES} "-DUSE_KQUEUE")
		SET( IS_FREEBSD TRUE)
	ELSE()
		SET( GLOBAL_DEFINES ${GLOBAL_DEFINES} "-DUSE_EPOLL")
		SET( IS_LINUX TRUE)
	ENDIF()
ENDIF()