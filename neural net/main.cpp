#include "layer.h"
#include "activation.h"
#include "numcpp.h"

int main()
{
	std::cout.precision(10);

	numcpp::Mf X;
	const int nMatSize = 3;
	numcpp::rng.Matrix(nMatSize, nMatSize, -1.0, 1.0, X);

	neural_net::LayerDense layer1 = neural_net::LayerDense(nMatSize, nMatSize);
	neural_net::ActivationReLU ReLU1;

	layer1.forward(X);
	ReLU1.forward(layer1.output);

	neural_net::LayerDense layerOut = neural_net::LayerDense(nMatSize, nMatSize);
	neural_net::ActivationSoftmax softmax;

	layerOut.forward(ReLU1.output);
	softmax.forward(layerOut.output); 
}
