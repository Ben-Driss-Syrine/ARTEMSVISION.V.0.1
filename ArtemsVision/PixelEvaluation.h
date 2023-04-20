#ifndef ARTEMSVISION_PIXELEVALUATION_H
#define ARTEMSVISION_PIXELEVALUATION_H
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// compute accuracy for binary classification problem
double accuracy(vector<int>& y_true, vector<int>& y_pred) {
    int correct = 0;
    for (int i = 0; i < y_true.size(); i++) {
        if (y_true[i] == y_pred[i]) {
            correct++;
        }
    }
    return (double)correct / y_true.size();
}

// compute mean squared error (MSE) for regression problem
double mse(vector<double>& y_true, vector<double>& y_pred) {
    double error = 0.0;
    for (int i = 0; i < y_true.size(); i++) {
        error += pow(y_true[i] - y_pred[i], 2);
    }
    return error / y_true.size();
}
double f1_score(vector<int>& y_true, vector<int>& y_pred) {
    int true_positives = 0, false_positives = 0, false_negatives = 0;

    for (int i = 0; i < y_true.size(); i++) {
        if (y_true[i] == 1 && y_pred[i] == 1) {
            true_positives++;
        } else if (y_true[i] == 0 && y_pred[i] == 1) {
            false_positives++;
        } else if (y_true[i] == 1 && y_pred[i] == 0) {
            false_negatives++;
        }
    }

    double precision = (double)true_positives / (true_positives + false_positives);
    double recall = (double)true_positives / (true_positives + false_negatives);

    return 2 * ((precision * recall) / (precision + recall));
}



#endif //ARTEMSVISION_PIXELEVALUATION_H
