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
	public:
		Dof6Constraint(Rigidbody& rigidbody, glm::vec3 pivot, float cfm = 0.50f, float erp = 0.50f,
			bool angularMotion = true, bool referenceB = false)
		{
			// btVector3 localPosition = rigidbody.getRigidbody()->getCenterOfMassTransform().inverse() * hitpoint;
			m_Rigidbody = rigidbody;
			btVector3 btPivot(pivot.x, pivot.y, pivot.z);
			btTransform p;
			p.setIdentity();
			p.setOrigin(btPivot);
			btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*m_Rigidbody.getRigidbody(), p, referenceB);

			if (angularMotion)
			{
				dof6->setAngularLowerLimit(btVector3(0, 0, 0));
				dof6->setAngularUpperLimit(btVector3(0, 0, 0));
			}
			// Strength per axis
			dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 0);
			dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 1);
			dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 2);
			dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 3);
			dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 4);
			dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 5);
			// Error reduction per axis
			dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 0);
			dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 1);
			dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 2);
			dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 3);
			dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 4);
			dof6->setParam(BT_CONSTRAINT_STOP_ERP, erp, 5);

			m_Constraint = dof6;
		}

		const char* getName() override { return "Dof6"; }
	};

}