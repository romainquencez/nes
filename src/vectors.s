; src/vectors.s - Interrupt vectors
.export _main
.import _nmi, _reset, _irq

.segment "CODE"

; Reset vector - called on power-up/reset
_reset:
    sei                 ; Disable interrupts
    cld                 ; Clear decimal mode (not used on NES)

    ; Initialize stack
    ldx #$FF
    txs

    ; Wait for PPU to stabilize (2 VBlanks)
    bit $2002
:   bit $2002
    bpl :-
:   bit $2002
    bpl :-

    ; Clear RAM
    lda #$00
    ldx #$00
:   sta $0000, x
    sta $0100, x
    sta $0200, x
    sta $0300, x
    sta $0400, x
    sta $0500, x
    sta $0600, x
    sta $0700, x
    inx
    bne :-

    ; Jump to C main function
    jmp _main

; NMI vector - called every VBlank (~60 Hz)
_nmi:
    rti

; IRQ vector - not used in this example
_irq:
    rti

; Interrupt vectors at end of ROM
.segment "CODE"
.org $FFFA
.word _nmi      ; NMI vector
.word _reset    ; Reset vector
.word _irq      ; IRQ vector
