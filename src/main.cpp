#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <csignal>
#include <ao/ao.h>
#include <sndfile.h>
#include "printargs.h"

// #define std_bpm_ms 60000

// Dummy function to simulate playing a sound
void playSound(const std::string &soundFile, int threadnum)
{

  std::cout << "i am thread: " << threadnum << std::endl;
  // Initialize libao
  ao_initialize();

  // Setup format for the audio file
  ao_sample_format format;
  format.bits = 16;
  format.channels = 2;
  format.rate = 44100;
  format.byte_format = AO_FMT_LITTLE;

  // Open the default driver
  int default_driver = ao_default_driver_id();
  ao_device *device = ao_open_live(default_driver, &format, nullptr);
  if (device == nullptr)
  {
    std::cerr << "Error opening audio device" << std::endl;
    ao_shutdown();
    return;
  }

  // Read the sound file
  FILE *file = fopen(soundFile.c_str(), "rb");
  if (file == nullptr)
  {
    std::cerr << "Error opening sound file: " << soundFile << std::endl;
    ao_close(device);
    ao_shutdown();
    return;
  }

  // Allocate buffer for reading
  const int bufferSize = 4096;
  char buffer[bufferSize];
  int bytesRead = 0;

  // Playback loop
  while ((bytesRead = fread(buffer, sizeof(char), bufferSize, file)) > 0)
  {
    ao_play(device, buffer, bytesRead);
  }

  // Close file and device
  fclose(file);
  ao_close(device);
  ao_shutdown();
}

// Signal handler function
volatile sig_atomic_t running = 1;
void signalHandler(int signal)
{
  std::cout << "Stopping Metronome..." << std::endl;
  running = 0;
}

int main(int argc, char *argv[])
{

  print_terminal_args(argc, argv);

  if (argc < 2)
  {
    std::cerr << "Basic Usage: " << argv[0] << " <bpm>" << std::endl;
    std::cerr << "Usage: " << argv[0] << " [OPTION]" << std::endl;
    std::cerr << "[OPTION]: --help " << std::endl;
    return 1;
  }

  // Set up signal handler for Ctrl+C
  signal(SIGINT, signalHandler);

  const int bpm = std::stoi(argv[1]);
  const int std_bpm_ms = 60000;
  int ticker = 0;
  const char *tick_chars = "\\/";

  std::thread soundthread;

  while (running)
  {
    if (soundthread.joinable())
    {
      soundthread.join();
    }

    soundthread = std::thread([&]
                              { playSound("tick.wav", ticker % 2); });

    std::cout << tick_chars[ticker % 2] << "\r" << std::flush;

    ticker++;

    std::this_thread::sleep_for(std::chrono::milliseconds(std_bpm_ms / bpm));
  }

  return 0;
}
