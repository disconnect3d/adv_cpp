# adv_cpp
c++ codes writtten for advanced programming course at AGH University of Science and Technology

The code here has been written in early 2014 and might not be of the best quality (e.g. lacks of smart pointers, the cross platform signal handling is written by hand instead of using boost).

Anyway here is a little insight what following directories contain:

* WhatsBestInCpp11 - we had a laboratory where we were asked to write what do we think is cool in c++11, that's what it is... (it should really show smart pointers and move semantics)

* ListOnAllocators - a double linked list implementation with possiblity to use different allocators

* ListOnAllocatorsWDbg - same as above but with logging mechanism added by compilation flags (this should use boost::log or another logging library, but it was fun to write it)

* DynamicallyLoadedLib - an easy example of loading dynamic libraries in runtime using dlfcn library (that's how plugins might work in some C/C++ software).

* BoostAsio_Server&Client - async tcp client & server written in boost::asio (async io), there's a little mess in there as it contains a Visual Studio project, a cmake project (in cmake directory ^^) and makefile like projects in (server)|(client)_src directories {also the makefiles won't work since they were copied from the university server, have to fix them someday}
