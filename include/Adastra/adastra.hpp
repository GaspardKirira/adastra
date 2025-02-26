#ifndef ADASTRA_ADASTRA_HPP
#define ADASTRA_ADASTRA_HPP

#include <vector>

namespace Adastra
{

    class Adastra
    {
    public:
        Adastra();
        void say_hello() const;
    };

    int binarySearch(const std::vector<int> &arr, int target);
    void test();

} // namespace adastra

#endif // ADASTRA_ADASTRA_HPP
