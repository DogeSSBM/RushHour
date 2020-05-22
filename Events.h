#pragma once
#define TPS		33

void shiftCar(const char letter, const Direction dir)
{
	Coord pos = {0, 0};
	uint len;
	Coord check;
	for(uint y = 0; y < GRIDLEN; y++){
		for(uint x = 0; x < GRIDLEN; x++){
			if(grid[x][y] == letter){
				pos.x = x;
				pos.y = y;
				goto ESCAPE;
			}
		}
	}
	ESCAPE:
	if(dirUD(dir)){
		if(grid[pos.x][pos.y+1] != letter)
			return;
	}else{
		if(grid[pos.x+1][pos.y] != letter)
			return;
	}
	for(uint i = 0; i < NUMCAR; i++){
		if(carArr[i].letter == letter){
			len = carArr[i].len;
			break;
		}
	}
	check = coordClamp(coordShift(pos, dir, dirPOS(dir)?len:1), 0, GRIDLEN);
	if(grid[check.x][check.y] == '-'){
		if(dirNEG(dir))
			pos = coordShift(pos, dirINV(dir), len-1);
		grid[check.x][check.y] = letter;
		grid[pos.x][pos.y] = '-';
	}
}

void events(Ticks frameEnd, char *selected)
{
	i32 ticksLeft = frameEnd - getTicks();
	while(ticksLeft > 0){
		static Event event;
		if(!SDL_WaitEventTimeout(&event, ticksLeft))
			return;
		switch(event.type){
		case SDL_QUIT:
			printf("Quitting now!\n");
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				printf("Quitting now!\n");
				exit(0);
				break;
			case SDLK_w:
			case SDLK_UP:
				if(*selected == '-')
					break;
				shiftCar(*selected, DIR_U);
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				if(*selected == '-')
					break;
				shiftCar(*selected, DIR_R);
				break;
			case SDLK_a:
			case SDLK_DOWN:
				if(*selected == '-')
					break;
				shiftCar(*selected, DIR_D);
				break;
			case SDLK_s:
			case SDLK_LEFT:
				if(*selected == '-')
					break;
				shiftCar(*selected, DIR_L);
				break;
			}
			break;
		case SDL_MOUSEMOTION:

			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				*selected =
		grid[screenToGrid(event.button.x)][screenToGrid(event.button.y)];
				break;
			case SDL_BUTTON_RIGHT:

				break;
			case SDL_BUTTON_MIDDLE:

				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:

				break;
			case SDL_BUTTON_RIGHT:

				break;
			case SDL_BUTTON_MIDDLE:

				break;
			}
			break;
		default:

			break;
		}
		ticksLeft = frameEnd - getTicks();
	}
}
