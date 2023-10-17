.include "w65c22.inc"

.export _time
.export _timer_interrupt_handle

.segment "DATA"
_time:
    .dword $00000000

.segment "CODE"

.proc _timer_interrupt_handle: near
    pha ;since this is an interrupt it can't clobber registers
    inc _time
    bne end
    inc _time + 1
    bne end
    inc _time + 2
    bne end
    inc _time + 3
end:
    lda w65c22_timer1_counter_high
    pla
    rti
.endproc