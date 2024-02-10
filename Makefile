# Universidade Federal do Rio de Janeiro
# Escola Politécnica
# Departamento de Eletrônica e Computação
# Prof. Fernando Silva
# EEL 670 - Linguagem de Programação
#
# Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
#          Leonan França    (leonancfr@poli.ufrj.br)
#          Gustavo Silva    (diguser@gmail.com)
#          Michael Douglas  (michaeldouglas@poli.ufrj.br)

CC = g++#-s
LD = g++#-s

SRCDIR = src
OBJDIR = obj
LIBDIR = lib
INCDIR = lib/include
HDRDIR = src
BINDIR = bin
RESDIR = res

ifeq ($(TIMER), 1)
MASG =$(shell echo %time%)
$(warning Start in $(MASG))
endif

ifeq ($(shell uname), Linux)
LINUX = N
CCFLAGS = -Wall -I./$(INCDIR)/
ifeq (x86_64,$(findstring x86_64,$(shell $(CC) -dumpmachine)))
LDFLAGS = -Wall -L./$(LIBDIR)/ -pthread -lIrrlicht -lcAudio
else
LDFLAGS = -Wall -L./$(LIBDIR)/ -pthread -lIrrlicht -lcAudio
endif
LINUX = Y
else
LINUX = N
CCFLAGS = -Wall -I./$(INCDIR)/
ifeq (x86_64,$(findstring x86_64,$(shell $(CC) -dumpmachine)))
LDFLAGS = -Wall -L./$(LIBDIR)/ -pthread -lIrrlicht -lcAudio -mwindows
else
LDFLAGS = -Wall -L./$(LIBDIR)/ -pthread -lIrrlicht -lcAudio -mwindows
endif
endif

ifeq ($(DEBUG),1)
CCFLAGS :=$(CCFLAGS) -DDEBUG
endif

SOURCES=\
AnimationCount.cpp \
AnimatorObjectList.cpp \
AnimatorQueue.cpp \
AudioCache.cpp \
AudioManager.cpp \
BB.cpp \
Callback.cpp \
CallbackAfterFall.cpp \
CallbackButtonOnHover.cpp \
CallbackButtonOnOut.cpp \
CallbackDestroy.cpp \
CallbackFillMatrix.cpp \
CallbackGameExitButtonClick.cpp \
CallbackMatrixOut.cpp \
CallbackMouseClickMatrix.cpp \
CallbackMouseHoverMatrix.cpp \
CallbackProcessMatrix.cpp \
CoreOpenGLVersion.cpp \
CoreProcess.cpp \
DecodeValue.cpp \
EventReceiver.cpp \
Events.cpp \
GameControl.cpp \
GameDefines.cpp \
GameHowToPlay.cpp \
GameLevel.cpp \
GameLevelFile.cpp \
GamePause.cpp \
GamePauseButton.cpp \
GamePointsMatrix.cpp \
GamePostScreen.cpp \
GameMainScreen.cpp \
GameSave.cpp \
GameTimeAttack.cpp \
GameTimeAttackRank.cpp \
GameTimeBar.cpp \
Gem.cpp \
Logger.cpp \
MainDraw.cpp \
MatrixBool.cpp \
MorphLinear.cpp \
MorphTimer.cpp \
ObjectMorph.cpp \
Percentage.cpp \
Random.cpp \
RGBA.cpp \
Score.cpp \
Screen.cpp \
ScreenButton.cpp \
ScreenButtonCircle.cpp \
ScreenButtonDefault.cpp \
ScreenButtonExtended.cpp \
ScreenButtonSimple.cpp \
ScreenButtonSprite.cpp \
ScreenHover.cpp \
ScreenHoverList.cpp \
ScreenHoverCircle.cpp \
ScreenHoverRect.cpp \
ScreenObject.cpp \
ScreenProgress.cpp \
ScreenText.cpp \
ScreenWindow.cpp \
SpriteAnimator.cpp \
TextureCache.cpp \
ThreadProcessMouse.cpp \
ThreadProcessTime.cpp \
Timer.cpp \
ZOrder.cpp \
main.cpp

EXECUTABLE = CrazyCrush
ifeq ($(LINUX), N)
EXECUTABLE :=$(EXECUTABLE).exe
endif

#find headers to dependencies (if edit .h -> make all)
HEADERS := $(wildcard $(HDRDIR)/*.hpp)

# To separate em various path (obj, src, etc)
DIRS_TO_CREATE = $(OBJDIR) $(LIBDIR) $(BINDIR)
SOURCES_WITH_PATH=$(addprefix $(SRCDIR)/,$(SOURCES))
OBJECTS_WITH_PATH=$(addprefix $(OBJDIR)/,$(patsubst %.cpp,%.o,$(SOURCES)))
EXECUTABLE_WITH_PATH=$(addprefix $(BINDIR)/,$(EXECUTABLE))

all:  $(DIRS_TO_CREATE) $(EXECUTABLE_WITH_PATH)

header: $(DIRS_TO_CREATE) $(OBJDIR)/zzzTestHeaders.o
	-del .\obj\zzzTestHeaders.o

no_path: $(OBJECTS_WITH_PATH)
	-@echo Linking   $(EXECUTABLE)
	@$(LD) $(OBJECTS_WITH_PATH) -o $(EXECUTABLE) $(LDFLAGS)
	-copy .\$(EXECUTABLE).exe .\bin\$(EXECUTABLE).exe
	-del .\$(EXECUTABLE).exe
ifeq ($(TIMER), 1)
	-@echo makefile:00: Finished in %time%
endif

main $(EXECUTABLE_WITH_PATH): $(OBJECTS_WITH_PATH)
	-@echo Linking   $(EXECUTABLE_WITH_PATH)
	@$(LD) $(OBJECTS_WITH_PATH) -o $(EXECUTABLE_WITH_PATH) $(LDFLAGS)
ifeq ($(TIMER), 1)
	-@echo makefile:00: Finished in %time%
endif
		
$(OBJDIR)/%.o:$(SRCDIR)/%.cpp $(HEADERS)
	-@echo Compile   $<
	@$(CC) $(CCFLAGS) -c $< -o $@

$(DIRS_TO_CREATE): 
	-mkdir $@

cleandirs: clean
	echo $(LDFLAGS)
	-rmdir $(OBJDIR)
#	-rmdir $(LIBDIR)	

clean:
ifeq ($(LINUX), Y)
	-rm -f $(OBJDIR)/*.o
	-rm -f $(LIBDIR)/*.a
	-rm -f $(EXECUTABLE_WITH_PATH)
	-rm -f $(EXECUTABLE_GUI_WITH_PATH)
else #assume it is windows
	-if exist $(OBJDIR)\*.o del $(OBJDIR)\*.o
	-if exist $(BINDIR)\*.exe del $(BINDIR)\*.exe
endif
