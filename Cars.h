#pragma once
#define NUMCAR			16

typedef enum {
	CAR_A,CAR_B,CAR_C,CAR_D,CAR_E,CAR_F,CAR_G,CAR_H,CAR_I,CAR_J,CAR_K,
	CAR_O,CAR_P,CAR_Q,CAR_R,
	CAR_X
}CarArrIndex;

typedef struct{
	CarArrIndex index;
	char letter;
	uint len;
	Color color;
}Car;

Car carArr[NUMCAR] = {
	{
		CAR_A,				// Index enum
		'A',					// Letter
		2,					// Length
		{0x90, 0xcc, 0x86, 0xff}	// Color
	},{
		CAR_B,				// Index enum
		'B',					// Letter
		2,					// Length
		{0xf6, 0x85, 0x29, 0xff}	// Color
	},{
		CAR_C,				// Index enum
		'C',					// Letter
		2,					// Length
		{0x24, 0xbb, 0xf0, 0xff}	// Color
	},{
		CAR_D,				// Index enum
		'D',					// Letter
		2,					// Length
		{0xef, 0x7d, 0xa1, 0xff}	// Color
	},{
		CAR_E,				// Index enum
		'E',					// Letter
		2,					// Length
		{0x67, 0x63, 0xad, 0xff}	// Color
	},{
		CAR_F,				// Index enum
		'F',					// Letter
		2,					// Length
		{0x0f, 0x98, 0x6c, 0xff}	// Color
	},{
		CAR_G,				// Index enum
		'G',					// Letter
		2,					// Length
		{0xd8, 0xd9, 0xdb, 0xff}	// Color
	},{
		CAR_H,				// Index enum
		'H',					// Letter
		2,					// Length
		{0xfd, 0xe5, 0xc3, 0xff}	// Color
	},{
		CAR_I,				// Index enum
		'I',					// Letter
		2,					// Length
		{0xfe, 0xf4, 0x54, 0xff}	// Color
	},{
		CAR_J,				// Index enum
		'J',					// Letter
		2,					// Length
		{0x90, 0x65, 0x55, 0xff}	// Color
	},{
		CAR_K,				// Index enum
		'K',					// Letter
		2,					// Length
		{0x8a, 0x8d, 0x08, 0xff}	// Color
	},{
		CAR_O,				// Index enum
		'O',					// Letter
		3,					// Length
		{0xfa, 0xd2, 0x01, 0xff}	// Color
	},{
		CAR_P,				// Index enum
		'P',					// Letter
		3,					// Length
		{0xa1, 0x7f, 0xbb, 0xff}	// Color
	},{
		CAR_Q,				// Index enum
		'Q',					// Letter
		3,					// Length
		{0x0d, 0x7e, 0xc2, 0xff}	// Color
	},{
		CAR_R,				// Index enum
		'R',					// Letter
		3,					// Length
		{0x0c, 0xaf, 0x9c, 0xff}	// Color
	},{
		CAR_X,				// Index enum
		'X',					// Letter
		2,					// Length
		{0xee, 0x21, 0x26, 0xff}	// Color
	}
};
