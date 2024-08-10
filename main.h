#ifndef MAIN_H
# define MAIN_H

# define ADD 1
# define STOP 2

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
t_list	*stop_sound(t_list **p_head, t_sound *sound);
t_list	*add_sound(t_list **p_head, t_sound *sound);

#endif /* MAIN_H */
