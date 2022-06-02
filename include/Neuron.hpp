#ifndef __NEURON_HPP__
#define __NEURON_HPP__

#include <cstddef>
#include <array>
#include <cmath>
#include <cstdlib>

template<size_t size>
class Neuron {
protected:
    std::array<double, size> m_weights;
    double m_bias;
    double m_variability;

public:
    Neuron(void);
    Neuron(std::array<double, size> weights, double bias);

    template<class InputIterator, class ActivationFunc>
    double activate(InputIterator & input, ActivationFunc activation) const;

    /**
     * Update weights based on delta of target layer and outputs of source layer
     * ∆w[j, k] = −η*δ[k]*o[j]
     */
    template<class InputIterator>
    void backpropagate(double delta, InputIterator & input, double learning_rate);
    void mutate(double mutation_odd);
};

struct sigmoid {
    double operator()(double x);
};

struct relu {
    constexpr double operator()(double x);
};

double sigmoid::operator()(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

constexpr double relu::operator()(double x) {
    return (x < 0.0) ? 0.0 : x;
}

template<size_t size>
Neuron<size>::Neuron(void): m_variability(1.0) {
    for (size_t i = 0; i < size; ++i) {
        m_weights[i] = static_cast<double>(rand()) * sqrt(size) / RAND_MAX;
    }
    m_bias = static_cast<double>(rand()) / RAND_MAX;
}

template<size_t size>
Neuron<size>::Neuron(std::array<double, size> weights, double bias): m_weights(weights), m_bias(bias), m_variability(1.0) {}


template<size_t size>
template<typename InputIterator, typename ActivationFunc>
double Neuron<size>::activate(InputIterator & input, ActivationFunc activation) const {
    double raw = m_bias;
    for (size_t i = 0; i < size; ++i, ++input) {
        raw += m_weights[i] * *input;
    }
    return activation(raw);
}

template<size_t size>
template<class InputIterator>
void Neuron<size>::backpropagate(double delta, InputIterator & input, double learning_rate) {
    for (size_t i = 0; i < size; ++i, ++input) {
        m_weights[i] += -learning_rate * delta * *input;
    }
    m_bias += -learning_rate * delta;
}

template<size_t size>
void Neuron<size>::mutate(double mutation_odd) {
    for (size_t i = 0; i < size; ++i, ++input) {
        if (std::rand() < mutation_odd * RAND_MAX) {
            m_weights[i] += static_cast<double>(std::rand()) / RAND_MAX - 0.5;
        }
    }
    if (std::rand() < mutation_odd * RAND_MAX) {
        m_bias += static_cast<double>(std::rand()) / RAND_MAX - 0.5;
    }
    ++input;
}

#endif // __NEURON_HPP__