#ifndef MAIN_H
# define MAIN_H

/*   Includes   */
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

/* Typedef */
typedef struct s_sound	t_sound;
typedef struct s_list	t_list;
typedef enum e_action	t_action;

/* Enums */
enum							e_action
{
	STOP,
	PAUSE,
	RESUME,
};

/* Prototypes */
int		play_sync(char *filename, double volume);
t_sound	*play_async(char *filename, double volume);
int		running_sounds(t_action action, t_sound *sound);
int		set_volume_value(t_sound *sound, double value);
void	init_ao(void);
void	destroy_ao(void);

#endif /* MAIN_H */
