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
			case SDLK_UP:
				sprintf(levelStr,"%02u",
					clamp((strToInt(levelStr)+1),0,100)
				);
				printf("levelStr: %s\n",levelStr);
				break;
			case SDLK_DOWN:
				sprintf(levelStr,"%02u",
					clamp((strToInt(levelStr)-1),0,100)
				);
				printf("levelStr: %s\n",levelStr);
				break;
			case SDLK_RETURN:
				printf("Selected level %d\n");
				return true;
				break;
			}
			break;
		}
		ticksLeft = frameEnd - getTicks();
	}
	return false;
}
