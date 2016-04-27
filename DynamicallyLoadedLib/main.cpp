#include <functional>
#include <iostream>
#include <dlfcn.h>
#include "list.h"

//////  COMPILATION REQUIRES:  ////
// CXXFLAGS = -std=c++11        ///
// LDFLAGS  = -ldl              ///
///////////////////////////////////

typedef void* HLIB; /// Library Handle,
// idea for name came from micro$hit (yes, microsoft) naming convention for handles:
// HWND - Window Handle
// HICON - Icon Handle

#define DL_ASSERT(condition) do { \
    if(condition) \
    { \
        std::cerr << "Assert in line: " << __LINE__ << ", Error: "; \
        std::cerr << dlerror() << std::endl;  \
    } \
} while(0)

int main(int argc, char* argv[])
{
    typedef list* (*listInit_t)();
    typedef void (*listDel_t)(list*);
    typedef void (*listPrint_t)(list*);

    const char* RELEASE      = "./liblist.so.1.0.0";
    const char* DEBUG        = "./liblist_debug.so.1.0.0";
    const char* FULL_DEBUG   = "./liblist_fulldebug.so.1.0.0";

    const char* LIB_VERSIONS[] = { RELEASE, DEBUG, FULL_DEBUG };

    if (argc <= 1 || argc >= 3 || !((*argv[1] >= '0') && (*argv[1] <= '2')))
    {
        std::cerr << "Usage: program X" << std::endl;
        std::cerr << "Where X can be: " << std::endl;
        std::cerr << "0 - release lib version" << std::endl;
        std::cerr << "1 - debug lib version" << std::endl;
        std::cerr << "2 - full_debug lib version" << std::endl;
        return 0;
    }

    // void* dlopen(const char* path, int flag)
    // possible flags:
    // RTLD_LAZY - resolve undef symbols when code from lib is executed
    // RTLD_NOW - resolve undef symbols before dlopen returns, fail if it can't be done
    // optional ('or' that flag):
    // RTLD_GLOBAL - symbols will be available to subsequently loaded libs
    HLIB handle = dlopen(LIB_VERSIONS[*argv[1]-'0'], RTLD_LAZY);
    DL_ASSERT(nullptr==handle);               // I put yoda expression here after making a mistake "handle=nullptr". At least compiler warned me about it.

    // value of the symbol returned by dlsym can actually be NULL and error checking should be made through dlerror(),
    // but I don't expect it to be null, so I assume the check I did should be correct.
    listInit_t create_list = reinterpret_cast<listInit_t>( dlsym(handle, "getNewList") );
    DL_ASSERT(nullptr==create_list);

    listDel_t delete_list = reinterpret_cast<listDel_t>( dlsym(handle, "delList") );
    DL_ASSERT(nullptr==delete_list);

    listPrint_t print_list = reinterpret_cast<listPrint_t>( dlsym(handle, "printList") );
    DL_ASSERT(nullptr==print_list);
    
    list* test = create_list();

    test->push_back(1);
    test->push_back(2);
    test->push_back(3);
    
    print_list(test);

    delete_list(test);

    DL_ASSERT(dlclose(handle) != 0);          // dlclose returns 0 on success, otherwise other number 
    
    return 0;
}
