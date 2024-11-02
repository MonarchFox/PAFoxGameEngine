#pragma once

#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "../../Engine/Public/FoxEngine.h"

constexpr float PI = 3.1415926535f;

struct Vertex
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Color;
};

class TestApp_2 final: public FoxEngine::FxEngine
{
    // TODO: Create AssetManager for all these crap!
    ID3D11Buffer* mpBoxVertexBuffer{ nullptr };
    ID3D11VertexShader* mpBoxVertexShader{ nullptr };

    ID3D11Buffer* mpBoxIndexBuffer{ nullptr };
    ID3D11PixelShader* mpBoxPixelShader{ nullptr };

    ID3D11Buffer* mpBoxConstantBuffer{ nullptr };
    ID3D11InputLayout* mpInputLayout{ nullptr };

    ID3DBlob* mpVertexShaderBlob{ nullptr };
    ID3DBlob* mpPixelShaderBlob{ nullptr };

    //~ Application Specific
    DirectX::XMFLOAT4X4 mWorld;
    DirectX::XMFLOAT4X4 mView;
    DirectX::XMFLOAT4X4 mProj;

    float mTheta;
    float mPhi;
    float mRadius;

    POINT mLastMousePosition;

public:
    TestApp_2();
    ~TestApp_2();

    bool Init() override;

    void OnResizeEnd() override;
    void UpdateScene(float deltaTime) override;
    void DrawScene() override;

    void OnMouseDown(WPARAM btnState, int x, int y) override;
    void OnMouseUp(WPARAM btnState, int x, int y) override;
    void OnMouseMove(WPARAM btnState, int x, int y) override;

private:
    void BuildGeometryBuffers();
    void BuildFX();
    void BuildVertexLayout();
};

