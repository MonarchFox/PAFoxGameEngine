#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

#include <string>
#include <vector>
#include <any>

#include "AssetsBase.h"
#include "../Utils/Helper.h"


namespace FoxAssets
{
	/*
	*	Used by Renderer for Generative PrimitiveShapes
	*/
	class FxPrimitiveShape : public FxAssetsBase
	{
		ID3D11Buffer* mpVertexBuffer{ nullptr };
		ID3D11Buffer* mpIndexBuffer { nullptr };

		D3D_PRIMITIVE_TOPOLOGY mPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		std::string   mEffectPath;

	public:
		FxPrimitiveShape() = default;
		~FxPrimitiveShape();

		//~ Build Set Functionalities

		/* @brief Defult Set To TriangleList */
		void SetBuildTopology(D3D_PRIMITIVE_TOPOLOGY topology) { mPrimitiveTopology = topology; }

		void SetBuildEffect(const std::string& effectPath);
		void SetBuildLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout);

		/**
		 * @brief Maps input layout to extract coordinates from a list of vertices.
		 *
		 * This method takes a list of vertices that must adhere to the specified input layout format.
		 * By default, it assumes that the 'POSITION' attribute is present in the layout, as this is a
		 * prerequisite for a `PrimitiveShape`. The function then maps the position indices with the
		 * vertices list to extract coordinates, which will be used later for generating geometry.
		 *
		 * @param vertices List of vertices containing coordinate features.
		 * @throws std::runtime_error If positions are not mapped correctly.
		 *
		 * @note To ensure all coordinates are present, use `GetUnitCubeCoordinates`, which guarantees that
		 * all sides are included.
		 */
		void SetBuildVertices(const std::vector<std::any>& vertices);

		/* @brief Not Requried, It will be build via geometric algorithm */
		void SetCustomBuildIncies(const std::vector<int>& indices);

		//~ Helper Functions
		std::vector<DirectX::XMFLOAT3> GetUnitCubeCoordinates() const;
	
	protected:
		virtual std::vector<int> CreateGeometry() = 0;

	private:
		void SetEffectPath(const std::string& effectPath);
	};
}
