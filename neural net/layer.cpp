#include "layer.h"

namespace neural_net {

	LayerDense::LayerDense(const int nInputs, const int nNeurons, double bias)
	{
		numcpp::rng.Matrix(nInputs, nNeurons, 0.0, 1.0, weights);
		LOG("(dense layer init) initialized with matrix: " << std::endl << weights);
		biases.fill(nNeurons, bias);
		LOG("(dense layer init) Filled Biases vector with a bias value of: " << bias << std::endl);
	}

	LayerDense::~LayerDense() {};

	void LayerDense::forward(const numcpp::Mf& inputs)
	{
		numcpp::matrixDot(inputs, weights, output);
		LOG(" (dense layer forward) inputs * weights in forward method of dense layer. output: " << std::endl << output);
		numcpp::matrixAdd(output, biases);
		LOG("(dense layer forward) biases added to output matrix from dot product of weights and input: " << std::endl << output);
	}

} 