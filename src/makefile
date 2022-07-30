#OBJS specifies which files to compile as part of the project
OBJS = $(OBJ_DIRECTORY)/main.o $(OBJ_DIRECTORY)/Texture.o $(OBJ_DIRECTORY)/window.o $(OBJ_DIRECTORY)/difficultymenu.o $(OBJ_DIRECTORY)/mediumgameplay.o $(OBJ_DIRECTORY)/hardgameplay.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = minesweeper

Header_DIRECTORY= -I../include

OBJ_DIRECTORY= ../obj

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) $(LINKER_FLAGS)

$(OBJ_DIRECTORY)/main.o : main.cpp 
	$(CC) -c main.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/main.o

$(OBJ_DIRECTORY)/Texture.o : Texture.cpp
	$(CC) -c Texture.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/Texture.o

$(OBJ_DIRECTORY)/window.o : window.cpp
	$(CC) -c window.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/window.o

$(OBJ_DIRECTORY)/difficultymenu.o : difficultymenu.cpp
	$(CC) -c difficultymenu.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/difficultymenu.o

$(OBJ_DIRECTORY)/easygameplay.o : easygameplay.cpp
	$(CC) -c easygameplay.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/easygameplay.o

$(OBJ_DIRECTORY)/mediumgameplay.o : mediumgameplay.cpp
	$(CC) -c mediumgameplay.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/mediumgameplay.o

$(OBJ_DIRECTORY)/hardgameplay.o : hardgameplay.cpp
	$(CC) -c hardgameplay.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/hardgameplay.o

