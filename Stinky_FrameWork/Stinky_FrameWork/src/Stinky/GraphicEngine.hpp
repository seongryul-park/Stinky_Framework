#pragma once 
#include <map>

#include <stack>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "../Models/Texture.hpp"

typedef unsigned int GLenum;
typedef unsigned int GLuint;

namespace Stinky
{
    //  options using GraphicEngine
    class Option
    {
    public:
        Option();

        glm::mat3 popMatrix3s;  // saved inverse matrices

        glm::vec4 outLineColors;
        glm::vec4 colors;
        glm::vec4 imageColors;

        float outLine;

        bool noTint;
        bool noFill;
        bool noOutLine;
    };

    class GraphicEngine
    {
    public:
        static GraphicEngine& Instance() { static GraphicEngine instance; return instance; }

        static std::vector<Shader>& GetShader() { return Instance().shaders; }              //  saved shaders
        static std::vector<Model>& GetModel() { return Instance().models; }                 //  saved models
        static std::map<std::string, Texture>& GetImage() { return Instance().images; }     //  saved images

        static std::stack<Option>& GetOptions() { return Instance().options; }              //  return options

        static glm::mat3& GetMatrix() { return Instance().matrix3; }                        //  return matrix

        static Camera& GetCamera() { return Instance().camera; }

        void Init(float width, float height);
        void PushSetting();
        void PopSetting();

    private:
        GraphicEngine();

        std::vector<Shader> shaders;
        std::vector<Model> models;
        std::map<std::string, Texture> images;

        std::stack<Option> options;

        glm::mat3 matrix3;

        Camera camera;
    };
}