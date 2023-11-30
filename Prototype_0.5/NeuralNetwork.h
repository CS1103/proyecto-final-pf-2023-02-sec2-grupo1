//
// Created by Carlo on 11/30/2023.
//

#ifndef PROTOTYPE_0_5_NEURALNETWORK_H
#define PROTOTYPE_0_5_NEURALNETWORK_H

#include "Dataset.h"
#include <random>

class NeuralNetwork {
    double*** weights;
    double** biases;
    double training_accuracy;
public:
    NeuralNetwork(const size_t&, const std::vector<size_t>&);

    void epoch_training(const size_t&);
    void predict(const double&);
};

#endif //PROTOTYPE_0_5_NEURALNETWORK_H