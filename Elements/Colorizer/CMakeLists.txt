SET ( PROJECT_FOLDER_NAME Colorizer )
SET ( PROJECT_PATH ${ELEMENT_NAME} )
SET ( OUTPUT_NAME "SE${PROJECT_FOLDER_NAME}" )
ADD_DEFINITIONS( -DELEMENT_NAME=\"${OUTPUT_NAME}\" )

# VERSION_HASH information : New since SAMSON 0.8.0
#
# The maximum size of this variable is 63 Bytes ie char[63].
# We can embed into elements file one string to identify it. Usualy we put the git commit hash or the svn revision number inside.
# The information is relevant only if the working copy is up to date and if everything is commited
# If you upload your element on samson-connect, you will see this information next to your element inside My SAMSON->My Factory->Edit Element.

# you can choose either git either svn either nothing
SET ( USE_GIT 1 )
SET ( USE_SVN 0 )

IF( ${USE_GIT} )
	# if USE_GIT=1 the next command will get the current commit hash and will store 
	# it inside VERSION_HASH variable.
	MESSAGE( "Getting current git commit hash and storing it inside VERSION_HASH variable." )
	EXECUTE_PROCESS(
	  COMMAND git log -1 --format=%H
	  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	  OUTPUT_VARIABLE VERSION_HASH
	  OUTPUT_STRIP_TRAILING_WHITESPACE
	 )
ELSE (${USE_GIT})
	IF (${USE_SVN})
		# if USE_SVN=1 and USE_GIT=0 the next command will get the current commit revision
		# of your working copy and will store it inside VERSION_HASH variable.
		MESSAGE( "Getting current svn revision and storing it inside VERSION_HASH variable." )
		find_package(Subversion)
		IF(SUBVERSION_FOUND)
		  Subversion_WC_INFO(${CMAKE_SOURCE_DIR} REPO)
		  SET ( VERSION_HASH ${REPO_WC_REVISION} )
		ENDIF()
	ELSE (${USE_SVN})
		# if USE_SVN=0 and USE_GIT=0 we set the variable VERSION_HASH equal to 
		# "undefined hash" or what you desire.
		SET(VERSION_HASH "undefined")
	ENDIF(${USE_SVN})
ENDIF(${USE_GIT})

SET( OUTPUT_UUID E770E4DE-F2C4-A42B-8BE1-3EBEE8BC9233 )
SET( OUTPUT_UUID-VAR \"${OUTPUT_UUID}\" )
ADD_DEFINITIONS( -DSB_ELEMENT_UUID=${OUTPUT_UUID-VAR} )
ADD_DEFINITIONS( -DSB_ELEMENT_VERSION_HASH="${VERSION_HASH}")

MESSAGE ( "-- ++ CREATING PROJECT OR MAKEFILE ---> ${OUTPUT_UUID} : ${OUTPUT_NAME}" )

FILE ( GLOB_RECURSE ${OUTPUT_UUID}_headers include/*.hpp )
FILE ( GLOB_RECURSE ${OUTPUT_UUID}_sources source/*.cpp )
FILE ( GLOB_RECURSE ${OUTPUT_UUID}_resources resource/*.qrc )
FILE ( GLOB_RECURSE ${OUTPUT_UUID}_form form/*.ui )
	
FILE( GLOB_RECURSE ${OUTPUT_UUID}_ts resource/translations/*.ts )

INCLUDE_DIRECTORIES ( include )
INCLUDE_DIRECTORIES ( ${CMAKE_CURRENT_BINARY_DIR} )

IF(QT_WRAP_CPP)

	QT5_WRAP_CPP( ${OUTPUT_UUID}_MOC_GENERATED ${${OUTPUT_UUID}_headersToMOC} )

ENDIF(QT_WRAP_CPP)

QT5_WRAP_UI( ${OUTPUT_UUID}_UI_GENERATED ${${OUTPUT_UUID}_form} )

QT5_ADD_RESOURCES( ${OUTPUT_UUID}_RCC_GENERATED ${${OUTPUT_UUID}_resources} )

QT5_ADD_TRANSLATION( ${OUTPUT_UUID}_QM  ${${OUTPUT_UUID}_ts} )

SOURCE_GROUP ( include FILES ${${OUTPUT_UUID}_headers} )
SOURCE_GROUP ( source FILES ${${OUTPUT_UUID}_sources} )
SOURCE_GROUP ( resource FILES ${${OUTPUT_UUID}_resources} )
SOURCE_GROUP ( form FILES ${${OUTPUT_UUID}_form} )
SOURCE_GROUP ( translationFiles FILES ${${PROJECT_FOLDER_NAME}_QM} ${${OUTPUT_UUID}_ts} )
SOURCE_GROUP ( GeneratedFiles FILES ${${OUTPUT_UUID}_MOC_GENERATED} ${${OUTPUT_UUID}_UI_GENERATED} ${${OUTPUT_UUID}_RCC_GENERATED} )

ADD_LIBRARY ( ${OUTPUT_NAME} SHARED ${${OUTPUT_UUID}_headers} ${${OUTPUT_UUID}_sources} ${${OUTPUT_UUID}_MOC_GENERATED} ${${OUTPUT_UUID}_UI_GENERATED} ${${OUTPUT_UUID}_RCC_GENERATED} ${${OUTPUT_UUID}_QM} )

TARGET_LINK_LIBRARIES (	${OUTPUT_NAME}
						${QT_LIBRARIES}
						${OPENGL_LIBRARY}
						${SAMSON_SDK_LIBRARIES}
						)
						
SET_TARGET_PROPERTIES(${OUTPUT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_UUID})		
						
IF( UNIX ) 
	SET_TARGET_PROPERTIES ( ${OUTPUT_NAME} PROPERTIES PREFIX "" )
ENDIF( UNIX ) 

SET_PROPERTY ( TARGET ${OUTPUT_NAME} PROPERTY FOLDER "Elements" )

SAMSON_INSTALL_ELEMENT_DIRECTORY( data/ ${OUTPUT_UUID}/Data )
SAMSON_INSTALL_ELEMENT_DIRECTORY( resource/ ${OUTPUT_UUID}/Resource )
SAMSON_INSTALL_ELEMENT_DIRECTORY( doc/ ${OUTPUT_UUID}/Documentation )

SAMSON_INSTALL_ELEMENT ( ${OUTPUT_NAME} ${OUTPUT_UUID} )
