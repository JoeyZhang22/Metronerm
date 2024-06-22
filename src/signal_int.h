#include <signal.h>
#include <csignal> // For signal handling
volatile sig_atomic_t stop_flag = 0;

// Signal handler function for Ctrl+C
inline void signalHandler(int sig)
{
    if (sig == SIGINT)
    {
        stop_flag = 1;
    }
}