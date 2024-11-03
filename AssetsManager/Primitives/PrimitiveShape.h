#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

#include <string>
#include <vector>
#include <any>

#include "../AssetsBase.h"
#include "../../Utils/Helper.h"


namespace FoxAssets
{
	/*
	*	Used by Renderer for Generative PrimitiveShapes
	*	Steps: Set Basic Properties
	*	Build: Extract Coordinates, generate indices base on it.
	*/
	class FAPrimitiveShape : public FAAssetsBase
	{
	public:
		FAPrimitiveShape() = default;
		~FAPrimitiveShape();

		//~ Used by Renderer To Build This Assest
		virtual void BuildAssets(FoxEngine::FxGraphicsRenderer* renderer) override;

		/* @brief Defult Set To TriangleList */
		void SetBuildTopology(D3D_PRIMITIVE_TOPOLOGY topology) { mPrimitiveTopology = topology; }

	protected:

		// ------------------------------------------------------------------------
		//	Framework Methods
		// ------------------------------------------------------------------------

		virtual std::wstring			CreateEffectPath()		   = 0;
		virtual D3D11_SUBRESOURCE_DATA	CreateGeometryIndices()	   = 0;
		virtual D3D11_SUBRESOURCE_DATA  CreateVertexCoordinates()  = 0;
		virtual D3D11_BUFFER_DESC		CreateVertexBufferDesc()   = 0;
		virtual D3D11_BUFFER_DESC		CreateIndexBufferDesc()	   = 0;
		virtual D3D11_BUFFER_DESC		CreateConstantBufferDesc() = 0;
		virtual D3D11_RASTERIZER_DESC   CreateRasterizerDesc()	   = 0;

		virtual std::vector<D3D11_INPUT_ELEMENT_DESC> CreateVertexLayout() = 0;

	protected:

		ID3D11Buffer* mpVertexBuffer	{ nullptr };
		ID3D11Buffer* mpIndexBuffer		{ nullptr };
		ID3D11Buffer* mpConstantBuffer	{ nullptr };

		ID3DBlob* mpVertexBlob			{ nullptr };
		ID3DBlob* mpPixelBlob			{ nullptr };

		ID3D11VertexShader*	   mpVertexShader	{ nullptr };
		ID3D11PixelShader*	   mpPixelShader	{ nullptr };
		ID3D11InputLayout*	   mpInputLayout	{ nullptr };

		D3D_PRIMITIVE_TOPOLOGY mPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		D3D11_SUBRESOURCE_DATA mVertexCoordinates{};
		D3D11_SUBRESOURCE_DATA mGeometricIndices{};

		std::wstring mEffectPath;
		std::vector<D3D11_INPUT_ELEMENT_DESC> mVertexLayout{};
	};
}
