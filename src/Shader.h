#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

class Shader {
public:
    unsigned int ID; // Shader program ID

    // Constructor: loads shaders from file paths
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    // Use the shader program
    void use() const;
/*
    // Utility functions for setting uniforms
    void setUniform1i(const std::string& name, int value) const;
    void setUniform1f(const std::string& name, float value) const;
    void setUniform3f(const std::string& name, float v1, float v2, float v3) const;
    void setUniformMatrix4fv(const std::string& name, const float* matrix) const;
*/
private:
    std::string loadShaderSource(const std::string& filepath);
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

#endif
