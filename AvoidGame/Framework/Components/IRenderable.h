#pragma once
class IRenderable
{
public:
	virtual void PostRender() = 0;
	virtual void Render() = 0;
};

