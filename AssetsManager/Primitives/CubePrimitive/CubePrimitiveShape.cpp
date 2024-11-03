#include "CubePrimitiveShape.h"

using namespace DirectX;

namespace FoxAssets
{

	void FACubePrimitiveShape::BuildAssets(FoxEngine::FxGraphicsRenderer* renderer)
	{
		FAPrimitiveShape::BuildAssets(renderer);
	}

	void FACubePrimitiveShape::PresetAssets(FoxEngine::FxGraphicsRenderer* renderer)
	{
		renderer->PresetInputLayout(mpInputLayout);

		UINT stride = sizeof(CubeVertexBuffer);
		UINT offset = 0;
		renderer->PresetVertexBuffer(mpVertexBuffer, 0, 1, &stride, &offset);

		renderer->PresetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		renderer->PresetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void FACubePrimitiveShape::Render(FoxEngine::FxGraphicsRenderer* renderer)
	{

	}

	std::wstring FACubePrimitiveShape::CreateEffectPath()
	{
		// TODO: Create a dynamic way for this!
		return L"../../../Effects/Primitives/Cube/Cube.fx";
	}

	D3D11_SUBRESOURCE_DATA FACubePrimitiveShape::CreateGeometryIndices()
	{
		WORD indices[] = {
			// front face
			0, 1, 2,
			0, 2, 3,
			// back face
			4, 6, 5,
			4, 7, 6,
			// left face
			4, 5, 1,
			4, 1, 0,
			// right face
			3, 2, 6,
			3, 6, 7,
			// top face
			1, 5, 6,
			1, 6, 2,
			// bottom face
			4, 0, 3,
			4, 3, 7
		};

		D3D11_SUBRESOURCE_DATA rd{};
		rd.pSysMem = indices;

		return rd;
	}

	D3D11_SUBRESOURCE_DATA FACubePrimitiveShape::CreateVertexCoordinates()
	{
		CubeVertexBuffer vertices[] =
		{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) }
		};

		nVertexPoints = ARRAYSIZE(vertices);

		D3D11_SUBRESOURCE_DATA rd{};
		rd.pSysMem = vertices;

		return rd;
	}

	D3D11_BUFFER_DESC FACubePrimitiveShape::CreateVertexBufferDesc()
	{
		D3D11_BUFFER_DESC bd{};
		bd.ByteWidth = sizeof(CubeVertexBuffer) * nVertexPoints;
		bd.Usage	 = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags	  = 0;
		bd.StructureByteStride = sizeof(CubeVertexBuffer);

		return bd;
	}

	D3D11_BUFFER_DESC FACubePrimitiveShape::CreateIndexBufferDesc()
	{
		D3D11_BUFFER_DESC bd{};
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.ByteWidth = sizeof(WORD) * nIndicesPoints;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = 0;

		return bd;
	}

	D3D11_BUFFER_DESC FACubePrimitiveShape::CreateConstantBufferDesc()
	{
		D3D11_BUFFER_DESC bd{};
		bd.ByteWidth = sizeof(CubeConstantBuffer);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		return bd;
	}

	D3D11_RASTERIZER_DESC FACubePrimitiveShape::CreateRasterizerDesc()
	{
		D3D11_RASTERIZER_DESC rd{};
		rd.CullMode = D3D11_CULL_NONE;
		rd.FillMode = D3D11_FILL_SOLID;
		rd.ScissorEnable = false;
		rd.DepthBias = 0.f;
		rd.DepthBiasClamp = 0.0f;
		rd.DepthClipEnable = true;
		rd.MultisampleEnable = false;
		rd.SlopeScaledDepthBias = 0.0f;

		return rd;
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> FACubePrimitiveShape::CreateVertexLayout()
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> vEd
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		return vEd;
	}
	
}
