#include "main.h"

double scale_volume(double volume)
{
	volume *= 0.01;
	if (volume < 0.0)
		volume = 0.0;
	else if (volume > 1.0)
		volume = 1.0;
	return (volume);
}
