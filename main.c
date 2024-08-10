#include "main.h"

int main(int ac, char **av)
{
	init_ao();
	if (ac > 2)
	{
		if (play_sync(av[1]) == -1)
			fprintf(stderr, "play_sync() error");
		t_sound *sound = play_async(av[2]);
		if (!sound)
			fprintf(stderr, "play_async() error");
		else
		{
			printf("playing\n");
			sleep(1);
			printf("pause\n");
			running_sounds(PAUSE, sound);
			sleep(1);
			printf("resume\n");
			running_sounds(RESUME, sound);
			sleep(3);
			printf("ending...\n");
			running_sounds(STOP, sound);
		}
	}
	destroy_ao();
	return (0);
}
