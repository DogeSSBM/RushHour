#pragma once

Time ClockPerMs = CLOCKS_PER_SEC / 1000;

Time refTime;

Ticks getTicks(void)
{
	return SDL_GetTicks();
}
