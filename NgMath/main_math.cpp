


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

	qt1.setRotation(ngm::Vec3f(0, 1, 0), TO_RADIANS(180));

	ngm::Vec3f p1(1, 0, 0);
	ngm::Vec3f p2(1, 0, 0);
	ngm::Vec3f p3(1, 0, 0);
	ngm::Vec3f p4(1, 0, 0);
	
	std::cout << p1 << std::endl;
	
	qt1.rotate4(p1, p2, p3, p4);

	std::cout << p1 << std::endl;

	std::cout << p2 << std::endl;

	std::cout << p3 << std::endl;

	std::cout << p4 << std::endl;

	getchar();

	return 0;
}


//uncomment to just run math example test_main, comment to remove main and use as library
/*
int main() {
	test_main();
	return 0;
}
*/
