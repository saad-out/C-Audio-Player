#include "main.h"

void	init_ao(void)
{
	ao_initialize();
}

void	destroy_ao(void)
{
	ao_shutdown();
}

void	init_sound(t_sound *sound, char *filename)
{
	if (sound)
	{
		sound->filename = filename;
		sound->volume = 1.0;
		sound->thread = 0;
		sound->end = false;
		sound->pause = false;
		sound->init = false;
		sound->volume_changed = false;
		if (pthread_mutex_init(&sound->mutex, NULL) != 0)
			return (perror("pthread_mutex_init() error"), (void)0);
	}
}
