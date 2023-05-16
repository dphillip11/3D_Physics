#include "PCH/pch.h"
#include "Shader.h"



Shader::Shader(const std::string& shaderPath)
{
	// 1. Retrieve the shader source code from the file
	std::string shaderCode;
	std::ifstream shaderFile;
	// Ensure ifstream object can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open the file
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// Read the file's buffer contents into a stream
		shaderStream << shaderFile.rdbuf();
		// Close the file
		shaderFile.close();
		// Convert the stream into a string
		shaderCode = shaderStream.str();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		throw; // Rethrow the exception or handle it appropriately
	}

	// Check if the shader code contains a geometry shader
	std::size_t geometryPos = shaderCode.find("#geometry");
	bool hasGeometryShader = (geometryPos != std::string::npos);

	auto cutOutSection = [](std::string& code, const std::string& delimiter) {
		std::size_t endPos = std::string(code).find(delimiter);
		auto section = code.substr(0, endPos);
		code.erase(0, endPos);
		return section;
	};

	auto removeBeforeVersion = [](std::string& code) {
		std::size_t startPos = std::string(code).find("#version");
		code = code.substr(startPos);
	};

	// Remove Shader.vertex
	removeBeforeVersion(shaderCode);

	//keep vertex shader code
	auto v_section = cutOutSection(shaderCode, "// Shader");
	const char* vertexSource = v_section.c_str();

	// Remove vertex code from shaderCode
	removeBeforeVersion(shaderCode);

	// Store geometry shader if present
	unsigned int geometry = 0;
	const char* geometrySource = nullptr;
	if (hasGeometryShader)
	{
		// Cut out geometry shader source
		auto g_section = cutOutSection(shaderCode, "// Shader");
		geometrySource = g_section.c_str();
		// Remove geometry code from shaderCode
		removeBeforeVersion(shaderCode);

		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &geometrySource, nullptr);
		glCompileShader(geometry);
		checkCompileErrors(geometry, "GEOMETRY");

	}

	// Store the rest as fragment code
	const char* fragmentSource = shaderCode.c_str();

	// Vertex shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, nullptr);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// Fragment shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, nullptr);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// Shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	if (hasGeometryShader)
		glAttachShader(ID, geometry);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// Delete redundant shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (hasGeometryShader)
		glDeleteShader(geometry);
}



// activate the shader
// ------------------------------------------------------------------------
void Shader::Use()
{
	glUseProgram(ID);
}

// deactivate the shader
// ------------------------------------------------------------------------
void Shader::Unuse()
{
	glUseProgram(0);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	float val[3] = { value.x,value.y,value.z };
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, val);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMaterial(Material material) const
{
	setVec3("material.diffuse", material.diffuse);
	setVec3("material.specular", material.specular);
	setVec3("material.ambient", material.ambient);
	setFloat("material.shininess", material.shininess);
}

void Shader::setLight(Light light) const
{
	setVec3("light.position", light.position);
	setVec3("light.ambient", light.ambient);
	setVec3("light.diffuse", light.ambient);
	setVec3("light.specular", light.ambient);

}


// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, std::string type)
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

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//create reference variable
	unsigned int vertex, fragment;
	// vertex shader
	//instantiate shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	//attach script to shader
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	//compile
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	//instantiate program and attach reference variable
	ID = glCreateProgram();
	//attach shaders
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	//link program
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete redundant shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		gShaderFile.open(geometryPath);
		std::stringstream vShaderStream, fShaderStream, gShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		gShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		geometryCode = gShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	//create reference variable
	unsigned int vertex, fragment, geometry;
	// vertex shader
	//instantiate shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	//attach script to shader
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	//compile
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, NULL);
	glCompileShader(geometry);
	checkCompileErrors(geometry, "GEOMETRY");
	//instantiate program and attach reference variable
	ID = glCreateProgram();
	//attach shaders
	glAttachShader(ID, vertex);
	glAttachShader(ID, geometry);
	glAttachShader(ID, fragment);
	//link program
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete redundant shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);
}
