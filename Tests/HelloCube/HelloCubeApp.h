#pragma once

#include "Common/Application.h"

using namespace moEngine;

class HelloCubeApp : public Application
{
public:
	HelloCubeApp(HINSTANCE hInstance);
	~HelloCubeApp();

	virtual bool Initialize() override;

protected:
	virtual void OnResize() override;
};