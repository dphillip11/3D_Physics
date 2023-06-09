#include "PCH/pch.h"
#include "GameEngine/FileManager.h"

// Define the file paths
const std::array<std::string, static_cast<std::size_t>(FileManager::Models::VOID)> FileManager::modelFilePaths_ = {
		"Assets/Models/cube.obj",       //Cube,
		"Assets/Models/hand.obj",       //Hand,
		"Assets/Models/hare.obj",       //Hare,
		"Assets/Models/robot.obj",      //Robot,
		"Assets/Models/butterfly.obj",  //Butterfly,
		"Assets/Models/taxi.obj",       //Taxi,
		"Assets/Models/tree.obj",       //Tree,
		"Assets/Airplane/plane.obj",       //Airplane,
		"Assets/Models/sphere.obj"       //sphere,
		// Add more model file paths as needed, ensure enum is updated
};

const std::array<std::string, static_cast<std::size_t>(FileManager::Textures::VOID)> FileManager::textureFilePaths_ = {
	"Assets/Textures/HareTexture.jpg",	//Hare,
	"Assets/Textures/matrix.jpg"		//Matrix,
	// Add more texture file paths as needed, ensure enum is updated
};

const std::array<std::string, static_cast<std::size_t>(FileManager::Shaders::VOID)> FileManager::shaderFilePaths_ = {
	"Shaders/Combined/Obj.hlsl",	//Obj,
	"Shaders/Combined/PointShader.hlsl"	,	//PointShader,
	"Shaders/Combined/Basic.hlsl" //Basic
	// Add more audio shader paths as needed, ensure enum is updated
};

// Method implementations
const char* FileManager::GetFilePath(Textures type) {
	return textureFilePaths_[static_cast<std::size_t>(type)].c_str();
}

const char* FileManager::GetFilePath(Models type) {
	return modelFilePaths_[static_cast<std::size_t>(type)].c_str();
}

const char* FileManager::GetFilePath(Shaders type) {
	return shaderFilePaths_[static_cast<std::size_t>(type)].c_str();
}
