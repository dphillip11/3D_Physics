#pragma once
#include <string>
#include "../Libraries/glm/glm/vec3.hpp"
#include "../Libraries/glm/glm/matrix.hpp"

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void checkCompileErrors(unsigned int shader, std::string type);

};  