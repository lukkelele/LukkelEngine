#ifndef _MATRIX_H
#define _MATRIX_H
#include <vector>
#include <string>


class Matrix {
public:
	Matrix();
	Matrix(int a);

public:
	struct vec2 { float u = 0; float v = 0; float w = 1; };
	struct vec3 { float x = 0; float y = 0; float z = 0; float w = 1; };
	struct triangle
	{
		vec3 p[4];
		vec2 t[3];  // texture 
	};
	struct mesh { std::vector<triangle> tris; };
	struct mat3 { float m[3][3] = { 0 }; };
	struct mat4 { float m[4][4] = { 0 }; };

private:
	mat3 m3;
	mat4 m4;
	mesh cube;

public:
	/* MATRIX UTILITY FUNCTIONS */
	vec3 matrix_multiplyVector(mat4& m, vec3& i);
	mat4 matrix_makeIdentity();
	mat4 matrix_makeRotationX(float fAngleRad);
	mat4 matrix_makeRotationY(float fAngleRad);
	mat4 matrix_makeRotationZ(float fAngleRad);
	mat4 matrix_makeTranslation(float x, float y, float z);
	mat4 matrix_makeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar);
	mat4 matrix_multiply(mat4& m1, mat4& m2);
	mat4 matrix_pointAt(vec3& pos, vec3& target, vec3& up);
	mat4 matrix_quickInverse(mat4& m); // Only for Rotation/Translation Matrices

	/* VECTOR UTILITY FUNCTIONS */
	vec3 vector_add(vec3& v1, vec3& v2);
	vec3 vector_sub(vec3& v1, vec3& v2);
	vec3 vector_mul(vec3& v1, float k);
	vec3 vector_div(vec3& v1, float k);
	float vector_dotProduct(vec3& v1, vec3& v2);
	float vector_length(vec3& v);
	vec3 vector_normalise(vec3& v);
	vec3 vector_crossProduct(vec3& v1, vec3& v2);
	vec3 vector_intersectPlane(vec3& plane_p, vec3& plane_n, vec3& lineStart, vec3& lineEnd, float& t);

	bool createCube();
	mat3 matrix3();
	mat3 identity_matrix3();

	mat4 matrix4();
	mat4 identity_matrix4();

};

#endif /* _MATRIX_H */
