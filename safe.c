#include "main.h"

bool	end_sound(t_sound *sound)
{
	bool	end;

	if (pthread_mutex_lock(&sound->mutex) != 0)
		return (perror("pthread_mutex_lock() error"), true);
	end = sound->end;
	if (pthread_mutex_unlock(&sound->mutex) != 0)
		return (perror("pthread_mutex_unlock() error"), true);
	return (end);
}

bool	set_sound_end(t_sound *sound)
{
	if (pthread_mutex_lock(&sound->mutex) != 0)
		return (perror("pthread_mutex_lock() error"), true);
	sound->end = true;
	if (pthread_mutex_unlock(&sound->mutex) != 0)
		return (perror("pthread_mutex_unlock() error"), true);
	return (false);
}
