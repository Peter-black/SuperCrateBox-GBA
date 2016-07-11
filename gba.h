/* GBA development header for AG0700, based on:
 * gba.h by eloist
 *
 * If you have additions or corrections to this header, please send
 * them to Adam Sampson <a.sampson@abertay.ac.uk>.
 */

#ifndef GBA_H
#define GBA_H

#include <stdint.h>

#define REGISTER_PTR(type, addr) ((volatile type *) (addr))
#define REGISTER(type, addr) (*REGISTER_PTR(type, (addr)))

// Video memory addresses

#define REG_PALETTE_BG       REGISTER_PTR(uint16_t, 0x5000000)
#define REG_PALETTE_OBJ      REGISTER_PTR(uint16_t, 0x5000200)
#define REG_VIDEO_BASE       REGISTER_PTR(uint16_t, 0x6000000)
#define REG_VIDEO_PAGE1      REGISTER_PTR(uint16_t, 0x6000000)
#define REG_VIDEO_PAGE2      REGISTER_PTR(uint16_t, 0x600A000)
#define REG_OBJ_BASE         REGISTER_PTR(uint16_t, 0x7000000)

// General registers

#define REG_INTERUPT         REGISTER(uint32_t, 0x3007FFC)
#define REG_DISPCNT          REGISTER(uint32_t, 0x4000000)
#define REG_DISPCNT_L        REGISTER(uint16_t, 0x4000000)
#define REG_DISPCNT_H        REGISTER(uint16_t, 0x4000002)
#define REG_DISPSTAT         REGISTER(uint16_t, 0x4000004)
#define REG_VCOUNT           REGISTER(uint16_t, 0x4000006)
#define REG_BG0CNT           REGISTER(uint16_t, 0x4000008)
#define REG_BG1CNT           REGISTER(uint16_t, 0x400000A)
#define REG_BG2CNT           REGISTER(uint16_t, 0x400000C)
#define REG_BG3CNT           REGISTER(uint16_t, 0x400000E)
#define REG_BG0HOFS          REGISTER(uint16_t, 0x4000010)
#define REG_BG0VOFS          REGISTER(uint16_t, 0x4000012)
#define REG_BG1HOFS          REGISTER(uint16_t, 0x4000014)
#define REG_BG1VOFS          REGISTER(uint16_t, 0x4000016)
#define REG_BG2HOFS          REGISTER(uint16_t, 0x4000018)
#define REG_BG2VOFS          REGISTER(uint16_t, 0x400001A)
#define REG_BG3HOFS          REGISTER(uint16_t, 0x400001C)
#define REG_BG3VOFS          REGISTER(uint16_t, 0x400001E)
#define REG_BG2PA            REGISTER(uint16_t, 0x4000020)
#define REG_BG2PB            REGISTER(uint16_t, 0x4000022)
#define REG_BG2PC            REGISTER(uint16_t, 0x4000024)
#define REG_BG2PD            REGISTER(uint16_t, 0x4000026)
#define REG_BG2X             REGISTER(uint32_t, 0x4000028)
#define REG_BG2X_L           REGISTER(uint16_t, 0x4000028)
#define REG_BG2X_H           REGISTER(uint16_t, 0x400002A)
#define REG_BG2Y             REGISTER(uint32_t, 0x400002C)
#define REG_BG2Y_L           REGISTER(uint16_t, 0x400002C)
#define REG_BG2Y_H           REGISTER(uint16_t, 0x400002E)
#define REG_BG3PA            REGISTER(uint16_t, 0x4000030)
#define REG_BG3PB            REGISTER(uint16_t, 0x4000032)
#define REG_BG3PC            REGISTER(uint16_t, 0x4000034)
#define REG_BG3PD            REGISTER(uint16_t, 0x4000036)
#define REG_BG3X             REGISTER(uint32_t, 0x4000038)
#define REG_BG3X_L           REGISTER(uint16_t, 0x4000038)
#define REG_BG3X_H           REGISTER(uint16_t, 0x400003A)
#define REG_BG3Y             REGISTER(uint32_t, 0x400003C)
#define REG_BG3Y_L           REGISTER(uint16_t, 0x400003C)
#define REG_BG3Y_H           REGISTER(uint16_t, 0x400003E)
#define REG_WIN0H            REGISTER(uint16_t, 0x4000040)
#define REG_WIN1H            REGISTER(uint16_t, 0x4000042)
#define REG_WIN0V            REGISTER(uint16_t, 0x4000044)
#define REG_WIN1V            REGISTER(uint16_t, 0x4000046)
#define REG_WININ            REGISTER(uint16_t, 0x4000048)
#define REG_WINOUT           REGISTER(uint16_t, 0x400004A)
#define REG_MOSAIC           REGISTER(uint32_t, 0x400004C)
#define REG_MOSAIC_L         REGISTER(uint32_t, 0x400004C)
#define REG_MOSAIC_H         REGISTER(uint32_t, 0x400004E)
#define REG_BLDMOD           REGISTER(uint16_t, 0x4000050)
#define REG_COLEV            REGISTER(uint16_t, 0x4000052)
#define REG_COLEY            REGISTER(uint16_t, 0x4000054)
#define REG_SG10             REGISTER(uint32_t, 0x4000060)
#define REG_SG10_L           REGISTER(uint16_t, 0x4000060)
#define REG_SG10_H           REGISTER(uint16_t, 0x4000062)
#define REG_SG11             REGISTER(uint16_t, 0x4000064)
#define REG_SG20             REGISTER(uint16_t, 0x4000068)
#define REG_SG21             REGISTER(uint16_t, 0x400006C)
#define REG_SG30             REGISTER(uint32_t, 0x4000070)
#define REG_SG30_L           REGISTER(uint16_t, 0x4000070)
#define REG_SG30_H           REGISTER(uint16_t, 0x4000072)
#define REG_SG31             REGISTER(uint16_t, 0x4000074)
#define REG_SG40             REGISTER(uint16_t, 0x4000078)
#define REG_SG41             REGISTER(uint16_t, 0x400007C)
#define REG_SGCNT0           REGISTER(uint32_t, 0x4000080)
#define REG_SGCNT0_L         REGISTER(uint16_t, 0x4000080)
#define REG_SGCNT0_H         REGISTER(uint16_t, 0x4000082)
#define REG_SGCNT1           REGISTER(uint16_t, 0x4000084)
#define REG_SGBIAS           REGISTER(uint16_t, 0x4000088)
#define REG_SGWR0            REGISTER(uint32_t, 0x4000090)
#define REG_SGWR0_L          REGISTER(uint16_t, 0x4000090)
#define REG_SGWR0_H          REGISTER(uint16_t, 0x4000092)
#define REG_SGWR1            REGISTER(uint32_t, 0x4000094)
#define REG_SGWR1_L          REGISTER(uint16_t, 0x4000094)
#define REG_SGWR1_H          REGISTER(uint16_t, 0x4000096)
#define REG_SGWR2            REGISTER(uint32_t, 0x4000098)
#define REG_SGWR2_L          REGISTER(uint16_t, 0x4000098)
#define REG_SGWR2_H          REGISTER(uint16_t, 0x400009A)
#define REG_SGWR3            REGISTER(uint32_t, 0x400009C)
#define REG_SGWR3_L          REGISTER(uint16_t, 0x400009C)
#define REG_SGWR3_H          REGISTER(uint16_t, 0x400009E)
#define REG_SGFIF0A          REGISTER(uint32_t, 0x40000A0)
#define REG_SGFIFOA_L        REGISTER(uint16_t, 0x40000A0)
#define REG_SGFIFOA_H        REGISTER(uint16_t, 0x40000A2)
#define REG_SGFIFOB          REGISTER(uint32_t, 0x40000A4)
#define REG_SGFIFOB_L        REGISTER(uint16_t, 0x40000A4)
#define REG_SGFIFOB_H        REGISTER(uint16_t, 0x40000A6)
#define REG_DM0SAD           REGISTER(uint32_t, 0x40000B0)
#define REG_DM0SAD_L         REGISTER(uint16_t, 0x40000B0)
#define REG_DM0SAD_H         REGISTER(uint16_t, 0x40000B2)
#define REG_DM0DAD           REGISTER(uint32_t, 0x40000B4)
#define REG_DM0DAD_L         REGISTER(uint16_t, 0x40000B4)
#define REG_DM0DAD_H         REGISTER(uint16_t, 0x40000B6)
#define REG_DM0CNT           REGISTER(uint32_t, 0x40000B8)
#define REG_DM0CNT_L         REGISTER(uint16_t, 0x40000B8)
#define REG_DM0CNT_H         REGISTER(uint16_t, 0x40000BA)
#define REG_DM1SAD           REGISTER(uint32_t, 0x40000BC)
#define REG_DM1SAD_L         REGISTER(uint16_t, 0x40000BC)
#define REG_DM1SAD_H         REGISTER(uint16_t, 0x40000BE)
#define REG_DM1DAD           REGISTER(uint32_t, 0x40000C0)
#define REG_DM1DAD_L         REGISTER(uint16_t, 0x40000C0)
#define REG_DM1DAD_H         REGISTER(uint16_t, 0x40000C2)
#define REG_DM1CNT           REGISTER(uint32_t, 0x40000C4)
#define REG_DM1CNT_L         REGISTER(uint16_t, 0x40000C4)
#define REG_DM1CNT_H         REGISTER(uint16_t, 0x40000C6)
#define REG_DM2SAD           REGISTER(uint32_t, 0x40000C8)
#define REG_DM2SAD_L         REGISTER(uint16_t, 0x40000C8)
#define REG_DM2SAD_H         REGISTER(uint16_t, 0x40000CA)
#define REG_DM2DAD           REGISTER(uint32_t, 0x40000CC)
#define REG_DM2DAD_L         REGISTER(uint16_t, 0x40000CC)
#define REG_DM2DAD_H         REGISTER(uint16_t, 0x40000CE)
#define REG_DM2CNT           REGISTER(uint32_t, 0x40000D0)
#define REG_DM2CNT_L         REGISTER(uint16_t, 0x40000D0)
#define REG_DM2CNT_H         REGISTER(uint16_t, 0x40000D2)
#define REG_DM3SAD           REGISTER(uint32_t, 0x40000D4)
#define REG_DM3SAD_L         REGISTER(uint16_t, 0x40000D4)
#define REG_DM3SAD_H         REGISTER(uint16_t, 0x40000D6)
#define REG_DM3DAD           REGISTER(uint32_t, 0x40000D8)
#define REG_DM3DAD_L         REGISTER(uint16_t, 0x40000D8)
#define REG_DM3DAD_H         REGISTER(uint16_t, 0x40000DA)
#define REG_DM3CNT           REGISTER(uint32_t, 0x40000DC)
#define REG_DM3CNT_L         REGISTER(uint16_t, 0x40000DC)
#define REG_DM3CNT_H         REGISTER(uint16_t, 0x40000DE)
#define REG_TM0D             REGISTER(uint16_t, 0x4000100)
#define REG_TM0CNT           REGISTER(uint16_t, 0x4000102)
#define REG_TM1D             REGISTER(uint16_t, 0x4000104)
#define REG_TM1CNT           REGISTER(uint16_t, 0x4000106)
#define REG_TM2D             REGISTER(uint16_t, 0x4000108)
#define REG_TM2CNT           REGISTER(uint16_t, 0x400010A)
#define REG_TM3D             REGISTER(uint16_t, 0x400010C)
#define REG_TM3CNT           REGISTER(uint16_t, 0x400010E)
#define REG_SCD0             REGISTER(uint16_t, 0x4000120)
#define REG_SCD1             REGISTER(uint16_t, 0x4000122)
#define REG_SCD2             REGISTER(uint16_t, 0x4000124)
#define REG_SCD3             REGISTER(uint16_t, 0x4000126)
#define REG_SCCNT            REGISTER(uint32_t, 0x4000128)
#define REG_SCCNT_L          REGISTER(uint16_t, 0x4000128)
#define REG_SCCNT_H          REGISTER(uint16_t, 0x400012A)
#define REG_KEYINPUT         REGISTER(uint16_t, 0x4000130)
#define REG_KEYCNT           REGISTER(uint16_t, 0x4000132)
#define REG_R                REGISTER(uint16_t, 0x4000134)
#define REG_HS_CTRL          REGISTER(uint16_t, 0x4000140)
#define REG_JOYRE            REGISTER(uint32_t, 0x4000150)
#define REG_JOYRE_L          REGISTER(uint16_t, 0x4000150)
#define REG_JOYRE_H          REGISTER(uint16_t, 0x4000152)
#define REG_JOYTR            REGISTER(uint32_t, 0x4000154)
#define REG_JOYTR_L          REGISTER(uint16_t, 0x4000154)
#define REG_JOYTR_H          REGISTER(uint16_t, 0x4000156)
#define REG_JSTAT            REGISTER(uint32_t, 0x4000158)
#define REG_JSTAT_L          REGISTER(uint16_t, 0x4000158)
#define REG_JSTAT_H          REGISTER(uint16_t, 0x400015A)
#define REG_IE               REGISTER(uint16_t, 0x4000200)
#define REG_IF               REGISTER(uint16_t, 0x4000202)
#define REG_WSCNT            REGISTER(uint16_t, 0x4000204)
#define REG_IME              REGISTER(uint16_t, 0x4000208)
#define REG_PAUSE            REGISTER(uint16_t, 0x4000300)

// Alternative names for registers (from the Harbour book, rather than TONC)

#define REG_P1               REG_KEYINPUT
#define REG_P1CNT            REG_KEYCNT

// Graphics constants

#define SCREEN_WIDTH         240
#define SCREEN_HEIGHT        160

// Flags in REG_DISPCNT

#define DCNT_MODE0           0x0
#define DCNT_MODE1           0x1
#define DCNT_MODE2           0x2
#define DCNT_MODE3           0x3
#define DCNT_MODE4           0x4
#define DCNT_MODE5           0x5

#define DCNT_GB              (1 << 3)
#define DCNT_PAGE            (1 << 4)
#define DCNT_OAM_HBL         (1 << 5)
#define DCNT_OBJ_1D          (1 << 6)
#define DCNT_BLANK           (1 << 7)
#define DCNT_BG0             (1 << 8)
#define DCNT_BG1             (1 << 9)
#define DCNT_BG2             (1 << 10)
#define DCNT_BG3             (1 << 11)
#define DCNT_OBJ             (1 << 12)
#define DCNT_W0              (1 << 13)
#define DCNT_W1              (1 << 14)
#define DCNT_OW              (1 << 15)

// Bit names we used in the first semester
#define BG2_ENABLE           DCNT_BG2
#define MODE3                DCNT_MODE3
#define MODE4                DCNT_MODE4

// Flags in REG_BGxCNT

#define BG_PRIO(v)           (v)
#define BG_CBB(v)            ((v) << 2)
#define BG_MOSAIC            (1 << 6)
#define BG_4BPP              (0 << 7)
#define BG_8BPP              (1 << 7)
#define BG_SBB(v)            ((v) << 8)
#define BG_WRAP              (1 << 13)

// Sizes for regular backgrounds
#define BG_REG_32x32         (0 << 14)
#define BG_REG_64x32         (1 << 14)
#define BG_REG_32x64         (2 << 14)
#define BG_REG_64x64         (3 << 14)

// Sizes for affine backgrounds
#define BG_AFF_16x16         (0 << 14)
#define BG_AFF_32x32         (1 << 14)
#define BG_AFF_64x64         (2 << 14)
#define BG_AFF_128x128       (3 << 14)

// Key bits (in REG_P1)

#define KEY_A                1
#define KEY_B                2
#define KEY_SELECT           4
#define KEY_START            8
#define KEY_RIGHT            16
#define KEY_LEFT             32
#define KEY_UP               64
#define KEY_DOWN             128
#define KEY_R                256
#define KEY_L                512

// DMA flags (untested -- probably broken)

// Enable DMA operation
#define DMACNT_ENABLE        ((1 << 31) & (0x80000000))
// Increment Destination after copy
#define DMACNT_INCDEST       (0)
// Decrement Destination after copy
#define DMACNT_DECDEST       ((1 << 21) & (0x200000))
// Leave Destination unchanged after copy
#define DMACNT_FIXDEST       ((1 << 22) & (0x400000))
// Increment Source after copy
#define DMACNT_INCSRC        (0)
// Decrement Source after copy
#define DMACNT_DECSRC        ((1 << 23) & (0x800000))
// Leave Source unchanged after copy
#define DMACNT_FIXSRC        ((1 << 24) & (0x1000000))
// Copy 32 bits at a time
#define DMACNT_32BIT         ((1 << 26) & (0x4000000))
// Copy 16 bits at a time
#define DMACNT_16BIT         (0)

// Flags in screenblock entries

#define SE_ID(v)             (v)
#define SE_HFLIP             (1 << 10)
#define SE_VFLIP             (1 << 11)
#define SE_PALBANK(v)        ((v) << 12)

// Structures in the OAM

#define NUM_OBJECTS          128

struct ObjAttr {
	uint16_t attr0;
	uint16_t attr1;
	uint16_t attr2;
	uint16_t pad;
} __attribute__((aligned(4), packed));

#define ATTR0_Y(v)           (v)
#define ATTR0_Y_MASK         ATTR0_Y(0xFF)
#define ATTR0_REG            (0 << 8)
#define ATTR0_AFF            (1 << 8)
#define ATTR0_HIDE           (2 << 8)
#define ATTR0_AFF_DBL        (3 << 8)
#define ATTR0_BLEND          (1 << 10)
#define ATTR0_WIN            (1 << 11)
#define ATTR0_MOSAIC         (1 << 12)
#define ATTR0_4BPP           (0 << 13)
#define ATTR0_8BPP           (1 << 13)
#define ATTR0_SHAPE(v)       ((v) << 14)
#define ATTR0_SQUARE         (0 << 14)
#define ATTR0_WIDE           (1 << 14)
#define ATTR0_TALL		     (2 << 14)

#define ATTR1_X(v)           (v)
#define ATTR1_X_MASK         ATTR1_X(0x1FF)
#define ATTR1_AFF(v)         ((v) << 9)
#define ATTR1_HFLIP          (1 << 12)
#define ATTR1_VFLIP          (1 << 13)
#define ATTR1_SIZE(v)        ((v) << 14)

#define ATTR2_ID(v)          (v)
#define ATTR2_ID4(v)         (v)
#define ATTR2_ID8(v)         ((v) * 2)
#define ATTR2_PRIO(v)        ((v) << 10)
#define ATTR2_PALBANK(v)     ((v) << 12)

struct ObjAffine {
	uint16_t pad0[3];
	int16_t pa;
	uint16_t pad1[3];
	int16_t pb;
	uint16_t pad2[3];
	int16_t pc;
	uint16_t pad3[3];
	int16_t pd;
} __attribute__((aligned(4), packed));

// Prototypes for things in gba.cpp

// The 8bpp display we're currently drawing to
extern volatile uint16_t *BackBuffer;

// The object buffer (a back buffer for the OAM)
extern ObjAttr ObjBuffer[NUM_OBJECTS];

// Wait for the start of the next video frame
void WaitVSync();

// Swap the front and back buffers.
// (If page-flipping is not already in use, this will enable it.)
void FlipBuffers();

// Clear the screen in an 8bpp mode
void ClearScreen8(uint8_t colour);

// Clear the screen in a 16bpp mode
void ClearScreen16(uint16_t colour);

// Copy the contents of the front buffer into the back buffer.
// (This is useful if you want to use page-flipping, but you still want
// the contents of the screen to persist between frames.)
void CopyScreen();

// Initialise the object buffer and OAM, so that no objects are visible.
void ClearObjects();

// Copy the object buffer into the OAM.
// This should be called immediately after WaitVSync().
void UpdateObjects();

// Copy data into video RAM, 16 bits at a time.
void CopyToVRAM(volatile uint16_t *dest, const uint16_t *src, int num_words);

// Graphics utility functions (short enough to be worth inlining)

// Construct an RGB colour value
static inline uint16_t RGB(uint16_t r, uint16_t g, uint16_t b)
{
	return (b << 10) | (g << 5) | r;
}

// Plot a pixel on the background in a 16bpp mode
static inline void PlotPixel16(int x, int y, uint16_t colour)
{
	// FIXME: check x, y in bounds
	REG_VIDEO_BASE[y * SCREEN_WIDTH + x] = colour;
}

// Get the colour of a pixel on the background in a 16bpp mode
static inline uint16_t GetPixel16(int x, int y)
{
	return REG_VIDEO_BASE[y * SCREEN_WIDTH + x];
}

// Plot a pixel on the background in an 8bpp mode
static inline void PlotPixel8(int x, int y, uint8_t colour)
{
	// FIXME: check x, y in bounds
	volatile uint16_t& pixel(BackBuffer[(y * SCREEN_WIDTH + x) / 2]);
	if (x % 2 == 0)
	{
		pixel = (pixel & 0xFF00) | colour;
	}
	else
	{
		pixel = (pixel & 0x00FF) | (colour << 8);
	}
}

// Get the colour of a pixel on the background in an 8bpp mode
static inline uint8_t GetPixel8(int x, int y)
{
	volatile uint16_t& pixel(BackBuffer[(y * SCREEN_WIDTH + x) / 2]);
	if (x % 2 == 0)
	{
		return pixel & 0xFF;
	}
	else
	{
		return (pixel >> 8) & 0xFF;
	}
}

// Set a background palette colour
static inline void SetPaletteBG(uint8_t entry, uint16_t colour)
{
	REG_PALETTE_BG[entry] = colour;
}

// Get a background palette colour
static inline uint16_t GetPaletteBG(uint8_t entry)
{
	return REG_PALETTE_BG[entry];
}

// Load the entire background palette from an array.
static inline void LoadPaletteBG(const uint16_t palette_data[256])
{
	CopyToVRAM(REG_PALETTE_BG, palette_data, 256);
}

// Load a variable amount of background palette data from an array,
// storing it in palette entries from first_entry onwards.
// data_bytes is the length of the data in bytes.
static inline void LoadPaletteBGData(int first_entry, const void *data, int data_bytes)
{
	CopyToVRAM(REG_PALETTE_BG + first_entry, (const uint16_t *) data, data_bytes / 2);
}

// Set an object palette colour
static inline void SetPaletteObj(uint8_t entry, uint16_t colour)
{
	REG_PALETTE_OBJ[entry] = colour;
}

// Get an object palette colour
static inline uint16_t GetPaletteObj(uint8_t entry)
{
	return REG_PALETTE_OBJ[entry];
}

// Load the entire object palette from an array.
static inline void LoadPaletteObj(const uint16_t palette_data[256])
{
	CopyToVRAM(REG_PALETTE_OBJ, palette_data, 256);
}

// Load a variable amount of object palette data from an array,
// storing it in palette entries from first_entry onwards.
// data_bytes is the length of the data in bytes.
static inline void LoadPaletteObjData(int first_entry, const void *data, int data_bytes)
{
	CopyToVRAM(REG_PALETTE_OBJ + first_entry, (const uint16_t *) data, data_bytes / 2);
}

// Load a 4bpp tile into video RAM.
static inline void LoadTile4(int charblock, int tile_num, const uint8_t tile_data[32])
{
	CopyToVRAM(REG_VIDEO_BASE + (charblock * 8192) + (tile_num * 16), (const uint16_t *) tile_data, 16);
}

// Load an 8bpp tile into video RAM.
static inline void LoadTile8(int charblock, int tile_num, const uint8_t tile_data[64])
{
	CopyToVRAM(REG_VIDEO_BASE + (charblock * 8192) + (tile_num * 32), (const uint16_t *) tile_data, 32);
}

// Load a variable amount of tile data from an array, storing it in charblock memory starting
// at the given position. data_bytes is the length of the data in bytes.
static inline void LoadTileData(int charblock, int first_tile, const void *data, int data_bytes)
{
	CopyToVRAM(REG_VIDEO_BASE + (charblock * 8192) + (first_tile * 32),
	           (const uint16_t *) data, data_bytes / 2);
}

// Set a tile entry within a (32x32) screenblock.
static inline void SetTile(int screenblock, int x, int y, int tile_num)
{
	REG_VIDEO_BASE[(screenblock * 1024) + (y * 32) + x] = tile_num;
}

// Get a tile entry from a screenblock.
static inline int GetTile(int screenblock, int x, int y)
{
	return REG_VIDEO_BASE[(screenblock * 1024) + (y * 32) + x];
}

// Load a complete screenblock into video RAM.
static inline void LoadScreenblock(int screenblock, const uint16_t screenblock_data[1024])
{
	CopyToVRAM(REG_VIDEO_BASE + (screenblock * 1024), screenblock_data, 1024);
}

// Set all of an object's attributes at once.
static inline void SetObject(int object, uint16_t attr0, uint16_t attr1, uint16_t attr2)
{
	ObjAttr& obj(ObjBuffer[object]);
	obj.attr0 = attr0;
	obj.attr1 = attr1;
	obj.attr2 = attr2;
}

// Set an object's X position.
static inline void SetObjectX(int object, int x)
{
	ObjAttr& obj(ObjBuffer[object]);
	obj.attr1 = (obj.attr1 & ~ATTR1_X_MASK) | ATTR1_X(x);
}

// Set an object's Y position.
static inline void SetObjectY(int object, int y)
{
	ObjAttr& obj(ObjBuffer[object]);
	obj.attr0 = (obj.attr0 & ~ATTR0_Y_MASK) | ATTR0_Y(y);
}

#endif
