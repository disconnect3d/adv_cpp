#ifndef HELPERS_H
#define HELPERS_H

///////////// used in auto example
#define EXAMPLE_HELPER_1 \
    std::vector<std::vector<int>> vec1; \
    std::vector<int> vec2 {1,2,3}; \
    vec1.push_back(vec2)

#define ITER_PRINT(iter, end, delimiter) \
    do { \
        std::cout << #iter " = ["; \
        while (iter != end) \
            std::cout << *iter++ << delimiter " "; \
        std::cout << "\b\b]\n"; \
    } while(0)



///////////// used in strongly typed enum example
#define X_DEF \
    struct X { \
        operator int() {return 0;} \
    };



///////////// used in nullptr example
void null_checker(int, const char* str)
{
    std::cout << "Here we get calling it with " << str << ", and the argument type is int!\n";
}

void null_checker(int*, const char* str)
{
    std::cout << "Here we get calling it with " << str << ", and the argument type is int*!\n";
}

#define NULL_TESTER(null) null_checker(null, #null)



///////////// used in threads example

#define AUTO_PRNT(vec, delimiter) do \
    { \
        std::cout << #vec " = ["; \
        for (auto& el : vec) \
            std::cout << el << delimiter " "; \
        std::cout << "\b\b]\n"; \
    } while(0)



///////////// used in template alias example
 /*
template <bool B, class T = void>
using enable_if_t = typename enable_if<B,T>::type;

template <class A, class B>
typename enable_if_t<sizeof(A)==4, int> foo()
{
    return A() + B();
}
// */
#endif /* end of include guard: HELPERS_H */

