
#include <algorithm>
#include <iostream>
#include <vector>

#include "VectorIterator.h"
#include "MyVectorTemplate.cpp"
#include "MyDataType.h"

int main()
{

    {
        int *a = new int[6];

        for (int i = 0; i < 6; ++i)
            a[i] = i;

        Vector<int> vec(a, 6);

        std::cout << "Fifth element is " << vec.at(5) << std::endl;
        vec.at(5) = 100;
        std::cout << "Fifth element is " << vec.at(5) << std::endl;

        std::cout << "Fifth element is " << vec[5] << std::endl;
        vec[5] = 10000;
        std::cout << "Fifth element is " << vec[5] << std::endl;

        for (int i : vec)
            std::cout << i << ' ';
        std::cout << std::endl;

        //std::cout << *std::find(vec.begin(), vec.end(), 3) << std::endl;

        std::cout << "First element of container is " << vec.front() << std::endl;
        std::cout << "Last element of container is " << vec.back() << std::endl;
        std::cout << "Adress of container: " << vec.data() << std::endl;
        std::cout << "Is container empty? - " << vec.empty() << std::endl;
        std::cout << "The size of container is " << vec.size() << std::endl;

        std::cout << "Capacity: " << vec.capacity() << std::endl;
        std::cout << "Capacity: " << vec.capacity() << std::endl;
        vec.print();
        vec.insert(vec.begin() + 3, 999);
        vec.print();
        vec.insert(vec.begin(), 876);
        vec.print();
        vec.insert(vec.end(), 12);
        vec.print();
        vec.insert(vec.end() - 1, 13);
        vec.print();
        auto iter = vec.insert(vec.end() - 2, 21);
        std::cout << *iter << std::endl;
        vec.print();

        vec.insert(vec.begin() + 5, 1, 456);
        vec.print();

        vec.clear();
        vec.insert(vec.end(), 1);
        vec.print();
        vec.insert(vec.end(), 99);
        vec.print();
        Vector<int> vec2(a, 6);
        vec.insert(vec.begin() + 1, vec2.begin(), vec2.end());
        vec.print();
        vec2.insert(vec2.end(), vec.begin(), vec.end());
        vec2.print();
        vec.print();

        vec.erase(vec.begin() + 5);
        vec.print();

        vec.erase(vec.begin() + 1, vec.begin() + 3);
        vec.print();

        vec.erase(vec.end() - 2, vec.end());
        vec.print();

        vec.erase(vec.begin(), vec.end());
        vec.print();

        vec.insert(vec.begin(), 5, 100);
        vec.print();

        vec.push_back(1233);
        vec.print();

        vec.pop_back();

        vec.resize(10);
        vec.print();

        vec.swap(vec2);
        vec.print();
        vec2.print();
    }

    {
        Vector<char> ch_vec;
        ch_vec.push_back('a');
        ch_vec.print();

        for (char a = 45; a > 35; a--)
            ch_vec.push_back(static_cast<char>(a));
        ch_vec.print();

        std::sort(ch_vec.begin(), ch_vec.end());
        ch_vec.print();

    }

    {
        Vector<MyDataType> vec;
        vec.push_back(MyDataType("Ivan", 18, "Music"));
        vec.print();
        vec.push_back(MyDataType("Vasya", 25, "Programming"));
        vec.insert(vec.begin() + 1, MyDataType("Katya", 5, "Drawing"));
        vec.print();
    }
    return 0;
}