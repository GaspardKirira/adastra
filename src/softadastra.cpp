#include "Adastra/softadastra.hpp"
#include <iostream>

namespace Adastra
{
    namespace Softadastra
    {
        Softadastra::Softadastra() {}
    } // namespace GK

}

extern "C"
{
    void say_hello()
    {
        std::cout << "Hello from Softadastra!" << std::endl;
    }
}
