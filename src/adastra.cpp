#include "Adastra/adastra.hpp"
#include <iostream>
#include <vector>

namespace Adastra
{

    Adastra::Adastra() {}

    void Adastra::say_hello() const
    {
        std::cout << "Hello from Adastra!" << std::endl;
    }

    int binarySearch(const std::vector<int> &arr, int target)
    {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target)
                return mid;
            if (arr[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1;
    }

    void test()
    {
        std::cout << "Hello form Adastra::Test" << std::endl;
    }

} // namespace adastra

extern "C"
{
    void test_adastra()
    {
        std::cout << "Hello form Adastra::Test" << std::endl;
    }
}
