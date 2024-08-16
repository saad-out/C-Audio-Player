#include "internal.h"

t_list	**get_sound_list(void)
{
	static t_list	*head = NULL;

	return (&head);
}

void	clear_sound_list(void)
{
	t_list	**head;
	t_list	*tmp;

	head = get_sound_list();
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		set_sound_end(tmp->sound);
		if (pthread_join(tmp->sound->thread, NULL) != 0)
			perror("pthread_join() error");
		free(tmp->sound);
		free(tmp);
	}
}

double scale_volume(double volume)
{
	volume *= 0.01;
	if (volume < 0.0)
		volume = 0.0;
	else if (volume > 1.0)
		volume = 1.0;
	return (volume);
}
