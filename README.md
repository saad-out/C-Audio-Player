# C-Audio-Player
## Project Overview

This project is a simple audio player implemented in C, providing both synchronous and asynchronous playback capabilities. It offers basic controls for audio playback, including play, pause, resume, volume control, and stop functionality.

```c
{
  // ...

  play_sync("sound.mp3", 100);
  printf("This is printed after sound.mp3 is done\n");

  play_async("sound2.mp3", 50.5);
  printf("This is printed while sound2.mp3 is playing\n");

  // ...
}
```

## Features

- Synchronous and asynchronous audio playback
- Pause and resume functionality
- Volume control
- Ability to stop playback

## API Documentation

The Simple Audio Player exposes the following API:

### Initialization and Cleanup

```c
void init_ao();
void destroy_ao();
```

- `init_ao()`: Initialize the audio output system. Must be called before using any other functions.
- `destroy_ao()`: Clean up and release resources used by the audio output system. Should be called at the end of the program.

### Playback Functions
```c
int play_sync(const char *filename, double volume);
t_sound *play_async(const char *filename, double volume);

// Volume is any double between 0 and 100, values out of range are scaled back
```
- `play_sync()`: Play an audio file synchronously. Returns -1 on error.
- `play_async()`: Start asynchronous playback of an audio file. Returns a pointer to a `t_sound` structure or NULL on error.

### Playback Control
```c
t_list *running_sounds(int action, t_sound *sound);
```
- `running_sounds()`: Control playback of a sound. The action parameter can be one of the following macros (returns `NULL` on error):

1- `PAUSE`: Pause the playback.

2- `RESUME`: Resume paused playback.

3- `CHANGE_VOLUME`: Apply volume change (set `sound->volume` before calling).

4- `STOP`: Stop the playback and clean up resources

## Usage example
```c
// You should always call these two functions ONCE to initialize
// and destroy output resources at the beginning and end of your
// code respectively.
int main(int ac, char **av)
{
  init_ao();

  // Your code goes here

  destory_ao();
}
```
Playing an audio file synchronously with max volume, taken from the commad line arguments:
```c
int main(int ac, char **av)
{
  init_ao();

  int ret = play_sync(av[1], 100);
  if (ret == -1)
    printf("error\n");

  destory_ao();
}
```
Same, but async:
```c
int main(int ac, char **av)
{
  init_ao();

  t_sound  *sound = play_async(av[1], 100);
  if (sound == NULL)
    printf("error");

  destory_ao();
}
```
You can then manipulate the playing sound using the `t_sound` instance you have, you can pause, resume, change volume and stop:
```c
int main(int ac, char **av)
{
  init_ao();

  t_sound  *sound = play_async(av[1], 100);
  if (sound == NULL)
    printf("error");

  // Pause
  if (running_sounds(PAUSE, sound) == NULL)
    printf("error");

  // Resume
  if (running_sounds(RESUME, sound) == NULL)
    printf("error");

  // Change volume
  sound->volume = 10;
  if (running_sounds(CHANGE_VOLUME, sound) == NULL)
    printf("error");

  // Stop
  if (running_sounds(STOP, sound) == NULL)
    printf("error");

  destory_ao();
}
```
# ...
