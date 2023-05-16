#pragma once

#include <unordered_map>
#include <map>
#include <typeindex>
#include <algorithm>
#include <memory>
#include <vector>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <chrono>
#include <math.h>
#include <numeric>
#include <ppl.h>
#include <ranges>
#include <functional>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "STB/stb_image.h"

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>

#include  "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "IMGUI/imgui_impl_glfw.h"

#include "ScopedTimer.h"

struct MeshVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};
