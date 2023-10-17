.import _init
.import _timer_interrupt_handle
.import _lcd_putc

.segment "CODE"

.segment "VECTORS"

.addr _timer_interrupt_handle
.addr _init
.addr _timer_interrupt_handle