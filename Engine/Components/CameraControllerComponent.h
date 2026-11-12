#pragma once
#include "Component.h"

namespace nu
{
	class CameraControllerComponent : public Component
	{
	public:
		CLASS_PROTOTYPE(CameraControllerComponent)

		void Update(float dt) override;

		void Read(const json::value_t& value) override;

	private:
		float m_speed{ 1 };
		float m_sensitivity{ 1 };
		float m_yaw{ 0 };
		float m_pitch{ 0 };
	};
}