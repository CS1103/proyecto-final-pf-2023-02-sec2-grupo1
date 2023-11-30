//
// Created by Carlo on 11/30/2023.
//

#ifndef PROTOTYPE_0_5_NEURALNETWORK_H
#define PROTOTYPE_0_5_NEURALNETWORK_H

#include "Dataset.h"
#include <random>
#include <algorithm>

class NeuralNetwork {
    double*** weights;
    std::vector<size_t> n_neurons_per_layer;
    double** biases;
    double training_accuracy;
    double learning_rate;

    double* feed_forward(const std::vector<double>&, const label&, double&, double*, double*);
    void backpropagation(const std::vector<double>&, const label&, double&, const double*, const double*);
    double training_result(const label&, const double*);
public:
    NeuralNetwork(const size_t&, const std::vector<size_t>&, const double&);

    void epoch_training(const size_t&, const Dataset&);
    void predict(const std::pair<std::vector<double>,label>&);
};

#endif //PROTOTYPE_0_5_NEURALNETWORK_H