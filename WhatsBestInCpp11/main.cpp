#include <iostream>
#include <vector>       // for auto
#include <cstdint>      // for strongly typed enums
#include <random>
#include <thread>

#include "helpers.h"    

int main()
{
    std::cout << "LINK WITH -pthread or else have fun with an error...\n";
    std::cout << "Compiled with: g++ -std=c++11 -Wall -pthread\n---\n" << std::endl;

    // most of this examples are trivial and were "shown" on the classes...


    ///////// auto
    // handy to write fast, but I'd say it is like a double-edged sword - in a bigger project may produce ambiguity, so must be used with care
    // what would be really cool imho - an IDE option to change all autos to the pure type the variable is

    EXAMPLE_HELPER_1;
    auto iter = vec1.begin()->begin();
    auto iter_end = vec1.begin()->end();
    ITER_PRINT(iter, iter_end, ",");


    ///////// strongly typed enums 
    // -no implicit int conversion
    // -you can have well-defined enum size across compilers (include cstdint, inherit from a type)
    enum class PreferedLangs : std::int8_t { C, Cpp, Python, Csharp };
    if ((int)PreferedLangs::Cpp == 0)
        std::cout << "New enum won't be implicitly casted to int!\n";

    enum OldEnum {too_bad};
    X_DEF; X Xobj;
    if (too_bad == Xobj)
        std::cout << "Old enums are less secure, because of being just integers. They can be compared with anything that can be implicitly casted to int.\n";


    ///////// nullptr       // check the NULL_TESTER macro
    NULL_TESTER(NULL);      // at least it produces warning...
    NULL_TESTER(nullptr);
    

    ///////// <random> random number generator OBJECTS,
    ///////// <thread> threads,
    ///////// lambdas
    ///////// decltype
    // for example when you are implementing a genetic algorithm, you sometimes end up with something that is embarassingly parallel but uses rngs. The old standard library didn't have rng objects, so you had to implement your own or use another lib (boost)
    // (well the other option would be a mutex, but you would probably end up with slower execution than without any parallelism...)
    typedef std::mt19937 rng;
    std::vector<int> vect1, vect2;
    std::default_random_engine seed_gen{};  // calling default ctor, doing seed_gen() would be a declaration of function!
    rng rng1(seed_gen()), rng2(seed_gen());                                 // creating random number generators
    std::uniform_int_distribution<int> dist1{0, 50}, dist2{0, 50}; 

    // decltype( (variable) ) returns T& where T is the type of variable
    auto func = [] (int num, decltype(&vect1) container, decltype(&dist1) distribution, decltype(&rng1) rnd) 
        {
            std::cout << "Thread " << num << " started\n";
            for(int i=0; i<20; ++i)
            {
                auto generated = (*distribution)(*rnd);
                container->push_back(generated);
            }
            std::cout << "Thread " << num << " ended\n";
        };

    // move semantics are used in here, since std::thread CAN'T BE COPIED (it's copy ctor is marked " = delete")
    std::vector<std::thread> threads{2};
    threads.push_back( std::thread(func, 1, &vect1, &dist1, &rng1) );
    threads.push_back( std::thread(func, 2, &vect2, &dist2, &rng2) );
    
    for (auto& thread : threads)    // THIS NEEDS ADDITIONAL LINKING: -pthread FLAG (anyway why doesn't -lpthread work?)
        if(thread.joinable())
            thread.join();             
    // Oh. I got it (asked on irc!) -pthread implies -lpthread when linking
    // lpthread is for the lib itself, pthread is for compiler internal things

    AUTO_PRNT(vect1, ",");
    AUTO_PRNT(vect2, ",");


    ///////// alias template, enable_if (usage here, defined in helpers.h)
    // I'm not sure, but I guess g++ 4.7.0 haven't implemented this...

    //int x = foo<int, int>();


    ///////// And a lot more... (constexpr, initializer_list, uniform initialization, calling other constructors in constructor init list, explicit overrides, final, default, delete) 
    // Probably the best thing in c++11 is move semantics - because it increases performance.
    // because this is the thing that we wouldn't be able to produce using language
    // some of the other things above we could implement ourselves ( smart pointers, <random>, static_assert() )
    //
    // Another good thing like this are extern templates, that can decrease compilation time, which is sometimes crucial in modyfing big project
    
    // Did you know..?
    // In old times in C/C++ code you could find things like:
    //      if ASSERT( (1 > 0)) == 1)
    // because the compilers didn't always follow the standard... so the "true" could be -1
    // (such a line was a part of Microsoft Word for Windows 1.1 version which source code has been released recently)
}
