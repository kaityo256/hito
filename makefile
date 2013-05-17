TARGET=a.out
#------------------------------------------------------
# Default Parameters
#------------------------------------------------------

CC=g++
CPPFLAGS=-O3 
LDFLAGS=

#------------------------------------------------------
# Compile Option
#------------------------------------------------------

-include makefile.opt

#------------------------------------------------------
# Source Files
#------------------------------------------------------

.SUFFIXES: .c .cc .h. .o .pov .png
SRC=$(shell ls *.cc)
HED=$(shell ls *.h)
OBJ=$(SRC:.cc=.o)
POV=$(shell ls *.pov)
PNG=$(POV:.pov=.png)
#------------------------------------------------------
# Rules
#------------------------------------------------------

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

.cc.o:
	$(CC) $(CPPFLAGS) -c $< 

.PHONY: clean dep

dep:
	g++ -MM -MG $(SRC) >makefile.depend

makefile.depend: 
	g++ -MM -MG $(SRC) >makefile.depend

clean:
	rm -f $(TARGET) $(OBJ) gmon.*.out gmon.out

tar:
	tar cvzf $(TARGET).tar.gz *.cfg $(SRC) $(HED) makefile

png: $(PNG)

.pov.png:
	povray $< 

cleanall: clean
	rm -f *.png
#--------------------------------------------------
-include makefile.depend
