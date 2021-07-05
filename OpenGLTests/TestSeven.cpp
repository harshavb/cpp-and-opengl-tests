#include "TestSeven.h"

void TestSeven::runTest()
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
	Shader shaderProgram("VertexShaderFour.vert", "FragmentShaderFour.frag");

	// Cube Vertices
	float vertices[] = 
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// Cube Struct
	struct Vertex 
	{
		GLfloat position[3];
		GLfloat uvCoords[2];
	};

	// Converts cube vertices to structs
	Vertex cubeVertices[36];
	for (int i = 0; i < 36; i++)
	{
		Vertex cubeVertex;
		copy(vertices + i * 5, vertices + i * 5 + 4, cubeVertex.position);
		copy(vertices + i * 5 + 3, vertices + i * 5 + 5, cubeVertex.uvCoords);
		cubeVertices[i] = cubeVertex;
	}

	// Generates a VBO and a VAO for storing vertices and how to deal with those vertices
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// First binds VAO(s), then binds and sets VBO(s)/EBO(s), then configures vertex attribute(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvCoords));

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

	// Projection Matrix
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	shaderProgram.setMat4("projection", projection);

	// Wireframe Mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Enables depth testing
	glEnable(GL_DEPTH_TEST);

	// Cube Coordinates
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

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

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.use();

		// Binds textures to fragment shader variables and draws based on the first VAO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		glBindVertexArray(VAO);

		// Sets model matrix for each cube
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);

			float angle = 20.0f * i;
			model = glm::rotate(model, float(glfwGetTime()) * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			shaderProgram.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Sets the view matrix
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.5f + cos(float(glfwGetTime()))));
		view = glm::rotate(view, float(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

		shaderProgram.setMat4("view", view);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swaps the buffers then checks and calls events (?)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// De-allocates resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}