#include "Adastra/softadastra.hpp"
#include <iostream>

namespace Adastra
{
    namespace Softadastra
    {
        Softadastra::Softadastra() {}

        void Softadastra::say_hello() const
        {
            std::cout << "Hello from Softadastra!" << std::endl;
        }
    } // namespace GK

}

extern "C"
{
    void say_hello()
    {
        std::cout << "Hello from Softadastra!" << std::endl;
    }
}
