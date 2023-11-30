#include <iostream>

#include <accel/compat>
#include <accel/macros>

using namespace accel;

int main()
{
    {
        variant<int, long, std::string> a(3l);

        struct visitor
        {
            int operator()(const int& a) { return 1; }
            int operator()(const std::string& b) { return 2; }
        };

        std::cout << "Visit result: " << visit(visitor{}, a) << "\n";

        std::cout << "a: " << a.get<std::string>() << "\n";
    }

    std::cout << "All tests ran successfully.\n";

    return 0;
}