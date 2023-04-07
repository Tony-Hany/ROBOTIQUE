#This is a template to build your own project with the e-puck2_main-processor folder as a library.
#Simply adapt the lines below to be able to compile

# Define project name here
#PROJECT = LineFollwer

#Define path to the e-puck2_main-processor folder
#GLOBAL_PATH = ../e-puck2_main-processor

#Source files to include
#CSRC += ./main.c \
		./audio_processing.c \
		./communications.c \
		./fft.c \

#Header folders to include
#INCDIR += 

#Jump to the main Makefile
#include $(GLOBAL_PATH)/Makefile




# For explanation check readme
##############################################################################
# Project, sources and paths
PROJECT = LineFollower

CSRC += ./main.c \	
		./motor.c \

ASMSRC +=

INCDIR +=

LIBS +=
LIBDIR +=
LIB_OBJ += 

LDSCRIPT +=

DEFS +=

OBJS = $(CSRC:.c=.o) $(ASMSRC:.s=.o)
IINCDIR = $(patsubst %,-I%,$(INCDIR))
LLIBDIR = $(patsubst %,-L%,$(LIBDIR))

##############################################################################
# Compiler settings

MCU  = cortex-m4											#Microcontroller architecture

TRGT = arm-none-eabi-										#Target platform
CC   = $(TRGT)gcc											#C-compiler
LD   = $(TRGT)gcc											#Linker
AS   = $(TRGT)gcc -x assembler-with-cpp						#Assembler
OD   = $(TRGT)objdump										#Object dump =(for generating a disassembly listing of the binary file)
SZ   = $(TRGT)size											#Size tool =(for calculating the size of the final executable or library)
NM   = $(TRGT)nm											#Name tool =(for listing the symbol table of the final executable or library)

# Compiler options:
###################

OPT = -O0 -ggdb
OPT += -fno-common

# THUMB-specific options
TOPT = -mthumb -mno-thumb-interwork

# Define C warning options
CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes

CFLAGS = -mcpu=$(MCU) $(OPT) $(CWARN) $(DEFS) $(TOPT) -MD -MP

ASFLAGS = -mcpu=$(MCU) $(TOPT)

LDFLAGS = -mcpu=$(MCU) $(OPT) -nostartfiles $(LLIBDIR) $(TOPT)
LDFLAGS += -Wl,--no-warn-mismatch,--gc-sections,--script=$(LDSCRIPT)

##############################################################################
# Make targets
#

.PHONY: all
all: $(PROJECT).elf $(PROJECT).list $(PROJECT).size $(PROJECT).mem
	$(SZ) $(PROJECT).elf
	@ echo "> Done"

.PHONY: clean
clean:
	@echo "> Cleaning"
	rm -f $(OBJS)
	rm $(CSRC:%.c=%.d)
	rm -f $(PROJECT).elf $(PROJECT).list $(PROJECT).size $(PROJECT).mem
	@echo "> Done"

%.o: %.c Makefile
	@echo "> Compiling" $(<F)
	$(CC) -c $(CFLAGS) $(IINCDIR) $< -o $@

%.o: %.s Makefile
	@echo "> Compiling" $(<F)
	$(AS) -c $(ASFLAGS) $(IINCDIR) $< -o $@

$(PROJECT).elf: $(OBJS) $(LDSCRIPT)
	@echo "> Linking" $@
	$(LD) $(OBJS) $(LIB_OBJ) $(LDFLAGS) $(LIBS) -o $@

$(PROJECT).list: $(PROJECT).elf
	@echo "> Creating" $@
	$(OD) -d $< > $@

$(PROJECT).size: $(PROJECT).elf
	@echo "> Creating" $@
	$(NM) --size-sort --print-size $< > $@

$(PROJECT).mem: $(PROJECT).elf
	@echo "> Creating" $@
	$(NM) --numeric-sort --print-size $< > $@

.PHONY: flash
flash: all
	arm-none-eabi-gdb --command=../../debug.gdb --command=../../flash.gdb $(PROJECT).elf

-include $(CSRC:%.c=%.d)