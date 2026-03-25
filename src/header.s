; src/header.s - iNES ROM header
.segment "HEADER"

.byte "NES", $1A        ; iNES magic number
.byte $02               ; 2 x 16KB PRG-ROM banks
.byte $01               ; 1 x 8KB CHR-ROM bank
.byte $00               ; Mapper 0 (NROM), horizontal mirroring
.byte $00               ; No special features
.byte $00, $00, $00, $00, $00, $00, $00, $00  ; Padding
