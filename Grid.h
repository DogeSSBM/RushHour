#pragma once

char grid[GRIDLEN][GRIDLEN];

void printGrid(void)
{
	for(uint y = 0; y < GRIDLEN; y++){
		for(uint x = 0; x < GRIDLEN; x++){
			putchar(grid[x][y]);
		}
		putchar('\n');
	}
}

void loadGrid(const char *levelStr)
{
	printf("Loading level file %s\n", levelStr);
}

// grid position to screen pixel location
uint gridToScreen(const uint pos)
{
	return SCALE*pos;
}

// screen pixel location to grid position
uint screenToGrid(const uint pos)
{
	return pos/SCALE;
	//return pos/SCALE + (pos%SCALE > HSCALE);
}

void moveCarGrid(Car *car, const Direction dir)
{

}
