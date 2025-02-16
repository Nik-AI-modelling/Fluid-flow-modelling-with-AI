#pragma once

#include "matrix.h"
#include <iostream>

#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;



struct Layer {
	//This block creates 3 objects of the Matrix type
	Matrix outputs;  // Stores the outputs of neurons in this layer
	Matrix biased;   // Stores biases for each neuron
	Matrix weights;  // Stores weights connecting this layer to the next

	Layer(int neuron_count = 0);  // Constructor to initialize the layer
	
	//layer1's data is moved to layer2, leaving layer1 in an empty state.
	//No expensive memory allocations or copies happe
	Layer(Layer&& other) noexcept; // Move constructor for efficient memory transfer

	// Create the next layer from current updating the weights.
	//Takes neuron_count as an argument(number of neurons in the next layer).
	//Uses the current layer’s weights to connect to the new layer.
	//Returns a new Layer object.

	Layer next_layer(int neuron_count);

	static void forward(Layer& curr, Layer& prev);
};