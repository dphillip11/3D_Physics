#include "PCH/pch.h"
#include "GameEngine/GUI.h"
#include "Program.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/CollisionManager.h"
#include "GameEngine/PrefabManager.h"
#include "GameEngine/TransformComponent.h"
#include "GameEngine/PhysicsComponent.h"

void GUI::Init(GLFWwindow* window)
{
	m_window = window;
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::GetIO().WantCaptureMouse = true;
}

void GUI::Render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	if (demo_window)
		DisplayDemoWindow();
	if (system_window)
		DisplaySystemWindow();
	if (hierarchy_window)
		DisplayHierarchy();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void GUI::DisplayHierarchy() {
	ImGui::SetNextWindowPos(ImVec2(0, 200));
	ImGui::SetNextWindowSize(ImVec2(450, -1));
	ImGui::Begin("Hierarchy", &hierarchy_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	ImGui::SetWindowFontScale(1.5f);
	DisplaySpawnButton();
	for (const auto& [id, gameObject] : DM.GameObjects) {
		DisplayGameObject(id);
	}
	ImGui::End();
}

void GUI::DisplayGameObject(int id)
{
	auto gameobject = DM.GetGameObject(id);
	if (gameobject == nullptr)
		return;

	ImGui::PushID(id);
	ImGui::Separator();

	auto namestring = gameobject->m_name.empty() ? "GameObject: " + std::to_string(id) : "GameObject: " + gameobject->m_name + " " + std::to_string(id);

	ImGui::Indent(ImGui::GetWindowWidth() - 100);
	if (ImGui::Button("Delete"))
		gameobject->deleted = true;
	ImGui::Unindent(ImGui::GetWindowWidth() - 100);
	ImGui::SameLine(1, 1);
	if (ImGui::CollapsingHeader(namestring.c_str()))
	{
		ImGui::Indent(20.0f);
		DisplayTransform(id);
		DisplayBoxCollider(id);
		DisplayRigidBody(id);
		ImGui::Indent(-20.0f);
	}
	ImGui::PopID();
}

void GUI::DisplaySpawnButton()
{
	ImGui::SetNextItemWidth(150);
	if (ImGui::BeginCombo("Prefab", PrefabManager::prefabLabels[(static_cast<int>(PrefabManager::selectedPrefab))]))
	{
		for (int i = 0; i < static_cast<int>(PrefabManager::Prefabs::TREE) + 1; i++)
		{
			PrefabManager::Prefabs prefab = static_cast<PrefabManager::Prefabs>(i);
			bool isSelected = (PrefabManager::selectedPrefab == prefab);
			if (ImGui::Selectable(PrefabManager::prefabLabels[i], isSelected))
			{
				PrefabManager::selectedPrefab = prefab;
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	ImGui::SameLine(250);
	if (ImGui::Button("Spawn"))
	{
		PrefabManager::Spawn(PrefabManager::selectedPrefab);
	}
}

void GUI::DisplayDemoWindow()
{
	ImGui::ShowDemoWindow(&demo_window);
}

void GUI::DisplaySystemWindow()
{

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("System Window", &system_window);
	ImGui::SetWindowFontScale(1.5f);
	if (ImGui::Button("Next Program"))
		Program::NextProgram();
	ImGui::ColorEdit3("clear color", (float*)&Window::instance->clearColor);
	ImGui::DragFloat3("Camera Position", reinterpret_cast<float*>(&Camera::currentCamera->_position.x));
	ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
	ImGui::End();
}

void GUI::DisplayTransformInfo(TransformComponent*& transform)
{
	auto translation = glm::vec3(0);
	ImGui::SliderFloat3("Translate: ", &translation[0], -0.01, 0.01);
	transform->Translate(translation);
	translation = glm::vec3(0);

	auto scale = glm::vec3(1);
	ImGui::SliderFloat3("Scale: ", &scale[0], 0.999, 1.001);
	transform->Scale(scale);
	scale = glm::vec3(1);

	auto rotation = glm::vec3(0);
	ImGui::SliderFloat3("Rotate: ", &rotation[0], -0.1, 0.1);
	transform->Rotate(rotation);
	rotation = glm::vec3(0);
}

void GUI::DisplayTransform(int id)
{
	auto transform = DM.GetComponent<TransformComponent>(id);

	if (transform == nullptr)
		return;

	if (ImGui::CollapsingHeader("Transform"))
	{
		DisplayTransformInfo(transform);
	}
}

void GUI::DisplayBoxCollider(int id)
{
	auto transform = CollisionManager::GetCollider(id);

	if (transform == nullptr)
		return;

	if (ImGui::CollapsingHeader("Box Collider"))
	{
		if (ImGui::Button("Show Collider"))
		{
			DM.GetComponent<ColliderComponent>(id)->ToggleCollider();
		}
		ImGui::PushID((std::to_string(id) + "Collider").c_str());
		DisplayTransformInfo(transform);
		ImGui::PopID();
	}
}

void GUI::DisplayRigidBody(int id)
{
	auto rb = DM.GetComponent<PhysicsComponent>(id);

	if (rb == nullptr)
		return;

	if (ImGui::CollapsingHeader("RigidBody"))
	{

		ImGui::Text("Velocity");
		auto velocity = rb->GetVelocity();
		ImGui::DragFloat3("##v", &velocity[0]);
		rb->SetVelocity(velocity);

		if (ImGui::Button("Rest"))
		{
			rb->SetAcceleration(glm::vec3(0));
			rb->SetVelocity(glm::vec3(0));
		}

		ImGui::Text("Gravity");
		auto gravity = rb->GetGravity();
		ImGui::DragFloat3("##g", &gravity[0]);
		rb->SetGravity(gravity);

		if (ImGui::Button("Static"))
		{
			rb->ToggleStatic();
		}
	}
}

void GUI::Close()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}