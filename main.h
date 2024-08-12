#ifndef MAIN_H
# define MAIN_H

# define ADD 1
# define STOP 2
# define PAUSE 3
# define RESUME 4
# define CHANGE_VOLUME 5

# include <ao/ao.h>
# include <mpg123.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>

/* Typedef */
typedef struct s_sound	t_sound;
typedef struct s_list	t_list;

/*   Macros   */
struct							s_sound
{
	char						*filename;
	double						volume;
	pthread_t					thread;
	mpg123_handle				*mh;
	unsigned char				*buffer;
	size_t						buffer_size;
	size_t						done;
	int							driver;
	ao_device					*dev;
	bool						end;
	bool						pause;
	bool						volume_changed;
	bool						init;
	pthread_mutex_t				mutex;
};

struct							s_list
{
	t_list		*prev;
	t_sound		*sound;
	t_list		*next;
};


/* Prototypes */
void	*play_mp3(void *arg);
t_sound	*play_async(char *filename);
int		play_sync(char *filename);
t_list	*running_sounds(int action, t_sound *sound);
void	init_ao(void);
void	destroy_ao(void);
void	init_sound(t_sound *sound, char *filename);
bool	set_sound_end(t_sound *sound);
bool	end_sound(t_sound *sound);
bool	set_sound_pause(t_sound *sound);
bool	pause_sound(t_sound *sound);
bool	set_sound_resume(t_sound *sound);
t_list	*resume_sound(t_list **p_head, t_sound *sound);
t_list	*stop_sound(t_list **p_head, t_sound *sound);
t_list	*add_sound(t_list **p_head, t_sound *sound);
t_list	*halt_sound(t_list **p_head, t_sound *sound);
void	output_sound(t_sound *sound);
bool	set_volume_unchanged(t_sound *sound);
bool	set_volume_changed(t_sound *sound);
bool	sound_volume_changed(t_sound *sound);
bool	set_volume_value(t_sound *sound, double value);
t_list	*change_sound(t_list **p_head, t_sound *sound);

#endif /* MAIN_H */
