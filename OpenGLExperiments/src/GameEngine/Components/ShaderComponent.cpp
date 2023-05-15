#include "PCH/pch.h"
#include "GameEngine/ShaderComponent.h"
#include "GameEngine/Component.h"

void ShaderComponent::Setup(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
	// Load and compile the vertex shader
	std::string vertex_shader_source = LoadShaderFromFile(vertex_shader_path);
	GLuint vertex_shader = CompileShader(vertex_shader_source, GL_VERTEX_SHADER);

	// Load and compile the fragment shader
	std::string fragment_shader_source = LoadShaderFromFile(fragment_shader_path);
	GLuint fragment_shader = CompileShader(fragment_shader_source, GL_FRAGMENT_SHADER);

	// Link the shaders into a program
	program_ = LinkShaders(vertex_shader, fragment_shader);

	// Get uniform locations for commonly-used uniforms
	model_uniform_ = glGetUniformLocation(program_, "u_model");
	view_uniform_ = glGetUniformLocation(program_, "u_view");
	projection_uniform_ = glGetUniformLocation(program_, "u_projection");
}

ShaderComponent::~ShaderComponent() {
	glDeleteProgram(program_);
}

void ShaderComponent::Use() const {
	glUseProgram(program_);
}

void ShaderComponent::Unuse() const {
	glUseProgram(0);
}

GLuint ShaderComponent::GetProgram() const { return program_; }

void ShaderComponent::SetModelMatrix(const glm::mat4& model_matrix) const {
	glUniformMatrix4fv(model_uniform_, 1, GL_FALSE, &model_matrix[0][0]);
}

void ShaderComponent::SetViewMatrix(const glm::mat4& view_matrix) const {
	glUniformMatrix4fv(view_uniform_, 1, GL_FALSE, &view_matrix[0][0]);
}

void ShaderComponent::SetProjectionMatrix(const glm::mat4& projection_matrix) const {
	glUniformMatrix4fv(projection_uniform_, 1, GL_FALSE, &projection_matrix[0][0]);
}

void ShaderComponent::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(program_, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void ShaderComponent::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(program_, name.c_str()), value);
}
// ------------------------------------------------------------------------
void ShaderComponent::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(program_, name.c_str()), value);
}

void ShaderComponent::SetVec3(const std::string& name, glm::vec3 value) const
{
	float val[3] = { value.x,value.y,value.z };
	glUniform3fv(glGetUniformLocation(program_, name.c_str()), 1, val);
}

void ShaderComponent::SetMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

std::string ShaderComponent::LoadShaderFromFile(const std::string& path) const {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(path);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	return shaderCode;

}

void ShaderComponent::CheckCompileErrors(GLuint shader, std::string type) const
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

GLuint ShaderComponent::CompileShader(const std::string& source, GLenum type) const {
	// Create a shader object of the specified type
	GLuint shader = glCreateShader(type);

	// Set the shader source code
	const char* source_cstr = source.c_str();
	glShaderSource(shader, 1, &source_cstr, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check for compilation errors
	CheckCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");

	return shader;
}

GLuint ShaderComponent::LinkShaders(GLuint vertex_shader, GLuint fragment_shader) const {
	// Create a program object
	GLuint program = glCreateProgram();

	// Attach the vertex and fragment shaders
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	// Link the program
	glLinkProgram(program);

	// Check for linking errors
	CheckCompileErrors(program, "PROGRAM");

	// Detach the shaders
	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);

	// Delete the shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}

