.include "zeropage.inc"
.include "w65c22.inc"

.export _lcd_short_wait
.export _lcd_ir_read
.export _lcd_ir_write
.export _lcd_data_read
.export _lcd_data_write
.export _lcd_preamble

.segment "CODE"

; Things that need to be done before the LCD can be used. Needs be called
; before touching the lcd, calling multiple times won't hurt anything.
.proc _lcd_preamble: near
    lda #$ff
    sta w65c22_port_a_direction
    lda w65c22_port_b_direction ;port b gets used for other stuff, so don't change bits 3-7
    ora #%00000111
    sta w65c22_port_b_direction ;port b gets used for other stuff, so don't change bits 3-7
.endproc

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
    sta w65c22_port_a
    lda #0 ;RS = 0, RW = 0
    sta w65c22_port_b
    jsr lcd_pulse_E
    rts
.endproc

;write contents of A to the LCD's data register
.proc _lcd_data_write: near
    sta w65c22_port_a
    lda #1 ;RS = 1, RW = 0
    sta w65c22_port_b
    jsr lcd_pulse_E
    rts
.endproc

; read the LCD's instruction register, return as unsigned char
.proc _lcd_ir_read: near
    lda #$00
    sta w65c22_port_a_direction
    lda #%10 ;RW = 1, RS = 0
    sta w65c22_port_b
    jsr lcd_pulse_E_and_read
    sta tmp1
    lda #$ff
    sta w65c22_port_a_direction
    lda tmp1
    ldx #0
    rts
.endproc

; read the LCD's data register, return as unsigned char ;todo repeat fix from above
.proc _lcd_data_read: near
    lda #$00
    sta w65c22_port_a_direction
    lda #%11 ;RW = 1, RS = 1
    sta w65c22_port_b
    jsr lcd_pulse_E
    lda w65c22_port_a
    sta tmp1
    lda #$ff
    sta w65c22_port_a_direction
    lda tmp1
    ldx #0
    rts
.endproc

; the contents of A (aside from bit 2 which corresponds to E) will be written to
; w65c22_port_b as is
lcd_pulse_E:
    sei
    ora #%100
    sta w65c22_port_b
    and #%11111011
    sta w65c22_port_b
    cli
    rts

lcd_pulse_E_and_read:
    sei
    ora #%100
    sta w65c22_port_b
    lda w65c22_port_a
    sta tmp2
    lda w65c22_port_b
    and #%11111011
    sta w65c22_port_b
    lda tmp2
    cli
    rts