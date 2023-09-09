#include <iostream>
#include <thread>
#include <chrono>

int main() {
	int count = 0;
	const int ITERATIONS = 1E6;

	thread t1([&count]() {
		for (int i = 0; i < ITERATIONS; i++)
		{
			++count;
		}
		});

	thread t2([]() {});

	t1.join();
	t2.join();

	std::count << count << std::endl;
	
	return 0;
}