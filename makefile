

BUILD_DIR=build
PROGRAM=$(BUILD_DIR)/rom.bin

C_DIR=c
ASM_DIR=asm

C_SOURCE=$(C_DIR)/src
C_INCLUDE=$(C_DIR)/include
ASM_SOURCE=$(ASM_DIR)/src
ASM_INCLUDE=$(ASM_DIR)/include

BUILD_DIR_C=$(BUILD_DIR)/$(C_DIR)
BUILD_DIR_ASM=$(BUILD_DIR)/$(ASM_DIR)

CA=ca65
AFLAGS = --cpu 65c02 -I $(ASM_INCLUDE)

CC=cc65
CFLAGS= --cpu 65c02 -I $(C_INCLUDE)

LD=ld65
LDFLAGS=

C_SOURCES := $(patsubst $(C_SOURCE)/%,%,$(shell find $(C_SOURCE) -name *.c))
ASM_SOURCES := $(patsubst $(ASM_SOURCE)/%,%,$(shell find $(ASM_SOURCE) -name *.s))

MKDIR_P=mkdir -p #-p to create parents as needed

RM_P=rm

#program for loading binary into eeprom
PROGRAMMER_P=minipro -p at28c256 -w

#build dirs listed first to ensure they exist
all: $(PROGRAM)

#cc65 and ca65 will automatically generate dependencies for us!
#include them if they exist, if not, they'll be generated below
-include $(patsubst %.c,$(BUILD_DIR_C)/%.d,$(C_SOURCES))
-include $(patsubst %.s,$(BUILD_DIR_ASM)/%.d,$(ASM_SOURCES))

$(PROGRAM): custom.cfg $(ASM_SOURCES:%.s=$(BUILD_DIR_ASM)/%.o) $(C_SOURCES:%.c=$(BUILD_DIR_C)/%.o) custom.lib
	@$(MKDIR_P) $(@D)
	$(LD) $(LDFLAGS) -C $^ -o $@

#--create-dep generates a makefile that specifies the files depended on
#by target
$(BUILD_DIR_C)/%.s: $(C_SOURCE)/%.c
	@$(MKDIR_P) $(@D)
	$(CC) $(CFLAGS) $< -o $@ --create-dep $(@:.s=.d)

$(BUILD_DIR_C)/%.o: $(BUILD_DIR_C)/%.s
	$(CA) $(AFLAGS) $< -o $@

#--create-dep generates a makefile that specifies the files depended on
#by target
$(BUILD_DIR_ASM)/%.o: $(ASM_SOURCE)/%.s
	@$(MKDIR_P) $(@D)
	$(CA) $(AFLAGS) $< -o $@ --create-dep $(@:.o=.d)

clean:
	$(RM_P) $(BUILD_DIR) -r

# load eepron with program
load: all
	$(PROGRAMMER_P) $(PROGRAM)

.PHONY: all load clean