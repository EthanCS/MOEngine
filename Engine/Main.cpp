#include "PCH.h"
#include "Common/Application.h"
#include "Common/ExceptionHandler.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		Application app(hInstance);
		if (!app.Initialize())
		{
			MessageBox(0, L"Window Initialization Failed!", L"Error", MB_OK);
			return 0;
		}

		return app.Execute();
	}
	catch (ExceptionHandler& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}