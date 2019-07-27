#pragma once

#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include "Common/TimeManager.h"

namespace moEngine
{
	class Application
	{
	public:
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static Application* GetApplication();

		int Execute();

	protected:
		Application(HINSTANCE hInstance);
		virtual ~Application();
		Application(const Application& rhs) = delete;
		Application& operator=(const Application& rhs) = delete;

		virtual bool Initialize();
		virtual void OnResize();
		virtual void Update(float deltaTime) = 0;
		virtual void Draw(float deltaTime) = 0;

		bool InitWindow();
		bool InitD3D12();
		void CreateCommandObjects();
		void CreateSwapChain();
		void CreateRtvAndDsvDescriptorHeaps();

		void FlushCommandQueue();

		HINSTANCE GetInstance() const { return m_HInstanceApp; }
		HWND GetWnd() const { return m_HWnd; }
		ID3D12Resource* GetCurrentBackBuffer() const
		{
			return m_SwapChainBuffer[m_CurBackBufferIdx].Get();
		}
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(
				m_RtvHeap->GetCPUDescriptorHandleForHeapStart(),
				m_CurBackBufferIdx,
				m_RtvSize);
		}
		D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const
		{
			return m_DsvHeap->GetCPUDescriptorHandleForHeapStart();
		}

	private:
		void DisplayFPSOnTitle();

	protected:
		// Application related
		static Application* m_Application;
		std::wstring m_WindowTitle = L"moEngine";
		int m_Width = 1280;
		int m_Height = 720;
		TimeManager m_TimeMgr;
		bool m_AppPaused = false;
		bool m_AppMinimized = false;
		bool m_AppMaximized = false;
		bool m_AppResizing = false;   // are the resize bars being dragged?


		// D3D12 related
		DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
		DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
		bool m_4xMsaaState = false;    // 4X MSAA enabled
		UINT m_4xMsaaQuality = 0;      // quality level of 4X MSAA

		Microsoft::WRL::ComPtr<IDXGIFactory4> m_DXGIFactory;
		Microsoft::WRL::ComPtr<ID3D12Device> m_D3DDevice;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;

		static const int SwapChainBufferCount = 2;
		int m_CurBackBufferIdx = 0;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffer[SwapChainBufferCount];
		Microsoft::WRL::ComPtr<ID3D12Resource> m_DepthStencilBuffer;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_CommandList;

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DsvHeap;

		D3D12_VIEWPORT m_ScreenViewport;
		D3D12_RECT m_ScissorRect;

		Microsoft::WRL::ComPtr<ID3D12Fence> m_Fence;
		UINT64 m_CurrentFenceVal = 0;

		UINT m_RtvSize = 0;
		UINT m_DsvSize = 0;
		UINT m_CbvSrvUavSize = 0;

		// WIN32 related
		HINSTANCE m_HInstanceApp = nullptr;
		HWND m_HWnd = nullptr;
	};
}