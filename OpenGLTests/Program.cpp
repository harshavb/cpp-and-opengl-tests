#include "TestOne.h"
#include "TestTwo.h"
#include "TestThree.h"
#include "TestFour.h"
#include "TestFive.h"
#include "TestSix.h"
#include "TestSeven.h"
#include "TestEight.h"

int main()
{
	// TestOne::runTest();  // Displays an orange and a yellow triangle
	// TestTwo::runTest();  // Displays a yellow triangle and a green triangle that changes color based on the time using a uniform attribute
	// TestThree::runTest();  // Displays a green triangle that changes color based on the time using a uniform attribute and a multicolored triangle by passing colors from the vertex shader to the fragment shader
	// TestFour::runTest();  // Does the same thing as test three, but using a Shader class that takes shader files and automatically creates a glProgram from them
	// TestFive::runTest();  // Loads a rectangle with two textures mixed together, using a struct for each vertex
	// TestSix::runTest();  // Creates two moving rectangles, one scaling and the other rotating, using matrix transformations
	// TestSeven::runTest();  // Creates a rotating cube, utizilizing a seperate model, view, and projection matrix
	TestEight::runTest();
	return 0;
}