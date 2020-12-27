#include "layer.h"
#include "activation.h"
#include "numcpp.h"

//NOTES:
//1. matrices are ordered row by column 
//2. LOG macro in numcpp.h file is responsible for logging. Set DEBUG macro to 0 to turn logging off.

int main()
{
	//output up to 10 digits
	std::cout.precision(10);

	//create a matrix 
	numcpp::Mf X;

	//all the matrices size will be 3x3 to make it easier to test things.
	const int nMatSize = 3;

	//fill X will random numbers between -1.0 and 1.0. 
	numcpp::rng.Matrix(nMatSize, nMatSize, -1.0, 1.0, X);

	//initilaize dense layer1 of size nMatSize x nMatSize
	neural_net::LayerDense layer1 = neural_net::LayerDense(nMatSize, nMatSize);
	//ReLU object for layer 1
	neural_net::ActivationReLU ReLU1;

	//forward pass of layer 1.
	layer1.forward(X);
	//output of layer 1 is passed to ReLU as input.
	ReLU1.forward(layer1.output);

	//initilaize dense layer2 of size nMatSize x nMatSize. This is an output layer.
	neural_net::LayerDense layerOut = neural_net::LayerDense(nMatSize, nMatSize);
	//it uses softmax activation function since its an output layer
	neural_net::ActivationSoftmax softmax;

	//output of ReLU1 is passed to the output layer as input.
	layerOut.forward(ReLU1.output);
	//output of output layer is passed through the softmax activation function.
	softmax.forward(layerOut.output); 
}
