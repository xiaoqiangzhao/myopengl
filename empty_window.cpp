#include <iostream>
#include <Windows.h>
//GLEW
#define GLEW_STATIC
#include <gl/glew.h>
//GLFW
#include<GLFW/glfw3.h>

//callback

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)

	{
		std::cout << "Escape From Window" << std::endl;
		
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
		
}

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 colour;\n"
"void main()\n"
"{\n"
"colour = color;\n"
"gl_Position = vec4(position.x, -position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 color1;\n"
"void main()\n"
"{\n"
"color = color1;\n"
"}\n\0";

const GLchar* fragmentShaderSource_2 = "#version 330 core\n"
"out vec4 color;\n"
"in vec3 colour;\n"
"void main()\n"
"{\n"
"color = vec4(colour, 1.0f);\n"
"}\n\0";


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Windows INIT
	GLFWwindow* window = glfwCreateWindow(800, 600, "Jay's OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	//get number of vertex attributes
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	//GLEW INIT
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width/2, height/2);

	//Vertex
	GLfloat first_vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		0.5f, -0.5f, 0.0f,  // right
		0.0f,  0.5f, 0.0f,   // middle
	};

	GLfloat second_vertices[] ={
		//second triangle
		1.0f, 0.5f, 0.0f, // left
		0.6f, -0.5f, 0.0f,  // right
		0.1f,  0.5f, 0.0f ,  // middle
	};

	GLfloat second_color[] = {
		1.0f,0,0, // red
		0,1.0f,0,// yellow
		0,0,1.0,//blue
	};

	//Shader Loader
	//vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check vertex shader compile
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check fragment shader compile
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//fragment shader
	GLuint fragmentShader_2;
	fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &fragmentShaderSource_2, NULL);
	glCompileShader(fragmentShader_2);
	//check fragment shader compile

	glGetShaderiv(fragmentShader_2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader_2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//link shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	GLuint shaderProgram_2;
	shaderProgram_2 = glCreateProgram();
	glAttachShader(shaderProgram_2, vertexShader);
	glAttachShader(shaderProgram_2, fragmentShader_2);
	glLinkProgram(shaderProgram_2);
	glGetProgramiv(shaderProgram_2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram_2, 512, NULL, infoLog);
	}

	//glUseProgram(shaderProgram);
	//delete shaders
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	//VBO VAO 0
	GLuint VBOs[2], VAOs[2];
	GLuint C_VBO;
	glGenBuffers(2, VBOs);
	glGenBuffers(1, &C_VBO);
	glGenVertexArrays(2, VAOs);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(first_vertices), first_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, C_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second_color), second_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	



	//VBO VAO 1

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second_vertices), second_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, C_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(second_color), second_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	//unbind VAO VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	//Engien
	GLint i = 0;
	while (!glfwWindowShouldClose(window))
	{
		
		i = i + 1;
		glfwPollEvents();
		glClearColor(0.8f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat TimeValue = glfwGetTime();
		GLfloat ColorValue = (sin(TimeValue) / 2) + 0.5;
		GLint Color1Location = glGetUniformLocation(shaderProgram, "color1");


		//std::cout << "Drawing" << std::endl;
		// Draw our first triangle
		glUseProgram(shaderProgram);
		glUniform4f(Color1Location, ColorValue, ColorValue, 0.0f, 1.0f);

		
		/*if (i % 2) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
*/
		//glPointSize(20);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram_2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
		//Sleep(200);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glfwTerminate();
	std::cout << "End of Jay's First Window" << std::endl;
	return 0;
}