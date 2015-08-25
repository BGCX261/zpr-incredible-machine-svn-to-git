# -*- cmake -*-

PROJECT(IncredibleMachines)

## section: include directory
# add your target-specific include directory here. 
    
INCLUDE_DIRECTORIES(
  
  )

## section: source files
# add your source files here
SET (IncredibleMachines_SOURCE_FILES
    ./AbstractPhysics.cpp
	./AntigravityElement.cpp
	./AntigravityPhysics.cpp
	./BallElement.cpp
	./BallPhysics.cpp
	./BucketElement.cpp
	./BucketPhysics.cpp
	./ContactListener.cpp
	./ConveyorElement.cpp
	./ConveyorPhysics.cpp
	./ElementFactory.cpp
	./GameLevel.cpp
	./GameWorld.cpp
	./IMApplication.cpp
	./LevelBoard.cpp
	./LevelTools.cpp
	./main.cpp
	./PhysicsWorld.cpp
	./PipeElement.cpp
	./PipePhysics.cpp
	./QuaterPipeElement.cpp
	./QuaterPipePhysics.cpp
	./RampElement.cpp
	./RampPhysics.cpp
	./Resources/resources.xml
	./SpringBoardElement.cpp
	./SpringBoardPhysics.cpp
	./ToolBox.cpp
	./ToolButton.cpp
    )

## section: header files
# add your header files here
SET(IncredibleMachines_HEADER_FILES
    ./AbstractElement.h
	./AbstractPhysics.h
	./AntigravityElement.h
	./AntigravityPhysics.h
	./BallElement.h
	./BallPhysics.h
	./BucketElement.h
	./BucketPhysics.h
	./ContactListener.h
	./ConveyorElement.h
	./ConveyorPhysics.h
	./ElementFactory.h
	./GameLevel.h
	./GameWorld.h
	./IMApplication.h
	./LevelBoard.h
	./LevelTools.h
	./PhysicsWorld.h
	./PipeElement.h
	./PipePhysics.h
	./QuaterPipeElement.h
	./QuaterPipePhysics.h
	./RampElement.h
	./RampPhysics.h
	./SpringBoardElement.h
	./SpringBoardPhysics.h
	./ToolBox.h
	./ToolButton.h
    )

SET_SOURCE_FILES_PROPERTIES(IncredibleMachines_HEADER_FILES
                            PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND IncredibleMachines_SOURCE_FILES ${IncredibleMachines_HEADER_FILES})

## section: add definitions
ADD_DEFINITIONS(${OSP_DEFINITIONS} )

## section: add target
ADD_LIBRARY (IncredibleMachines SHARED ${IncredibleMachines_SOURCE_FILES} )

## section: add dependency
# ADD_DEPENDENCIES(IncredibleMachines )

## section: set link libraries
# DO NOT add suffix(.lib .so) to lib name.
TARGET_LINK_LIBRARIES( IncredibleMachines
        )
