#include <filesystem>
#include <stdexcept>

#include "PrimitiveShape.h"


namespace FoxAssets
{

	FxPrimitiveShape::~FxPrimitiveShape()
	{
		bool status = true;

		SAFE_RELEASE(mpVertexBuffer, status);
		SAFE_RELEASE(mpIndexBuffer, status);
	}

	void FxPrimitiveShape::SetBuildEffect(const std::string& effectPath)
	{

	}

	void FxPrimitiveShape::SetBuildLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
	{

	}

	void FxPrimitiveShape::SetBuildVertices(const std::vector<std::any>& vertices)
	{

	}

	void FxPrimitiveShape::SetCustomBuildIncies(const std::vector<int>& indices)
	{

	}

	std::vector<DirectX::XMFLOAT3> FxPrimitiveShape::GetUnitCubeCoordinates() const
	{
		return std::vector<DirectX::XMFLOAT3>();
	}

	void FxPrimitiveShape::SetEffectPath(const std::string& effectPath)
	{
		std::filesystem::path p(effectPath);

		if (std::filesystem::exists(p))
		{
			mEffectPath = effectPath;
		}
		else
		{
			throw std::runtime_error("Path " + effectPath + " Does Not EXIT!");
		}
	}
}
