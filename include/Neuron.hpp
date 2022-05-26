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

public:
    Neuron(void);
    Neuron(std::array<double, size> weights, double bias);

    template<class InputIterator, class ActivationFunc>
    double activate(InputIterator & input, ActivationFunc activation) const;
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
Neuron<size>::Neuron(void): m_bias(0) {
    for (size_t i = 0; i < size; ++i) {
        m_weights[i] = static_cast<double>(rand()) * sqrt(size) / RAND_MAX;
    }
}

template<size_t size>
Neuron<size>::Neuron(std::array<double, size> weights, double bias): m_weights(weights), m_bias(bias) {}


template<size_t size>
template<typename InputIterator, typename ActivationFunc>
double Neuron<size>::activate(InputIterator & input, ActivationFunc activation) const {
    double raw = m_bias;
    for (size_t i = 0; i < size; ++i, ++input) {
        raw += m_weights[i] * *input;
    }
    return activation(raw);
}

#endif // __NEURON_HPP__