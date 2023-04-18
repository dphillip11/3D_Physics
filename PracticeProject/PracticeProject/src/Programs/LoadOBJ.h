//// LoadOBJ.h
#include "../Classes/Model.h"
#include "../Classes/obj.h"
#include "../Classes/Texture.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include "../Classes/camera.h"
#include "../InputHandlers/BasicCameraInput.h"



class LoadOBJ : public Program {
    // settings
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;
    //setup camera
public:
    const char* model_path = "src/Assets/hare.obj";
    const char* texture_path = "src/Assets/HareTexture.jpg";
    Camera camera = Camera(glm::vec3(0, 100, -200), glm::vec3(0, 100, -10));
    obj model_data;
    Model model;
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
        model_data.read(model_path);
        model_data.vertices = model_data.unravelIndices(model_data.vertices, model_data.vertexIndices);
        model_data.normalMap = model_data.unravelIndices(model_data.normalMap, model_data.normalIndices);
        model_data.textureMap = model_data.unravelIndices(model_data.textureMap, model_data.textureIndices);

        //vertices
        glBindVertexArray(model._VAO);
        model.setVertices(&model_data.vertices[0], (int)model_data.vertices.size() * 3, model._VAO, model._VBO);
        model.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

        //normals
        if (model_data.normalMap.size() > 0)
        {
            model.shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl");
            model.setVertices(&model_data.normalMap[0], (int)model_data.normalMap.size() * 3, model._VAO, model._VBOnormal);
            model.setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        }
        else
            model.shader = std::make_unique<Shader>("src/shaders/vertex/obj.hlsl", "src/shaders/fragment/obj.hlsl", "src/shaders/geometry/calculateNormals.hlsl");

        //texturemap
        if (model_data.textureMap.size() > 0)
        {
            model.setVertices(&model_data.textureMap[0], (int)model_data.textureMap.size() * 3, model._VAO, model._VBOtexture);
            model.setAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
            //bind texture
            Texture diffuse_texture;
            diffuse_texture.loadImage(texture_path, GL_RGB, true);
            diffuse_texture.bind();
            GLuint textureSamplerLoc = glGetUniformLocation(model.shader->ID, "diffuse_texture");
            glUniform1i(textureSamplerLoc, 0); // 0 for texture unit 0, can be adjusted to match the texture unit index
        }

        
    }

    void Run(float deltaTime)
    {
        time += deltaTime;
        glm::mat4 view = camera.lookAt();
        model.shader->use();
        model.draw();
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -(time)+3.14f, glm::vec3(0, 1, 0));
        model.shader->setMat4("model", glm::translate(rotationMatrix, glm::vec3(10, 0, 0)));
        model.draw();
        rotationMatrix = glm::rotate(glm::mat4(1.0f), -(time), glm::vec3(0, 1, 0));
        model.shader->setMat4("model", glm::translate(rotationMatrix, glm::vec3(10, 0, 0)));
        model.shader->setMat4("view", camera.lookAt());
        model.shader->setMat4("projection", camera.projection);
        model.shader->setVec3("viewPosition", camera._position);
        model.shader->setLight(light1);
        model.shader->setMaterial(mat1);
    }

    InputObserver* getInputHandler()
    {
        return &inputHandler;
    }
};
