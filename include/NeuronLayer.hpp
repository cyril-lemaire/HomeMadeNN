#ifndef __NEURONLAYER_HPP__
#define __NEURONLAYER_HPP__

#include <cstddef>
#include <array>
#include "Neuron.hpp"

class NeuronLayerBase {
public:
    template<class InputIterator, class OutputIterator>
    void activate(OutputIterator output, InputIterator input) const;
};

template<size_t size, size_t neuron_size>
class NeuronLayer: NeuronLayerBase {
protected:
    std::array<Neuron<neuron_size>, size> m_neurons;

public:
    template<class OutputIterator, class InputIterator, class ActivationFunc>
    void activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const;
};

template<size_t size, size_t neuron_size>
template<class OutputIterator, class InputIterator, class ActivationFunc>
void NeuronLayer<size, neuron_size>::activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const {
    for (auto const neuron: m_neurons) {
        *output = neuron.activate(input, activation);
        ++output;
    }
}

#endif // __NEURONLAYER_HPP__