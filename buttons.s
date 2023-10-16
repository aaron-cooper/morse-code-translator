.include "w65c22.inc"

.proc _buttons_preamble: near
    lda w65c22_port_b_direction ;port b gets used for other stuff, so don't change other bits
    ora #%00111000
    sta w65c22_port_b_direction
    rts
.endproc

.proc _buttons_get_state: near
    lda w65c22_port_b
    and #%00111000
    ldx #0
    rts
.endproc