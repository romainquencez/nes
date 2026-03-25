// src/neslib.c - Basic NES library functions
#include "nes.h"

// Turn off PPU rendering
void ppu_off(void) {
    PPU_MASK = 0x00;
}

// Enable background rendering only
void ppu_on_bg(void) {
    PPU_MASK = PPU_MASK_BG;
}

// Enable all rendering (background + sprites)
void ppu_on_all(void) {
    PPU_MASK = PPU_MASK_BG | PPU_MASK_SPR;
}

// Wait for vertical blank (safe time to update graphics)
void ppu_wait_vblank(void) {
    while (!(PPU_STATUS & 0x80));  // Wait for VBlank flag
}

// Read controller state
unsigned char read_controller(void) {
    unsigned char buttons = 0;
    unsigned char i;

    // Strobe controller to latch current state
    CONTROLLER1 = 0x01;
    CONTROLLER1 = 0x00;

    // Read 8 button states
    for (i = 0; i < 8; ++i) {
        buttons <<= 1;
        buttons |= (CONTROLLER1 & 0x01);
    }

    return buttons;
}

// Set PPU address for VRAM writes
void ppu_set_address(unsigned int addr) {
    PPU_ADDR = (addr >> 8);    // High byte
    PPU_ADDR = (addr & 0xFF);  // Low byte
}

// Write byte to PPU data register
void ppu_write_data(unsigned char data) {
    PPU_DATA = data;
}

// Clear nametable (background tiles)
void clear_nametable(void) {
    unsigned int i;

    ppu_off();
    ppu_set_address(0x2000);  // Nametable 0 address

    // Write 960 blank tiles (32x30 screen)
    for (i = 0; i < 960; ++i) {
        ppu_write_data(0x00);
    }

    // Write 64 bytes of attribute table (palette data)
    for (i = 0; i < 64; ++i) {
        ppu_write_data(0x00);
    }
}
