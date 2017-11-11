GPP=g++
BIN=GravityMarauders
SERVER_BIN=GMServer

OBJDIR=obj
SERVER_OBJDIR=obj/server

LIBDIR= 
INCDIR=-I"." -I"./core" -I"./view" -I"./controller" -I"./network" -I"./graphics"

CFLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic -O2 -g

DEFINES=
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

CPPFILES=$(wildcard *.cpp) $(wildcard core/*.cpp) $(wildcard view/*.cpp) $(wildcard controller/*.cpp) $(wildcard network/*.cpp) $(wildcard graphics/*.cpp)


OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CPPFILES))
SERVER_OBJS=$(patsubst %.cpp,$(SERVER_OBJDIR)/%.o,$(CPPFILES))

$(OBJDIR)/%.o : %.cpp
	$(GPP) $(CFLAGS) $(INCDIR) -c $< -o $@ $(DEFINES)

$(SERVER_OBJDIR)/%.o : %.cpp
	$(GPP) $(CFLAGS) $(INCDIR) -c $< -o $@ $(DEFINES) -DSERVER

default: $(BIN)

$(BIN): $(OBJS)
	$(GPP) $(OBJS) -o $(BIN) $(LIBDIR) $(LIBS)

$(SERVER_BIN): $(SERVER_OBJS)
	$(GPP) $(SERVER_OBJS) -o $(SERVER_BIN) $(LIBDIR) $(LIBS)

build:
	mkdir -p $(OBJDIR) $(OBJDIR)/core $(OBJDIR)/view $(OBJDIR)/controller $(OBJDIR)/network $(OBJDIR)/graphics
	mkdir -p $(SERVER_OBJDIR) $(SERVER_OBJDIR)/core $(SERVER_OBJDIR)/view $(SERVER_OBJDIR)/controller $(SERVER_OBJDIR)/network $(SERVER_OBJDIR)/graphics

clean:
	rm -f $(BIN) $(SERVER_BIN) $(OBJS) $(SERVER_OBJS)

.PHONY: check
check:
	cppcheck -I. -I"controller" -I"core" -I"network" -I"ui" -I"view" --inconclusive --enable=all .
