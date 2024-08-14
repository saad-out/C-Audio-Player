#include "internal.h"

int	add_sound(t_list **p_head, t_sound *sound)
{
	t_list	*node;
	t_list	*tmp;

	if (!p_head || !sound)
		return (-1);
	node = malloc(sizeof(t_list));
	if (!node)
		return (-1);
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
	return (0);
}

int	stop_sound(t_list **p_head, t_sound *sound)
{
	t_list	*tmp;

	if (!p_head || !sound)
		return (-1);
	tmp = *p_head;
	while (tmp && tmp->sound != sound)
		tmp = tmp->next;
	if (!tmp)
		return (fprintf(stderr, "Sound does not exist!"), -1);
	set_sound_end(tmp->sound);
	if (pthread_join(tmp->sound->thread, NULL) != 0)
		return (perror("pthread_join() error"), -1);
	if (tmp == *p_head)
		*p_head = NULL;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	free(tmp->sound);
	free(tmp);
	return (0);
}

int	halt_sound(t_list **p_head, t_sound *sound)
{
	t_list	*tmp;

	if (!p_head || !sound)
		return (-1);
	tmp = *p_head;
	while (tmp && tmp->sound != sound)
		tmp = tmp->next;
	if (!tmp)
		return (fprintf(stderr, "Sound does not exist!"), -1);
	if (pause_sound(tmp->sound))
		return (fprintf(stderr, "Sound is already paused!"), -1);
	set_sound_pause(sound);
	if (pthread_join(sound->thread, NULL) != 0)
		return (perror("pthread_join() error"), -1);
	return (0);
}

int	resume_sound(t_list **p_head, t_sound *sound)
{
	t_list	*tmp;

	if (!p_head || !sound)
		return (-1);
	tmp = *p_head;
	while (tmp && tmp->sound != sound)
		tmp = tmp->next;
	if (!tmp)
		return (fprintf(stderr, "Sound does not exist!"), -1);
	if (!pause_sound(tmp->sound))
		return (fprintf(stderr, "Sound is not paused!"), -1);
	set_sound_resume(sound);
	if (pthread_create(&sound->thread, NULL, play_mp3, (void *)sound) != 0)
		return (perror("pthread_create() error"), free(sound), -1);
	return (0);
}

int	change_sound(t_list **p_head, t_sound *sound)
{
	t_list	*tmp;

	if (!p_head || !sound)
		return (-1);
	tmp = *p_head;
	while (tmp && tmp->sound != sound)
		tmp = tmp->next;
	if (!tmp)
		return (fprintf(stderr, "Sound does not exist!"), -1);
	set_volume_changed(sound);
	return (0);
}
