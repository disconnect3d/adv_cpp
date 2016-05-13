//
// Written by Dominik Czarnota	 aka disconnect3d
//
// Compiled as:
// g++ -std=c++14 -Wall -Wextra -Wpedantic not_full_static.cpp -o not_full_static
//
// For more info, read comments of 'full_static.cpp'
// This file is just partial work of what has been done in 'full_static.cpp'

#include <iostream>
#include <memory>
#include <vector>

struct ParticlesCollectionBase {
	virtual void invokeAdd() = 0;	
};

template <typename ParticleType>
struct ParticlesCollection : ParticlesCollectionBase {

	ParticlesCollection(std::size_t n)
	: particles(n) {}

	std::vector<ParticleType> particles;

	void invokeAdd() {
		for(auto& item: particles)
			item.add();
	}
};


struct ParticleSystem {	
	ParticleSystem(std::initializer_list<std::shared_ptr<ParticlesCollectionBase>> pc) 
	: particlesCollectionsCollection{pc} {}

	std::vector<std::shared_ptr<ParticlesCollectionBase>> particlesCollectionsCollection;

	void add() {
		for(auto& collection: particlesCollectionsCollection)
			collection->invokeAdd();
	}
};

struct ParticleA {
	void add() { std::cout << "A::add" << std::endl; }
};

struct ParticleB {
	void add() { std::cout << "B::add" << std::endl; }
};

struct ParticleC {
	void add() { std::cout << "C::add" << std::endl; }
};

int main() {
	ParticleSystem ps{
		std::make_shared<ParticlesCollection<ParticleA>>(1),
		std::make_shared<ParticlesCollection<ParticleB>>(2),
		std::make_shared<ParticlesCollection<ParticleC>>(3)
	};
	
	ps.add();
}
