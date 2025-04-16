// baruh.ifraimov@gmail.com
#include <iostream>
#include <stdexcept>
#include "../inc/MatrixUtils.hpp"

namespace mtrx{

	void swap(double& a, double& b) {
		double temp = a;
		a = b;
		b = temp;
	}

}