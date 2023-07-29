#include <cstdlib>
#include <iostream>

#include "file_backend.hpp"
#include "notebook.hpp"

int main(int argc, const char** argv)
{
    termnote::file_backend back;
    termnote::notebook book{&back};

    book.add_note("This is a Test!");

    for (const auto& note : book.get_notes())
    {
        std::cout << note << "\n";
    }

    book.write();
    return 0;
}
