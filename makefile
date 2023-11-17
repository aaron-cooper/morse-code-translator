PROGRAM=rom.bin

C_SOURCE_DIR=./c/src
C_INCLUDE_DIR=./c/include
ASM_SOURCE_DIR=./asm/src
ASM_INCLUDE_DIR=./asm/include

BUILD_DIR=./build

CA=ca65
AFLAGS = --cpu 65c02 -I $(ASM_INCLUDE_DIR)

CC=cc65
CFLAGS= --cpu 65c02 -I $(C_INCLUDE_DIR)

LD=ld65
LDFLAGS=

C_SOURCES = main.c lcd.c time.c buttons.c morse_code.c
ASM_SOURCES = input.s lcd.s time.s vectors.s

MKDIR_P=mkdir

RM_P=rm

all: $(BUILD_DIR) $(PROGRAM:%=$(BUILD_DIR)/%)

-include $(BUILD_DIR)/_$(C_SOURCES:.c=.d)

$(PROGRAM:%=$(BUILD_DIR)/%): custom.cfg $(ASM_SOURCES:%.s=$(BUILD_DIR)/%.o) $(C_SOURCES:%.c=$(BUILD_DIR)/_%.o) custom.lib
	$(LD) $(LDFLAGS) -C $^ -o $@

$(BUILD_DIR)/_%.s: $(C_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ --create-dep $(@:.s=.d)

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.s
	$(CA) $(AFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(ASM_SOURCE_DIR)/%.s
	$(CA) $(AFLAGS) $< -o $@ --create-dep $(@:.o=.d)

$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

clean:
	$(RM_P) $(BUILD_DIR) -r

.PHONY: all