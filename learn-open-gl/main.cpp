#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string get_file_contents(const char* filename);

const double aspect_ratio = 16.0 / 9.0;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = static_cast<int>(SCR_WIDTH / aspect_ratio);

float quad_verts[] = {
	//verticies               //uv coords
	-1.0f,  1.0f, 0.0f,         0, 1,
	-1.0f, -1.0f, 0.0f,			0, 0,
	 1.0f, -1.0f, 0.0f,			1, 0,
	 1.0f,  1.0f, 0.0f,			1, 1,
};

unsigned int quad_ind[] = {
	0, 1, 3,
	1, 2, 3,
};

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif  



	//init the glfw window object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	//register resize function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	// glad: load all OpenGL function pointers
    // ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	//first two params set the location of the bottom left corner of the window
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verts), quad_verts, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_ind), quad_ind, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// stuff for the render loop lol
	shader ray_trace_shader("rt.vert", "rt.frag");

	//very simple render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//set background color		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		


		
		/////////////////////////////////
		///* rendering commands here *///
		/////////////////////////////////
		ray_trace_shader.activate();
		unsigned int loc = glGetUniformLocation(ray_trace_shader.ID, "u_aspect_ratio");
		glUniform1f(loc, aspect_ratio);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ray_trace_shader.del();
	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
