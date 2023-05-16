#pragma once
#include "GameEngine/RendererComponent.h"


class CubeRenderer : public RendererComponent
{
	struct Impl;
public:
	CubeRenderer() = delete;
	CubeRenderer(int gameobjectID);
	virtual void Update(float deltaTime) override {}
	virtual void Render() override
	{
		RendererComponent::Render();
	}

private:
	bool isLoaded{ false };
	std::unique_ptr<Impl> _impl;
};