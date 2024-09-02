#include <ao/ao.h>
#include <chrono>
#include <csignal>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>

enum class argExitValue
{
  app_continue = 0,
  app_end_early = 1,
};

// Function to generate and play a simple sine wave beep
void playBeep(const bool &isTick)
{
  // Initialize libao
  ao_initialize();

  // Setup format for the audio
  ao_sample_format format;
  format.bits = 16;
  format.channels = 2; // Stereo
  format.rate = 48000; // 48 kHz
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = strdup("L,R");

  // Open the default driver
  int default_driver = ao_default_driver_id();
  ao_device *device = ao_open_live(default_driver, &format, nullptr);
  if (device == nullptr)
  {
    std::cerr << "Error opening audio device" << std::endl;
    ao_shutdown();
    return;
  }

  // Parameters for the beep sound
  double frequency = isTick ? 880.0 : 440.0; // Tick: 880 Hz, Tock: 440 Hz
  double duration = 0.1;                     // 100 milliseconds
  int num_samples = static_cast<int>(duration * format.rate);
  short *buffer = new short[num_samples * format.channels];

  // Generate sine wave
  for (int i = 0; i < num_samples; ++i)
  {
    double sample = sin(2.0 * M_PI * frequency * i / format.rate);
    short sample_value =
        static_cast<short>(sample * 32767); // Max amplitude for 16-bit audio
    buffer[i * 2] = sample_value;           // Left channel
    buffer[i * 2 + 1] = sample_value;       // Right channel
  }

  // Play the generated sound
  ao_play(device, reinterpret_cast<char *>(buffer),
          num_samples * format.channels * sizeof(short));

  // Clean up
  delete[] buffer;
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

// Args handler
argExitValue argHandler(const int &argc, char *argv[])
{
  // Less than 2 args and Help Menu
  if (argc < 2 || std::strcmp(argv[1], "-h") == 0 ||
      std::strcmp(argv[1], "--help") == 0)
  {
    std::cerr << "Usage: " << argv[0] << " <bpm>" << std::endl;
    std::cerr << "Usage: " << argv[0] << " [OPTION]" << std::endl;
    std::cerr << "[OPTION]: --help, -h" << std::endl;
    std::cout << "<Ctrl+C> to stop" << std::endl;
    return argExitValue::app_end_early;
  }

  // Invalid option usage
  try
  {
    std::stoi(argv[1]);
  }
  catch (std::exception &err)
  {
    std::cerr << "Invalid Usage!" << std::endl;
    std::cerr << "[OPTION]: --help, -h" << std::endl;
    return argExitValue::app_end_early;
  }
  return argExitValue::app_continue;
}

int main(int argc, char *argv[])
{
  // Handle input arguments
  if (argHandler(argc, argv) == argExitValue::app_end_early)
  {
    return 0;
  }

  // Setup Routine
  signal(SIGINT, signalHandler); // Set up signal handler for Ctrl+C

  const static int bpm = std::abs(std::stoi(argv[1]));
  const static int std_bpm_ms = 60000;
  int ticker = 0;
  const char *tick_chars = "\\/";
  std::thread soundthread;

  // Routine for Metronome beeps
  while (running)
  {
    if (soundthread.joinable())
    {
      soundthread.join();
    }

    bool tickOrToc = ticker % 2 ? true : false;
    soundthread = std::thread([&]
                              { playBeep(tickOrToc); });

    std::cout << tick_chars[ticker % 2] << "\r" << std::flush;

    ticker++;

    std::this_thread::sleep_for(std::chrono::milliseconds(std_bpm_ms / bpm));
  }

  return 0;
}
