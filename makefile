#OBJS specifies which files to compile as part of the project
OBJS = $(OBJ_DIRECTORY)/main.o $(OBJ_DIRECTORY)/Texture.o $(OBJ_DIRECTORY)/window.o $(OBJ_DIRECTORY)/difficultymenu.o $(OBJ_DIRECTORY)/mediumgameplay.o $(OBJ_DIRECTORY)/hardgameplay.o $(OBJ_DIRECTORY)/easygameplay.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = minesweeper

Header_DIRECTORY= -Iinclude

$(OBJ_DIRECTORY):
	mkdir build

OBJ_DIRECTORY= build

CPP_DIR= src

#This is the target that compiles our executable
all : $(OBJ_DIRECTORY)  $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) $(LINKER_FLAGS) && ./minesweeper

$(OBJ_DIRECTORY)/main.o : $(CPP_DIR)/main.cpp 
	$(CC) -c $(CPP_DIR)/main.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/main.o

$(OBJ_DIRECTORY)/Texture.o : $(CPP_DIR)/Texture.cpp include/Texture.hpp
	$(CC) -c $(CPP_DIR)/Texture.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/Texture.o

$(OBJ_DIRECTORY)/window.o : $(CPP_DIR)/window.cpp include/window.hpp
	$(CC) -c $(CPP_DIR)/window.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/window.o

$(OBJ_DIRECTORY)/difficultymenu.o : $(CPP_DIR)/difficultymenu.cpp include/difficultymenu.hpp
	$(CC) -c $(CPP_DIR)/difficultymenu.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/difficultymenu.o

$(OBJ_DIRECTORY)/easygameplay.o : $(CPP_DIR)/easygameplay.cpp include/easygameplay.hpp
	$(CC) -c $(CPP_DIR)/easygameplay.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/easygameplay.o

$(OBJ_DIRECTORY)/mediumgameplay.o : $(CPP_DIR)/mediumgameplay.cpp include/mediumgameplay.hpp
	$(CC) -c $(CPP_DIR)/mediumgameplay.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/mediumgameplay.o

$(OBJ_DIRECTORY)/hardgameplay.o : $(CPP_DIR)/hardgameplay.cpp include/hardgameplay.hpp
	$(CC) -c $(CPP_DIR)/hardgameplay.cpp $(Header_DIRECTORY) -o $(OBJ_DIRECTORY)/hardgameplay.o

build:
	mkdir build

clean :
	rm $(OBJ_DIRECTORY)/*.o