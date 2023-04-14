//// RenderPlane.h
#include "../Model.h"
#include "../obj.h"
#include "../Texture.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include "../Camera.h"

#ifndef RENDERPLANE_H
#define RENDERPLANE_H

namespace RenderPlane {
    // settings
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;
    //setup camera
    Camera camera = Camera(glm::vec3(0, 5, 0), glm::vec3(0, 0, 10));
    obj taxi;
    std::unique_ptr<Model> taxi_model;
    Light light1{ glm::vec3(0,5,-20), glm::vec3(1), glm::vec3(1), glm::vec3(1) };
    Material mat1{ glm::vec3(0.2), glm::vec3(0.7), glm::vec3(0.4), 32 };

    void Setup()
    {
        taxi_model = std::make_unique<Model>();
        taxi.read("src/Assets/plane/plane.obj");
        taxi.vertices = taxi.unravelIndices(taxi.vertices, taxi.vertexIndices);
        taxi.normalMap = taxi.unravelIndices(taxi.normalMap, taxi.normalIndices);
        taxi.textureMap = taxi.unravelIndices(taxi.textureMap, taxi.textureIndices);

        //vertices
        glBindVertexArray(taxi_model->_VAO);
        taxi_model->setVertices(&taxi.vertices[0], taxi.vertices.size() * 3, taxi_model->_VAO, taxi_model->_VBO);
        taxi_model->setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

        //normals
        if (taxi.normalMap.size() > 0)
        {
            taxi_model->shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl");
            taxi_model->setVertices(&taxi.normalMap[0], taxi.normalMap.size() * 3, taxi_model->_VAO, taxi_model->_VBOnormal);
            taxi_model->setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        }
        else
            taxi_model->shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl", "src/shaders/geometry/calculateNormals.hlsl");

        //texturemap
        if (taxi.textureMap.size() > 0)
        {
            taxi_model->setVertices(&taxi.textureMap[0], taxi.textureMap.size() * 3, taxi_model->_VAO, taxi_model->_VBOtexture);
            taxi_model->setAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        }
        //bind texture
        Texture diffuse_texture;
        diffuse_texture.loadImage("src/Assets/plane/plane_diffuse.jpg", GL_RGB, true);
        diffuse_texture.bind();
        GLuint textureSamplerLoc = glGetUniformLocation(taxi_model->shader->ID, "diffuse_texture");
        glUniform1i(textureSamplerLoc, 0); // 0 for texture unit 0, can be adjusted to match the texture unit index
    }

    void Run(float time)
    {
        glm::mat4 view = camera.lookAt();
        taxi_model->shader->use();
        taxi_model->draw();
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -(time) + 3.14f, glm::vec3(0, 1, 0));
        taxi_model->shader->setMat4("model", glm::translate(rotationMatrix, glm::vec3(10, 0, 0)));
        taxi_model->draw();
        rotationMatrix = glm::rotate(glm::mat4(1.0f), -(time), glm::vec3(0, 1, 0));
        taxi_model->shader->setMat4("model", glm::translate(rotationMatrix, glm::vec3(10, 0, 0)));
        taxi_model->shader->setMat4("view", camera.lookAt());
        taxi_model->shader->setMat4("projection", camera.projection);
        taxi_model->shader->setVec3("viewPosition", camera._position);
        taxi_model->shader->setLight(light1);
        taxi_model->shader->setMaterial(mat1);
    }
}

#endif // RENDERPLANE_H