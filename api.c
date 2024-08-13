#include "main.h"

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
	if (running_sounds(ADD, sound) == NULL)
		return (free(sound), NULL);
	return (sound);
}

t_list	*running_sounds(int action, t_sound *sound)
{
	static t_list	*head = NULL;

	if (action == ADD)
		return (add_sound(&head, sound));
	else if (action == STOP)
		return (stop_sound(&head, sound));
	else if (action == PAUSE)
		return (halt_sound(&head, sound));
	else if (action == RESUME)
		return (resume_sound(&head, sound));
	else if (action == CHANGE_VOLUME)
		return (change_sound(&head, sound));
	else
		return (fprintf(stderr, "Invalid action! valid => ADD / STOP"), NULL);
}
