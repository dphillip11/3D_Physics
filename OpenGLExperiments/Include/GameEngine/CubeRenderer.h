#pragma once
#include "RendererComponent.h"


class CubeRenderer : public RendererComponent
{
	struct Impl;
public:
	CubeRenderer() = delete;
	CubeRenderer(int gameobjectID);
	virtual void Update(float deltaTime) override {}
	virtual void Render() override;

private:
	std::unique_ptr<Impl> _impl;
};