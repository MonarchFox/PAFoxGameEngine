#include <stdexcept>
#include <iostream>

#include "../Public/GraphicsRenderer.h"



namespace FoxEngine
{
    FxGraphicsRenderer::FxGraphicsRenderer()
        = default;

    FxGraphicsRenderer::~FxGraphicsRenderer()
    {
        if (!Release())
        {
            std::cout << "Tho I didnt throw error there's some problem in Release call with Renderer!\n";
        }
    }

    FxGraphicsRenderer* FxGraphicsRenderer::Get()
    {
        static FxGraphicsRenderer instance;
        return &instance;
    }

    bool FxGraphicsRenderer::InitDevices(HWND hWnd)
    {
        mWindowHandle = hWnd;
        CreateDevice();
        CreateSwapChain();
        CreateRenderTargetView();
        CreateViewPort();
        return true;
    }

    bool FxGraphicsRenderer::Render() const
    {
        mDxDeviceContext->ClearRenderTargetView(mRenderTargetView, GetBackgroundColor().data());
        mDxDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        const HRESULT hr = mSwapChain->Present(1, 0);
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed To Present!\n");
        }
        return true;
    }

    bool FxGraphicsRenderer::Release() const
    {
        SAFE_RELEASE(mBackBuffer);
        SAFE_RELEASE(mDepthStencilBuffer);
        SAFE_RELEASE(mDepthStencilView);
        SAFE_RELEASE(mRenderTargetView);
        SAFE_RELEASE(mSwapChain);

        //~ Devices
        mDxDeviceContext->ClearState();

        SAFE_RELEASE(mDxgiAdapter);
        SAFE_RELEASE(mDxgiDevice);
        SAFE_RELEASE(mDxgiFactory);
        SAFE_RELEASE(mDxDeviceContext);
        SAFE_RELEASE(mDxDevice);

        return true;
    }

    void FxGraphicsRenderer::CreateDevice()
    {
        constexpr D3D_FEATURE_LEVEL featuresLevels[]{ D3D_FEATURE_LEVEL_11_0 };
        constexpr UINT nFeatureLevels = std::size(featuresLevels);

        HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
            featuresLevels, nFeatureLevels,
            D3D11_SDK_VERSION, &mDxDevice,
            nullptr, &mDxDeviceContext);
        if (FAILED(hr)) throw std::runtime_error("FxGraphicsRenderer::Init(): D3D11CreateDevice() failed");

        hr = mDxDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&mDxgiDevice));
        if (FAILED(hr)) throw std::runtime_error("Failed ID3D11Device::QueryInterface(dxgiDevice) failed");

        hr = mDxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&mDxgiAdapter));
        if (FAILED(hr)) throw std::runtime_error("Failed DxgiDevice::GetParent(Adapter) failed");

        hr = mDxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&mDxgiFactory));
        if (FAILED(hr)) throw std::runtime_error("Failed DxgiAdapter::GetParent(Factory) failed");
    }

    void FxGraphicsRenderer::CreateSwapChain()
    {
        if (!mWindowHandle) throw std::runtime_error("WindowHandle is Null!");
        RECT windowSize;
        GetClientRect(mWindowHandle, &windowSize);

        DXGI_SWAP_CHAIN_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.BufferCount = 2;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.BufferDesc.Width = windowSize.right - windowSize.left;
        desc.BufferDesc.Height = windowSize.bottom - windowSize.top;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.RefreshRate.Numerator = 60;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.Windowed = TRUE;
        desc.OutputWindow = mWindowHandle;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        HRESULT hr = mDxgiFactory->CreateSwapChain(mDxDevice, &desc, &mSwapChain);
        if (FAILED(hr)) {
            std::cerr << "Failed to create swap chain. HRESULT: " << std::hex << hr << std::endl;
            throw std::runtime_error("Failed DxgiFactory::CreateSwapChain() failed");
        }
    }

    void FxGraphicsRenderer::CreateRenderTargetView()
    {
        HRESULT hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&mBackBuffer));
        if (FAILED(hr)) throw std::runtime_error("Failed mSwapChain::GetBuffer() failed");

        hr = mDxDevice->CreateRenderTargetView(mBackBuffer, nullptr, &mRenderTargetView);
        if (FAILED(hr)) throw std::runtime_error("Failed DxDevice->CreateRenderTargetView() failed");

        //~ Creating Depth Stencil View
        if (!mWindowHandle) throw std::runtime_error("WindowHandle is Null!");
        RECT windowSize;
        GetClientRect(mWindowHandle, &windowSize);

        D3D11_TEXTURE2D_DESC desc;
        desc.Height = windowSize.bottom - windowSize.top;
        desc.Width = windowSize.right - windowSize.left;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        hr = mDxDevice->CreateTexture2D(&desc, nullptr, &mDepthStencilBuffer);
        if (FAILED(hr)) throw std::runtime_error("Failed DxDevice->CreateTexture2D(DepthStencilBuffer) failed");

        hr = mDxDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView);
        if (FAILED(hr)) throw std::runtime_error("Failed DxDevice->CreateDepthStencilView() failed");

        mDxDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
        std::cout << "Initialized RenderTargets!\n";
    }

    void FxGraphicsRenderer::CreateViewPort()
    {
        if (!mWindowHandle) throw std::runtime_error("WindowHandle is Null!");
        RECT windowSize;
        GetClientRect(mWindowHandle, &windowSize);

        mScreenViewport.Width = static_cast<float>(windowSize.right - windowSize.left);
        mScreenViewport.Height = static_cast<float>(windowSize.bottom - windowSize.top);
        mScreenViewport.MinDepth = 0.0f;
        mScreenViewport.MaxDepth = 1.0f;
        mScreenViewport.TopLeftX = static_cast<float>(windowSize.left);
        mScreenViewport.TopLeftY = static_cast<float>(windowSize.top);
        mDxDeviceContext->RSSetViewports(1, &mScreenViewport);

        std::cout << "ViewPort Set!\n";
    }

#pragma region Asset_Build_Functionality
    void FxGraphicsRenderer::BuildAsset(FoxAssets::FxAssetsBase* asset)
    {

    }

    HRESULT FxGraphicsRenderer::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
    {
        HRESULT hr = S_OK;

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

        ID3DBlob* pErrorBlob = nullptr;
        hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint,
            szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

        if (FAILED(hr))
        {
            if (pErrorBlob)
            {
                OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
                pErrorBlob->Release();
            }
            return hr;
        }
        if (pErrorBlob) pErrorBlob->Release();
        return S_OK;
    }

    void FxGraphicsRenderer::BuildAssetVertexShader(FoxAssets::FxAssetsBase* asset)
    {

    }

    void FxGraphicsRenderer::BuildAssetPixelShader(FoxAssets::FxAssetsBase* asset)
    {

    }

    void FxGraphicsRenderer::BuildAssetInputLayout(FoxAssets::FxAssetsBase* asset)
    {

    }

    void FxGraphicsRenderer::BuildAssetVertexBuffer(FoxAssets::FxAssetsBase* asset)
    {

    }

    void FxGraphicsRenderer::BuildAssetIndexBuffer(FoxAssets::FxAssetsBase* asset)
    {
        D3D11_BUFFER_DESC desc{};
        desc.ByteWidth = sizeof(asset->mIndices[0]) * asset->mIndices.size();

        D3D11_SUBRESOURCE_DATA initIndicesData{};
        initIndicesData.pSysMem = asset->mIndices.data();

        const HRESULT hr = mDxDevice->CreateBuffer(&desc, &initIndicesData, &asset->mpIndicesBuffer);
        if (FAILED(hr))
            throw std::runtime_error("Failed To Create Index Buffer!");
    }

    void FxGraphicsRenderer::BuildAssetConstantBuffer(FoxAssets::FxAssetsBase* asset)
    {

    }

#pragma endregion
}
