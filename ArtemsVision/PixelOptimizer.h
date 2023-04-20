#ifndef ARTEMSVISION_PIXELOPTIMIZER_H
#define ARTEMSVISION_PIXELOPTIMIZER_H
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
class PixelOptimizer{

class adamOptimizer {
private:
    double alpha, beta1, beta2, epsilon;
    vector<double> m, v;
    int t;
public:
    adamOptimizer(double learning_rate = 0.001, double beta_1 = 0.9, double beta_2 = 0.999, double eps = 1e-8) {
        alpha = learning_rate;
        beta1 = beta_1;
        beta2 = beta_2;
        epsilon = eps;
        t = 0;
    }
    vector<double> update(vector<double> &theta, vector<double> &grads) {
        t++;
        if (m.empty() && v.empty()) {
            m = vector<double>(theta.size(), 0);
            v = vector<double>(theta.size(), 0);
        }
        for (int i = 0; i < theta.size(); i++) {
            m[i] = beta1 * m[i] + (1 - beta1) * grads[i];
            v[i] = beta2 * v[i] + (1 - beta2) * pow(grads[i], 2);
            double m_hat = m[i] / (1 - pow(beta1, t));
            double v_hat = v[i] / (1 - pow(beta2, t));
            theta[i] -= alpha * m_hat / (sqrt(v_hat) + epsilon);
        }
        return theta;
    }
};
    class MomentumOptimizer {
    private:
        double learning_rate, momentum;
        vector<double> velocity;
    public:
        MomentumOptimizer(double lr = 0.001, double mom = 0.9) {
            learning_rate = lr;
            momentum = mom;
        }

        vector<double> update(vector<double> &theta, vector<double> &grads) {
            if (velocity.empty()) {
                velocity = vector<double>(theta.size(), 0.0);
            }
            for (int i = 0; i < theta.size(); i++) {
                velocity[i] = momentum * velocity[i] - learning_rate * grads[i];
                theta[i] += velocity[i];
            }
            return theta;
        }
    };
    class RMSProp {
    private:
        double learning_rate, decay_rate, epsilon;
        vector<double> cache;
    public:
        RMSProp(double lr = 0.001, double dr = 0.9, double eps = 1e-8) {
            learning_rate = lr;
            decay_rate = dr;
            epsilon = eps;
        }

        vector<double> update(vector<double> &theta, vector<double> &grads) {
            if (cache.empty()) {
                cache = vector<double>(theta.size(), 0.0);
            }
            for (int i = 0; i < theta.size(); i++) {
                cache[i] = decay_rate * cache[i] + (1 - decay_rate) * pow(grads[i], 2);
                theta[i] -= learning_rate * grads[i] / (sqrt(cache[i]) + epsilon);
            }
            return theta;
        }
    };
    class Adagrad {
    private:
        double learning_rate, epsilon;
        vector<double> cache;
    public:
        Adagrad(double lr = 0.01, double eps = 1e-8) {
            learning_rate = lr;
            epsilon = eps;
        }

        vector<double> update(vector<double> &theta, vector<double> &grads) {
            if (cache.empty()) {
                cache = vector<double>(theta.size(), 0.0);
            }
            for (int i = 0; i < theta.size(); i++) {
                cache[i] += pow(grads[i], 2);
                theta[i] -= learning_rate * grads[i] / (sqrt(cache[i]) + epsilon);
            }
            return theta;
        }
    };


};


#endif //ARTEMSVISION_PIXELOPTIMIZER_H
