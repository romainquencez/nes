// src/main.c - Simple NES "Hello World" with moving sprite
#include "nes.h"

// Sprite structure (OAM - Object Attribute Memory format)
typedef struct {
    unsigned char y;       // Y position (0-239)
    unsigned char tile;    // Tile index
    unsigned char attr;    // Attributes (palette, flip bits)
    unsigned char x;       // X position (0-255)
} Sprite;

// Sprite data in RAM (copied to OAM during VBlank)
Sprite sprites[64];

// Palette data (4 background + 4 sprite palettes)
const unsigned char palette[32] = {
    // Background palettes
    0x0F, 0x00, 0x10, 0x30,  // Palette 0
    0x0F, 0x00, 0x10, 0x30,  // Palette 1
    0x0F, 0x00, 0x10, 0x30,  // Palette 2
    0x0F, 0x00, 0x10, 0x30,  // Palette 3

    // Sprite palettes
    0x0F, 0x16, 0x27, 0x18,  // Palette 0 (our sprite uses this)
    0x0F, 0x00, 0x10, 0x30,  // Palette 1
    0x0F, 0x00, 0x10, 0x30,  // Palette 2
    0x0F, 0x00, 0x10, 0x30   // Palette 3
};

// Load palette into PPU
void load_palette(void) {
    unsigned char i;

    ppu_off();
    ppu_set_address(0x3F00);  // Palette address in PPU

    for (i = 0; i < 32; ++i) {
        ppu_write_data(palette[i]);
    }
}

// Initialize sprite at position
void init_sprite(unsigned char index, unsigned char x, unsigned char y) {
    sprites[index].x = x;
    sprites[index].y = y;
    sprites[index].tile = 0x01;  // Tile index (from CHR-ROM)
    sprites[index].attr = 0x00;  // Use sprite palette 0
}

// Copy sprites to OAM (must be done during VBlank)
void update_sprites(void) {
    unsigned char i;
    unsigned char* oam = (unsigned char*)0x0200;  // OAM location in RAM
    unsigned char* spr = (unsigned char*)sprites;

    for (i = 0; i < 256; ++i) {
        oam[i] = spr[i];
    }

    // Trigger OAM DMA transfer
    *(unsigned char*)0x4014 = 0x02;  // High byte of OAM address
}

// Main program
void main(void) {
    unsigned char controller;
    unsigned char sprite_x = 100;
    unsigned char sprite_y = 100;

    // Initialize
    ppu_off();
    clear_nametable();
    load_palette();

    // Initialize one sprite
    init_sprite(0, sprite_x, sprite_y);

    // Hide remaining sprites (move offscreen)
    for (unsigned char i = 1; i < 64; ++i) {
        sprites[i].y = 0xFF;
    }

    // Enable NMI and rendering
    PPU_CTRL = PPU_CTRL_NMI | PPU_CTRL_BG_0000 | PPU_CTRL_SPRITE8;
    ppu_on_all();

    // Main game loop
    while (1) {
        ppu_wait_vblank();

        // Read controller
        controller = read_controller();

        // Move sprite based on input
        if (controller & BTN_UP)    sprite_y--;
        if (controller & BTN_DOWN)  sprite_y++;
        if (controller & BTN_LEFT)  sprite_x--;
        if (controller & BTN_RIGHT) sprite_x++;

        // Update sprite position
        sprites[0].x = sprite_x;
        sprites[0].y = sprite_y;

        // Copy sprites to OAM
        update_sprites();
    }
}
