#include <stdio.h>
#include "../inc/myMath.hpp"

namespace mtrx{
	double mpow(double n1, double n2){
		double result =0;
		for (int i = 0; i < n2; i++)
		{
			result *= n1;
		}
		return result;
	}
}