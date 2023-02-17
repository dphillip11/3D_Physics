#pragma once
#include <memory>
#include "Model.h"
#include "Camera.h"

class ShaderExperiment
{
    std::unique_ptr<Model> model;
    std::unique_ptr<Shader> shader;
    static const int BLOCKS = 5000;
    int COLUMNS;
public:
    ShaderExperiment();
    void draw(Camera camera, float time);
};

