#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = -IC:\\SDL2\\SDL2-2.0.9\\x86_64-w64-mingw32\\include -IC:\\SDL2\\SDL2_image-2.0.4\\x86_64-w64-mingw32\\include -IC:\\SDL2\\SDL2_mixer-2.0.4\\x86_64-w64-mingw32\\include -IC:\\SDL2\\SDL2_ttf-2.0.15\\x86_64-w64-mingw32\\include -IC:\\SDL2\\SDL2-2.0.9\\x86_64-w64-mingw32\\include\\SDL2 -IC:\\SDL2\\SDL2_image-2.0.4\\x86_64-w64-mingw32\\include\\SDL2 -IC:\\SDL2\\SDL2_mixer-2.0.4\\x86_64-w64-mingw32\\include\\SDL2 -IC:\\SDL2\\SDL2_ttf-2.0.15\\x86_64-w64-mingw32\\include\\SDL2 -IC:\\Users\\2013b\\Git\\Ossium\\Engine\\src -IC:\\Users\\2013b\\Git\\Ossium\\Engine\\Box2D
CFLAGS = -Wall -fexceptions
RESINC = 
LIBDIR = -LC:\\SDL2\\SDL2-2.0.9\\x86_64-w64-mingw32\\lib\ -LC:\\SDL2\\SDL2_image-2.0.4\\x86_64-w64-mingw32\\lib -LC:\\SDL2\\SDL2_mixer-2.0.4\\x86_64-w64-mingw32\\lib -LC:\\SDL2\\SDL2_ttf-2.0.15\\x86_64-w64-mingw32\\lib
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g -std=c++1z -DOSSIUM_DEBUG
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR) -LC:\Users\2013b\Git\Ossium\Engine\bin\ossium
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS) -Wl,--whole-archive,C:\Users\2013b\Git\Ossium\Engine\bin\ossium\libossium.a,--no-whole-archive C:\Users\2013b\Git\Ossium\Engine\Box2D\bin\Release\libBox2D.a -lmingw32 -lcomdlg32 -lole32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -static-libgcc -static-libstdc++
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\ossium.exe

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2 -std=c++1z
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR) -LC:\Users\2013b\Git\Ossium\Engine\bin\ossium
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s -Wl,--whole-archive,C:\Users\2013b\Git\Ossium\Engine\bin\Debug\libOssium.a,--no-whole-archive C:\Users\2013b\Git\Ossium\Engine\Box2D\bin\Release\libBox2D.a -lmingw32 -lcomdlg32 -lole32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -static-libgcc -static-libstdc++
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\Project.exe

INC_DEBUG__EDITOR_ = $(INC)
CFLAGS_DEBUG__EDITOR_ = $(CFLAGS) -g -std=c++1z -DOSSIUM_EDITOR -DOSSIUM_DEBUG
RESINC_DEBUG__EDITOR_ = $(RESINC)
RCFLAGS_DEBUG__EDITOR_ = $(RCFLAGS)
LIBDIR_DEBUG__EDITOR_ = $(LIBDIR) -LC:\Users\2013b\Git\Ossium\Engine\bin\OssiumEditorDebug
LIB_DEBUG__EDITOR_ = $(LIB)
LDFLAGS_DEBUG__EDITOR_ = $(LDFLAGS) -Wl,--whole-archive,C:\Users\2013b\Git\Ossium\Engine\bin\OssiumEditorDebug\libOssium.a,--no-whole-archive C:\Users\2013b\Git\Ossium\Engine\Box2D\bin\Release\libBox2D.a -lmingw32 -lcomdlg32 -lole32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -static-libgcc -static-libstdc++
OBJDIR_DEBUG__EDITOR_ = obj\\DebugEditor
DEP_DEBUG__EDITOR_ = 
OUT_DEBUG__EDITOR_ = bin\\Debug\\OssiumEditor.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\src\\Ingame\\explorer.o $(OBJDIR_DEBUG)\\src\\Ingame\\GameController.o $(OBJDIR_DEBUG)\\src\\Ingame\\UI\\PlacementButton.o $(OBJDIR_DEBUG)\\src\\main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\src\\Ingame\\explorer.o $(OBJDIR_RELEASE)\\src\\Ingame\\GameController.o $(OBJDIR_RELEASE)\\src\\Ingame\\UI\\PlacementButton.o $(OBJDIR_RELEASE)\\src\\main.o

OBJ_DEBUG__EDITOR_ = $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\explorer.o $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\GameController.o $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\UI\\PlacementButton.o $(OBJDIR_DEBUG__EDITOR_)\\src\\main.o

all: debug release debug__editor_

clean: clean_debug clean_release clean_debug__editor_

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG)\\src\\Ingame md $(OBJDIR_DEBUG)\\src\\Ingame
	cmd /c if not exist $(OBJDIR_DEBUG)\\src\\Ingame\\UI md $(OBJDIR_DEBUG)\\src\\Ingame\\UI
	cmd /c if not exist $(OBJDIR_DEBUG)\\src md $(OBJDIR_DEBUG)\\src

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\src\\Ingame\\explorer.o: src\\Ingame\\explorer.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Ingame\\explorer.cpp -o $(OBJDIR_DEBUG)\\src\\Ingame\\explorer.o

$(OBJDIR_DEBUG)\\src\\Ingame\\GameController.o: src\\Ingame\\GameController.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Ingame\\GameController.cpp -o $(OBJDIR_DEBUG)\\src\\Ingame\\GameController.o

$(OBJDIR_DEBUG)\\src\\Ingame\\UI\\PlacementButton.o: src\\Ingame\\UI\\PlacementButton.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\Ingame\\UI\\PlacementButton.cpp -o $(OBJDIR_DEBUG)\\src\\Ingame\\UI\\PlacementButton.o

$(OBJDIR_DEBUG)\\src\\main.o: src\\main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src\\main.cpp -o $(OBJDIR_DEBUG)\\src\\main.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)\\src\\Ingame
	cmd /c rd $(OBJDIR_DEBUG)\\src\\Ingame\\UI
	cmd /c rd $(OBJDIR_DEBUG)\\src

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE)\\src\\Ingame md $(OBJDIR_RELEASE)\\src\\Ingame
	cmd /c if not exist $(OBJDIR_RELEASE)\\src\\Ingame\\UI md $(OBJDIR_RELEASE)\\src\\Ingame\\UI
	cmd /c if not exist $(OBJDIR_RELEASE)\\src md $(OBJDIR_RELEASE)\\src

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) -mwindows $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\src\\Ingame\\explorer.o: src\\Ingame\\explorer.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Ingame\\explorer.cpp -o $(OBJDIR_RELEASE)\\src\\Ingame\\explorer.o

$(OBJDIR_RELEASE)\\src\\Ingame\\GameController.o: src\\Ingame\\GameController.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Ingame\\GameController.cpp -o $(OBJDIR_RELEASE)\\src\\Ingame\\GameController.o

$(OBJDIR_RELEASE)\\src\\Ingame\\UI\\PlacementButton.o: src\\Ingame\\UI\\PlacementButton.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\Ingame\\UI\\PlacementButton.cpp -o $(OBJDIR_RELEASE)\\src\\Ingame\\UI\\PlacementButton.o

$(OBJDIR_RELEASE)\\src\\main.o: src\\main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src\\main.cpp -o $(OBJDIR_RELEASE)\\src\\main.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)\\src\\Ingame
	cmd /c rd $(OBJDIR_RELEASE)\\src\\Ingame\\UI
	cmd /c rd $(OBJDIR_RELEASE)\\src

before_debug__editor_: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame md $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame
	cmd /c if not exist $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\UI md $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\UI
	cmd /c if not exist $(OBJDIR_DEBUG__EDITOR_)\\src md $(OBJDIR_DEBUG__EDITOR_)\\src

after_debug__editor_: 

debug__editor_: before_debug__editor_ out_debug__editor_ after_debug__editor_

out_debug__editor_: before_debug__editor_ $(OBJ_DEBUG__EDITOR_) $(DEP_DEBUG__EDITOR_)
	$(LD) $(LIBDIR_DEBUG__EDITOR_) -o $(OUT_DEBUG__EDITOR_) $(OBJ_DEBUG__EDITOR_)  $(LDFLAGS_DEBUG__EDITOR_) $(LIB_DEBUG__EDITOR_)

$(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\explorer.o: src\\Ingame\\explorer.cpp
	$(CXX) $(CFLAGS_DEBUG__EDITOR_) $(INC_DEBUG__EDITOR_) -c src\\Ingame\\explorer.cpp -o $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\explorer.o

$(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\GameController.o: src\\Ingame\\GameController.cpp
	$(CXX) $(CFLAGS_DEBUG__EDITOR_) $(INC_DEBUG__EDITOR_) -c src\\Ingame\\GameController.cpp -o $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\GameController.o

$(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\UI\\PlacementButton.o: src\\Ingame\\UI\\PlacementButton.cpp
	$(CXX) $(CFLAGS_DEBUG__EDITOR_) $(INC_DEBUG__EDITOR_) -c src\\Ingame\\UI\\PlacementButton.cpp -o $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\UI\\PlacementButton.o

$(OBJDIR_DEBUG__EDITOR_)\\src\\main.o: src\\main.cpp
	$(CXX) $(CFLAGS_DEBUG__EDITOR_) $(INC_DEBUG__EDITOR_) -c src\\main.cpp -o $(OBJDIR_DEBUG__EDITOR_)\\src\\main.o

clean_debug__editor_: 
	cmd /c del /f $(OBJ_DEBUG__EDITOR_) $(OUT_DEBUG__EDITOR_)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame
	cmd /c rd $(OBJDIR_DEBUG__EDITOR_)\\src\\Ingame\\UI
	cmd /c rd $(OBJDIR_DEBUG__EDITOR_)\\src

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release before_debug__editor_ after_debug__editor_ clean_debug__editor_

