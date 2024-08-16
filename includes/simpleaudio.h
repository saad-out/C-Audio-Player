#ifndef SIMPLE_AUDIO_H
# define SIMPLE_AUDIO_H

/*   Includes   */
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

/* Typedef */
typedef struct s_sound	t_sound;
typedef enum e_action	t_action;
typedef enum e_state	t_state;

/* Enums */
enum	e_action
{
	STOP,
	PAUSE,
	RESUME,
};

enum	e_state
{
	PLAYING,
	PAUSED,
	END,
	ERROR,
};

/* Prototypes */
int		play_sync(char *filename, double volume);
t_sound	*play_async(char *filename, double volume);
int		running_sounds(t_action action, t_sound *sound);
int		set_volume_value(t_sound *sound, double value);
void	init_ao(void);
void	destroy_ao(void);
t_state	get_state(t_sound *sound);

#endif /* SIMPLE_AUDIO_H */
