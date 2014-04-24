#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Clases/Animations/Animable.o \
	${OBJECTDIR}/Clases/Animations/AnimatedSprite.o \
	${OBJECTDIR}/Clases/Animations/Animation.o \
	${OBJECTDIR}/Clases/Animations/SpriteParticleSystem.o \
	${OBJECTDIR}/Clases/Animations/SpriteSheet.o \
	${OBJECTDIR}/Clases/Entities/Bullet.o \
	${OBJECTDIR}/Clases/Entities/Enemy.o \
	${OBJECTDIR}/Clases/Entities/EntActive.o \
	${OBJECTDIR}/Clases/Entities/EntPassive.o \
	${OBJECTDIR}/Clases/Entities/Entity.o \
	${OBJECTDIR}/Clases/Entities/Gun.o \
	${OBJECTDIR}/Clases/Entities/Player.o \
	${OBJECTDIR}/Clases/Factories/StateFactory.o \
	${OBJECTDIR}/Clases/Game.o \
	${OBJECTDIR}/Clases/HUD/Button.o \
	${OBJECTDIR}/Clases/HUD/HUD.o \
	${OBJECTDIR}/Clases/HUD/Lifebar.o \
	${OBJECTDIR}/Clases/Managers/InputManager.o \
	${OBJECTDIR}/Clases/Managers/ResourceManager.o \
	${OBJECTDIR}/Clases/Managers/StateManager.o \
	${OBJECTDIR}/Clases/Motor2D/Level.o \
	${OBJECTDIR}/Clases/Motor2D/MapLoader/DebugShape.o \
	${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLayer.o \
	${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLoaderPrivate.o \
	${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLoaderPublic.o \
	${OBJECTDIR}/Clases/Motor2D/MapLoader/MapObject.o \
	${OBJECTDIR}/Clases/Motor2D/MapLoader/QuadTreeNode.o \
	${OBJECTDIR}/Clases/Motor2D/MapLoader/pugixml.o \
	${OBJECTDIR}/Clases/Motor2D/Mapa.o \
	${OBJECTDIR}/Clases/Motor2D/RenderState.o \
	${OBJECTDIR}/Clases/Motor2D/RenderWindow.o \
	${OBJECTDIR}/Clases/MotorPhysics/Colisionable.o \
	${OBJECTDIR}/Clases/MotorPhysics/Maths.o \
	${OBJECTDIR}/Clases/MotorPhysics/PhysicsState.o \
	${OBJECTDIR}/Clases/Otros/Clock.o \
	${OBJECTDIR}/Clases/Otros/LoadingTask.o \
	${OBJECTDIR}/Clases/Otros/Rectangle.o \
	${OBJECTDIR}/Clases/Otros/StringUtils.o \
	${OBJECTDIR}/Clases/Otros/Time.o \
	${OBJECTDIR}/Clases/Otros/Vector.o \
	${OBJECTDIR}/Clases/States/LevelSelectionState.o \
	${OBJECTDIR}/Clases/States/LoadingState.o \
	${OBJECTDIR}/Clases/States/MenuState.o \
	${OBJECTDIR}/Clases/States/WorldState.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/SFML/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lz

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hito2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hito2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hito2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Clases/Animations/Animable.o: Clases/Animations/Animable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Animations
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Animations/Animable.o Clases/Animations/Animable.cpp

${OBJECTDIR}/Clases/Animations/AnimatedSprite.o: Clases/Animations/AnimatedSprite.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Animations
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Animations/AnimatedSprite.o Clases/Animations/AnimatedSprite.cpp

${OBJECTDIR}/Clases/Animations/Animation.o: Clases/Animations/Animation.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Animations
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Animations/Animation.o Clases/Animations/Animation.cpp

${OBJECTDIR}/Clases/Animations/SpriteParticleSystem.o: Clases/Animations/SpriteParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Animations
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Animations/SpriteParticleSystem.o Clases/Animations/SpriteParticleSystem.cpp

${OBJECTDIR}/Clases/Animations/SpriteSheet.o: Clases/Animations/SpriteSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Animations
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Animations/SpriteSheet.o Clases/Animations/SpriteSheet.cpp

${OBJECTDIR}/Clases/Entities/Bullet.o: Clases/Entities/Bullet.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Entities
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Entities/Bullet.o Clases/Entities/Bullet.cpp

${OBJECTDIR}/Clases/Entities/Enemy.o: Clases/Entities/Enemy.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Entities
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Entities/Enemy.o Clases/Entities/Enemy.cpp

${OBJECTDIR}/Clases/Entities/EntActive.o: Clases/Entities/EntActive.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Entities
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Entities/EntActive.o Clases/Entities/EntActive.cpp

${OBJECTDIR}/Clases/Entities/EntPassive.o: Clases/Entities/EntPassive.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Entities
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Entities/EntPassive.o Clases/Entities/EntPassive.cpp

${OBJECTDIR}/Clases/Entities/Entity.o: Clases/Entities/Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Entities
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Entities/Entity.o Clases/Entities/Entity.cpp

${OBJECTDIR}/Clases/Entities/Gun.o: Clases/Entities/Gun.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Entities
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Entities/Gun.o Clases/Entities/Gun.cpp

${OBJECTDIR}/Clases/Entities/Player.o: Clases/Entities/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Entities
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Entities/Player.o Clases/Entities/Player.cpp

${OBJECTDIR}/Clases/Factories/StateFactory.o: Clases/Factories/StateFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Factories
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Factories/StateFactory.o Clases/Factories/StateFactory.cpp

${OBJECTDIR}/Clases/Game.o: Clases/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Game.o Clases/Game.cpp

${OBJECTDIR}/Clases/HUD/Button.o: Clases/HUD/Button.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/HUD
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/HUD/Button.o Clases/HUD/Button.cpp

${OBJECTDIR}/Clases/HUD/HUD.o: Clases/HUD/HUD.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/HUD
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/HUD/HUD.o Clases/HUD/HUD.cpp

${OBJECTDIR}/Clases/HUD/Lifebar.o: Clases/HUD/Lifebar.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/HUD
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/HUD/Lifebar.o Clases/HUD/Lifebar.cpp

${OBJECTDIR}/Clases/Managers/InputManager.o: Clases/Managers/InputManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Managers
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Managers/InputManager.o Clases/Managers/InputManager.cpp

${OBJECTDIR}/Clases/Managers/ResourceManager.o: Clases/Managers/ResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Managers
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Managers/ResourceManager.o Clases/Managers/ResourceManager.cpp

${OBJECTDIR}/Clases/Managers/StateManager.o: Clases/Managers/StateManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Managers
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Managers/StateManager.o Clases/Managers/StateManager.cpp

${OBJECTDIR}/Clases/Motor2D/Level.o: Clases/Motor2D/Level.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/Level.o Clases/Motor2D/Level.cpp

${OBJECTDIR}/Clases/Motor2D/MapLoader/DebugShape.o: Clases/Motor2D/MapLoader/DebugShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D/MapLoader
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/MapLoader/DebugShape.o Clases/Motor2D/MapLoader/DebugShape.cpp

${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLayer.o: Clases/Motor2D/MapLoader/MapLayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D/MapLoader
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLayer.o Clases/Motor2D/MapLoader/MapLayer.cpp

${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLoaderPrivate.o: Clases/Motor2D/MapLoader/MapLoaderPrivate.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D/MapLoader
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLoaderPrivate.o Clases/Motor2D/MapLoader/MapLoaderPrivate.cpp

${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLoaderPublic.o: Clases/Motor2D/MapLoader/MapLoaderPublic.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D/MapLoader
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/MapLoader/MapLoaderPublic.o Clases/Motor2D/MapLoader/MapLoaderPublic.cpp

${OBJECTDIR}/Clases/Motor2D/MapLoader/MapObject.o: Clases/Motor2D/MapLoader/MapObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D/MapLoader
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/MapLoader/MapObject.o Clases/Motor2D/MapLoader/MapObject.cpp

${OBJECTDIR}/Clases/Motor2D/MapLoader/QuadTreeNode.o: Clases/Motor2D/MapLoader/QuadTreeNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D/MapLoader
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/MapLoader/QuadTreeNode.o Clases/Motor2D/MapLoader/QuadTreeNode.cpp

${OBJECTDIR}/Clases/Motor2D/MapLoader/pugixml.o: Clases/Motor2D/MapLoader/pugixml.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D/MapLoader
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/MapLoader/pugixml.o Clases/Motor2D/MapLoader/pugixml.cpp

${OBJECTDIR}/Clases/Motor2D/Mapa.o: Clases/Motor2D/Mapa.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/Mapa.o Clases/Motor2D/Mapa.cpp

${OBJECTDIR}/Clases/Motor2D/RenderState.o: Clases/Motor2D/RenderState.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/RenderState.o Clases/Motor2D/RenderState.cpp

${OBJECTDIR}/Clases/Motor2D/RenderWindow.o: Clases/Motor2D/RenderWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Motor2D
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Motor2D/RenderWindow.o Clases/Motor2D/RenderWindow.cpp

${OBJECTDIR}/Clases/MotorPhysics/Colisionable.o: Clases/MotorPhysics/Colisionable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/MotorPhysics
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/MotorPhysics/Colisionable.o Clases/MotorPhysics/Colisionable.cpp

${OBJECTDIR}/Clases/MotorPhysics/Maths.o: Clases/MotorPhysics/Maths.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/MotorPhysics
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/MotorPhysics/Maths.o Clases/MotorPhysics/Maths.cpp

${OBJECTDIR}/Clases/MotorPhysics/PhysicsState.o: Clases/MotorPhysics/PhysicsState.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/MotorPhysics
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/MotorPhysics/PhysicsState.o Clases/MotorPhysics/PhysicsState.cpp

${OBJECTDIR}/Clases/Otros/Clock.o: Clases/Otros/Clock.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Otros
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Otros/Clock.o Clases/Otros/Clock.cpp

${OBJECTDIR}/Clases/Otros/LoadingTask.o: Clases/Otros/LoadingTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Otros
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Otros/LoadingTask.o Clases/Otros/LoadingTask.cpp

${OBJECTDIR}/Clases/Otros/Rectangle.o: Clases/Otros/Rectangle.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Otros
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Otros/Rectangle.o Clases/Otros/Rectangle.cpp

${OBJECTDIR}/Clases/Otros/StringUtils.o: Clases/Otros/StringUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Otros
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Otros/StringUtils.o Clases/Otros/StringUtils.cpp

${OBJECTDIR}/Clases/Otros/Time.o: Clases/Otros/Time.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Otros
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Otros/Time.o Clases/Otros/Time.cpp

${OBJECTDIR}/Clases/Otros/Vector.o: Clases/Otros/Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/Otros
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/Otros/Vector.o Clases/Otros/Vector.cpp

${OBJECTDIR}/Clases/States/LevelSelectionState.o: Clases/States/LevelSelectionState.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/States
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/States/LevelSelectionState.o Clases/States/LevelSelectionState.cpp

${OBJECTDIR}/Clases/States/LoadingState.o: Clases/States/LoadingState.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/States
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/States/LoadingState.o Clases/States/LoadingState.cpp

${OBJECTDIR}/Clases/States/MenuState.o: Clases/States/MenuState.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/States
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/States/MenuState.o Clases/States/MenuState.cpp

${OBJECTDIR}/Clases/States/WorldState.o: Clases/States/WorldState.cpp 
	${MKDIR} -p ${OBJECTDIR}/Clases/States
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Clases/States/WorldState.o Clases/States/WorldState.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/local/SFML/include -IIncludes -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hito2

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
