// printargs.cpp
#include <iostream>
#include "printargs.h"

void print_terminal_args(const int &argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }
}
