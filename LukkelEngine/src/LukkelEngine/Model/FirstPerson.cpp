#include "LKpch.h"
#include "LukkelEngine/Model/FirstPerson.h"


namespace LukkelEngine {

	namespace Model {

		FirstPerson::FirstPerson()
		{
		}

		FirstPerson::FirstPerson(FirstPersonProperties& props, Scene& scene)
			: m_Props(props)
		{
			Entity entity = scene.CreateEntity(props.name);
		}

	}
}