//
// Created by Carlo on 11/30/2023.
//

#pragma once
#include "NeuralNetwork.h"

double* NeuralNetwork::feed_forward(const std::vector<double>& pxl_values, const label& lbl, double& sum, double* a1, double* a2) {
    auto* dE = new double[n_neurons_per_layer[2]];
    for (size_t i = 0; i < n_neurons_per_layer[1]; i++) {
        sum = biases[0][i];
        for (int j = 0; j < n_neurons_per_layer[0]; j++)
            sum += weights[0][j][i]* pxl_values[j];
        a1[i] = 1 / (1 + std::exp(-1 * sum));
    }
    for (size_t i = 0; i < n_neurons_per_layer[2]; i++) {
        sum = biases[1][i];
        for (int j = 0; j < n_neurons_per_layer[1]; j++)
            sum += weights[1][j][i] * a1[j];
        a2[i] = 1 / (1 + std::exp(-1 * sum));
        dE[i] = learning_rate * ((i == lbl) - a2[i]) * a2[i] * (1 - a2[i]);
    }
    return dE;
}

void NeuralNetwork::backpropagation(const std::vector<double>& pixel_values, const label& lbl, double& sum, const double* a1, const double* dE) {
    for (size_t i = 0; i < n_neurons_per_layer[1]; i++) {
        sum = 0;
        for (size_t j = 0; j < n_neurons_per_layer[2]; j++)
            sum += weights[1][i][j] * dE[j];
        sum *= a1[i] * (1 - a1[i]);
        for (int j = 0; j < n_neurons_per_layer[0]; j++)
            weights[0][j][i] += sum * pixel_values[j];
    }
    for (size_t i = 0; i < n_neurons_per_layer[2]; i++) {
        biases[1][i] += dE[i];
        for (size_t j = 0; j < n_neurons_per_layer[1]; j++)
            weights[1][j][i] += dE[i] * a1[j];
    }
}

double NeuralNetwork::training_result(const label& lbl, const double* a2) {
    double prob = 0;
    label pred = -1;
    for (size_t i = 0; i < n_neurons_per_layer[2]; i++)
        if (a2[i] > prob) {
            prob = a2[i];
            pred = i;
        }
    return pred == lbl;
}

NeuralNetwork::NeuralNetwork(const size_t& n_layers, const std::vector<size_t>& n_n_per_layer, const double& l_r) : training_accuracy(0.0), learning_rate(l_r) {
    if (n_layers != n_n_per_layer.size())
        throw std::runtime_error(R"(size of parameters "n_neurons_per_layer" and "n_layers" must be equal)");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);

    size_t n_l = n_layers - 1;
    weights = new double**[n_l];
    biases = new double*[n_l];
    n_neurons_per_layer = n_n_per_layer;

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

NeuralNetwork::~NeuralNetwork() {
    for (size_t l = 0; l < n_neurons_per_layer.size() - 1; l++) {
        for (size_t n = 0; n < n_neurons_per_layer[l]; n++)
            delete[] weights[l][n];
        delete[] weights[l];
    }
    delete[] weights;

    for (size_t l = 0; l < n_neurons_per_layer.size() - 1; l++)
        delete[] biases[l];
    delete[] biases;
}


//Se entrena a la red neuronal el número de epochs que se requiera
void NeuralNetwork::epoch_training(const size_t& epochs, const Dataset& dataset) {
    std::cout << "\nTraining started!\n";
    for (size_t epoch = 0; epoch < epochs; epoch++) {
        for (int i = 0; i < dataset.get_training_size(); i++) {
            auto t_example = dataset.get_training_example(i);
            double sum = 0;
            auto* act1 = new double[n_neurons_per_layer[1]];
            auto* act2 = new double[n_neurons_per_layer[2]];
            auto* dError = feed_forward(t_example.first, t_example.second, sum, act1, act2);
            backpropagation(t_example.first, t_example.second, sum, act1, dError);
            training_accuracy += training_result(t_example.second, act2);
            delete[] act1;
            delete[] act2;
            delete[] dError;
        }
        std::cout << "Epoch " << epoch + 1 << ": Training Data Accuracy: " << training_accuracy / dataset.get_training_size() * 10.0 << std::endl;
    }


}

void NeuralNetwork::predict(const std::pair<std::vector<double>, label>& example) {
    double sum = 0;
    auto* act1 = new double[n_neurons_per_layer[1]];
    auto* act2 = new double[n_neurons_per_layer[2]];

    feed_forward(example.first, example.second, sum, act1, act2);

    label predicted_label = std::distance(act2, std::max_element(act2, act2 + n_neurons_per_layer[2]));

    std::cout << "Predicted Label: " << predicted_label << std::endl;
    std::cout << "Real Label: " << example.second << std::endl;

    delete[] act1;
    delete[] act2;
}

void NeuralNetwork::saveParameters() {
    std::ofstream file("network_parameters.txt");

    // Guardar pesos
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < (i == 0 ? 784 : 28); ++j) {
            for (int k = 0; k < (i == 0 ? 28 : 10); ++k)
                file << weights[i][j][k] << " ";
            file << "\n";
        }

    // Guardar sesgos
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < (i == 0 ? 28 : 10); ++j)
            file << biases[i][j] << " ";
        file << "\n";
    }

    file.close();
}

bool NeuralNetwork::loadParameters() {
    std::ifstream file("network_parameters.txt");
    if (!file.is_open())
        return false; // El archivo no existe, continuar con la inicialización normal

    // Cargar pesos
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < (i == 0 ? 784 : 28); ++j)
            for (int k = 0; k < (i == 0 ? 28 : 10); ++k)
                file >> weights[i][j][k];

    // Cargar sesgos
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < (i == 0 ? 28 : 10); ++j)
            file >> biases[i][j];

    file.close();
    return true;
}