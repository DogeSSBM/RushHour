#define GRIDLEN			6

#define WINLEN			900
#define HWINLEN			(WINLEN/2)
#define QWINLEN			(HWINLEN/2)

#define SCALE			(WINLEN/GRIDLEN)
#define HSCALE			(SCALE/2)
#define QSCALE			(HSCALE/2)

#define FPS				30
#define TPS				(1000/FPS)
#include "Includes.h"

int main(int argc, char const *argv[])
{
	init(WINLEN, WINLEN);
	while(1){
		menu();
		char selected = 'X';
		while(selected != '!'){
			Ticks frameStart = getTicks();
			clear();
			drawGrid();
			if(selected != '-')
				drawCarOutline(selected);
			drawCars();
			draw();
			events(frameStart + TPS, &selected);
		}
	}
	return 0;
}
