#include "TestSix.h"

void TestSix::runTest()
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
	Shader shaderProgram("VertexShaderThree.vert", "FragmentShaderThree.frag");

	// Rectangle vertices - duplicate vertices only listed once
	struct Vertex {
		GLfloat position[3];
		GLfloat color[3];
		GLfloat uvCoords[2];
	};

	Vertex topRight{ { 0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } };
	Vertex bottomRight{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } };
	Vertex bottomLeft{ { -0.5f, -0.5f, 0.0f } , { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } };
	Vertex topLeft{ { -0.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } };

	Vertex eboRectangleVertices[] = { topRight, bottomRight, bottomLeft, topLeft };

	// Defines indices of vertices of triangles to be drawn
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Generates a VBO, EBO, and a VAO for storing vertices and how to deal with those vertices
	// GLuint VBO, EBO, VAO;
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// First binds VAO(s), then binds and sets VBO(s)/EBO(s), then configures vertex attribute(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(eboRectangleVertices), eboRectangleVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvCoords));

	// Generates the textures
	GLuint textures[2];
	glGenTextures(2, textures);

	// Binds texture
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	// Sets texture details
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Loads texture using stb
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Second texture
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	shaderProgram.use();

	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	GLfloat mixPercent = 0.2f;
	shaderProgram.setFloat("mixPercent", mixPercent);

	// Wireframe Mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		// Input
		UsefulMethods::processInput(window);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			if (mixPercent < 1.0f) mixPercent += 0.001f;
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			if (mixPercent > 0.0f) mixPercent -= 0.001f;
		}

		shaderProgram.setFloat("mixPercent", mixPercent);

		// Creates a matrix that scales by half, rotates by glfwGetTime(), then translates to the bottom right
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

		shaderProgram.setMat4("transform", trans);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		// Binds textures to fragment shader variables and draws based on the first VAO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Creates a matrix that scales by time, then translates to the top left
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(abs(sin(glfwGetTime()))));

		shaderProgram.setMat4("transform", trans);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swaps the buffers then checks and calls events (?)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// De-allocates resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
}