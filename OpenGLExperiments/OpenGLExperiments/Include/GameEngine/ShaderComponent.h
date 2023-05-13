#pragma once

#include "Component.h"

class ShaderComponent : public Component {
public:
	ShaderComponent(int gameObjectID) : Component(gameObjectID) {};

	void Setup(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
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

	~ShaderComponent() {
		glDeleteProgram(program_);
	}

	void Use() const {
		glUseProgram(program_);
	}

	void Unuse() const {
		glUseProgram(0);
	}

	GLuint GetProgram() const { return program_; }

	void SetModelMatrix(const glm::mat4& model_matrix) const {
		glUniformMatrix4fv(model_uniform_, 1, GL_FALSE, glm::value_ptr(model_matrix));
	}

	void SetViewMatrix(const glm::mat4& view_matrix) const {
		glUniformMatrix4fv(view_uniform_, 1, GL_FALSE, glm::value_ptr(view_matrix));
	}

	void SetProjectionMatrix(const glm::mat4& projection_matrix) const {
		glUniformMatrix4fv(projection_uniform_, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	}

	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(program_, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(program_, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(program_, name.c_str()), value);
	}

	void SetVec3(const std::string& name, glm::vec3 value) const
	{
		float val[3] = { value.x,value.y,value.z };
		glUniform3fv(glGetUniformLocation(program_, name.c_str()), 1, val);
	}

	void SetMat4(const std::string& name, const glm::mat4& mat) const {
		glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}


	void Update(float deltaTime) override {};

	void Render() override {};

private:
	GLuint program_{ 0 };
	GLint model_uniform_{ 0 };
	GLint view_uniform_{ 0 };
	GLint projection_uniform_{ 0 };

	std::string LoadShaderFromFile(const std::string& path) const {
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

	void CheckCompileErrors(GLuint shader, std::string type) const
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

	GLuint CompileShader(const std::string& source, GLenum type) const {
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

	GLuint LinkShaders(GLuint vertex_shader, GLuint fragment_shader) const {
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

};
