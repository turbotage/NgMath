#pragma once

#include "mathdef.h"
#include "Vec3f.h"
#include "Vec4f.h"

namespace ngm {
	class Plane : public Vec4f
	{
	private:

	public:

		float normOfBasis;
		ALIGN(16) float a, b, c, d;

		Plane();
		Plane(Vec3f planeNormal, Vec3f point);

		void setPlane(Vec3f planeNormal, Vec3f point);

		float distanceToPoint(Vec3f point);

	};

}

