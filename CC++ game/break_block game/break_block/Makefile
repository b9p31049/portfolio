# <- Lines start from # are comments.

#########################################################
# Library directories
#########################################################

LIBRARY_DIRECTORY = ../pdcurses_library
COMPILE		= cl.exe -nologo -I$(LIBRARY_DIRECTORY) -c -utf-8 -EHsc

#########################################################
# The name of .exe
#########################################################

TARGET_NAME = demo

all: $(TARGET_NAME).exe

#########################################################
# The list of objs we need to make .exe
#########################################################

OBJS		= main.obj paddle.obj wall.obj ball.obj block.obj 

main.obj : main.cpp sys.h
	$(COMPILE) $*.cpp

paddle.obj : paddle.cpp paddle.h sys.h
	$(COMPILE) $*.cpp

wall.obj : wall.cpp wall.h
	$(COMPILE) $*.cpp

ball.obj : ball.cpp ball.h sys.h
	$(COMPILE) $*.cpp

block.obj : block.cpp block.h sys.h
	$(COMPILE) $*.cpp


#########################################################
# Libraries
#########################################################

LIBRARY = pdcurses.lib

#########################################################
# Target of Makefile.
# all: The default target.
# clean: Delete all products we made so far
#########################################################


clean:
	del *.obj
	del *.exe

#########################################################
# How to compile : .cpp => .obj 
#########################################################

# A Rule to convert .cpp to .obj
#.cpp.obj:
#	$(COMPILE) $<

#########################################################
# How to link : .obj => .exe
#########################################################

LINK		= link.exe -nologo ws2_32.lib  user32.lib advapi32.lib $(LIBRARY_DIRECTORY)/$(LIBRARY) -out:$(TARGET_NAME).exe 

sys.obj : sys.cpp sys.h
	$(COMPILE) $*.cpp

# A Rule to convert .obj to .exe
$(TARGET_NAME).exe : $(OBJS) sys.obj
	$(LINK) $(OBJS) sys.obj




