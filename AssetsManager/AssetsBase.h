#pragma once

#include "../Engine/Public/GraphicsRenderer.h"


namespace FoxAssets
{
	class FAAssetsBase
	{
	public:
		virtual void BuildAssest(FoxEngine::FxGraphicsRenderer* renderer) = 0;
	};
}
