#pragma once

#include "matrix.h"
#include "layer.h"
#include <iostream>

#include <vector>

struct NN {

	matrix_t learn_rate = 0.01;
	std::vector<Layer> layers;
	std::vector<std::string> output_labels;

	int trained = 0;    // Number of times the model trained on the dataset.
	int data_index = 0; // Index in the dataset to the next training data.

	//null constractor
	NN();
	//A vector of integers, probably defining the architecture(e.g., number of neurons in each layer).
	//output_labels: A vector of strings, likely representing the labels of the output layer.
	//output_labels: A vector of strings, likely representing the labels of the output layer.

	NN(const std::vector<int>& config, const std::vector<std::string>& output_labels);

	//Returns a reference to the output Matrix, which contains the final predictions after a forward pass.
	Matrix& get_outputs();

	//Computes the output of the neural network given an input matrix.
	void forward(const Matrix& input);

	//Backpropagation (Training Step)
	void backprop(const Matrix& expected);

	//Adjusts the network's weights based on the expected output (expected),
	//which is needed for supervised learning.
	void save(const char* path) const;

	//Loads the model parameters from a file.
	void load(const char* path);

	float error(Matrix& out, Matrix& exp);
};