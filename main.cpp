#include "Prototype_0.5/NeuralNetwork.h"

float get_number() {
    float number;
    while (!(std::cin >> number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return number;
}

template<typename T>
T get_specific() {
    float number = get_number();
    while (number != static_cast<T>(number))
        number = get_number();
    return static_cast<T>(number);
}

int main() {
    /*std::cout << "Enter the number of layers you want for the network:\n";
    auto number_of_layers = get_specific<size_t>();
    std::cout << "Enter the number of neurons you want for each layer:\n";
    std::vector<size_t> neurons_per_layer(number_of_layers);
    for (auto& n_n : neurons_per_layer)
        n_n = get_specific<size_t>();*/

    std::string training_data("C:/Users/Carlo/CLionProjects/Progra3/DL_Proyect/Prototype_0.4/cmake-build-debug/mnist_train.csv");
    std::string test_data("C:/Users/Carlo/CLionProjects/Progra3/DL_Proyect/Prototype_0.4/cmake-build-debug/mnist_test.csv");
    Dataset data;
    data.load_data_from_csv(training_data, test_data);
    /*std::ifstream stream(training_data);
    if (stream.fail())
        std::cout << "Fallo 1\n";
    stream.close();
    stream.open(test_data);
    if (stream.fail())
        std::cout << "Fallo 2\n";
    stream.close();*/

    //NeuralNetwork NN(number_of_layers, neurons_per_layer, 0.4);
    NeuralNetwork NN(3, {784, 28, 10}, 0.4);

    NN.epoch_training(30, data);

    return 0;
}
