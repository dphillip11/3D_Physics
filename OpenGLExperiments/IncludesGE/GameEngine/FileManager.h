#include <array>
#include <string>

class FileManager {
public:
	// Asset types enum classes
	enum class Textures {
		Hare,
		Matrix,
		// Add more texture types as needed
		VOID
	};

	enum class Models {
		Cube,
		Hand,
		Hare,
		Robot,
		Butterfly,
		Taxi,
		Tree,
		Airplane,
		Sphere,
		// Add more model types as needed
		VOID
	};

	enum class Shaders {
		Obj,
		PointShader,
		Basic,
		// Add more audio types as needed
		VOID
	};

	// Method for getting the file path by name
	static const const char* GetFilePath(Textures type);
	static const const char* GetFilePath(Models type);
	static const const char* GetFilePath(Shaders type);

private:
	// Internal data structure to store file paths
	static const std::array<std::string, static_cast<std::size_t>(Models::VOID)> modelFilePaths_;
	static const std::array<std::string, static_cast<std::size_t>(Textures::VOID)> textureFilePaths_;
	static const std::array<std::string, static_cast<std::size_t>(Shaders::VOID)> shaderFilePaths_;
};

#define Models FileManager::Models
#define Textures FileManager::Textures
#define Shaders FileManager::Shaders
#define GetFilePath FileManager::GetFilePath


