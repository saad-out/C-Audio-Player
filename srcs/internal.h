#ifndef INTERNAL_H
# define INTERNAL_H


/*   Includes   */
# include <ao/ao.h>
# include <mpg123.h>
# include <pthread.h>
# include <math.h>
# include "../includes/simpleaudio.h"

/*   Typedefs   */
typedef struct s_list	t_list;

/*   Structs   */
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

/*   Prototypes   */
void	*play_mp3(void *arg);
void	init_sound(t_sound *sound, char *filename, double volume);
bool	set_sound_end(t_sound *sound);
bool	end_sound(t_sound *sound);
bool	set_sound_pause(t_sound *sound);
bool	pause_sound(t_sound *sound);
bool	set_sound_resume(t_sound *sound);
int		resume_sound(t_list **p_head, t_sound *sound);
int		stop_sound(t_list **p_head, t_sound *sound);
int		add_sound(t_list **p_head, t_sound *sound);
int		halt_sound(t_list **p_head, t_sound *sound);
int		change_sound(t_list **p_head, t_sound *sound);
void	output_sound(t_sound *sound);
bool	set_volume_unchanged(t_sound *sound);
bool	set_volume_changed(t_sound *sound);
bool	sound_volume_changed(t_sound *sound);
double scale_volume(double volume);
t_list	**get_sound_list(void);

#endif /* INTERNAL_H */
