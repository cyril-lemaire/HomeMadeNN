#ifndef __NEURALLAYER_HPP__
#define __NEURALLAYER_HPP__

#include <cstddef>
#include <array>
#include "Neuron.hpp"

class NeuralLayerBase {
public:
    template<class InputIterator, class OutputIterator>
    void activate(OutputIterator output, InputIterator input) const;
    NeuronBase* operator[](size_t index);
    void mutate(double mutation_odd);
};

template<size_t size, size_t neuron_size>
class NeuralLayer: public NeuralLayerBase {
protected:
    std::array<Neuron<neuron_size>, size> m_neurons;

public:
    template<class OutputIterator, class InputIterator, class ActivationFunc>
    void activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const;
    NeuronBase* operator[](size_t index);
    void mutate(double mutation_odd);
};

template<size_t size, size_t neuron_size>
template<class OutputIterator, class InputIterator, class ActivationFunc>
void NeuralLayer<size, neuron_size>::activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const {
    for (auto const neuron: m_neurons) {
        *output = neuron.activate(input, activation);
        ++output;
    }
}

template<size_t size, size_t neuron_size>
NeuronBase* NeuralLayer<size, neuron_size>::operator[](size_t index) {
    return &m_neurons[index];
}

template<size_t size, size_t neuron_size>
void NeuralLayer<size, neuron_size>::mutate(double mutation_odd) {
    for (Neuron<neuron_size> & n: m_neurons) {
        n.mutate(mutation_odd);
    }
}

#endif // __NEURALLAYER_HPP__