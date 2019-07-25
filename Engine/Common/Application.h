#pragma once

#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

class Application
{
public:
	Application(HINSTANCE hInstance);
	Application(const Application& rhs) = delete;
	Application& operator=(const Application& rhs) = delete;

	bool Initialize();
	int Execute();

	static Application* GetApplication();
	HINSTANCE GetInstance() const { return m_HInstanceApp; }
	HWND GetWnd() const { return m_HWnd; }
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool InitWindow();
	bool InitD3D12();

	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateRtvAndDsvDescriptorHeaps();

public:
	static const int SwapChainBufferCount = 2;

private:
	// Application related
	static Application* m_Application;
	std::wstring m_WindowTitle = L"moEngine";
	int m_Width = 1280;
	int m_Height = 720;
	DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
	DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	bool m_4xMsaaState = false;    // 4X MSAA enabled
	UINT m_4xMsaaQuality = 0;      // quality level of 4X MSAA

	// D3D12 related
	Microsoft::WRL::ComPtr<IDXGIFactory4> m_DXGIFactory;
	Microsoft::WRL::ComPtr<ID3D12Device> m_D3DDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DsvHeap;

	Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
	UINT64 m_CurrentFenceVal = 0;

	UINT m_RtvSize = 0;
	UINT m_DsvSize = 0;
	UINT m_CbvSrvUavSize = 0;

	// WIN32 related
	HINSTANCE m_HInstanceApp = nullptr;
	HWND m_HWnd = nullptr;
};