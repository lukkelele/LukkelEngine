#pragma once
#include "LukkelEngine/Core/Base.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"

/*
	LukkelEngine: Vector

	As Bullet uses their own btVector's and most of LukkelEngine uses glm::vec,
	this Vector class aims to create one single class to be used for both endpoints
*/

namespace LukkelEngine {


    template <typename V>
    class Vec3
    {
    public:
        Vec3() {}
        Vec3(V const& vec) 
            :m_Vec(vec) {}

        V m_Vec;

        template <typename T>
        Vec3(Vec3<T> const& vec) {
            m_Vec.x = vec.getX();
            m_Vec.y = vec.getY();
            m_Vec.z = vec.getZ();
        }

        template <typename T>
        Vec3& operator=(Vec3<T> const& vec) {
            m_Vec.x = vec.getX();
            m_Vec.y = vec.getY();
            m_Vec.z = vec.getZ();
            return *this;
        }

		template<typename T, typename Z>
		static Z& convertVec3(T vector);

        Vec3 operator+(Vec3 const& vec) const { return Vec3(m_Vec + vec.m_Vec); }
        Vec3 operator-(Vec3 const& vec) const { return Vec3(m_Vec - vec.m_Vec); }
        Vec3 operator*(float const scalar) const { return Vec3(m_Vec * scalar); }

        float getX() const { return m_Vec.x; }
        float getY() const { return m_Vec.y; }
        float getZ() const { return m_Vec.z; }
        V getVec3() const { return m_Vec; }


    // typedef Vec3<btVector3> BulletVec3;
    // typedef Vec3<glm::vec3> GLMVec3;
    };

}