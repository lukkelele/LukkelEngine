#pragma once


namespace LukkelEngine::Math {

	bool decomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::quat& rotation, glm::vec3& scale);

}