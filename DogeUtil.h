#pragma once

void clearTerminal(void)
{
	printf("\e[1;1H\e[2J");
}

float randRange(float a, float b)
{
	return ((b-a)*((float)rand()/RAND_MAX))+a;
}

char* readin(char *buffer, int size)
{
	if(fgets(buffer, size, stdin) == NULL){
		printf("Error! fgets() returned NULL while reading from stdin\n");
		printf("\tRead size: %d\n", size);
		printf("\tRead buffer contents- ");
		fwrite(buffer, sizeof(char), size, stdout);
		putchar('\n');
		exit(1);
	}
	return buffer;
}

void init(uint winXlen, uint winYlen)
{
	srand(time(NULL));
	gfx_init(winXlen, winYlen);
	img_init();
	text_init();
}
