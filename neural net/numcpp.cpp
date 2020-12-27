#include "numcpp.h"


namespace numcpp {

	//#######################################
	//#               RANDOM                #
	//#######################################


	// To make generate the same set of random numbers (for debugging)
	//comment out: std::mt19937 randomEngine(randomSeed());
	//uncomment: std::mt19937 randomEngine(3);
	Random::Random() 
	{ 
		std::random_device randomSeed;
		//std::mt19937 randomEngine(3);
		std::mt19937 randomEngine(randomSeed());
		_randomEngine = randomEngine;
	};

	Random::~Random() {};

	Random& Random::Get()
	{
		static Random random; 
		return random;
	}

	int Random::Range(const int lower, const int upper)
	{
		std::uniform_int_distribution<int> distribution(lower, upper);
		return distribution(_randomEngine);
	}

	double Random::Range(const double lower, const double upper)
	{
		std::uniform_real_distribution<double> distribution(lower, upper);
		return distribution(_randomEngine);
	}

	void Random::Matrix(const unsigned int rows, const unsigned int cols, const double lower, const double upper, Mf& outmat)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			Vf tempVec;
			for (unsigned int j = 0; j < cols; j++)
			{
				tempVec.v.push_back(Range(lower, upper));
			}
			outmat.m.push_back(tempVec);
		}
	}

	void Random::Vector(const unsigned int size, const double lower, const double upper, Vf& outvec)
	{
		for (unsigned int i = 0; i < size; i++)
			outvec.v.push_back(Range(lower, upper));
	}
}