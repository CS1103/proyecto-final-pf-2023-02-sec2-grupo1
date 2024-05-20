#include "Prototype_0.5/NeuralNetwork.h"

std::string training_data("C:/Users/Carlo/CLionProjects/Progra3/DL_Proyect/Prototype_0.4/cmake-build-debug/mnist_train.csv");
std::string test_data("C:/Users/Carlo/CLionProjects/Progra3/DL_Proyect/Prototype_0.4/cmake-build-debug/mnist_test.csv");

void example_1() {
    Dataset data;
    data.load_data_from_csv(training_data, test_data);

    NeuralNetwork NN(3, {784, 28, 10}, 0.4);

    NN.epoch_training(100, data);
    NN.predict(data.get_test_example(100));

    NN.saveParameters();
}

void example_2() {
    Dataset data;
    data.load_data_from_csv(training_data, test_data);

    NeuralNetwork NN(3, {784, 28, 10}, 0.4);
    NN.loadParameters();
    NN.predict(data.get_test_example(100));
}

int main() {
    example_1();
    //example_2();

    return 0;
}
