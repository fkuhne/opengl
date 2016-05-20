// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
#include <string>
#include <sstream>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE

	mat3 IdMatrix(1.0); // Identity matrix 3x3
	float radAngle = degrees * (pi / 180.0);
	// Remember that this is a column-major representation
	mat3 dualMatrix(0, axis.z, -axis.y,
		-axis.z, 0, axis.x,
		axis.y, -axis.x, 0);
	mat3 aat(axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
		axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
		axis.x * axis.z, axis.y * axis.z, axis.z * axis.z);

	// Rodrigues formula for generic rotation matrices
	glm::mat3 m = cos(radAngle) * IdMatrix +
		(1.0 - cos(radAngle)) * aat +
		sin(radAngle) * dualMatrix;

  // You will change this return call
  return m;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE

	vec3 upNormalized = glm::normalize(up);
	eye = rotate(degrees, upNormalized) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	
	vec3 upNormalized = glm::normalize(up); 
	vec3 eyeNormalized = glm::normalize(eye);
	vec3 rightVector = glm::cross(upNormalized, eyeNormalized);

	eye = rotate(-degrees, rightVector) * eye;
	
	eyeNormalized = glm::normalize(eye);
	up = glm::cross(eyeNormalized, rightVector);
}
	
// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

	mat4 Translation(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,	
		-eye.x, -eye.y, -eye.z, 1);

	vec3 w = glm::normalize(eye); // center is (0,0,0)
	vec3 bw = glm::cross(up, w);
	vec3 u = glm::normalize(bw);
	vec3 v = glm::cross(w, u);

	mat4 Rotation(u.x, v.x, w.x, 0,
		u.y, v.y, w.y, 0,
		u.z, v.z, w.z, 0,
		0, 0, 0, 1);

	mat4 myLookAt = Rotation * Translation;

  // You will change this return call
  return myLookAt;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
