//
// Written by Dominik Czarnota	aka disconnect3d
//
// Compiled as:
// g++ -std=c++14 -Wall -Wextra -Wpedantic full_static.cpp -o full_static

// This code was written to present that it's possible to create a collection of different types, 
// call 'add()' on each element and...
// do that without using interfaces/virtual functions
//
// This is a sick example.
// Do not try this at home.
// 
// You probably don't need such magic.
// PS: Latest compilers can actually devirtualize some of the virtual calls you do
// (when it is possible to deduct on which type the method is called)
//
//
//
// ### Interesting / related read:
//
// * http://eli.thegreenplace.net/2013/12/05/the-cost-of-dynamic-virtual-calls-vs-static-crtp-dispatch-in-c
//
// * "Porównanie interfejsu i wydajność dynamicznego oraz statycznego polimorfizmu w zależności od warunków użycia kodu"
//   Magdalena Jaroszyńska, 29.01.2016 - my gf's thesis, written in Polish; if you want to get a copy, 
//   feel free to contact me
//

#include <iostream>
#include <vector>
#include <tuple>

struct ParticleA { 
    void add() {
        std::cout << "A::add" << std::endl;
    }
};


struct ParticleB { 
    void add() {
        std::cout << "B::add" << std::endl;
    }
};

struct ParticleC { 
    void add() {
        std::cout << "C::add" << std::endl;
    }
};

template <typename ParticleType, std::size_t n>
struct ParticlesCollection {
    ParticlesCollection()
    : particles(n) {}

    std::vector<ParticleType> particles;

    void invokeAdd() {
        for(auto& item: particles)
            item.add();
    }
};


template <size_t i>
struct ForLoop {
    template <typename TupleType, template <typename ParticleType> class Func>
    static void iterate(TupleType& tuple) {
        auto& item = std::get<i-1>(tuple);

        Func<decltype(item)>()(item);

        ForLoop<i-1>::template iterate<TupleType, Func>(tuple);
    }
};

template<>
struct ForLoop<1> {
    template <typename TupleType, template <typename ParticleType> class Func>
    static void iterate(TupleType& tuple) {
        auto& item = std::get<0>(tuple);

        Func<decltype(item)>()(item);
    }
};

template<typename... ParticlesCollectionTypes>
struct ParticleSystem {
    std::tuple<ParticlesCollectionTypes...> particlesCollectionsCollection;

    void add() {
        ForLoop<std::tuple_size<TUPLE_T>::value>::template iterate<TUPLE_T, AddInvoker>(particlesCollectionsCollection);
    }

private:
    using TUPLE_T = decltype(particlesCollectionsCollection); 

    template <typename ParticleCollectionType2>
    struct AddInvoker {
        void operator()(ParticleCollectionType2 & pc) {
            pc.invokeAdd();
        }
    };
};

int main() {
    ParticleSystem<
        ParticlesCollection<ParticleA, 1>,
        ParticlesCollection<ParticleB, 2>,
        ParticlesCollection<ParticleC, 3>
    > ps;

    std::cout << "before add" << std::endl;
    ps.add();
    std::cout << "after add" << std::endl;
}
