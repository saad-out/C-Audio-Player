#ifndef MAIN_H
# define MAIN_H

# include <ao/ao.h>
# include <mpg123.h>
# include <stdio.h>
# include <pthread.h>

/*   Mcros   */
struct							s_sound
{
	mpg123_handle				*mh;
	unsigned char				*buffer;
	size_t						buffer_size;
	size_t						done;
	int							driver;
	ao_device					*dev;
};
typedef struct s_sound t_sound;



void	play_async(char *filename);
void	play_sync(char *filename);
#endif
