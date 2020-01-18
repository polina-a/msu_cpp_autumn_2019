#include <iostream>
#include "ThreadPool.h"

struct A {};

int foo(const A &) { return 15; }

int main() {
	ThreadPool pool(8);
	
	auto task0 = pool.exec(foo, A());
	std::cout << task0.get() << std::endl;
	
	auto task1 = pool.exec([]() { return 1; });
	std::cout << task1.get() << std::endl;
	
	for (int i = 1; i < 10; i++) {
		std::cout << pool.exec([i]() { return i; }).get() << std::endl;
	}
    
    return 0;
}