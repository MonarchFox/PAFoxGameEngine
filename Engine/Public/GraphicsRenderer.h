#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <vector>
#include <windows.h>

#include "../../Assets/AssetsBase.h"


#define SAFE_RELEASE(p, status) \
    if (p != nullptr) {         \
        p->Release();           \
    }                           \


namespace FoxEngine
{
    class FxGraphicsRenderer
    {
        //~ Members
        ID3D11Device* mDxDevice{ nullptr };
        ID3D11DeviceContext* mDxDeviceContext{ nullptr };
        IDXGIAdapter* mDxgiAdapter{ nullptr };
        IDXGIDevice* mDxgiDevice{ nullptr };
        IDXGIFactory* mDxgiFactory{ nullptr };

        IDXGISwapChain* mSwapChain{ nullptr };
        ID3D11RenderTargetView* mRenderTargetView{ nullptr };
        ID3D11Texture2D* mBackBuffer{ nullptr };
        ID3D11Texture2D* mDepthStencilBuffer{ nullptr };
        ID3D11DepthStencilView* mDepthStencilView{ nullptr };
        D3D11_VIEWPORT           mScreenViewport{};

        HWND mWindowHandle{ nullptr };

        //~ Settings
        UINT m4xMsaaQuality{};
        bool mbEnable4xMsaa{ true };

        //~ Rendering Members
        std::vector<float> mBackgroundColor{ 0.0f, 0.0f, 0.0f, 1.0f };

    public:
        FxGraphicsRenderer();
        ~FxGraphicsRenderer();
        static FxGraphicsRenderer* Get();

        bool InitDevices(HWND hWnd);

        //~ Rendering Functionality
        [[nodiscard]] bool Render() const;
        void BuildAsset(FoxAssets::FxAssetsBase* asset);

        void SetBackGroundColor(const std::vector<float>& f4Color) { mBackgroundColor = f4Color; }
        [[nodiscard]] std::vector<float> GetBackgroundColor() const { return mBackgroundColor; }

        [[nodiscard]] bool Release() const;

    private:
        void CreateDevice();
        void CreateSwapChain();
        void CreateRenderTargetView();
        void CreateViewPort();

        //~ Asset Build Functions
        HRESULT CompileShaderFromFile(const WCHAR* szFileName,
                                      LPCSTR szEntryPoint,
                                      LPCSTR szShaderModel,
                                      ID3DBlob** ppBlobOut);
        
        void BuildAssetVertexShader(FoxAssets::FxAssetsBase* asset);
        void BuildAssetPixelShader(FoxAssets::FxAssetsBase* asset);
        void BuildAssetInputLayout(FoxAssets::FxAssetsBase* asset);

        void BuildAssetVertexBuffer(FoxAssets::FxAssetsBase* asset);
        void BuildAssetIndexBuffer(FoxAssets::FxAssetsBase* asset);
        void BuildAssetConstantBuffer(FoxAssets::FxAssetsBase* asset);
    };
}
