#pragma once

#include "../Engine/Public/GraphicsRenderer.h"


namespace FoxAssets
{
	class FAAssetsBase
	{
	public:
		//** Builds Assets */
		virtual void BuildAssets(FoxEngine::FxGraphicsRenderer* renderer) = 0;

		//** Setups Before Rendering */
		virtual void PresetAssets(FoxEngine::FxGraphicsRenderer* renderer) = 0;

		//** Asset Should Render itself using Renderer api */
		virtual void Render(FoxEngine::FxGraphicsRenderer* renderer) = 0;
	};
}
