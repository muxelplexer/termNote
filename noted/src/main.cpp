#include <unistd.h>
#include <iostream>

int main()
{
    auto child_pid = fork();
    if (child_pid == -1) return 1;
    if (child_pid == 0)
    {
        std::cout << "Hello from child process!\n";
    } else {
        std::cout << "Created child process!\n";
    }
    return 0;
}
