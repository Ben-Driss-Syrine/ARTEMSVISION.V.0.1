#ifndef ARTEMSVISION_PEXELPROCESSOR_H
#define ARTEMSVISION_PEXELPROCESSOR_H
#include "PixelEditor.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
class PixelProcessor : public PixelEditor {
public:
    using PixelEditor::PixelEditor; // inherit PixelEditor's constructor(s)
    using PixelEditor::getWidth; // inherit PixelEditor's getWidth() method
    using PixelEditor::getHeight; // inherit PixelEditor's getHeight() method
    using PixelEditor::getPixels; // inherit PixelEditor's getPixel() method



// Define the convolutional layer
    void convLayer(std::vector<std::vector<double>>& input,
                std::vector<std::vector<double>>& kernel,
                std::vector<std::vector<double>>& output) {

        int in_height = input.size();
        int in_width = input[0].size();
        int k_height = kernel.size();
        int k_width = kernel[0].size();

        // Set the output size
        int out_height = in_height - k_height + 1;
        int out_width = in_width - k_width + 1;
        output.resize(out_height, std::vector<double>(out_width, 0.0));

        // Perform the convolution
        for (int i = 0; i < out_height; i++) {
            for (int j = 0; j < out_width; j++) {
                for (int k = 0; k < k_height; k++) {
                    for (int l = 0; l < k_width; l++) {
                        output[i][j] += input[i+k][j+l] * kernel[k][l];
                    }
                }
            }
        }
    }

    // Define the ReLU activation function
    double relu(double x) {
        return std::max(0.0, x);
    }

// Define the activation layer
    void activation_relu(std::vector<std::vector<double>>& input,
                         std::vector<std::vector<double>>& output) {

        // Set the output size
        int height = input.size();
        int width = input[0].size();
        output.resize(height, std::vector<double>(width, 0.0));

        // Perform the ReLU activation
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                output[i][j] = relu(input[i][j]);
            }
        }
    }

    // Define the max pooling layer
    void maxPooling(std::vector<std::vector<double>>& input,
                     int pool_size,
                     std::vector<std::vector<double>>& output) {

        int in_height = input.size();
        int in_width = input[0].size();
        int out_height = in_height / pool_size;
        int out_width = in_width / pool_size;

        // Set the output size
        output.resize(out_height, std::vector<double>(out_width, 0.0));

        // Perform the max pooling
        for (int i = 0; i < out_height; i++) {
            for (int j = 0; j < out_width; j++) {
                double max_val = -std::numeric_limits<double>::infinity();
                for (int k = 0; k < pool_size; k++) {
                    for (int l = 0; l < pool_size; l++) {
                        double val = input[i*pool_size+k][j*pool_size+l];
                        if (val > max_val) {
                            max_val = val;
                        }
                    }
                }
                output[i][j] = max_val;
            }
        }
    }
    // Define the fully connected layer
    void fullyConnected(std::vector<double>& input,
                         std::vector<std::vector<double>>& weights,
                         std::vector<double>& biases,
                         std::vector<double>& output) {

        int input_size = input.size();
        int output_size = biases.size();

        // Set the output size
        output.resize(output_size, 0.0);

        // Perform the matrix multiplication
        for (int i = 0; i < output_size; i++) {
            for (int j = 0; j < input_size; j++) {
                output[i] += input[j] * weights[j][i];
            }
            output[i] += biases[i];
        }

    }
    // concatenate two vectors along a given axis
    vector<vector<double>> concatenate(vector<vector<double>>& a, vector<vector<double>>& b, int axis) {
        int size_a = a.size();
        int size_b = b.size();

        vector<vector<double>> result;
        if (axis == 0) {
            // concatenate along rows
            for (int i = 0; i < size_a; i++) {
                result.push_back(a[i]);
            }
            for (int i = 0; i < size_b; i++) {
                result.push_back(b[i]);
            }
        } else if (axis == 1) {
            // concatenate along columns
            for (int i = 0; i < size_a; i++) {
                vector<double> row = a[i];
                row.insert(row.end(), b[i].begin(), b[i].end());
                result.push_back(row);
            }
        } else {
            // invalid axis
            cout << "Invalid axis" << endl;
        }
        return result;
    }
    // Define the sigmoid activation function
    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

// Define the derivative of the sigmoid activation function
    double sigmoid_derivative(double x) {
        double s = sigmoid(x);
        return s * (1 - s);
    }

// Define the feedforward function
    void feedForward(std::vector<double>& input,
                     std::vector<std::vector<double>>& weights1,
                     std::vector<double>& biases1,
                     std::vector<std::vector<double>>& weights2,
                     std::vector<double>& biases2,
                     std::vector<double>& output) {

        // Calculate the hidden layer output
        std::vector<double> hidden(weights1[0].size(), 0.0);
        for (int i = 0; i < weights1[0].size(); i++) {
            for (int j = 0; j < input.size(); j++) {
                hidden[i] += input[j] * weights1[j][i];
            }
            hidden[i] += biases1[i];
            hidden[i] = sigmoid(hidden[i]);
        }

        // Calculate the output layer output
        output.resize(weights2[0].size(), 0.0);
        for (int i = 0; i < weights2[0].size(); i++) {
            for (int j = 0; j < hidden.size(); j++) {
                output[i] += hidden[j] * weights2[j][i];
            }
            output[i] += biases2[i];
            output[i] = sigmoid(output[i]);
        }
    }

// Define the backpropagation function
    void backPropagation(std::vector<double>& input,
                         std::vector<double>& target_output,
                         std::vector<std::vector<double>>& weights1,
                         std::vector<double>& biases1,
                         std::vector<std::vector<double>>& weights2,
                         std::vector<double>& biases2,
                         double learning_rate) {

        // Perform the feedforward pass
        std::vector<double> output;
        feedForward(input, weights1, biases1, weights2, biases2, output);

        // Calculate the output layer error
        std::vector<double> output_error(target_output.size(), 0.0);
        for (int i = 0; i < target_output.size(); i++) {
            output_error[i] = (target_output[i] - output[i]) * sigmoid_derivative(output[i]);
        }

        // Calculate the hidden layer error
        std::vector<double> hidden(weights1[0].size(), 0.0);
        std::vector<double> hidden_error(weights2.size(), 0.0);
        for (int i = 0; i < weights2.size(); i++) {
            for (int j = 0; j < weights2[0].size(); j++) {
                hidden_error[i] += output_error[j] * weights2[i][j];
            }
            hidden_error[i] *= sigmoid_derivative(hidden[i]);
        }

        // Update the weights and biases of the output layer
        for (int i = 0; i < weights2.size(); i++) {
            for (int j = 0; j < weights2[0].size(); j++) {
                weights2[i][j] += learning_rate * output_error[j] * hidden[i];
            }
            biases2[i] += learning_rate * output_error[i];
        }
        // Update the weights and biases of the hidden layer
        for (int i = 0; i < weights1.size(); i++) {
            for (int j = 0; j < weights1[0].size(); j++) {
                weights1[i][j] += learning_rate * hidden_error[j] * input[i];
            }
            biases1[i] += learning_rate * hidden_error[i];
        }
    }};
#endif //ARTEMSVISION_PEXELPROCESSOR_H
