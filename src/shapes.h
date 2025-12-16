#ifndef SHAPES_H
#define SHAPES_H

#include "vstd/vtypes.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
namespace S_FILES
{
	std::unordered_map<const char*, u32> Textures;
}


class Shape 
{
protected: 
	u32 m_VAO = 0;
	u32 m_EBO = 0;
	u32 m_VBO = 0;
	u32 m_DefinitionLevel;
	std::vector<vec3> m_Vertices  = {};
	std::vector<i32> m_Indices  = {};
	std::vector<u32> m_Textures  = {};
public:
	Shape(u32 def_level)
	{
		m_DefinitionLevel = def_level > 10 ? 10 : def_level;
	}
	virtual ~Shape() = default;
	virtual void Draw(u32 program) = 0;
	u32 LoadTexture(const char* file_path) 
	{
		u32 TextureID;
		if (S_FILES::Textures.contains(file_path))
		{
			TextureID =  S_FILES::Textures[file_path];
		}
		else
		{
			glGenTextures(0, &TextureID);
			glBindTexture(TextureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_set_flip_vertically_on_load(true);

			int Width, Height, NumChannels;
			GLenum ImageFormat;
			switch (NumChannels)
			{
				case 1: {
					ImageFormat = GL_RED;
				} break;
				case 3: {
					ImageFormat = GL_RGB;
				} break;
				case 4: {
					ImageFormat = GL_RGBA;
				} break;
				default: {
					throw std::runtime_error("IMAGE FORMAT NOT SUPOORTED");
				}
			}

			unsigned char* data = stbi_load(file_path, &Width, &Height, &NumChannels, 0);
			if (data)
			{
				glTexImage2D(
					GL_TEXTURE_2D, 0, GL_RGBA,
					Width, Height, 0, ImageFormat,
					GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				S_FILES::Textures[file_path] = TextureID;
			}
			else
			{
				throw std::runtime_error("Not able to read image");
			}
			stbi_image_free(data);
		}
		return TextureID;
	}
};

class Quad: public Shape
{
private:
public:
	Quad(u32 def_level): Shape(def_level)
	{

		for (int y = 0; y < m_DefinitionLevel; y++)
		{
			for (int x = 0; x < m_DefinitionLevel; x++)
			{
				m_Vertices.emplace_back((f32(x) / f32(m_DefinitionLevel), (f32(y) / f32(m_DefinitionLevel), 0.0f) :
			}
		}

		for (int y = 0; y < m_DefinitionLevel; y++)
		{
			for (int x = 0; x < m_DefinitionLevel; x++)
			{
				m_Indices.emplace_back(x, x + 1, x + m_DefinitionLevel);
				m_Indices.emplace_back(x + 1, x + 1 + m_DefinitionLevel, x + m_DefinitionLevel);
			}
		}

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), &m_Vertices, GL_STATIC_DRAW);
		
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), &m_Indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
		glEnableVertexAttribArray(0);
	}
	void Draw(u32 program) override
	{
		glUseProgram(program);
		glBindVertexArray(m_VAO);
	}
	void AddTexture(u32 texture, int id)
	{
		if (id > m_Textures.size() - 1) m_Textures.reserve(id);
		m_Textures[id] = texture;
	}



};



#endif