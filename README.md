# ARTEMSVISION.V.0.1
The ARTEMESVISION library provides a collection of classes and functions for performing computer vision tasks, including image processing and machine learning


 C++ library is a collection of classes and functions designed to facilitate computer vision tasks such as image segmentation, object detection, and classification. The library provides a range of tools for image processing and manipulation, including functions for reading and writing images, transforming images, and filtering images. The library also includes classes for building and training deep learning models, with support for popular architectures such as Convolutional Neural Networks (CNNs)


PixelEditor() ->  C++ class that represents an image editor, capable of reading an image file, storing its pixel data, applying filters to the pixels, displaying the edited image using a window API, annotating pixels with text, and resizing the image. The class uses a 2D array of Pixel structs to store the image's RGB color values. The PixelEditor class provides methods for accessing the image dimensions and pixel data and modifying the pixels. The class can also display the edited image in a new window and annotate pixels with text at specific coordinates. Additionally, the class can resize the image to a new set of dimensions by creating a new 2D array of pixels with the new dimensions and copying over the existing pixel data.

PixelEditor(string filename)
The constructor reads the pixel data from the given image file and stores it in the pixels member variable.
~PixelEditor()
The destructor frees the memory allocated for the pixels member variable.
int getWidth()
This getter method returns the width of the image in pixels.
int getHeight()
This getter method returns the height of the image in pixels.
Pixel** getPixels()
This getter method returns a pointer to the 2D array of Pixel structs that contains the pixel data.
void filterPixels()
This method applies a pastel filter to the image by averaging the RGB components of each pixel with 255 (white).
void displayPixels()
This method displays the image in a window using a device context and the SetPixel function.
void pixelAnnotator(int x, int y, string message, PixelEditor& editor)
This method annotates a specific pixel with a message by creating a new Pixel struct with a white background and the same RGB values as the original pixel, blending the two pixels together based on a given alpha value, writing the message on the new pixel using the DrawText function, and setting the pixel at the given coordinates to the annotated pixel.
void pixelResizer(int newWidth, int newHeight)
This method resizes the image by creating a new 2D array of Pixel structs with the given dimensions, copying the pixel data from the original array to the new array using bilinear interpolation, and updating the pixels, width, and height member variables to point to the new array and reflect the new dimensions.





PixelProcessor()-> derived class of PixelEditor that provides additional functionality for image processing.

voidconvLayer(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& kernel, std::vector<std::vector<double>>& output)
performs a convolution operation on the input vector using a specified kernel and stores the output in the output vector. Parameters: input: a 2D vector representing the input image kernel: a 2D vector representing the convolution kernel output: a 2D vector representing the output image
double relu(double x)
implements the Rectified Linear Unit (ReLU) activation function. Parameters: x: a scalar value to be processed Returns: A scalar value which is the result of applying ReLU on the input value
vector<vector<double>> concatenate(vector<vector<double>>& a, vector<vector<double>>& b, int axis)
takes as input two or more tensors with the same number of dimensions and returns a new tensor with the concatenated values. The axis along which to concatenate the tensors is specified as an integer parameter. The function creates a new tensor with the required shape, copies the values from the input tensors into the appropriate positions in the new tensor, and returns the result.
void activation_relu(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output)
applies the ReLU activation function to each element of the input matrix and stores the result in the output matrix. Parameters: input: a 2D vector representing the input matrix output: a 2D vector representing the output matrix
void maxPooling(std::vector<std::vector<double>>& input, int pool_size, std::vector<std::vector<double>>& output)
performs max pooling on the input image using a specified pool size and stores the output in the output vector.
parameters
input: a 2D vector representing the input image
pool_size: an integer value specifying the pooling size
output: a 2D vector representing the output image


void fullyConnected(std::vector<double>& input, std::vector<std::vector<double>>& weights, std::vector<double>& biases, std::vector<double>& output)
performs a fully connected layer operation on the input vector using a specified weight matrix and bias vector, and stores the output in the output vector. Parameters: input: a 1D vector representing the input weights: a 2D vector representing the weights biases: a 1D vector representing the biases output: a 1D vector representing the output
double sigmoid(double x)
implements the sigmoid activation function. Parameters: x: a scalar value to be processed
Returns: A scalar value which is the result of applying sigmoid on the input value
double sigmoid_derivative(double x)
calculates the derivative of the sigmoid function at a specified value. Parameters: x: a scalar value to be processed Returns: A scalar value which is the result of applying the derivative of sigmoid on the input value
void feedForward(std::vector<double>& input, std::vector<std::vector<double>>& weights1, std::vector<double>& biases1, std::vector<std::vector<double>>& weights2, std::vector<double>& biases2, std::vector<double>& output) 
performs feedforward on the input vector using specified weight matrices and bias vectors, and stores the output in the output vector. Parameters: input: a 1D vector representing the input weights1: a 2D vector representing the weights for the first layer biases1: a 1D vector representing the biases for the first layer weights2: a 2D vector representing the weights for the second layer biases2: a 1D vector representing the biases for the second layer output: a 1D vector representing the output.
void backPropagation(std::vector<double>& input, std::vector<double>& target_output, std::vector<std::vector<double>>& weights1, std::vector<double>& biases1, std::vector<std::vector<double>>& weights2, std::vector<double>& biases2, double learning_rate)
It takes in the input, target output, weights, biases, and learning rate as arguments, and updates the weights and biases based on the error in the output. The function first performs a feedforward pass using the input and current weights and biases to calculate the output of the neural network. Then, it calculates the error in the output layer by taking the difference between the target output and the actual output, and multiplying it by the derivative of the sigmoid function applied to the output. Next, it calculates the error in the hidden layer by using the output layer error and the weights between the hidden and output layers. It multiplies the output layer error by the weights and applies the derivative of the sigmoid function to the hidden layer output. Finally, it updates the weights and biases of both the output and hidden layers based on the errors calculated.





PixelOptimizer() -> contains four nested classes:adamOptimizer, MomentumOptimizer, RMSProp, and Adagrad. These nested classes implement different optimization algorithms for updating the values of a set of parameters represented by a vector of doubles called theta, given their gradients represented by another vector of doubles called grads.
All four nested classes have an update method that takes in the current parameter values theta and their gradients grads, and returns the updated parameter values after applying the corresponding optimization algorithm. The methods update the internal states of the optimizer, such as the momentum or the cache of the squared gradients, which are used for the subsequent update steps. Overall, this header file provides a set of common optimization algorithms for updating the values of a set of parameters given their gradients. These algorithms are used widely in training deep learning models and other optimization problems.



adamOptimizer
implements the Adam optimization algorithm, which is an adaptive learning rate optimization algorithm that combines the benefits of both the Momentum and RMSProp algorithms. It uses the first and second moments of the gradients to update the parameters. It takes in four optional parameters: the learning rate, the beta1 and beta2 decay rates, and the epsilon value.
MomentumOptimizer
implements the Momentum optimization algorithm, which adds a fraction of the previous update vector to the current update vector, introducing momentum to the optimization process. It takes in two optional parameters: the learning rate and the momentum coefficient.
RMSProp
implements the RMSProp optimization algorithm, which uses a moving average of squared gradients to adjust the learning rate for each parameter. It takes in three optional parameters: the learning rate, the decay rate, and the epsilon value.
Adagrad
implements the Adagrad optimization algorithm, which adapts the learning rate for each parameter based on the sum of the squares of its historical gradients. It takes in two optional parameters: the learning rate and the epsilon value.



PixelEvaluation.h -> C++ header file defining three functions for evaluating the performance of machine learning models on classification and regression problems:
The implementation of these functions is straightforward and follows standard formulas for accuracy, MSE, and F1 score. The header file also includes standard C++ headers (<iostream>, <vector>, and <cmath>) for input/output, vectors, and mathematical functions, respectively.

accuracy(vector<int>& y_true, vector<int>& y_pred)
computes the accuracy of binary classification predictions, where y_true is a vector of true binary labels (0 or 1) and y_pred is a vector of predicted binary labels.
mse(vector<double>& y_true, vector<double>& y_pred)
computes the mean squared error (MSE) for regression predictions, where y_true is a vector of true numerical values and y_pred is a vector of predicted numerical values.
f1_score(vector<int>& y_true, vector<int>& y_pred)
computes the F1 score of binary classification predictions, where y_true is a vector of true binary labels (0 or 1) and y_pred is a vector of predicted binary labels.




