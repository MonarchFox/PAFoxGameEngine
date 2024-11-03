#pragma once
#include "../PrimitiveShape.h"


namespace FoxAssets
{

    struct CubeVertexBuffer
    {
        DirectX::XMFLOAT3 Pos;
        DirectX::XMFLOAT4 Color;
    };

    struct CubeConstantBuffer
    {
        DirectX::XMMATRIX mWorld;
        DirectX::XMMATRIX mView;
        DirectX::XMMATRIX mProjection;
    };

    class FACubePrimitiveShape final: public FAPrimitiveShape
    {
    protected:
        
        // Inherited via FAPrimitiveShape
        std::wstring CreateEffectPath() override;

        D3D11_SUBRESOURCE_DATA CreateGeometryIndices()   override;
        D3D11_SUBRESOURCE_DATA CreateVertexCoordinates() override;

        D3D11_BUFFER_DESC CreateVertexBufferDesc()   override;
        D3D11_BUFFER_DESC CreateIndexBufferDesc()    override;
        D3D11_BUFFER_DESC CreateConstantBufferDesc() override;

        std::vector<D3D11_INPUT_ELEMENT_DESC> CreateVertexLayout() override;

    private:
        UINT nVertexPoints{};
        UINT nIndicesPoints{};
    };
}
