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

bool isValidChar(const int c)
{
	if(c == '-')
		return true;
	for(uint i = 0; i < NUMCAR; i++){
		if(c == carArr[i].letter)
			return true;
	}
	return false;
}

bool parseLevelFile(File *f)
{
	if(flen(f) < 42){
		printf("Levels should be >= 42bytes\n");
		printf("Size of file: %ld\n", flen(f));
	}
	rewind(f);
	int c;
	for(uint y = 0; y < 6; y++){
		for(uint x = 0; x < 6; x++){
			c = fgetc(f);
			if(!isValidChar(c))
				return false;
			grid[x][y] = c;
		}
		c = fgetc(f);
		if(c != '\n' && y != 5)
			return false;
	}
	for(uint i = 0; i < NUMCAR; i++){
		for(uint y = 0; y < 6; y++){
			for(uint x = 0; x < 6; x++){
				if(carArr[i].letter == grid[x][y]){
					carArr[i].enabled = true;
					y = 6;
					break;
				}
			}
		}
	}
	return true;
}

void loadGrid(const char *levelStr)
{
	for(uint i = 0; i < NUMCAR; i++){
		carArr[i].enabled = false;
	}
	if(strlen(levelStr) > 2){
		printf("strlen(LevelStr) incorrect len.\n");
		printf("LevelStr: %s\n", levelStr);
		exit(1);
	}
	char path[] = "./lvls/00";
	sprintf(path, "./lvls/%s", levelStr);
	File *f = fopen(path, "r");
	if(f == NULL){
		printf("could not open path: %s\n", path);
		exit(1);
	}
	if(!parseLevelFile(f)){
		printf("Error parsing level file\n");
	}
	//printGrid();
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

Coord gridCoordToScreen(const Coord gpos)
{
	const Coord spos = {gridToScreen(gpos.x), gridToScreen(gpos.y)};
	return spos;
}

uint countChar(const char c)
{
	uint total = 0;
	for(uint y = 0; y < GRIDLEN; y++){
		for(uint x = 0; x < GRIDLEN; x++){
			total += grid[x][y] == c;
		}
	}
	return total;
}

uint getCharCarLen(const char c)
{
	for(uint i = 0; i < NUMCAR; i++){
		if(carArr[i].letter == c)
			return carArr[i].len;
	}
	printf("Err! Car %c does not exist\n", c);
	exit(1);
}

char checkGrid(void)
{
	for(uint y = 0; y < GRIDLEN; y++){
		for(uint x = 0; x < GRIDLEN; x++){
			const char c = grid[x][y];
			if(c != '-' && countChar(c) != getCharCarLen(c))
				return c;
		}
	}
	return '-';
}

void checkLevel(const uint level)
{
	const char c = checkGrid();
	if(c != '-'){
		printf("Level %02u: ", level);
		printf("Failed char: %c\n", c);
		printGrid();
	}
	//else{printf("Passed\n");}
}

void checkLevels(void)
{
	static char levelStr[] = "00";
	for(uint i = 0; i < 26; i++){
		sprintf(levelStr,"%02u",
			clamp((strToInt(levelStr)+1),1,41)
		);
		loadGrid(levelStr);
		checkLevel(i+1);
	}
}
