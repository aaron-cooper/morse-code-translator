.include "zeropage.inc"

.export _lcd_short_wait
.export _lcd_ir_read
.export _lcd_ir_write
.export _lcd_data_read
.export _lcd_data_write

direction_a = %0110000000000011
port_a = %0110000000000001

direction_b = %0110000000000010
port_b = %0110000000000000


.segment "CODE"

;waits for 38 or more cycles to pass, this should be enough time for the LCD
;to complete all but the "Return home" instruction. Calling this is usually
;easier than checking the busy flag
.proc _lcd_short_wait: near
    lda #10 ;2 cycles
@L0: ;run loop 10 times, total of 9*3 + 2 cycles
    dec ;2 cycles
    bne @L0 ;3 except for final, which is 2
    nop
    rts ;at least 3
.endproc

;write to the LCD's instruction register. This is used for most commands
.proc _lcd_ir_write: near
    sta port_a
    lda #0 ;RS = 0, RW = 0
    sta port_b
    jsr lcd_pulse_E
    rts
.endproc

;write contents of A to the LCD's data register
.proc _lcd_data_write: near
    sta port_a
    lda #1 ;RS = 1, RW = 0
    sta port_b
    jsr lcd_pulse_E
    rts
.endproc

; read the LCD's instruction register, return as unsigned char
.proc _lcd_ir_read: near
    lda #$00
    sta direction_a
    lda #%10 ;RW = 1, RS = 0
    sta port_b
    jsr lcd_pulse_E_and_read
    sta tmp1
    lda #$ff
    sta direction_a
    lda tmp1
    ldx #0
    rts
.endproc

; read the LCD's data register, return as unsigned char ;todo repeat fix from above
.proc _lcd_data_read: near
    lda #$00
    sta direction_a
    lda #%11 ;RW = 1, RS = 1
    sta port_b
    jsr lcd_pulse_E
    lda port_a
    sta tmp1
    lda #$ff
    sta direction_a
    lda tmp1
    ldx #0
    rts
.endproc

; the contents of A (aside from bit 2 which corresponds to E) will be written to
; port_b as is
lcd_pulse_E:
    ora #%100
    sta port_b
    and #%11111011
    sta port_b
    rts

lcd_pulse_E_and_read:
    ora #%100
    sta port_b
    lda port_a
    sta tmp2
    lda port_b
    and #%11111011
    sta port_b
    lda tmp2
    rts