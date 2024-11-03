#include "../Public/AssetsManager.h"

#include <memory>


namespace FoxEngine
{
	FxAssetsManager::FxAssetsManager()
	{
	
	}

	std::unique_ptr<FoxAssets::FAAssetsBase> FxAssetsManager::GetAssetsToBuild()
	{
		if (mNotBuildedAssets.empty()) return nullptr;
		
		std::unique_ptr<FoxAssets::FAAssetsBase> topAsset = std::move(mNotBuildedAssets.top());
		mNotBuildedAssets.pop();
		return topAsset;
	}
}