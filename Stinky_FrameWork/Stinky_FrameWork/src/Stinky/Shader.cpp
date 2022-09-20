#pragma once
#include <fstream>


#include <glad/glad.h>
#include "Shader.hpp"
#include "Math/Matrix.hpp"
#include "GraphicEngine.hpp"


namespace Stinky
{
    std::string GetFileContents(const char* fileName) noexcept
    {
        std::ifstream in(fileName, std::ios::binary);

        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }

        return std::string{};
    }
    
    unsigned int MakeShader(const char* shaderSource, unsigned int shaderType);

    Shader::Shader(const char* vertex, const char* frag)
    {
        std::string vertexCode = GetFileContents(vertex);
        std::string fragCode = GetFileContents(frag);

        const char* vertexSource = vertexCode.c_str();
        const char* fragSource = fragCode.c_str();

        unsigned int vertexShader = MakeShader(vertexSource, GL_VERTEX_SHADER);
        unsigned int fragmentShader = MakeShader(fragSource, GL_FRAGMENT_SHADER);

        ID = LinkShader(vertexShader, fragmentShader);
    }

    unsigned int MakeShader(const char* shaderSource, unsigned int shaderType)
    {
        //  Make Shader
        unsigned int shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];

        // check for shader compile errors
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);

            if(shaderType == GL_VERTEX_SHADER)
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            else
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        
            std::exit(EXIT_FAILURE);
        }

        return shader;
    }

    unsigned int Shader::LinkShader(unsigned int vertexShader, unsigned int fragShader)
    {
        // link shaders
        ID = glCreateProgram();

        int success;
        char infoLog[512];

        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragShader);
        glLinkProgram(ID);

        // check for linking errors
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            std::exit(EXIT_FAILURE);
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragShader);

        return ID;
    }

    void Shader::Activate()
    {
        glUseProgram(ID);
    }

    void Shader::UnActivate()
    {
        glUseProgram(0);
    }

    bool IsExistUniform(unsigned int uniforms);

    void Shader::SetUniform(std::string name, int value)
    {
        GLint uniforms = glGetUniformLocation(ID, name.c_str());

        if (IsExistUniform(uniforms) == true)
            glUniform1i(uniforms, value);
    }

    void Shader::SetUniform(std::string name, bool value)
    {
        SetUniform(name, static_cast<int>(value));
    }

    void Shader::SetUniform(std::string name, float value)
    {
        GLint uniforms = glGetUniformLocation(ID, name.c_str());

        if (IsExistUniform(uniforms) == true)
            glUniform1f(uniforms, value);
    }

    void Shader::SetUniform(std::string name, int value1, int value2)
    {
        GLint uniforms = glGetUniformLocation(ID, name.c_str());

        if (IsExistUniform(uniforms) == true)
            glUniform2i(uniforms, value1, value2);
    }

    void Shader::SetUniform(std::string name, float value1, float value2)
    {
        GLint uniforms = glGetUniformLocation(ID, name.c_str());

        if (IsExistUniform(uniforms) == true)
            glUniform2f(uniforms, value1, value2);
    }

    void Shader::SetUniform(std::string name, const float* value)
    {
        GLint uniforms = glGetUniformLocation(ID, name.c_str());

        if (IsExistUniform(uniforms) == true)
            glUniformMatrix3fv(uniforms, 1, GL_FALSE, value);
    }

    void Shader::SetUniform_MToN_Matrix(glm::vec2 translate, glm::vec2 scale)
    {
        GraphicEngine& engine = GraphicEngine::Instance();

        SetUniform("MTON", &(engine.GetCamera().GetCameraMatrix() * TranslateMatrix(translate) * engine.GetMatrix() * ScaleMatrix(scale))[0].x);
    }

    bool IsExistUniform(unsigned int uniforms)
    {
        if (uniforms >= 0)
            return true;

        std::cout << "Uniform variable doesn't exist!!!\n";
        std::exit(EXIT_FAILURE);
    }

    void Shader::Delete()
    {
        glDeleteProgram(ID);
    }    
}