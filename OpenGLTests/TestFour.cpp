#include "TestFour.h"

void TestFour::runTest()
{
	glfwInit();  // Begins GLFW
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // For Mac support
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // Defines GL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);  // Defines GL version - 4.1 because Mac doesn't support 4.2 to 4.6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Sets whether or not to use post 3.0 GL features, pre 3.0 GL features, or both

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLTests", NULL, NULL);  // Creates the GL window
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);  // Sets window to run GL
	glfwSetFramebufferSizeCallback(window, UsefulMethods::framebuffer_size_callback);  // Defines what function to run whenever window is resized

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // Allows GLAD to read functions from driver (OS specific without GLAD)
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Creates the shader programs for each of the triangles
	Shader shaderProgram("VertexShaderOne.vert", "FragmentShaderOne.frag");
	Shader shaderProgramTwo("VertexShaderOne.vert", "FragmentShaderTwo.frag");

	float exerciseTwoVerticesOne[] = {
		-0.5f, -0.25f, 0.0f, 5.0f,
		0.0f, -0.25f, 0.0f, 5.0f,
		-0.25f,  0.25f, 0.0f, 5.0f
	};

	float exerciseTwoVerticesTwo[] = {
		0.5f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 5.0f,
		0.0f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f,
		0.25f,  0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 5.0f
	};

	// Defines indices of vertices of triangles to be drawn
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Generates a VBO, EBO, and a VAO for storing vertices and how to deal with those vertices
	// GLuint VBO, EBO, VAO;
	GLuint VBOs[2], VAOs[2];

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	// First binds VAO(s), then binds and sets VBO(s)/EBO(s), then configures vertex attribute(s)
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(exerciseTwoVerticesOne), exerciseTwoVerticesOne, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	// Also allowed: glVertexAttribPointer(glGetAttribLocation("aPos"), 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(3 * sizeof(float)));

	glBindVertexArray(VAOs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(exerciseTwoVerticesTwo), exerciseTwoVerticesTwo, GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(6 * sizeof(float)));

	// Unbinds the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Wireframe Mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		// Input
		UsefulMethods::processInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		// Draws based on the first VAO
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Updates color based on time and passes it to global variable
		float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
		shaderProgram.setVec4("ourColorUniform", 0.0f, greenValue, 0.0f, 1.0f);

		shaderProgramTwo.use();

		// Draws based on the second VAO
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swaps the buffers then checks and calls events (?)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// De-allocates resources
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();
}