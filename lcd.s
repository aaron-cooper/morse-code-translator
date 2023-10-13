RS = %001
RW = %010
E  = %00000100
NE = %11111011

.include "zeropage.inc"

.export _lcd_init
.export _lcd_puts

direction_b = %0110000000000010
port_b = %0110000000000000

direction_a = %0110000000000011
port_a = %0110000000000001

.zeropage
_str_loc:   .res 2

.segment "CODE"

_lcd_set_port_a:
    sta regsave
    jsr lcd_busy_wait
    rts



.proc _lcd_puts: near
    sta _str_loc
    stx _str_loc + 1
    ldy #00

loop:
    lda (_str_loc),y
    beq ret
    iny
    pha
    jsr lcd_busy_wait
    pla
    sta port_a ;put the character out on port_b
    lda #RS
    sta port_b
    lda #(RS | E); pulse the clock pin
    sta port_b
    lda #RW
    sta port_b
    bra loop
ret:
    rts

.endproc

.proc _lcd_init: near

    ;set pins for A and B to output mode.
    jsr lcd_output_mode
    lda direction_b
    ora #(E | RW | RS)

    ;put all output pins low. TODO: don't touch other pins in port_b
    lda #0
    sta port_a
    sta port_b

    ;function set
    jsr lcd_busy_wait
    lda #%00111000
    sta port_a
    jsr lcd_pulse_clock

    
    ;set display stuff
    jsr lcd_busy_wait
    lda #%00001110
    sta port_a
    jsr lcd_pulse_clock

    ;entry mode
    jsr lcd_busy_wait
    lda #%00000110
    sta port_a
    jsr lcd_pulse_clock

    ;clear display
    jsr lcd_busy_wait
    lda #1
    sta port_a
    jsr lcd_pulse_clock

    rts
.endproc

.proc _lcd_clear
    jsr lcd_busy_wait
    lda #1
    sta port_b
    lda #0
    sta port_a
    lda #%10000000 ;put E high
    sta port_a
    lda #0
    sta port_a 
.endproc

lcd_busy_wait:
    lda port_b
    ora #RW
    and #!RS
    sta port_b

L0: jsr _lcd_receive
    and #%10000000
    bne L0
    rts


lcd_pulse_clock:
    lda port_b
    ora #E
    sta port_b
    and #%11111011
    sta port_b
    rts

lcd_input_mode:
    lda #0
    sta direction_a
    rts

lcd_output_mode:
    lda #$ff
    sta direction_a
    rts

.proc _lcd_receive: near
    jsr lcd_input_mode

    lda port_b ;assert E while leaving other pins untouched
    ora #E
    sta port_b

    lda port_a ;read from port a and set value aside
    sta tmp1

    lda port_b ;unassert E while leaving other pins untouched
    and # NE
    sta port_b

    jsr lcd_output_mode
    lda tmp1 ;value is returned in A
    ldx #0 ;compiler wants us to promote the value and return the high byte in x
    rts
.endproc