#pragma once
#pragma once
#include "RendererComponent.h"

namespace nu
{
	class CameraComponent : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(CameraComponent)

			void Draw(const Renderer& renderer) override;

	private:
	};
}