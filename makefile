PROGRAM=rom.bin

C_SOURCES = main.c lcd.c time.c buttons.c
ASM_SOURCES = $(C_SOURCES:%.c=_%.s) input.s lcd.s time.s vectors.s

all: $(PROGRAM)

$(PROGRAM): custom.cfg $(ASM_SOURCES:%.s=%.o) custom.lib
	ld65 -C $^

_%.s: %.c
	cc65 --cpu 65c02 $^ -o $@

%.o: %.s
	ca65 --cpu 65c02 $^

clean:
	rm *.o _*.s rom.bin

.PHONY: clean all