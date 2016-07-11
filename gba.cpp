/* GBA development library for AG0700
 *
 * If you have additions or corrections to this code, please send
 * them to Adam Sampson <a.sampson@abertay.ac.uk>.
 */

#include "gba.h"

volatile uint16_t *BackBuffer = REG_VIDEO_PAGE1;

ObjAttr ObjBuffer[NUM_OBJECTS];

void WaitVSync()
{
	while(REG_VCOUNT >= 160);   // wait till VDraw
	while(REG_VCOUNT < 160);    // wait till VBlank
}

void FlipBuffers()
{
	// Toggle the DCNT_PAGE bit to show the other page
	uint32_t new_dispcnt = REG_DISPCNT ^ DCNT_PAGE;
	REG_DISPCNT = new_dispcnt;
	
	if (new_dispcnt & DCNT_PAGE)
	{
		// We're now showing the second page -- make the first the back buffer
		BackBuffer = REG_VIDEO_PAGE1;
	}
	else
	{
		// Vice versa
		BackBuffer = REG_VIDEO_PAGE2;
	}
}

void ClearScreen8(uint8_t colour)
{
	// Set up a 32-bit value containing four pixels in the right colour.
	uint32_t value = (colour << 24) | (colour << 16) | (colour << 8) | colour;

	// Fill the display by writing 32 bits at a time.
	volatile uint32_t *p = (volatile uint32_t *) BackBuffer;
	int count = (240 * 160) / 4;
	while (count-- > 0)
	{
		*p++ = value;
	}
}

void ClearScreen16(uint16_t colour)
{
	// Set up a 32-bit value containing two pixels in the right colour.
	uint32_t value = (colour << 16) | colour;

	// Fill the display by writing 32 bits at a time.
	volatile uint32_t *p = (volatile uint32_t *) REG_VIDEO_BASE;
	int count = (240 * 160) / 2;
	while (count-- > 0)
	{
		*p++ = value;
	}
}

void CopyScreen()
{
	volatile uint32_t *src, *dest;
	if (REG_DISPCNT & DCNT_PAGE)
	{
		// Page 1 is the back buffer.
		src = (volatile uint32_t *) REG_VIDEO_PAGE2;
		dest = (volatile uint32_t *) REG_VIDEO_PAGE1;
	}
	else
	{
		// Page 2 is the back buffer.
		src = (volatile uint32_t *) REG_VIDEO_PAGE1;
		dest = (volatile uint32_t *) REG_VIDEO_PAGE2;
	}
	
	// Copy from the front buffer to the back buffer in 32-bit chunks.
	int count = (240 * 160) / 4;
	while (count-- > 0)
	{
		*dest++ = *src++;
	}
}

void ClearObjects()
{
	for (int i = 0; i < NUM_OBJECTS; ++i)
	{
		// This can't just set all the attributes to 0, because an object
		// with attr0 == 0 is actually visible.
		SetObject(i, ATTR0_HIDE, 0, 0);
	}

	UpdateObjects();
}

void UpdateObjects()
{
	CopyToVRAM(REG_OBJ_BASE, (uint16_t *) ObjBuffer, sizeof(ObjBuffer) / sizeof(uint16_t));
}

void CopyToVRAM(volatile uint16_t *dest, const uint16_t *src, int num_words)
{
	while (num_words-- > 0)
	{
		*dest++ = *src++;
	}
}
