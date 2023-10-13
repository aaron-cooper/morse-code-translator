RS = %001
RW = %010
E  = %00000100
NE = %11111011

.include "zeropage.inc"

.export _lcd_init

direction_a = %0110000000000011
port_a = %0110000000000001

direction_b = %0110000000000010
port_b = %0110000000000000


.segment "CODE"

.proc _lcd_init: near
    lda #$ff
    sta direction_a
    sta direction_b

    lda #$00
    sta port_b

    lda #%00111000
    sta port_a
    lda #E
    sta port_b
    lda #0
    sta port_b

    jsr lcd_short_wait

    lda #%00001110
    sta port_a
    lda #E
    sta port_b
    lda #0
    sta port_b

    jsr lcd_short_wait

    lda #%00000110
    sta port_a
    lda #E
    sta port_b
    lda #0
    sta port_b
    
    jsr lcd_short_wait

    lda #%1
    sta port_b
    lda #%01001000
    sta port_a
    lda #%101
    sta port_b
    lda #1
    sta port_b
.endproc

.proc lcd_short_wait: ;wait for a minimum of 38 cycles
    lda #10 ;2 cycles
@L0: ;run loop 10 times, total of 9*3 + 2 cycles
    dec ;2 cycles
    bne @L0 ;3 except for final, which is 2
    nop
    rts ;at least 3
.endproc
