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

		ConstraintType getConstraintType() const { return m_ConstraintType; }

	protected:
		UUID m_ID;
		btTypedConstraint* m_Constraint = nullptr;
		ConstraintType m_ConstraintType = Null;
	};

	
	class PivotConstraint : public Constraint
	{
	public:
		PivotConstraint(RigidBody& rigidbody, glm::vec3 pivot)
			: m_Pivot(pivot)
		{
			btVector3 p(pivot.x, pivot.y, pivot.z);
			btRigidBody* rb = rigidbody.getRigidBody();
			m_Constraint = new btPoint2PointConstraint(*rb, p);
			m_ID = (UUID)rigidbody.getID();
		}

	private:
		glm::vec3 m_Pivot{0.0f, 0.0f, 0.0f};
	};

}