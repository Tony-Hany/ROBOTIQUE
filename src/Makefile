##################################
#For explanation check readme/wiki
##################################

#SECTION 1 - Project, sources and paths:
########################################

PROJECT = LineFollower

GLOBAL_PATH = ../e-puck2_main-processor

CSRC += ./main.c \

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

#SECTION 2 - Compiler settings:
###############################

ifeq ($(optimise), true)

MCU  = cortex-m4

TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
LD   = $(TRGT)gcc
AS   = $(TRGT)gcc -x assembler-with-cpp
OD   = $(TRGT)objdump
SZ   = $(TRGT)size
NM   = $(TRGT)nm

# Compiler options
OPT = -O0 -ggdb
OPT += -fno-common

# THUMB-specific options
TOPT = -mthumb -mno-thumb-interwork

# Define C warning options
CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes

#Flags
CFLAGS = -mcpu=$(MCU) $(OPT) $(CWARN) $(DEFS) $(TOPT) -MD -MP
ASFLAGS = -mcpu=$(MCU) $(TOPT)
LDFLAGS = -mcpu=$(MCU) $(OPT) -nostartfiles $(LLIBDIR) $(TOPT)
LDFLAGS += -Wl,--no-warn-mismatch,--gc-sections,--script=$(LDSCRIPT)

endif

# SECTION 3 - Make targets:
###########################

include $(GLOBAL_PATH)/Makefile

ifeq ($(optimise), true)

.PHONY: dclean
dclean:
	@echo -e "\\033[1;32m> Starting Deep Cleaning"
	@rm -f *.o *.d *.mem *.list *.size *.elf *.a ; \
		echo "> Removed files: .o .d .mem .list .size .elf and .a"; \

	@if [ -d .dep ]; then \
		rm -rf .dep; \
		echo "> .dep removed"; \
	else \
		echo "> .dep was already removed"; \
	fi

	@if [ -d build ]; then \
		rm -rf build; \
		echo "build removed"; \
	else \
		echo "> build was already removed"; \
	fi

	@echo "> Deep Cleaning Done"

.PHONY: commitprep
commitprep:
	@echo -e "\\033[1;32m> Starting by Deep Cleaning"
	@rm -f *.o *.d *.mem *.list *.size *.elf *.a ; \
		echo "> Removed files: .o .d .mem .list .size .elf and .a"; \

	@if [ -d .dep ]; then \
		rm -rf .dep; \
		echo "> .dep removed"; \
	else \
		echo "> .dep was already removed"; \
	fi

	@if [ -d build ]; then \
		rm -rf build; \
		echo "build removed"; \
	else \
		echo "> build was already removed"; \
	fi

	@echo "> Deep Cleaning Done"
	@echo "> Now unlinking the library"
	@rm -rf ../e-puck2_main-processor
	@echo "> library removed"
	@echo "You can commit now"

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

endif