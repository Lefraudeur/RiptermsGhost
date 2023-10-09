#include "Modules.h"
#include "../../java/lang/ClassLoader/ClassLoader.h"

void Ripterms::Modules::Test::renderGUI()
{
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	if (ImGui::Button("Run Test"))
	{
		Ripterms::JavaClassV2::JClass lol(Ripterms::JavaClassV2::findClass("io/github/lefraudeur/ClassPatcher"));
		if (lol.isValid())
		{
			std::cout << "found" << std::endl;
		}
		else 
		{
			std::cout << "not found" << std::endl;
		}
		Ripterms::Maths::Vector3d position = cache->thePlayer.getPosition();
		Ripterms::Maths::Vector2d rotation = cache->thePlayer.getRotation();

		const float PI = 3.1415926535;
		float yaw = rotation.x * (PI / 180.0f);
		float pitch = rotation.y * (PI / 180.0f);
		const float move_forward = 3.0f;
		Ripterms::Maths::Vector3d motion{};

		float hypxz = std::cos(pitch) * move_forward;
		motion.z = std::cos(yaw) * hypxz;
		motion.x = -std::sin(yaw) * hypxz;
		motion.y = -std::sin(pitch) * move_forward;
		cache->thePlayer.setMotion(motion);
	}
}