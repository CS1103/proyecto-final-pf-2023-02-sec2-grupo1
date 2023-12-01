//
// Created by Carlo on 11/30/2023.
//

#include "Dataset.h"

Dataset::Dataset() = default;

template<template<typename...> class Container>
Dataset::Dataset(const Container<double>& trn_d, const Container<double>& tst_d, const Container<double>& val_d) : training_data(trn_d), test_data(tst_d), validation_data(val_d) {}

Dataset::~Dataset() = default;

void Dataset::load_data_from_csv(const std::string& trn_d, const std::string& tst_d, const std::string& val_d) {
    auto load_csv = [](const std::string& file_path, std::vector<std::pair<std::vector<double>, label>>& data) {
        std::ifstream in_stream(file_path);
        std::string line;
        if (!in_stream.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + file_path);
        }

        // Leer y descartar la primera línea (encabezados)
        std::getline(in_stream, line);

        while (std::getline(in_stream, line)) {
            std::stringstream line_stream(line);
            std::string cell;
            std::vector<double> pixels;
            label lbl;

            // Leer la etiqueta
            std::getline(line_stream, cell, ',');
            lbl = std::stoi(cell);

            // Leer los valores de los píxeles
            while (std::getline(line_stream, cell, ',')) {
                pixels.push_back(std::stod(cell) / 255.0); // Normalizar los valores de los píxeles
            }

            data.emplace_back(pixels, lbl);
        }
    };

    load_csv(trn_d, training_data);

    load_csv(tst_d, test_data);

    if (!val_d.empty())
        load_csv(val_d, validation_data);
}

std::pair<std::vector<double>,label> Dataset::get_training_example(const size_t& idx) const {
    return training_data[idx];
}
std::pair<std::vector<double>,label> Dataset::get_test_example(const size_t& idx) const {
    return test_data[idx];
}
std::pair<std::vector<double>,label> Dataset::get_validation_example(const size_t& idx) const {
    return validation_data[idx];
}

size_t Dataset::get_training_size() const {
    return training_data.size();
}
size_t Dataset::get_test_size() const {
    return test_data.size();
}
size_t Dataset::get_validation_size() const {
    return validation_data.size();
}

void Dataset::leer_imagen_2predict(const std::string& path) {
    // Cargar la imagen
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR); // Cargar como imagen en color
    if (img.empty()) {
        throw std::runtime_error("No se pudo cargar la imagen.");
    }

    // Convertir a escala de grises si es necesario
    cv::Mat img_gray;
    if (img.channels() > 1) {
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    } else {
        img_gray = img; // La imagen ya está en escala de grises
    }

    // Normalizar y almacenar los píxeles
    image_2b_predicted.clear();
    img_gray.convertTo(img_gray, CV_64F, 1.0 / 255); // Convierte a double y normaliza

    for (int i = 0; i < img_gray.rows; ++i) {
        for (int j = 0; j < img_gray.cols; ++j) {
            image_2b_predicted.push_back(img_gray.at<double>(i, j));
        }
    }
}