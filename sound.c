#include "main.h"

unsigned char	*init_mpg123(mpg123_handle **mh, size_t *buffer_size)
{
	int				err;
	unsigned char	*buffer;

	mpg123_init();
	(*mh) = mpg123_new(NULL, &err);
	(*buffer_size) = mpg123_outblock(*mh);
	buffer = (unsigned char *) malloc((*buffer_size) * sizeof(unsigned char));
	return (buffer);
}

void	open_out_device(mpg123_handle **mh, char *filename, \
						ao_device **dev, int driver)
{
	ao_sample_format	format;
	int					channels;
	int					encoding;
	long				rate;

	mpg123_open(*mh, filename);
	mpg123_getformat(*mh, &rate, &channels, &encoding);
	format.bits = mpg123_encsize(encoding) * 8;
	format.rate = rate;
	format.channels = channels;
	format.byte_format = AO_FMT_NATIVE;
	format.matrix = 0;
	(*dev) = ao_open_live(driver, &format, NULL);
	if ((*dev) == NULL)
		return (printf("Error opening device.\n"), (void)0);
}

void	cleanup(t_sound *sound)
{
	free(sound->buffer);
	ao_close(sound->dev);
	mpg123_close(sound->mh);
	mpg123_delete(sound->mh);
	mpg123_exit();
}

void	*play_mp3(void *arg)
{
	t_sound	*sound;

	if (arg == NULL)
		return (NULL);
	sound = (t_sound *)arg;
	sound->driver = ao_default_driver_id();
	sound->buffer = init_mpg123(&sound->mh, &sound->buffer_size);
	open_out_device(&sound->mh, sound->filename, &sound->dev, sound->driver);
	mpg123_volume(sound->mh, 0.1);
	while (mpg123_read(sound->mh, sound->buffer, sound->buffer_size, &sound->done) \
			== MPG123_OK && sound->end == false)
		ao_play(sound->dev, (char *)sound->buffer, sound->done);
	cleanup(sound);
	return (NULL);
}
