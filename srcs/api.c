#include "internal.h"

void	init_ao(void)
{
	ao_initialize();
}

void	destroy_ao(void)
{
	ao_shutdown();
}

int	play_sync(char *filename, double volume)
{
	t_sound	*sound;

	sound = malloc(sizeof(t_sound));
	if (!sound)
		return (perror("malloc() error"), -1);
	init_sound(sound, filename, volume);
	play_mp3((void *)sound);
	free(sound);
	return (0);
}

t_sound	*play_async(char *filename, double volume)
{
	t_sound	*sound;

	sound = malloc(sizeof(t_sound));
	if (!sound)
		return (perror("malloc() error"), NULL);
	init_sound(sound, filename, volume);
	if (pthread_create(&sound->thread, NULL, play_mp3, (void *)sound) != 0)
		return (perror("pthread_create() error"), free(sound), NULL);
	if (add_sound(get_sound_list(), sound) == -1)
		return (free(sound), NULL);
	return (sound);
}

int	running_sounds(t_action action, t_sound *sound)
{
	t_list	**head;

	head = get_sound_list();
	if (action == STOP)
		return (stop_sound(head, sound));
	else if (action == PAUSE)
		return (halt_sound(head, sound));
	else if (action == RESUME)
		return (resume_sound(head, sound));
	else
		return (fprintf(stderr, "Invalid action!"), -1);
}

int	set_volume_value(t_sound *sound, double value)
{
	if (pthread_mutex_lock(&sound->mutex) != 0)
		return (perror("pthread_mutex_lock() error"), -1);
	sound->volume = value;
	if (pthread_mutex_unlock(&sound->mutex) != 0)
		return (perror("pthread_mutex_unlock() error"), -1);
	if (set_volume_changed(sound) == true)
		return (-1);
	return (0);
}
