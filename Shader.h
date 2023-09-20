#pragma once

#include <glad/glad.h>

#include <string>

class Shader
{
public:
	unsigned int ID;

	// Constructor to read and build shader
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	// Destructor to delete shader program
	~Shader();

	// Function to use shader program
	void use();

	// Utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	// Utility functions
	void glCompileShaderLogging(GLuint shader, GLenum pname, const char* message);
	void glLinkShaderProgramLogging(GLuint program, GLenum pname, const char* message);
};