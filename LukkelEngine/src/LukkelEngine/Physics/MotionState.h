#pragma once

#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	class MotionState: public btDefaultMotionState {
	public:
		MotionState(const btTransform &transform) : btDefaultMotionState(transform) {}

		void getWorldTransformOpenGL(btScalar* transform) {
			btTransform trans;
			getWorldTransform(trans);
			trans.getOpenGLMatrix(transform);
		}
	};

}
