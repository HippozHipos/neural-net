//https://github.com/HippozHipos/neural-net/tree/master/neural%20net
#include "activation.h"

namespace neural_net {

	ActivationReLU::ActivationReLU() {};

	ActivationReLU::~ActivationReLU() {};

	void ActivationReLU::forward(const numcpp::Mf& input)
	{
		output = numcpp::matrixCapMin(0.0, input);
		LOG("(ReLU forward) forward pass. matrix capped at min value of 0. output: " << std::endl << output);
	}


	ActivationSoftmax::ActivationSoftmax() {};

	void ActivationSoftmax::forward(const numcpp::Mf& input)
	{
		numcpp::Mf negated = numcpp::matrixMinusMaxInAxis(input, 1);
		LOG("(softmax forward) input matrix's highest value negated from all the elements in matrix. output: " << std::endl << negated);
		numcpp::Mf exp = numcpp::matrixExp(negated);
		LOG("(softmax forward) all the elements in the negated matrix exponentiated. output: " << std::endl << exp);
		output = numcpp::matrixNormalizeInAxis(exp, 1);
		LOG("(softmax forward) exponentiated matrix is normalized. output: " << std::endl << output);
	}

}



