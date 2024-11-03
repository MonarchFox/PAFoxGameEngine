#include <filesystem>
#include <stdexcept>
#include <iostream>

#include "PrimitiveShape.h"


namespace FoxAssets
{

	FAPrimitiveShape::~FAPrimitiveShape()
	{
		bool status = true;

		SAFE_RELEASE(mpVertexBuffer, status);
		SAFE_RELEASE(mpIndexBuffer, status);
		SAFE_RELEASE(mpConstantBuffer, status);
		SAFE_RELEASE(mpVertexBlob, status);
		SAFE_RELEASE(mpPixelBlob, status);
		SAFE_RELEASE(mpVertexShader, status);
		SAFE_RELEASE(mpPixelShader, status);
		SAFE_RELEASE(mpInputLayout, status);
	}

	void FAPrimitiveShape::BuildAssets(FoxEngine::FxGraphicsRenderer* renderer)
	{
		//~ Setting Up Core Components only Kids Must Build itself from render.
		
		mEffectPath			= CreateEffectPath();
		mGeometricIndices	= CreateGeometryIndices();
		mVertexCoordinates	= CreateVertexCoordinates();
		mVertexLayout		= CreateVertexLayout();

		//~ Building Assets
		renderer->BuildAssetVertexShader(mEffectPath, mpVertexBlob, mpVertexShader);
		renderer->BuildAssetPixelShader(mEffectPath,  mpPixelBlob,  mpPixelShader);
		renderer->BuildAssetInputLayout(mpVertexBlob, mVertexLayout, mpInputLayout);
		renderer->BuildAssetsBuffer(CreateVertexBufferDesc(), &mVertexCoordinates, mpVertexBuffer);
		renderer->BuildAssetsBuffer(CreateIndexBufferDesc(), &mGeometricIndices, mpIndexBuffer);
		renderer->BuildAssetsBuffer(CreateConstantBufferDesc(), nullptr, mpConstantBuffer);
		renderer->BuildRasterizerState(&CreateRasterizerDesc());
	}
}
