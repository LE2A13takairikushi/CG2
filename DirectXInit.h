#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include "WinAPI.h"
#include <vector>
#include <string>
//ここに置いとくと危ないんじゃない？
#include<wrl.h>
using namespace Microsoft::WRL;

//アダプターの列挙用
static std::vector<ComPtr<IDXGIAdapter4>> adapters;

//ここに特定の名前をもつアダプターオブジェクトが入る
static IDXGIAdapter4* tmpAdapter = nullptr;

class DirectX12
{
public:

	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgifactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	std::vector<ComPtr<ID3D12Resource>> backBuffers;

	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

public:
	void yobidasi(WinAPI winApi_);

	void AdapterSort();

	void CreateDevice();

	void CreateCmdList();

	void SetSwapChain(WinAPI winApi_);

	void SetDescHeap();

	void SetBackBuffer();

	void RenderTargetView();

	void CreateFence();
};

static DirectX12 DX12;

ID3D12Device *bGetDevice();