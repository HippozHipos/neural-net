#pragma once

#include "numcpp.h"

namespace neural_net {

	struct ActivationReLU
	{
		numcpp::Mf output; 
		ActivationReLU();
		~ActivationReLU();
		void forward(const numcpp::Mf& input);
	};

	struct ActivationSoftmax
	{ 
		numcpp::Mf output;
		ActivationSoftmax();
		void forward(const numcpp::Mf& input);
	};

}
