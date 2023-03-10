#include "ShaderExperiment.h"


ShaderExperiment::ShaderExperiment(): COLUMNS((int)sqrt(BLOCKS)), model(std::make_unique<Model>())
{
    shader = std::make_unique<Shader>("src/shaders/vertex/drawOblongs.hlsl", "src/shaders/fragment/drawOblongs.hlsl", "src/shaders/geometry/drawOblongs.hlsl");

    auto params = new glm::vec3[BLOCKS];

    for (int i = 0;i < BLOCKS; i++)
    {
        params[i] = glm::vec3((float)i, rand() % 10, rand() % 50);
    }
    model->setVertices(params, 3 * BLOCKS);
    delete[](params);
    model->setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    shader->setInt("columns", COLUMNS);
}

void ShaderExperiment::draw(Camera camera, float time) 
{
    shader->use();
    shader->setFloat("time", time);
    shader->setInt("columns", COLUMNS);
    shader->setMat4("MVP", camera.projection * camera.lookAt());
    shader->setVec3("lightPosition", glm::vec3(50,50,100));
    shader->setVec3("camPosition", camera._position);
    shader->setVec3("ambientColor", glm::vec3(1));
    shader->setVec3("diffuseColor", glm::vec3(1));
    shader->setVec3("specularColor", glm::vec3(1));
    shader->setFloat("shininess", 250.0f);
    shader->setFloat("ambientIntensity", 0.2f);
    shader->setFloat("diffuseIntensity",0.4f);
    shader->setFloat("specularIntensity",0.5f);
    model->draw();
}
