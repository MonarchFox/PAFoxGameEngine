#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <vector>
#include <windows.h>
#include <string>

#include "../../Utils/Helper.h"
#include "FoxEngine.h"


namespace FoxEngine
{
    class FxGraphicsRenderer
    {

    public:
        FxGraphicsRenderer();
        ~FxGraphicsRenderer();
        static FxGraphicsRenderer* Get();

        bool InitDevices(HWND hWnd);

        //------------------------------------------------------------------------
        // Rendering Functionality
        //------------------------------------------------------------------------

        //~ PreRendering Setup
        bool PresetInputLayout(ID3D11InputLayout* layout);
        bool PresetVertexBuffer(ID3D11Buffer* ppVertexBuffer, UINT startSlot, UINT numberBuffers, UINT* pStride, UINT* pOffset);
        bool PresetIndexBuffer(ID3D11Buffer* ppIndexBuffer, DXGI_FORMAT format, UINT offset);
        bool PresetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);

        //~ Rendering Setup
        bool RenderVertextShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const * ppClassInstances, UINT numClassInstances);
        bool RenderPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT numClassInstances);
        bool RenderVertexConstantBuffer(ID3D11Buffer* ppConstantBuffer, UINT startSlot, UINT numberBuffers);

        //~ Build Asset Funtions
        void BuildAssetVertexShader(std::wstring& effectPath, ID3DBlob* vertexBlop, ID3D11VertexShader* vertexShader);
        void BuildAssetPixelShader(std::wstring& effectPath, ID3DBlob* pixelBlop, ID3D11PixelShader* pixelShader);
        void BuildAssetInputLayout(ID3DBlob* vertexBlop, std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayoutDesc, ID3D11InputLayout* inputLayout);
        void BuildAssetsBuffer(D3D11_BUFFER_DESC desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer* buffer);
        void BuildRasterizerState(D3D11_RASTERIZER_DESC* rasterDesc);

        //~ Setters and Getters
        void SetBackGroundColor(const std::vector<float>& f4Color) { mBackgroundColor = f4Color; }
        std::vector<float> GetBackgroundColor() const              { return mBackgroundColor; }

    private:

        //~ Render on Screen
        bool Render(const std::vector<std::unique_ptr<FoxAssets::FAAssetsBase>>& pAsset) const;
        friend FxEngine;

        void CreateDevice();
        void CreateSwapChain();
        void CreateRenderTargetView();
        void CreateViewPort();

        //~ Self Destructed since only 1 instance per program
        bool Release() const;

        //~ Helper Functions
        HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    private:
        //~ Members
        ID3D11Device*        mDxDevice       { nullptr };
        ID3D11DeviceContext* mDxDeviceContext{ nullptr };
        IDXGIAdapter*        mDxgiAdapter    { nullptr };
        IDXGIDevice*         mDxgiDevice     { nullptr };
        IDXGIFactory*        mDxgiFactory    { nullptr };

        IDXGISwapChain*         mSwapChain          { nullptr };
        ID3D11RenderTargetView* mRenderTargetView   { nullptr };
        ID3D11Texture2D*        mBackBuffer         { nullptr };
        ID3D11Texture2D*        mDepthStencilBuffer { nullptr };
        ID3D11DepthStencilView* mDepthStencilView   { nullptr };
        D3D11_VIEWPORT          mScreenViewport{};

        ID3D11RasterizerState* mpRasterizerState{ nullptr };

        HWND mWindowHandle{ nullptr };

        //~ Settings
        UINT m4xMsaaQuality{};
        bool mbEnable4xMsaa{ true };
        std::vector<float> mBackgroundColor{ 0.0f, 0.0f, 0.0f, 1.0f };
    };
}
