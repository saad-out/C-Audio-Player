#include "internal.h"

t_list	**get_sound_list(void)
{
	static t_list	*head = NULL;

	return (&head);
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
