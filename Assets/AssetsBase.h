#pragma once

#include "../Engine/Public/GraphicsRenderer.h"


namespace FoxAssets
{
	class FxAssetsBase
	{
	public:
		virtual void BuildAssest(FoxEngine::FxGraphicsRenderer* renderer) = 0;
	};
}
