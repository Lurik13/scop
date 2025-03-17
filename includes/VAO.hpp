#pragma once

#include <../libraries/glad/glad.h>
#include "VBO.hpp"

// Vertex Array Object
class VAO
{
	public:
		GLuint ID;
		VAO();

		void LinkVBO(VBO& VBO, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
};
