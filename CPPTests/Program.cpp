#include "Program.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

template <class T1, class T2>
double sum(T1 a, T2 b)
{
	return a + b;
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		cout << sum(5, 3.2) << "\n";
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}