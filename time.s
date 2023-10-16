
.export _time
.export _timer_interrupt_handle

.segment "DATA"
_time:
    .dword $00000000

.segment "CODE"

.proc _timer_interrupt_handle: near
    pha
    inc _time
    bne end
    inc _time + 1
    bne end
    inc _time + 2
    bne end
    inc _time + 3
end:
    lda $6004
    pla
    rti
.endproc