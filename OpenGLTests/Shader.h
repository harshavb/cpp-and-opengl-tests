#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

class Shader
{
public:
    // the program ID
    GLuint shaderProgram;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // destructor unlodas the shader
    ~Shader();

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec4(const std::string& name, float val1, float val2, float val3, float val4) const;
    void setMat4(const std::string& name, glm::mat4 mat) const;
};