#pragma once

#include <vector>

#include "../Engine/Public/GraphicsRenderer.h"


namespace FoxAssets
{
	class FxAssetsBase
	{
	protected:

		std::vector<WORD> mIndices;

		ID3D11VertexShader* mpVertexShader { nullptr };
		ID3D11PixelShader*  mpPixelShader  { nullptr };
		
		ID3D11InputLayout*  mpVertexLayout { nullptr };
		
		ID3D11Buffer* mpVertexBuffer  { nullptr };
		ID3D11Buffer* mpIndicesBuffer { nullptr };
		ID3D11Buffer* mpConstantBuffer{ nullptr };

	private:
		//~ Graphics Renderer will be responsible for building.
		friend FoxEngine::FxGraphicsRenderer;
	};
}
