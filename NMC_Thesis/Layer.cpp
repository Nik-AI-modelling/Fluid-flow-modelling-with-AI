#include "matrix.h"
#include "layer.h"
#include <iostream>

Layer::Layer(int neuron_count) {
	outputs.init(1, neuron_count);
	biased.init(1, neuron_count);
}


//This creates a new layer from the current one
Layer Layer::next_layer(int neuron_count) {
	//Create a new object layer called next
	Layer next;
	//Initialize outputs Matrix of the layer next
	//The outputs matrix of next is initialized with 1 row and neuron_count columns.
	next.outputs.init(1, neuron_count);
	//Initialize biased Matrix of the layer next
	//The outputs matrix of next is initialized with 1 row and neuron_count columns.
	next.biased.init(1, neuron_count);

	//Resizes the weight matrix to connect the current layer to the new layer.

	//this->weights -referes to the outputs of the current layer
	//The weight matrix connects the current layer’s neurons to the new layer.
	//Each row represents a neuron in the current layer.
	// Each column represents a neuron in the new layer.
	//This allows the output of the current layer to be transformed into the input of the next layer.

	this->weights.init(this->outputs.cols(), next.outputs.cols());
	return next;
}

//std::move(a) converts a into an rvalue reference, triggering the move constructor.
//Instead of copying data, the b object steals resources from a, leaving a in a valid but unspecified state.
//✔ Performance Optimization: Moves resources instead of copying them.
//✔ Avoids Expensive Copies : Reduces memory allocations and deallocations.
//✔ Supports Modern C++ Features : Works seamlessly with STL containers.
//Ensures exception safety with noexcept


//Since all work is done in the initializer list, the function body remains empty.
Layer::Layer(Layer&& other) noexcept :
	outputs(std::move(other.outputs)),
	biased(std::move(other.biased)),
	weights(std::move(other.weights))
{}

//The function performs a forward pass in a neural network layer by computing the weighted sum of the previous layer’s outputs,
//applying biases, and then using the sigmoid activation function.

//This adds the bias vector(curr.biased) to the result.
//Bias helps the network shift the activation function to improve learning.
//The += modifies prev.outputs * prev.weights in place and updates the variable.


//[y1 y2 y3]=sigmoid.([x1 x2]*[w1 w3 w5 ! w2 w4 w6]+[b1 b2 b3])
//Y=sigmoid(X*W+B)
// 
// 
// 
//The sigmoid function is applied element - wise to curr.outputs.
void Layer::forward(Layer& curr, Layer& prev) {
	curr.outputs = (
		(prev.outputs * prev.weights) += curr.biased
		).sigmoid();
}