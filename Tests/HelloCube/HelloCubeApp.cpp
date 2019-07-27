#include "stdafx.h"
#include "HelloCubeApp.h"
#include "Common/ExceptionHandler.h"

HelloCubeApp::HelloCubeApp(HINSTANCE hInstance)
	:Application(hInstance)
{
	m_WindowTitle = L"Hello Cube";
}

HelloCubeApp::~HelloCubeApp()
{
}

bool HelloCubeApp::Initialize()
{
	if (!Application::Initialize())
		return false;

	return true;
}

void HelloCubeApp::OnResize()
{
	Application::OnResize();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
	
	try
	{
		HelloCubeApp app(hInstance);
		if (!app.Initialize())
			return 0;

		return app.Execute();
	}
	catch (ExceptionHandler& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}