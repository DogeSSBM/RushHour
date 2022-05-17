#define GRIDLEN			6

#define WINLEN			600
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
	checkLevels();
	init(WINLEN, WINLEN);
	menu(false);
	while(1){
		char selected = 'X';
		while(selected != '!' && selected != '~'){
			Ticks frameStart = getTicks();
			clear();
			drawGrid();
            for(uint i = 0; i < NUMCAR; i++)
                if(carArr[i].enabled)
                    drawCarOutline(carArr[i].letter, selected == carArr[i].letter);
			drawCars();
			draw();
			events(frameStart + TPS, &selected);
		}
		menu(selected == '!');
	}
	return 0;
}
