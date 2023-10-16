.include "w65c22.inc"

.export _buttons_preamble
.export _buttons_get_state

.proc _buttons_preamble: near
    lda w65c22_port_b_direction ;port b gets used for other stuff, so don't change other bits
    and #%11000111
    sta w65c22_port_b_direction
    rts
.endproc

.proc _buttons_get_state: near
    lda w65c22_port_b
    ldx #0
    rts
.endproc