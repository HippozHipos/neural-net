#pragma once

#include "iostream"
#include <vector>
#include <random>

//Set debug to 0 to disable logging

#define DEBUG 1
#if DEBUG == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

//#######################################
//#            CONSTANTS                #
//#######################################

#define EULERS_NUMBER pow((1.0 + 1.0 / 10000000.0), 10000000.0)
#define PI 3.14159265359

namespace numcpp {

	//#######################################
	//#                TYPES                #
	//#######################################

	//Vector -> contains a std::vector that holds a bunch of double 
	//Its called vf becasue it used to hold floats until i realised 
	//that a double is needed, so it really should be called Vd
	struct Vf
	{
		std::vector<double> v;

		//fill vector with num
		void fill(const unsigned int size, const double num)
		{
			v.clear();
			for (unsigned int i = 0; i < size; i++)
				v.push_back(num);
		}

		friend std::ostream& operator << (std::ostream& out, const Vf& vec)
		{
			out << "[";
			for (unsigned int j = 0; j < vec.v.size(); j++)
			{
				if (j % vec.v.size() == vec.v.size() - 1)
					out << vec.v[j] << "]" << std::endl;
				else
					out << vec.v[j] << ", ";
			}
			return out;
		}
	};

	//Matrix -> contains a std::vector that holds a bunch of numcpp::Vf
	//row by column
	struct Mf 
	{
		std::vector<Vf> m;

		//fill matrix with num
		void fill(unsigned const int rows, unsigned const int cols, const double num)
		{
			m.clear();
			for (unsigned int i = 0; i < rows; i++)
			{
				Vf tempVec;
				for (unsigned int j = 0; j < cols; j++)
				{
					tempVec.v.push_back(num);
				}
				m.push_back(tempVec);
			}
		}

		friend std::ostream& operator << (std::ostream& out, const Mf& mat)
		{
			out << "[" << std::endl << std::endl;
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				out << "[";
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
				{
					if (j % mat.m[i].v.size() == mat.m[i].v.size() - 1)
						out << mat.m[i].v[j] << "]" << std::endl << std::endl;
					else
						out << mat.m[i].v[j] << ", ";
				}
			}
			out << "]" << std::endl;
			return out;
		}
	};

	//#######################################
	//#               RANDOM                #
	//#######################################

	class Random
	{
	private:
		Random();
		~Random();
		Random(const Random&) = delete;
		std::mt19937 _randomEngine;

	public:
		static Random& Get();
		int Range(const int lower, const int upper);
		double Range(const double lower, const double upper);
		void Matrix(const unsigned int rows, const unsigned int cols, const double lower, const double upper, Mf& outmat);
		void Vector(const unsigned int size, const double lower, const double upper, Vf& outvec);
	};

	static Random& rng = Random::Get();

	//#######################################
	//#   UTILITY FUNCTIONS FOR VECTOR      #
	//#######################################

	inline double vectorDot(const Vf& v1, const Vf& v2)
	{
		if (v1.v.size() != v2.v.size())
			throw std::exception();

		double total = 0.0;
		for (unsigned int i = 0; i < v1.v.size(); i++)
		{
			total += v1.v[i] * v2.v[i];
		}
		return total;
	}

	inline double vectoGetMax(const Vf& vec)
	{
		double biggest = vec.v[0];
		for (unsigned int i = 1; i < vec.v.size(); i++)
		{
			biggest = MAX(biggest, vec.v[i]);
		}
		return biggest;
	}

	inline double vectorGetMin(const Vf& vec)
	{
		double smallest = vec.v[0];
		for (unsigned int i = 1; i < vec.v.size(); i++)
		{
			smallest = MIN(smallest, vec.v[i]);
		}
		return smallest;
	}

	inline Vf vectorCapMax(const double value, const Vf& vec)
	{
		Vf tempv;
		for (unsigned int i = 0; i < vec.v.size(); i++)
		{
			tempv.v.push_back(MIN(value, vec.v[i]));
		}
		return tempv;
	}

	inline Vf vectorCapMin(const double value, const Vf& vec)
	{
		Vf tempv;
		for (unsigned int i = 0; i < vec.v.size(); i++)
		{
			tempv.v.push_back(MAX(value, vec.v[i]));
		}
		return tempv;
	}

	inline Vf vectorExp(const Vf& vec)
	{
		Vf tempv;
		for (unsigned int i = 0; i < vec.v.size(); i++)
		{
			tempv.v.push_back(pow(EULERS_NUMBER, vec.v[i]));
		}
		return tempv;
	}

	inline double vectorSum(const Vf& vec)
	{
		double total = 0.0;
		for (unsigned int i = 0; i < vec.v.size(); i++)
			total += vec.v[i];
		return total;
	}

	inline Vf vectorNormalize(const Vf& vec)
	{
		Vf tempv;
		double total = vectorSum(vec);
		for (unsigned int i = 0; i < vec.v.size(); i++)
		{
			tempv.v.push_back(vec.v[i] / total);
		}
		return tempv;
	}

	//#######################################
	//#   UTILITY FUNCTIONS FOR MATRIX      #
	//#######################################


	//Assumes that all the vectors in a matrix will have the same size. The only way 
	//for a vectors to have different sizes is if they are set manually, since all the
	//functions provided in this lib only produce rectangle shaped matrices, i.e all 
	//vectors in the matrix are the same size
	inline void matrixDot(const Mf& m1, const Mf& m2, Mf& outm)
	{
		if (m1.m[0].v.size() && m2.m.size())
			if (m1.m[0].v.size() != m2.m.size())
			{
				LOG("Shape mismatch: " << "matrix1 columns: " << m1.m[0].v.size() << ", " << "matrix2 rows: " << m2.m.size());
				throw std::exception();
			}

		unsigned int m1x = 0; unsigned int m1y = 0; unsigned int m2y = 0; //m2y = m1x

		while (outm.m.size() < m1.m.size())
		{
			Vf tempv;
			while (tempv.v.size() < m2.m[0].v.size())
			{
				double total = 0.0;
				while (m1x < m1.m[0].v.size())
				{
					total += m1.m[m1y].v[m1x] * m2.m[m1x].v[m2y];
					m1x++;
				}
				tempv.v.push_back(total);
				m1x = 0;
				m2y < m2.m[0].v.size() - 1 ? m2y++ : m2y = 0;
			}
			m1y < m1.m.size() - 1 ? m1y++ : m1y = 0;
			outm.m.push_back(tempv);
		}
	}

	//assumes that all the vectors in the matrix will be the same size
	inline void matrixAdd(Mf& mat, const Vf& vec)
	{
		if (mat.m[0].v.size() != vec.v.size())
		{
			LOG("Shape mismatch: " << "matrix columns: " << mat.m[0].v.size() << ", " << "vector size: " << vec.v.size());
			throw std::exception();
		}

		for (unsigned int i = 0; i < mat.m.size(); i++)
			for (unsigned int j = 0; j < vec.v.size(); j++)
			{
				mat.m[i].v[j] += vec.v[j];
			}

	}

	//value less than lower, than lower otherwise value (cap values at lower)
	//used for rectified linear activation function in hidden layer
	inline Mf matrixCapMin(const double value, const Mf& inmat)
	{
		Mf outmat;
		for (unsigned int i = 0; i < inmat.m.size(); i++)
		{
			Vf tempv;
			for (unsigned int j = 0; j < inmat.m[i].v.size(); j++)
			{
				tempv.v.push_back(MAX(value, inmat.m[i].v[j]));
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}

	//caps max value in matrix at value
	inline Mf matrixCapMax(const double value, const Mf& inmat)
	{
		Mf outmat;
		for (unsigned int i = 0; i < inmat.m.size(); i++)
		{
			Vf tempv;
			for (unsigned int j = 0; j < inmat.m[i].v.size(); j++)
			{
				tempv.v.push_back(MIN(value, inmat.m[i].v[j]));
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}

	//axis = 0 means max value in each row
	//axis = 1 means max value in each column
	inline Vf matrixGetMaxInAxis(const Mf& mat, const int axis)
	{
		Vf tempv; 

		if (axis == 0)
		{
		for (unsigned int i = 0; i < mat.m[0].v.size(); i++)
		{
			tempv.v.push_back(mat.m[0].v[i]);
			for (unsigned int j = 1; j < mat.m.size(); j++)
			{
				tempv.v[i] = MAX(mat.m[j].v[i], tempv.v[i]);
			}
		}
		}
		else if (axis == 1)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				tempv.v.push_back(mat.m[i].v[0]);
				for (unsigned int j = 1; j < mat.m[i].v.size(); j++)
				{
					tempv.v[i] = MAX(mat.m[i].v[j], tempv.v[i]);
				}
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}

		return tempv;
	}

	//returns biggest value from whole of the matrix
	inline double matrixGetMax(const Mf& mat)
	{
		double biggest = mat.m[0].v[0];
		for (unsigned int i = 0; i < mat.m.size(); i++)
			for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
			{
				biggest = MAX(mat.m[i].v[j], biggest);
			}
		return biggest;
	}

	//exponentiate all the elements
	inline Mf matrixExp(const Mf& mat)
	{
		Mf outmat;
		for (unsigned int i = 0; i < mat.m.size(); i++)
		{
			Vf tempv;
			for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
			{
				tempv.v.push_back(pow(EULERS_NUMBER, mat.m[i].v[j]));
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}

	//minus value from all the elements
	inline Mf matrixMinus(const double value, const Mf& mat)
	{
		Mf outmat;
		for (unsigned int i = 0; i < mat.m.size(); i++)
		{
			Vf tempv;
			for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
			{
				tempv.v.push_back(mat.m[i].v[j] - value);
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}


	// 0 = rows, 1 = columns
	inline Mf matrixMinusMaxInAxis(const Mf& mat, const int axis)
	{
		Mf outmat;
		if (axis == 0)
		{
			outmat = mat;
			Vf max = matrixGetMaxInAxis(mat, 0);
			for (unsigned int i = 0; i < mat.m[0].v.size(); i++)
				for (unsigned int j = 0; j < mat.m.size(); j++)
				{
					outmat.m[j].v[i] = mat.m[j].v[i] - max.v[i];
				}
		}
		else if (axis == 1)
		{
			Vf max = matrixGetMaxInAxis(mat, 1);
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				Vf tempv;
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
				{
					tempv.v.push_back(mat.m[i].v[j] - max.v[i]);
				}
				outmat.m.push_back(tempv);
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}
		return outmat;
	}

	//axis 0 means rows are summed 
	//axis 1 means that columns 
	inline Vf matrixSumInAxis(const Mf& mat, const int axis)
	{
		Vf tempv;

		if (axis == 0)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				double total = 0.0;
				for (unsigned int j = 0; j < mat.m[0].v.size(); j++)
				{
					total += mat.m[i].v[j];
				}
				tempv.v.push_back(total);
			}
		}
		else if (axis == 1)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				tempv.v.push_back(vectorSum(mat.m[i]));
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}
		return tempv;
	}

	/*axis 0 means rows are summed to normalize
	axis 1 means that columns are summed to normalize*/
	inline Mf matrixNormalizeInAxis(const Mf& mat, int axis)
	{
		Mf outmat;
		if (axis == 0)
		{
			Vf _tempv = matrixSumInAxis(mat, 0);
			Vf tempv;
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
				{
					tempv.v.push_back(mat.m[i].v[j] / _tempv.v[j]);
				}
				outmat.m.push_back(tempv);
			}
		}
		else if (axis == 1)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				Vf tempv;
				double total = vectorSum(mat.m[i]);
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
				{
					if (total != 0)
						tempv.v.push_back(mat.m[i].v[j] / total);
					else
						tempv.v.push_back(1.0 / mat.m[i].v.size());
				}
				outmat.m.push_back(tempv);
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}
		return outmat;
	}

}
