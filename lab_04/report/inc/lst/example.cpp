#include <iostream>
#include <thread>

void foo(int a)
{
	std::cout << a << '\n';
}

int main()
{
	std::thread thread(foo, 10);
	thread.join();

	return 0;
}