#pragma once

#include "../../AssetsManager/AssetsBase.h"

#include <vector>
#include <stack>


namespace FoxEngine
{
    class FxAssetsManager
    {

    public:
        FxAssetsManager();
        ~FxAssetsManager() = default;

        void AddUnBuildAssets(const std::unique_ptr<FoxAssets::FAAssetsBase>& ptr) { mNotBuildedAssets.emplace(std::move(ptr)); }
        bool IsUnBuildEmpty() const { return mNotBuildedAssets.empty(); }

        [[nodiscard("Pointer Will Dangle here and there")]]
        void AddFinishedAssets(const std::unique_ptr<FoxAssets::FAAssetsBase>& ptr) { mWorldAssets.emplace_back(std::move(ptr)); }

        std::unique_ptr<FoxAssets::FAAssetsBase> GetAssetsToBuild();

        //~ Assets (dont ask me m new to engine development)
        std::vector<std::unique_ptr<FoxAssets::FAAssetsBase>> mWorldAssets{};
        std::stack<std::unique_ptr<FoxAssets::FAAssetsBase>> mNotBuildedAssets{};
    };
}
