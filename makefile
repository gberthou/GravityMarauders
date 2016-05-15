GPP=g++
BIN=GravityMarauders

OBJDIR=obj

LIBDIR= 
INCDIR=-I"." -I"./core" -I"./view" -I"./controller"

CFLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic -O2 -g

DEFINES=
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

CPPFILES=$(wildcard *.cpp) $(wildcard core/*.cpp) $(wildcard view/*.cpp) $(wildcard controller/*.cpp)


OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CPPFILES))

$(OBJDIR)/%.o : %.cpp
	$(GPP) $(CFLAGS) $(INCDIR) -c $< -o $@ $(DEFINES)

default: $(OBJS)
	$(GPP) $(OBJS) -o $(BIN) $(LIBDIR) $(LIBS)
	
build:
	mkdir -p $(OBJDIR) $(OBJDIR)/core $(OBJDIR)/view $(OBJDIR)/controller

clean:
	rm -f $(OBJS) 

