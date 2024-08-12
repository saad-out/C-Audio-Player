#include "main.h"

unsigned char	*init_mpg123(mpg123_handle **mh, size_t *buffer_size)
{
	int				err;
	unsigned char	*buffer;

	if (mpg123_init() != MPG123_OK)
		return (perror("mpg123_init() failure"), NULL);
	(*mh) = mpg123_new(NULL, &err);
	if (!*mh)
		return (perror("mpg123_new() failure"), NULL);
	(*buffer_size) = mpg123_outblock(*mh);
	buffer = (unsigned char *) malloc((*buffer_size) * sizeof(unsigned char));
	return (buffer);
}

int	open_out_device(mpg123_handle **mh, char *filename, \
						ao_device **dev, int driver)
{
	ao_sample_format	format;
	int					channels;
	int					encoding;
	long				rate;

	if (mpg123_open(*mh, filename) != MPG123_OK)
		return (perror("mpg123_open() failure"), -1);
	if (mpg123_getformat(*mh, &rate, &channels, &encoding) != MPG123_OK)
		return (perror("mpg123_getformat() failure"), -1);
	format.bits = mpg123_encsize(encoding) * 8;
	if (format.bits == 0)
		return (perror("mpg123_encsize() failure"), -1);
	format.rate = rate;
	format.channels = channels;
	format.byte_format = AO_FMT_NATIVE;
	format.matrix = 0;
	(*dev) = ao_open_live(driver, &format, NULL);
	if ((*dev) == NULL)
		return (perror("op_open_live() failure"), -1);
	return (MPG123_OK);
}

void	cleanup(t_sound *sound)
{
	free(sound->buffer);
	ao_close(sound->dev);
	mpg123_close(sound->mh);
	mpg123_delete(sound->mh);
	mpg123_exit();
}

void	output_sound(t_sound *sound)
{
	while (mpg123_read(sound->mh, sound->buffer, sound->buffer_size, &sound->done) \
			== MPG123_OK && !end_sound(sound) && !pause_sound(sound))
	{
		if (sound_volume_changed(sound))
		{
			mpg123_volume(sound->mh, sound->volume);
			set_volume_unchanged(sound);
		}
		ao_play(sound->dev, (char *)sound->buffer, sound->done);
	}
	if (!pause_sound(sound))
		cleanup(sound);
}

void	*play_mp3(void *arg)
{
	t_sound	*sound;

	if (arg == NULL)
		return (NULL);
	sound = (t_sound *)arg;
	if (sound->init == true)
		return (output_sound(sound), NULL);
	if (access(sound->filename, F_OK | R_OK) == -1)
		return (fprintf(stderr, "%s: No such file or directory!\n", sound->filename), NULL);
	sound->driver = ao_default_driver_id();
	sound->buffer = init_mpg123(&sound->mh, &sound->buffer_size);
	if (!sound->buffer)
		return (NULL);
	if (open_out_device(&sound->mh, sound->filename, &sound->dev, sound->driver) != MPG123_OK)
		return (NULL);
	if (mpg123_volume(sound->mh, 0.1) != MPG123_OK)
		return (perror("mpg123_volume() failure"), NULL);
	sound->init = true;
	output_sound(sound);
	return (NULL);
}
