#pragma once

#include "mathdef.h"

#include <complex>
#include <iostream>
#include <valarray>


namespace ngm {

	typedef std::complex<double> Complex;
	typedef std::valarray<Complex> ComplexArray;

	class FFT
	{
	private:
		ComplexArray Array;
	public:

		void transform();
		static void transform(ComplexArray& arr);

		void inverseTransform();
		static void inverseTransform(ComplexArray& arr);

		friend std::ostream& operator<<(std::ostream& stream, const FFT& fourier);

		static std::string outputCArrayReal(ComplexArray& arr, double stepSize);

		static std::string outputCArrayAbs(ComplexArray& arr, double stepSize);

		int getSizeFFT();

		FFT(ComplexArray arr);
	};

}

