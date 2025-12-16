
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vstd/vlogger.h"
#include "vstd/vgeneral.h"
#include "main.h"
#include "iostream"
#include <array>
#include "shaders.h"
#include <Windows.h>
#include "perlin.h"
#include <random>
#include "shapes.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

constexpr auto WIDTH = 1200;
constexpr auto HEIGHT = 1200;
constexpr auto CHANNEL_NUM = 4;

constexpr auto SIZE_COLOR_BUFFER = WIDTH * HEIGHT * CHANNEL_NUM;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<f32>distrib(1, 2);

int main() 
{
	Logger::SetLevelDefault();

	
	GLFWwindow *Window = GetGLFWWindow();
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);


	Quad quad(1);
	//u32 texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)0);

	//glBindTexture(GL_TEXTURE_2D, texture);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, ColorBuffer);




	while (!glfwWindowShouldClose(Window))
	{
		processInput(Window, ColorBuffer);

		glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ShaderProgram.UseProgram();
		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, ColorBuffer);
		glUniform1i(glGetUniformLocation(ShaderProgram.GetProgram(), "ColorBuff"), 0);


		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	glfwTerminate();

	VirtualFree(ColorBuffer, 0, MEM_RELEASE);
	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window, void* buff)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		stbi_write_png(NOISE_PATH "03.png", WIDTH, HEIGHT, CHANNEL_NUM, buff, WIDTH * CHANNEL_NUM);
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{

		GeneratePerlinNoise(buff, WIDTH, HEIGHT, distrib(mt), distrib(mt), distrib(mt));
		std::cout << "MORE\n";
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{

		std::random_device rd;
		std::mt19937 jd(rd());
		std::uniform_int_distribution<i64>distrib(1, 3284557443);
		i64 seed = distrib(jd);
		SetNewSeed(seed);
		std::cout << "New seed = " << seed << std::endl;
		GeneratePerlinNoise(buff, WIDTH, HEIGHT, 1, 1, 1.2);
	}



}

//int CountFilesInFolder(const char* file_path)
//{
//	
//
//}

GLFWwindow* GetGLFWWindow() {
	if (!glfwInit())
	{
		glfwTerminate();
		throw std::runtime_error("GLFW WAS NOT INITIALIZED\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifndef MACOS
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	GLFWwindow* Window = glfwCreateWindow(WIDTH, HEIGHT, "Perlin Noise", NULL, NULL);
	if (Window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("FAILED CREATE GLFW WINDOW");
	}

	glfwMakeContextCurrent(Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw std::runtime_error("FAILED INITIALIZE GLAD");
	}

	return Window;

}


void WriteWeirdGradient(void* buff, int XOffset, int YOffset ) 
{
	u32 Pitch = 4 * WIDTH;
	u8* Row = (u8 *)buff;
	for (int x = 0; x < HEIGHT; x++)
	{
		u32* Pixel = (u32 *) Row;
		for (int y = 0; y < WIDTH; y++)
		{
			// RGBA
			u8 Blue = (XOffset + x) % 255;
			u8 Green = (YOffset + y) % 255;

			*Pixel++ = (Blue << 8 | Green << 16);
		}
		Row += Pitch;
	}
}
