#include "Shader.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	// Step 1 : Retrieve the vertex/fragment source code from filePath

	std::string vertexShaderCode, fragmentShaderCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;

	// Ensure ifstream objects can throw exceptions
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open file
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);
		std::stringstream vertexShaderStream, fragmentShaderStream;

		// Read file's buffer content into streams
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// Close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Convert stream into string
		vertexShaderCode = vertexShaderStream.str();
		fragmentShaderCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	// Step 2 : Compile and linking shader

	const char* vertexShaderCodeCString = vertexShaderCode.c_str();
	const char* fragmentShaderCodeCString = fragmentShaderCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderCodeCString, NULL);
	glCompileShader(vertexShader);
	glCompileShaderLogging(vertexShader, GL_COMPILE_STATUS, "ERROR::SHADER::VERTEX::COMPILATION_FAILED");

	glShaderSource(fragmentShader, 1, &fragmentShaderCodeCString, NULL);
	glCompileShader(fragmentShader);
	glCompileShaderLogging(fragmentShader, GL_COMPILE_STATUS, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glLinkShaderProgramLogging(ID, GL_LINK_STATUS, "ERROR::SHADER::SHADER_PROGRAM_LINKING_FAILED");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::glCompileShaderLogging(GLuint shader, GLenum pname, const char* message)
{
	int success;
	char infoLog[512];

	glGetShaderiv(shader, pname, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cout << message << "\n" << infoLog << std::endl;
	}
}

void Shader::glLinkShaderProgramLogging(GLuint program, GLenum pname, const char* message)
{
	int success;
	char infoLog[512];

	glGetProgramiv(program, pname, &success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cout << message << "\n" << infoLog << std::endl;
	}
}
