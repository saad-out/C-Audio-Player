#include "main.h"

t_list	*add_sound(t_list **p_head, t_sound *sound)
{
	t_list	*node;
	t_list	*tmp;

	if (!p_head || !sound)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->sound = sound;
	node->next = NULL;
	tmp = *p_head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	node->prev = tmp;
	if (tmp)
		tmp->next = node;
	else
		*p_head = node;
	return (node);
}

t_list	*stop_sound(t_list **p_head, t_sound *sound)
{
	t_list	*tmp;

	if (!p_head || !sound)
		return (NULL);
	tmp = *p_head;
	while (tmp && tmp->sound != sound)
		tmp = tmp->next;
	if (!tmp)
		return (fprintf(stderr, "Sound does not exist!"), NULL);
	set_sound_end(tmp->sound);
	if (pthread_join(tmp->sound->thread, NULL) != 0)
		return (perror("pthread_join() error"), NULL);
	if (tmp == *p_head)
		*p_head = NULL;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	free(tmp->sound);
	free(tmp);
	return (*p_head);
}

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
			sleep(2);
			printf("ending...\n");
			running_sounds(STOP, sound);
		}
	}
	destroy_ao();
	return (0);
}
