#define GRIDLEN			6

#define WINLEN			900
#define HWINLEN			(WINLEN/2)
#define QWINLEN			(HWINLEN/2)

#define SCALE			(WINLEN/GRIDLEN)
#define HSCALE			(SCALE/2)
#define QSCALE			(HSCALE/2)
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init(WINLEN, WINLEN);
	Ticks frameStart;
	char levelStr[] = "01";
	printf("Entering menu\n");
	do{
		frameStart = getTicks();
		clear();
		drawTextCentered(HWINLEN,HWINLEN,levelStr);
		draw();
	}while(!menuSelect(frameStart + TPS, levelStr));
	printf("Loading grid\n");
	loadGrid(levelStr);
	printf("Starting main loop\n");
	char selected = 'X';
	while(1){
		frameStart = getTicks();
		clear();
		drawGrid();
		if(selected != '-')
			drawCarOutline(selected);
		drawCars();
		draw();
		events(frameStart + TPS, &selected);
	}
	return 0;
}
