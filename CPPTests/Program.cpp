#include "Program.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <array>
#include <new>
using namespace std;

template <class T1, class T2>
double sum(T1 a, T2 b)
{
	return a + b;
}

void arrayTest(int arrayOfSetLength[5])  // value 5 is ignored - it's just a pointer
{
	for (int i = 0; i < 4 ; i++)
	{
		cout << arrayOfSetLength[i] << '\n';
	}
}

void arrayTest2(int array[])  // exact same as above function
{
	for (int i = 0; i < 4; i++)
	{
		cout << array[i] << '\n';
	}
}

void arrayTest3(array<int, 4> betterArray)  // expensively copies values when passed, but more functionality
{
	for (int i = 0; i < 4; i++)
	{
		cout << betterArray[i] << '\n';
	}
}

void pointerPrecedence(const int* start, const int* stop)
{
	while (start != stop)
	{
		cout << *start << '\n';
		++start;
	}
}

void allocMemoryTest1()
{
	int* foo = new (nothrow) int[500];
	while (foo != nullptr)
	{
		foo = new (nothrow) int[500];
	}
}

void allocMemoryTest2()  // Runs indefinitely (as expected)
{
	int* foo = new (nothrow) int[500];
	while (foo != nullptr)
	{
		delete[] foo;
		// free(foo);  // same thing as line above EXCEPT it does not call the destructor, so it should only be used for malloc() operations, which are usually irrelevant in C++ anyways
		foo = new (nothrow) int[500];
	}
}

struct TestStruct
{
	int testInt = 0;
	double testDouble = 0.0;
	string testString;
} testObject, testStructArray [3];

void structTest1(TestStruct* test)
{
	test->testInt = 5;
	test->testDouble = 4.2;
	test->testString = "test";
}

void initialTests()
{
	for (int i = 0; i < 3; i++)
	{
		cout << 3 - i << "\n";
		this_thread::sleep_for(std::chrono::seconds(1));
	}
	cout << '\n';

	int testArray[4] = { 1, 5, 7, 2 };
	int testArray2[5] = { 1, 5, 7, 2, 10 };
	int testArray3[6] = { 1, 5, 7, 2, 10, 24 };

	arrayTest(testArray);
	cout << '\n';
	arrayTest(testArray2);
	cout << '\n';
	arrayTest(testArray3);
	cout << '\n';

	array<int, 4> testArray4 = { 5, 3, 2, 9 };
	arrayTest3(testArray4);

	cout << '\n';

	int numbers[] = { 10,20,30 };
	pointerPrecedence(numbers, numbers + 3);
	pointerPrecedence(numbers, numbers + 3);
	// const type * pointers can have their value changed, only the value they point to cannot change
	// type * const pointers can have the value they point to change, but not their own value changed
	// const type * const pointers can't have either changed 

	// allocMemoryTest1();

	cout << '\n';

	TestStruct* testObjectPtr = &testObject;  // Surprisingly &testObject isn't nullptr... was memory already allocated for the object when it was declared?
	structTest1(testObjectPtr);
	// Turns out I was misinformed - memory is allocated as soon as a primitive or struct is declared. Good thing I'm testing for this stuff.

	testStructArray[0] = testObject;
	testStructArray[1] = testObject;
	testStructArray[2] = testObject;
	cout << testStructArray[0].testString << "1\n";
	cout << testStructArray[1].testString << "2\n";
	cout << testStructArray[2].testString << "3\n";
}

class Circle {
	double radius;
public:
	Circle(double r) : radius(r) { }
	double area() { return radius * radius * 3.14159265; }
};

class Cylinder {
	Circle base;
	double height;
public:
	Cylinder(double r, double h) : base(r), height(h) {}  // This works

	/*Cylinder(double r, double h)  // This does not work
	{
		base = Circle(r);
		height = h;
	}*/

	double volume() { return base.area() * height; }
};

class StaticAndConst
{
	//static int staticVariable = 5;  //Not allowed
	static const int staticVariable2 = 5;  //Allowed
	int definedVariable = 5;  //Allowed
	static int staticVariable;  //Allowed
	const int constVariable = 3;

public:
	static void printFive()  // Static methods can be defined within a class, but not static variables
	{
		cout << 5 + '\n';
	}

	int getConst()
	{
		return constVariable;
	}

	int const getConst2()
	{
		return constVariable;
	}
};



int StaticAndConst::staticVariable = 5;  // Allowed

void classTests()
{
	Cylinder testCylinder(10, 20);

	cout << "testCylinder's volume: " << testCylinder.volume() << '\n';

	StaticAndConst staticConstObject;
	const StaticAndConst constStaticConstObject;

	cout << staticConstObject.getConst() << '\n';  // Allowed
	// cout << constStaticConstObject.getConst() << '\n';  // Not allowed - getConst() isn't declared const
	cout << staticConstObject.getConst2() << '\n';  // Allowed
}

int main()
{
	// initialTests();
	classTests();
}