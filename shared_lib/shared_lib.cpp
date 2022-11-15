#include "shared_lib.h"

library_class::library_class()
{
    std::cout << "library constructor" << std::endl;
}

library_class::~library_class()
{
    std::cout << "library destructor" << std::endl;
}

void library_class::print()
{
    std::cout << "INFO IS " << this->x << std::endl;
}