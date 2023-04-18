//// RenderPlane.h
#include "../Classes/Model.h"
#include "../Classes/obj.h"
#include "../Classes/Texture.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include "../Classes/camera.h"
#include "../InputHandlers/BasicCameraInput.h"



class RenderPlane : public Program {
    // settings
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;
    //setup camera
public:
    const char* model_path = "src/Assets/hare.obj";
    const char* texture_path = "src/Assets/HareTexture.jpg";
    Camera camera = Camera(glm::vec3(0, 100, -200), glm::vec3(0, 100, -10));
    obj taxi;
    Model taxi_model;
    Light light1{ glm::vec3(0,100,-500), glm::vec3(1), glm::vec3(1), glm::vec3(1) };
    Material mat1{ glm::vec3(0.2f), glm::vec3(0.7f), glm::vec3(0.4f), 32 };
    float time = 0;
    BasicCameraInput inputHandler = BasicCameraInput(&camera);
    void Setup()
    {
        camera.setFOV(90);
        camera.moveSpeed = 100;
        camera.panSpeed = 400;
        camera.zoomSpeed = 1000;
        camera.isLockedOn = false;
        taxi.read(model_path);
        taxi.vertices = taxi.unravelIndices(taxi.vertices, taxi.vertexIndices);
        taxi.normalMap = taxi.unravelIndices(taxi.normalMap, taxi.normalIndices);
        taxi.textureMap = taxi.unravelIndices(taxi.textureMap, taxi.textureIndices);

        //vertices
        glBindVertexArray(taxi_model._VAO);
        taxi_model.setVertices(&taxi.vertices[0], (int)taxi.vertices.size() * 3, taxi_model._VAO, taxi_model._VBO);
        taxi_model.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

        //normals
        if (taxi.normalMap.size() > 0)
        {
            taxi_model.shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl");
            taxi_model.setVertices(&taxi.normalMap[0], (int)taxi.normalMap.size() * 3, taxi_model._VAO, taxi_model._VBOnormal);
            taxi_model.setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        }
        else
            taxi_model.shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl", "src/shaders/geometry/calculateNormals.hlsl");

        //texturemap
        if (taxi.textureMap.size() > 0)
        {
            taxi_model.setVertices(&taxi.textureMap[0], (int)taxi.textureMap.size() * 3, taxi_model._VAO, taxi_model._VBOtexture);
            taxi_model.setAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
            //bind texture
            Texture diffuse_texture;
            diffuse_texture.loadImage(texture_path, GL_RGB, true);
            diffuse_texture.bind();
            GLuint textureSamplerLoc = glGetUniformLocation(taxi_model.shader->ID, "diffuse_texture");
            glUniform1i(textureSamplerLoc, 0); // 0 for texture unit 0, can be adjusted to match the texture unit index
        }

        
    }

    void Run(float deltaTime)
    {
        time += deltaTime;
        glm::mat4 view = camera.lookAt();
        taxi_model.shader->use();
        taxi_model.draw();
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -(time)+3.14f, glm::vec3(0, 1, 0));
        taxi_model.shader->setMat4("model", glm::translate(rotationMatrix, glm::vec3(10, 0, 0)));
        taxi_model.draw();
        rotationMatrix = glm::rotate(glm::mat4(1.0f), -(time), glm::vec3(0, 1, 0));
        taxi_model.shader->setMat4("model", glm::translate(rotationMatrix, glm::vec3(10, 0, 0)));
        taxi_model.shader->setMat4("view", camera.lookAt());
        taxi_model.shader->setMat4("projection", camera.projection);
        taxi_model.shader->setVec3("viewPosition", camera._position);
        taxi_model.shader->setLight(light1);
        taxi_model.shader->setMaterial(mat1);
    }

    InputObserver* getInputHandler()
    {
        return &inputHandler;
    }
};
