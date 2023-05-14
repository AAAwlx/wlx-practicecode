#include <iostream>

template <typename T, int size>
class Array {
public:
    T values[size];
    void Fill(T value) {
        for (int i = 0; i < size; i++) {
            values[i] = value;
        }
    }
};

int main() {
    Array<int, 5> arr1;
    arr1.Fill(42);
    for (int i = 0; i < 5; i++) {
        std::cout << arr1.values[i] << " ";
    }
    std::cout << std::endl;

    Array<double, 3> arr2;
    arr2.Fill(3.14);
    for (int i = 0; i < 3; i++) {
        std::cout << arr2.values[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
