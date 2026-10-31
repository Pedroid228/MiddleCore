#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>

void OnFrameBufferSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "MiddleCore", nullptr, nullptr);
	if (window == nullptr)
	{
		printf("window was nullptr");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetFramebufferSizeCallback(window, OnFrameBufferSizeChanged);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // Left Bottom
		 0.5f, -0.5f, 0.0f, // Right Bottom
		 0.0f,  0.5f, 0.0f // Middle Top
	};

	// Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	{
		std::ifstream file("assets/shaders/basic.vert");
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string source_str = buffer.str();
		const char* source_chars = source_str.c_str();

		glShaderSource(vertexShader, 1, &source_chars, NULL);
		glCompileShader(vertexShader);

		const int infoLogBufferSize = 512;
		int success;
		char infoLog[infoLogBufferSize];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (success == false)
		{
			glGetShaderInfoLog(vertexShader, infoLogBufferSize, NULL, infoLog);
			printf("------- Vertex Shader Compile Error -------\n");
			printf("%s", infoLog);
		}
	}

	// Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	{
		std::ifstream file("assets/shaders/basic.frag");
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string source_str = buffer.str();
		const char* source_chars = source_str.c_str();

		glShaderSource(fragmentShader, 1, &source_chars, NULL);
		glCompileShader(fragmentShader);

		const int infoLogBufferSize = 512;
		int success;
		char infoLog[infoLogBufferSize];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (success == false)
		{
			glGetShaderInfoLog(fragmentShader, infoLogBufferSize, NULL, infoLog);
			printf("------- Fragment Shader Compile Error -------\n");
			printf("%s", infoLog);
		}
	}

	// Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	{
		const int infoLogBufferSize = 512;
		int success;
		char infoLog[infoLogBufferSize];

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

		if (success == false)
		{
			glGetProgramInfoLog(shaderProgram, infoLogBufferSize, NULL, infoLog);
			printf("------- Shader Program Linking Error -------\n");
			printf("%s", infoLog);
		}
	}

	// Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 1. VAO - Vertex Array
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 2. VBO - Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. Set attribute pointer
	const int attributeSize = 3;
	glVertexAttribPointer(0, attributeSize, GL_FLOAT, GL_FALSE, attributeSize * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.051f, 0.067f, 0.090f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
