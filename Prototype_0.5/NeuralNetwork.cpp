//
// Created by Carlo on 11/30/2023.
//

#pragma once
#include "NeuralNetwork.h"

//Se inicializan los arreglos multidimensionales de acuerdo a los parámetros
NeuralNetwork::NeuralNetwork(const size_t& n_layers, const std::vector<size_t>& n_neurons_per_layer) {
    if (n_layers != n_neurons_per_layer.size())
        throw std::runtime_error(R"(size of parameters "n_neurons_per_layer" and "n_layers" must be equal)");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);

    size_t n_l = n_layers - 1;
    weights = new double**[n_l];
    biases = new double*[n_l];

    for (size_t l = 0; l < n_l; l++) {
        size_t curr_n_neurons = n_neurons_per_layer[l];
        size_t next_n_neurons = n_neurons_per_layer[l + 1];

        weights[l] = new double*[curr_n_neurons];
        biases[l] = new double[next_n_neurons];
        for (size_t curr_n = 0; curr_n < curr_n_neurons; curr_n++) {
            weights[l][curr_n] = new double[next_n_neurons];
            for (size_t next_n = 0; next_n < next_n_neurons; next_n++)
                weights[l][curr_n][next_n] = dis(gen) / 100.0;
        }
        for (size_t next_n = 0; next_n < next_n_neurons; next_n++) {
            biases[l][next_n] = dis(gen) / 100.0;
        }
    }
}

//Se entrena a la red neuronal el número de epochs que se requiera
void NeuralNetwork::epoch_training(const size_t& epochs) {

}

void NeuralNetwork::predict(const double& pixel_values) {

}