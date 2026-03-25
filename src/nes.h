// src/nes.h - NES hardware definitions
#ifndef NES_H
#define NES_H

// PPU Control Register ($2000)
#define PPU_CTRL   (*(unsigned char*)0x2000)
#define PPU_MASK   (*(unsigned char*)0x2001)
#define PPU_STATUS (*(unsigned char*)0x2002)
#define PPU_SCROLL (*(unsigned char*)0x2005)
#define PPU_ADDR   (*(unsigned char*)0x2006)
#define PPU_DATA   (*(unsigned char*)0x2007)

// PPU Control Flags
#define PPU_CTRL_NMI     0x80  // Enable NMI interrupts
#define PPU_CTRL_SPRITE8 0x00  // 8x8 sprites
#define PPU_CTRL_BG_0000 0x00  // Background pattern table at $0000

// PPU Mask Flags
#define PPU_MASK_BG      0x08  // Show background
#define PPU_MASK_SPR     0x10  // Show sprites
#define PPU_MASK_SHOW    0x1E  // Show all (bg + sprites + leftmost)

// Controller Ports
#define CONTROLLER1 (*(unsigned char*)0x4016)
#define CONTROLLER2 (*(unsigned char*)0x4017)

// Controller Buttons
#define BTN_A      0x01
#define BTN_B      0x02
#define BTN_SELECT 0x04
#define BTN_START  0x08
#define BTN_UP     0x10
#define BTN_DOWN   0x20
#define BTN_LEFT   0x40
#define BTN_RIGHT  0x80

// Function declarations
void ppu_off(void);
void ppu_on_bg(void);
void ppu_on_all(void);
void ppu_wait_vblank(void);
unsigned char read_controller(void);

#endif // NES_H
