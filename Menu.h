#pragma once

bool menuSelect(Ticks frameEnd, char *levelStr)
{
	i32 ticksLeft = frameEnd - getTicks();
	while(ticksLeft > 0){
		static Event event;
		if(!SDL_WaitEventTimeout(&event, ticksLeft))
			return false;
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
			case SDLK_d:
			case SDLK_UP:
			case SDLK_RIGHT:
				sprintf(levelStr,"%02u",
					clamp((strToInt(levelStr)+1),1,41)
				);
				printf("levelStr: %s\n",levelStr);
				break;
			case SDLK_s:
			case SDLK_a:
			case SDLK_DOWN:
			case SDLK_LEFT:
				sprintf(levelStr,"%02u",
					clamp((strToInt(levelStr)-1),1,41)
				);
				printf("levelStr: %s\n",levelStr);
				break;
			case SDLK_SPACE:
			case SDLK_RETURN:
				printf("Selected level %s\n", levelStr);
				return true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT){
				printf("Selected level %s\n", levelStr);
				return true;
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
			if(event.wheel.y>0){
				sprintf(levelStr,"%02u",
					clamp((strToInt(levelStr)+1),1,41)
				);
				printf("levelStr: %s\n",levelStr);
				break;
			}else if(event.wheel.y<0){
				sprintf(levelStr,"%02u",
					clamp((strToInt(levelStr)-1),1,41)
				);
				printf("levelStr: %s\n",levelStr);
				break;
			}
			break;
		}
		ticksLeft = frameEnd - getTicks();
	}
	return false;
}

void menu(void)
{
	setFontSize(SCALE);
	Ticks frameStart;
	static char levelStr[] = "00";
	sprintf(levelStr,"%02u",
		clamp((strToInt(levelStr)+1),1,41)
	);
	printf("Entering menu\n");
	do{
		frameStart = getTicks();
		clear();
		drawTextCentered(HWINLEN,HWINLEN,levelStr);
		draw();
	}while(!menuSelect(frameStart + TPS, levelStr));
	printf("Loading grid\n");
	loadGrid(levelStr);
}
