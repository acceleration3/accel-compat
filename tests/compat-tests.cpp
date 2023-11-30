#include <cstddef>
#include <iostream>

#include <accel/compat>
#include <accel/macros>
#include <string>
#include <typeinfo>

using namespace accel;

int main()
{
    {
        variant<int, long, std::string> a(in_place_type_t<long>{}, 10);

        struct visitor
        {
            int operator()(const int&) { return 1; }
            int operator()(const long&) { return 2; }
            int operator()(const std::string&) { return 3; }
        };

        ACC_ASSERT(visit(visitor{}, a) == 2);
        ACC_ASSERT(a.get<long>() == 10);
        ACC_ASSERT_EXCEPTION(a.get<int>(), std::bad_cast);

        a.emplace<std::string>("Hello, World!");

        ACC_ASSERT(visit(visitor{}, a) == 3);
        ACC_ASSERT(a.get<std::string>() == "Hello, World!");
        ACC_ASSERT_EXCEPTION(a.get<int>(), std::bad_cast);
    }

    {
        string_view sv("Hello, World!");
        ACC_ASSERT(sv.get_size() == 13);
        ACC_ASSERT(sv.get_data() != nullptr);
        ACC_ASSERT(sv[0] == 'H');
        ACC_ASSERT(sv[12] == '!');
        ACC_ASSERT(sv.starts_with("Hello"));
        ACC_ASSERT(sv.starts_with('H'));
        ACC_ASSERT(!sv.starts_with("abcd"));
        ACC_ASSERT(sv.contains("World"));
        ACC_ASSERT(sv.contains('W'));
        ACC_ASSERT(!sv.contains("abcd"));
        ACC_ASSERT(sv.ends_with("World!"));
        ACC_ASSERT(sv.ends_with('!'));
        ACC_ASSERT(!sv.ends_with("abcd"));
        ACC_ASSERT(sv.find("World") == 7);
        ACC_ASSERT(sv.find('W') == 7);
        ACC_ASSERT(sv.find_first_of("l") == 2);
        ACC_ASSERT(sv.find_first_of("abcd") == 11);
        ACC_ASSERT(sv.find_first_of("fgu") == string_view::npos);
        ACC_ASSERT(sv.find_last_of("l") == 10);
        ACC_ASSERT(sv.find_last_of("abcd") == 11);
        ACC_ASSERT(sv.find_last_of("fgu") == string_view::npos);
        ACC_ASSERT(sv.find_first_not_of("H") == 1);
        ACC_ASSERT(sv.find_first_not_of("feHl") == 4);
        ACC_ASSERT(sv.find_first_not_of("Helo, Wrd!") == string_view::npos);
        ACC_ASSERT(sv.find_last_not_of("!") == 11);
        ACC_ASSERT(sv.find_last_not_of("qlkldr!") == 8);
        ACC_ASSERT(sv.find_last_not_of("Helo, Wrd!") == string_view::npos);
    }

    std::cout << "All tests ran successfully.\n";

    return 0;
}