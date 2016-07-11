# Makefile for AG0700 projects.

# Use the ARM C++ toolchain.
CC = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy

# Compiler options:
# -g      Enable debugging symbols
# -O3     Full compiler optimisations
# -Wall   Enable all warnings
CFLAGS = -g -O3 -Wall

# Architecture options for the GBA.
MODEL = -mthumb -mthumb-interwork -specs=gba_mb.specs

# The name of the program to build.
TARGET = main

# The object files to link into the final program.
# The rules below will build foo.o from foo.cpp automatically.
OBJECTS = \
	$(TARGET).o \
	gba.o \
	font.o \
	background.o \
	sprites.o

# The default target to make if none is specified.
all: $(TARGET).gba

# Convert a .elf file into a .gba ROM image.
%.gba: %.elf
	$(OBJCOPY) -O binary $< $@
	gbafix $@

# Link .o files together to produce a .elf file.
$(TARGET).elf: $(OBJECTS)
	$(CC) $(MODEL) -o $@ $^ -lm

# Compile a .cpp file into a .o file.
%.o: %.cpp
	$(CC) $(CFLAGS) $(MODEL) -c $<

# Run the ROM image using VBA.
run: $(TARGET).gba
	VisualBoyAdvance $(TARGET).gba

# Run a program with a different value of TARGET.
# (This lets you have multiple GBA programs in the same directory;
# if you have foo.cpp, you can compile and run it with "make run-foo".)
run-%:
	@$(MAKE) run TARGET=$*

# Remove all the compiled files.	
clean:
	rm -f *.gba *.elf *.o depend.mk

# Automatically extract dependencies from .cpp files.
# Invoking the compiler with -MM below makes it scan the source files and
# write out Makefile-style rules saying which other files they depend upon;
# we then include that file.
-include depend.mk
depend.mk: *.cpp *.h
	$(CC) -MM *.cpp >depend.mk
