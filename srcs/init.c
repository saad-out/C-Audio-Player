#include "internal.h"

void	init_sound(t_sound *sound, char *filename, double volume)
{
	if (sound)
	{
		sound->filename = filename;
		sound->volume = volume;
		sound->thread = 0;
		sound->end = false;
		sound->pause = false;
		sound->init = false;
		sound->volume_changed = false;
		if (pthread_mutex_init(&sound->mutex, NULL) != 0)
			return (perror("pthread_mutex_init() error"), (void)0);
	}
}
