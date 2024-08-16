# <p align="center">C-Audio-Player</p>

<p align="center">
  <img src="https://github.com/saad-out/C-Audio-Player/blob/main/images/audio-bg.png" style="width:300px;"/>
</p>

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
- Monitor playback state

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
- `play_sync()`: Play an audio file synchronously. Returns `-1` on error.
- `play_async()`: Start asynchronous playback of an audio file. Returns a pointer to a `t_sound` structure or `NULL` on error.

### Playback Control
```c
int   running_sounds(t_action action, t_sound *sound);
```
- `running_sounds()`: Control playback of a sound. The `action` parameter can be one of the following (returns `-1` on error):

1- `PAUSE`: Pause the playback.

2- `RESUME`: Resume paused playback.

3- `STOP`: Stop the playback and clean up resources.

(**IMPORTANT: After `STOP`ing a sound, the matching `t_sound` instance is completely destroyed. Any usage of the variable after this will result in an undefined behavior**)


```c
int	set_volume_value(t_sound *sound, double value);
```
- `set_volume_value()`: Sets the sound's volume. `value` should be `0 <= value <= 100`.

### Monitor playback state
```c
t_state	get_state(t_sound *sound);
```
- `get_state()`: Returns the state of a sound. The `t_state` return type is one of the following:

1- `PLAYING`: Currently playing.

2- `PAUSED`: Currently paused.

3- `END`: Playback has ended.

4- `ERROR`: Error occured while checking state.

## Examples
```c
// Include the header file
#include "simpleaudio.h"

// You should always call these two functions ONCE to initialize
// and destroy output resources at the beginning and end of your
// code respectively.
int main(int ac, char **av)
{
  init_ao();

  // Your code goes here

  destroy_ao();
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

  destroy_ao();
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

  destroy_ao();
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
  if (running_sounds(PAUSE, sound) == -1)
    printf("error");

  // Resume
  if (running_sounds(RESUME, sound) == -1)
    printf("error");

  // Change volume to 25%
  if (set_volume_value(sound, 25) == -1)
    printf("error");

  // Stop
  if (running_sounds(STOP, sound) == -1)
    printf("error");

  destroy_ao();
}
```

We'll add some `sleep()` functions to observe sound's changes. Our full program would be:
```c
#include "simpleaudio.h"
#include <stdio.h>

int main(int ac, char **av)
{
  init_ao();

  printf("Let's play audio\n");
  t_sound  *sound = play_async(av[1], 100);
  if (sound == NULL)
    printf("error");
  sleep(1);

  // Pause
  printf("Let's pause\n");
  if (running_sounds(PAUSE, sound) == -1)
    printf("error");
  sleep(1);

  // Resume
  printf("Let's resume\n");
  if (running_sounds(RESUME, sound) == -1)
    printf("error");
  sleep(1);

  // Change volume to 25%
  printf("Let's change volume\n");
  if (set_volume_value(sound, 25) == -1)
    printf("error");
  sleep(1);

  // Stop
  printf("Let's stop\n");
  if (running_sounds(STOP, sound) == -1)
    printf("error");
  sleep(1);

  destroy_ao();
}
```

Lastly, you can wait for an async playback to end, like this: 
```c
{
  // ...

  // wait for playback to end
  while (get_state(sound) != END)
    usleep(1000); // adjustable
 
  // ...
}
```

## How to use

First, you need to install two dependencies that the library needs:
```bash
sudo apt-get install libao-dev libmpg123-dev
```

### Clone repo
Then clone this repo locally:
```bash
git clone https://github.com/saad-out/C-Audio-Player
cd C-Audio-Player
```

### Building the library
Once you've cloned the repository, you can build the library using the provided Makefile:
```bash
make
```
This command will compile the source files and generate static `libsimpleaudio.a` library in the `lib/` directory.

### Linking with your program
To use the library in your own program, you need to include the header file and link against the library.

1- Copy the `include/simpleaudio.h` header file to your project directory or add the `include/` directory to your include path.

2- Copy the `lib/libsimpleaudio.a` file to your project directory or a directory in your library path.

3- In your C file, include the header:
```c
#include "simpleaudio.h"
```

4-Compile your program, linking it with the Simple Audio Player library. Here's an example compilation command:
```bash
gcc -o your_program your_program.c -L. -lsimpleaudio -lmpg123 -lao -lpthread -lm
```
Make sure to replace your_program and your_program.c with your actual program name and source file.
Note: The `-lmpg123 -lao -lpthread -lm` flags are necessary because our lib depends on these libraries. Make sure you have them installed on your system.
