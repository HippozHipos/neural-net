#pragma once

#include "numcpp.h"

namespace neural_net {

	struct LayerDense
	{
		numcpp::Mf weights;
		numcpp::Mf output;
		numcpp::Vf biases;
		LayerDense(const int nInputs, const int nNeurons, double bias=0.0);
		~LayerDense();
		void forward(const numcpp::Mf& inputs); 
	};
  
}