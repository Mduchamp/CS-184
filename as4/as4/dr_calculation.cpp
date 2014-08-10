/*#include <stdlib.h>
#include "Eigen/Eigen/Core"
using namespace Eigen;

typedef Matrix<double, Dynamic, Dynamic> MatrixXd;

MatrixXf calculate_dr(MatrixXf jacobian, Vector3f goal, Vector3f end)
{
	MatrixXf J_inverse(3, 3);
	//calculate the inverse of jacobian - according to https://piazza.com/class/hphrpbmh5yc5wy?cid=321
	J_inverse = jacobian.transpose() * (jacobian * jacobian.transpose()).inverse();
	float diff = (goal - end).norm();
	float alpha = 0.8 * diff; //norm actually means magnitude...
	return J_inverse * diff * alpha;
}

void attempt()
{
	//just initializing variables
	float distance = 0;
	MatrixXf J(3,3);
	MatrixXf dr(3,4); 
	MatrixXf goal(3,1);

	Vector3f goal(0, 0, 0); //will get value for this
	Vector3f end(1, 1, 1);

	while (distance > 0.1)
	{
		J = MatrixXf::Random(3,3); //get the jacobian
		// matrix dr (3 by N) = J ^ -1 * ALPHA (goal - END vector of arm OR PE)
		dr = calculate_dr(J, goal, end);
		// update rotation(dr)
		// updateposition(dr)
	}
}

int main(int argc, char *argv[]) {
  return 0;
}*/