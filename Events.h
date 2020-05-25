#pragma once

void shiftCar(char *selected, const Direction dir)
{
	Coord pos = {0, 0};
	uint len;
	Coord check;
	for(uint y = 0; y < GRIDLEN; y++){
		for(uint x = 0; x < GRIDLEN; x++){
			if(grid[x][y] == *selected){
				pos.x = x;
				pos.y = y;
				goto ESCAPE;
			}
		}
	}
	ESCAPE:
	if(*selected == 'X' && pos.x == 4 && pos.y == 2){
		printf("Win cond!\n");
		*selected = '!';
		return;
	}
	if(dirUD(dir)){
		if(grid[pos.x][pos.y+1] != *selected)
			return;
	}else{
		if(grid[pos.x+1][pos.y] != *selected)
			return;
	}
	for(uint i = 0; i < NUMCAR; i++){
		if(carArr[i].letter == *selected){
			len = carArr[i].len;
			break;
		}
	}
	check = coordClamp(coordShift(pos, dir, dirPOS(dir)?len:1), 0, GRIDLEN);
	if(grid[check.x][check.y] == '-'){
		if(dirNEG(dir))
			pos = coordShift(pos, dirINV(dir), len-1);
		grid[check.x][check.y] = *selected;
		grid[pos.x][pos.y] = '-';
	}
	return;
}

char cycleCar(const char selected, bool prev)
{
	for(int i = 0; i < NUMCAR; i++){
		if(carArr[i].letter == selected){
			if(prev){
				printf("Prev\n");
				do{
					i=i>0?i-1:NUMCAR-1;
				}while(!carArr[i].enabled);
				return carArr[i].letter;
			}else{
				printf("Next\n");
				do{
					i=(i+1)%NUMCAR;
				}while(!carArr[i].enabled);
				return carArr[i].letter;
			}
		}
	}
	return selected;
}

void events(Ticks frameEnd, char *selected)
{
	i32 ticksLeft = frameEnd - getTicks();
	static Coord clickPos = {-1,-1};
	while(ticksLeft > 0){
		Coord relativeMotion;
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
			case SDLK_TAB:
				*selected = cycleCar(*selected, SDL_GetModState()&KMOD_LSHIFT);
				break;
			case SDLK_ESCAPE:
				*selected = '~';
				return;
				break;
			case SDLK_w:
			case SDLK_UP:
				if(*selected == '-')
					break;
				shiftCar(selected, DIR_U);
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				if(*selected == '-')
					break;
				shiftCar(selected, DIR_R);
				if(*selected == '!')
					return;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				if(*selected == '-')
					break;
				shiftCar(selected, DIR_D);
				break;
			case SDLK_a:
			case SDLK_LEFT:
				if(*selected == '-')
					break;
				shiftCar(selected, DIR_L);
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			if(
				SDL_GetMouseState(NULL, NULL) &
				SDL_BUTTON(SDL_BUTTON_LEFT) &&
				*selected != '-' &&
				clickPos.x != -1 &&
				clickPos.y != -1
			){
				relativeMotion.x = event.motion.x - clickPos.x;
				relativeMotion.y = event.motion.y - clickPos.y;
				if(ABS(relativeMotion.x) > HSCALE){
					clickPos.x=event.motion.x;
					shiftCar(selected, relativeMotion.x>0?DIR_R:DIR_L);
					if(*selected == '!')
						return;
				}
				if(ABS(relativeMotion.y) > HSCALE){
					clickPos.y=event.motion.y;
					shiftCar(selected, relativeMotion.y>0?DIR_D:DIR_U);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				*selected =
		grid[screenToGrid(event.button.x)][screenToGrid(event.button.y)];
				if(*selected == '-'){
					clickPos.x = -1;
					clickPos.y = -1;
				}else{
					clickPos.x = event.button.x;
					clickPos.y = event.button.y;
				}
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
				clickPos.x = -1;
				clickPos.y = -1;
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
