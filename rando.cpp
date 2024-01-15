#include "rando.h"

#include <cmath>

#define MY_ONEUPONSQRT2PI 0.39894228040143267793994605993438186847585863116493465766592582967065792589930184
#define MY_SQRTPI  1.772453850905516027298167483341145182797549456122387128213808
#define MY_SQRT2   1.41421356237309504880168872420969807856967187537694807317668
#define MY_PI 3.141592653589793238462643383279502884197169399375105820974945

double NormPdf(double x)
{
#define UPPERLIMIT 25.0 
	if (x < -UPPERLIMIT) return 0.0;
	if (x > UPPERLIMIT) return 0;
	return MY_ONEUPONSQRT2PI
		* exp(-0.5 * x * x);
#undef UPPERLIMIT
}


double NormCdf(double x)
{
#define MY_SQRT2   1.41421356237309504880168872420969807856967187537694807317668
#define MY_SQRTPI  1.772453850905516027298167483341145182797549456122387128213808
#define UPPERLIMIT 20.0 
	/* I won't return either of univariate normal density or
	   probability when x < -UPPERLIMIT  or x > UPPERLIMIT. */

#define P10 242.66795523053175
#define P11 21.979261618294152
#define P12 6.9963834886191355
#define P13 -.035609843701815385
#define Q10 215.05887586986120
#define Q11 91.164905404514901
#define Q12 15.082797630407787
#define Q13 1.0

#define P20 300.4592610201616005
#define P21 451.9189537118729422
#define P22 339.3208167343436870
#define P23 152.9892850469404039
#define P24 43.16222722205673530
#define P25 7.211758250883093659
#define P26 .5641955174789739711
#define P27 -.0000001368648573827167067
#define Q20 300.4592609569832933
#define Q21 790.9509253278980272
#define Q22 931.3540948506096211
#define Q23 638.9802644656311665
#define Q24 277.5854447439876434
#define Q25 77.00015293522947295
#define Q26 12.78272731962942351
#define Q27 1.0

#define P30 -.00299610707703542174
#define P31 -.0494730910623250734
#define P32 -.226956593539686930
#define P33 -.278661308609647788
#define P34 -.0223192459734184686
#define Q30 .0106209230528467918
#define Q31 .191308926107829841
#define Q32 1.05167510706793207
#define Q33 1.98733201817135256
#define Q34 1.0


	int sn;
	double R1, R2, y, y2, y3, y4, y5, y6, y7;
	double myerf, myerfc, z, z2, z3, z4;
	double phi;

	if (x < -UPPERLIMIT) return 0.0;
	if (x > UPPERLIMIT) return 1.0;

	y = x / MY_SQRT2;
	if (y < 0) {
		y = -y;
		sn = -1;
	}
	else
		sn = 1;

	y2 = y * y;
	y4 = y2 * y2;
	y6 = y4 * y2;

	if (y < 0.46875) {
		R1 = P10 + P11 * y2 + P12 * y4 + P13 * y6;
		R2 = Q10 + Q11 * y2 + Q12 * y4 + Q13 * y6;
		myerf = y * R1 / R2;
		if (sn == 1)
			phi = 0.5 + 0.5 * myerf;
		else
			phi = 0.5 - 0.5 * myerf;
	}
	else
		if (y < 4.0) {
			y3 = y2 * y;
			y5 = y4 * y;
			y7 = y6 * y;
			R1 = P20 + P21 * y + P22 * y2 + P23 * y3 +
				P24 * y4 + P25 * y5 + P26 * y6 + P27 * y7;
			R2 = Q20 + Q21 * y + Q22 * y2 + Q23 * y3 +
				Q24 * y4 + Q25 * y5 + Q26 * y6 + Q27 * y7;
			myerfc = exp(-y2) * R1 / R2;
			if (sn == 1)
				phi = 1.0 - 0.5 * myerfc;
			else
				phi = 0.5 * myerfc;
		}
		else {
			z = y4;
			z2 = z * z;
			z3 = z2 * z;
			z4 = z2 * z2;
			R1 = P30 + P31 * z + P32 * z2 + P33 * z3 + P34 * z4;
			R2 = Q30 + Q31 * z + Q32 * z2 + Q33 * z3 + Q34 * z4;
			myerfc = (exp(-y2) / y) * (1.0 / MY_SQRTPI + R1 / (R2 * y2));
			if (sn == 1)
				phi = 1.0 - 0.5 * myerfc;
			else
				phi = 0.5 * myerfc;
		}

	return phi;
#define UPPERLIMIT 20.0 
	/* I won't return either of univariate normal density or
	   probability when x < -UPPERLIMIT  or x > UPPERLIMIT. */

#undef P10
#undef P11
#undef P12
#undef P13
#undef Q10
#undef Q11
#undef Q12
#undef Q13

#undef P20
#undef P21
#undef P22
#undef P23
#undef P24
#undef P25
#undef P26
#undef P27
#undef Q20
#undef Q21
#undef Q22
#undef Q23
#undef Q24
#undef Q25
#undef Q26
#undef Q27

#undef P30
#undef P31
#undef P32
#undef P33
#undef P34
#undef Q30
#undef Q31
#undef Q32
#undef Q33
#undef Q34
}
