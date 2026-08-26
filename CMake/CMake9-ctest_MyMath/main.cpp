#include <iostream>
#include "math/math.h"
#include <cassert>

int main()
{
    assert(add(2,3)==5);
    assert(sub(2,3)==-1);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}