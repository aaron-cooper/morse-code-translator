direction_b = %0110000000000010
port_b = %0110000000000000

direction_a = %0110000000000011
port_a = %0110000000000001

.export _dpad_read

.segment "CODE"

.proc _dpad_read: near
    ; set port a to input mode
    lda #0
    sta direction_a
    lda port_a
    pha
    lda #$ff
    sta direction_a
    pla
    rts
.endproc