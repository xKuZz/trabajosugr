#############################################################################
# Makefile for building: MH-P1
# Generated by qmake (2.01a) (Qt 4.8.7) on: mi� abr 12 20:49:59 2017
# Project:  ./FUENTES/MH-P1.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -spec /usr/share/qt4/mkspecs/unsupported/linux-clang CONFIG+=debug -o Makefile ./FUENTES/MH-P1.pro
#############################################################################

####### Compiler, tools and options

CC            = /usr/bin/clang-3.9
CXX           = /usr/bin/clang++-3.9
DEFINES       = 
CFLAGS        = -pipe -Qunused-arguments -g -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -Qunused-arguments -std=c++1z -g -Wall -W $(DEFINES) -O3
INCPATH       = -I./FUENTES
LINK          = /usr/bin/clang++-3.9
LFLAGS        = -ccc-gcc-name g++
LIBS          = $(SUBLIBS)    
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

####### Files

SOURCES       = ./FUENTES/main.cpp \
		./FUENTES/inputdata.cpp \
		./FUENTES/greedy.cpp \
		./FUENTES/qaprepresentation.cpp \
		./FUENTES/simulatedannealing.cpp
OBJECTS       = ./OBJ/main.o \
		./OBJ/inputdata.o \
		./OBJ/greedy.o \
		./OBJ/qaprepresentation.o \
		./OBJ/simulatedannealing.o \
		./OBJ/bmb.o \
		./OBJ/grasp.o \
		./OBJ/ils.o

TARGET        = ./BIN/practica2

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: ./BIN/practica2

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

####### Compile

./OBJ/main.o: ./FUENTES/main.cpp ./FUENTES/greedy.h \
		./FUENTES/inputdata.h \
		./FUENTES/qaprepresentation.h \
		./FUENTES/hillclimbing.h \
                ./FUENTES/hillclimbing.cpp \
		./FUENTES/simulatedannealing.h \
		./FUENTES/simulatedannealing.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/main.o ./FUENTES/main.cpp

./OBJ/inputdata.o: ./FUENTES/inputdata.cpp ./FUENTES/inputdata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/inputdata.o ./FUENTES/inputdata.cpp

./OBJ/greedy.o: ./FUENTES/greedy.cpp ./FUENTES/greedy.h \
		./FUENTES/inputdata.h \
		./FUENTES/qaprepresentation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/greedy.o ./FUENTES/greedy.cpp

./OBJ/simulatedannealing.o: ./FUENTES/simulatedannealing.cpp ./FUENTES/simulatedannealing.h \
                ./FUENTES/inputdata.h \
                ./FUENTES/qaprepresentation.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/simulatedannealing.o ./FUENTES/simulatedannealing.cpp

./OBJ/qaprepresentation.o: ./FUENTES/qaprepresentation.cpp ./FUENTES/qaprepresentation.h \
		./FUENTES/inputdata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/qaprepresentation.o ./FUENTES/qaprepresentation.cpp

./OBJ/bmb.o: ./FUENTES/bmb.cpp ./FUENTES/bmb.h \
		./FUENTES/inputdata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/bmb.o ./FUENTES/bmb.cpp

./OBJ/grasp.o: ./FUENTES/grasp.cpp ./FUENTES/grasp.h \
		./FUENTES/inputdata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/grasp.o ./FUENTES/grasp.cpp

./OBJ/ils.o: ./FUENTES/ils.cpp ./FUENTES/ils.h \
		./FUENTES/inputdata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ./OBJ/ils.o ./FUENTES/ils.cpp


clean:
	rm -r ./OBJ/*
	rm -r ./BIN/practica2
