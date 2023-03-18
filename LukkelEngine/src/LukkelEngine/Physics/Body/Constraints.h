#pragma once
#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	enum ConstraintType
	{
		Null      = -1,
		Generic   =  0,
		Pivot     =  1,
		Slider    =  2,
		Spherical =  3,
		Hinge     =  4,
		ConeTwist =  5
	};

	class Constraint
	{
	public:
		virtual ~Constraint() = default;

		virtual const char* getName() { return "Constraint"; };

		btTypedConstraint* getConstraint() const { return m_Constraint; }
		ConstraintType getConstraintType() const { return m_ConstraintType; }
		Rigidbody& getRigidbody() { return m_Rigidbody; }
		UUID getID() const { return m_Rigidbody.getID(); }

	protected:
		Rigidbody m_Rigidbody;
		btTypedConstraint* m_Constraint = nullptr;
		ConstraintType m_ConstraintType = Null;
	};

	
	class PivotConstraint : public Constraint
	{
	public:
		PivotConstraint(Rigidbody& rigidbody, glm::vec3 pivot)
			: m_Pivot(pivot)
		{
			btVector3 p(pivot.x, pivot.y, pivot.z);
			m_Rigidbody = rigidbody;
			m_Constraint = new btPoint2PointConstraint(*m_Rigidbody.getRigidbody(), p);
			m_ConstraintType = ConstraintType::Pivot;
		}
		~PivotConstraint() { delete m_Constraint; }

		const char* getName() override { return "Pivot"; }

	private:
		glm::vec3 m_Pivot{0.0f, 0.0f, 0.0f};
	};

	class Dof6Constraint : public Constraint
	{
		Dof6Constraint(Rigidbody& rigidbody)
		{
		}

		const char* getName() override { return "Dof6"; }
	};

}