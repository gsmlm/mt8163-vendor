#include "cust_dc.h"
// --------------------------------------------------------------------------
//  Behavior configuration
// --------------------------------------------------------------------------

const DISPLAY_DC_T dcindex =
{
entry:
{
	{// 0 *** level 0 means disable
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0x0A,
		0x30, 0x40, 0x06, 0x12, 40, 0x40, 0x80, 0x40, 0x40, 1,
		0x80, 0x60, 0x80, 0x10, 0x34, 0x40, 0x40, 1, 0x80, 0xa,
		0x19, 0x00, 0x20, 0, 0, 1, 2, 1, 80, 0,
		50, 8, 0x20, 0x30, 80, 8, 0x20, 0x60, 0x32
	},

	// Video 1
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x6, 0x12, 0x28, 0x10, 0x30, 0x10, 0x30, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x30, 0x2, 0x80, 0xA,
		0x19, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x30, 0x50, 0x8, 0x10, 0x30, 0x30
	},

	// Video 2
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x6, 0x12, 0x28, 0x10, 0x50, 0x10, 0x50, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x50, 0x2, 0x80, 0xA,
		0x19, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x50, 0x50, 0x8, 0x10, 0x50, 0x50
	},

	// Video 3
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x6, 0x12, 0x28, 0x10, 0x70, 0x10, 0x70, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x70, 0x2, 0x80, 0xA,
		0x19, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x70, 0x50, 0x8, 0x10, 0x70, 0x70
	},

	// Video 4
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x6, 0x12, 0x28, 0x10, 0x90, 0x10, 0x90, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x90, 0x2, 0x80, 0xA,
		0x19, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x90, 0x50, 0x8, 0x10, 0x90, 0x90
	},

	// Video 5
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x6, 0x12, 0x28, 0x10, 0xB0, 0x10, 0xB0, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0xB0, 0x2, 0x80, 0xA,
		0x19, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0xB0, 0x50, 0x8, 0x10, 0xB0, 0xB0
	},

	// Image 1
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x6, 0x12, 0x28, 0x10, 0x20, 0x10, 0x20, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x20, 0x2, 0x80, 0x15,
		0x25, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x10, 0x50, 0x8, 0x10, 0x30, 0x28
	},

	// Image 2
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x6, 0x18, 0x22, 0x10, 0x38, 0x10, 0x38, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x38, 0x2, 0x80, 0x15,
		0x25, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x26, 0x50, 0x8, 0x10, 0x38, 0x38
	},

	// Image 3
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0x8, 0x1C, 0x1C, 0x10, 0x58, 0x10, 0x58, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x58, 0x2, 0x80, 0x15,
		0x25, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x48, 0x50, 0x8, 0x10, 0x43, 0x4F
	},

	// Image 4
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0xA, 0x20, 0x16, 0x10, 0x80, 0x10, 0x80, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0x80, 0x2, 0x80, 0x15,
		0x25, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0x76, 0x50, 0x8, 0x10, 0x50, 0x6C
	},

	// Image 5
	{
		0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xA,
		0x30, 0x40, 0xC, 0x24, 0x10, 0x10, 0xA0, 0x10, 0xA0, 0x2,
		0x80, 0x20, 0x40, 0x0, 0x40, 0x10, 0xA0, 0x2, 0x80, 0x15,
		0x25, 0x0, 0x40, 0x0, 0x0, 0x1, 0x2, 0x1, 0x20, 1,
		0x32, 0x8, 0x20, 0xB0, 0x50, 0x8, 0x10, 0x60, 0x90
	}
}
};
