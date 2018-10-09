


#include "src\quaternion.h"

ngm::Vec3f rotateNoSSE(const ngm::Quaternion& quat, const ngm::Vec3f& vec) {
	float tmpX, tmpY, tmpZ, tmpW;
	tmpX = (((quat.getW() * vec.x) + (quat.getY() * vec.z)) - (quat.getZ() * vec.y));
	tmpY = (((quat.getW() * vec.y) + (quat.getZ() * vec.x)) - (quat.getX() * vec.z));
	tmpZ = (((quat.getW() * vec.z) + (quat.getX() * vec.y)) - (quat.getY() * vec.x));
	tmpW = (((quat.getX() * vec.x) + (quat.getY() * vec.y)) + (quat.getZ() * vec.z));
	return ngm::Vec3f(
		((((tmpW * quat.getX()) + (tmpX * quat.getW())) - (tmpY * quat.getZ())) + (tmpZ * quat.getY())),
		((((tmpW * quat.getY()) + (tmpY * quat.getW())) - (tmpZ * quat.getX())) + (tmpX * quat.getZ())),
		((((tmpW * quat.getZ()) + (tmpZ * quat.getW())) - (tmpX * quat.getY())) + (tmpY * quat.getX()))
	);
}


/**  write your test code here and call it from your main, currently it is a test for quaternion rotations  **/
int test_main() {

	ngm::Quaternion qt1;

	qt1.setRotation(ngm::Vec3f(1.0f, 1.0f, 1.0f).normalize(), TO_RADIANS(90.0f));
	qt1.normalize();

	ngm::Mat4f rotationMatrix = ngm::Mat4f::rotation(ngm::Vec3f(1.0f, 1.0f, 1.0f).normalize(), TO_RADIANS(90.0f));

	ngm::Vec3f p1(1.0f, 3.0f, 2.0f);
	ngm::Vec3f p2(0, 1, 0);
	ngm::Vec3f p3(0, 0, 1);
	ngm::Vec3f p4(0, 0, 1);
	
	std::cout << p1 << std::endl;

	std::cout << rotationMatrix * p1 << std::endl;
	
	
	qt1.rotate4(p1, p2, p3, p4);

	std::cout << p1 << std::endl;

	std::cout << p2 << std::endl;

	std::cout << p3 << std::endl;

	std::cout << p4 << std::endl;

	getchar();

	return 0;
}

#define DEFINE_ENTRY_POINT 1

#if DEFINE_ENTRY_POINT
int main() {
	test_main();
	return 0;
}
#endif // DEFINE_ENTRY_POINT
