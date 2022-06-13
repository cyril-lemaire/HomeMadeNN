#ifndef __NEURALNETWORK_HPP__
#define __NEURALNETWORK_HPP__

#include <cstddef>
#include <array>
#include "NeuralLayer.hpp"
#include <memory>

class NeuralNetworkBase {
public:
    template<class OutputIterator, class InputIterator, class ActivationFunc>
    void activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const;
    std::unique_ptr<NeuralLayerBase> & operator[](size_t index);
    void mutate(double mutation_odd);
};

/**
 * @brief A Neural Network with simple possibilities
 * 
 * @tparam input_size
 * @tparam hidden_size
 * @tparam output_size
 */
template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
class NeuralNetwork: public NeuralNetworkBase {
protected:
    std::array<std::unique_ptr<NeuralLayerBase>, hidden_count + 1> m_layers;

public:
    NeuralNetwork(void);

    template<class OutputIterator, class InputIterator, class ActivationFunc>
    void activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const;
    NeuralLayerBase* operator[](size_t index);
    void mutate(double mutation_odd);
};

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::NeuralNetwork(void) {
    if constexpr (hidden_count == 0) {
        // One-Layer network
        m_layers.front() = std::make_unique<NeuralLayer<output_size, input_size>>();
    } else {
        m_layers.front() = std::make_unique<NeuralLayer<hidden_size, input_size>>();
        for (size_t i = 0; i < hidden_count - 1; ++i) {
            m_layers[i+1] = std::make_unique<NeuralLayer<hidden_size, hidden_size>>();
        }
        m_layers.back() = std::make_unique<NeuralLayer<output_size, hidden_size>>();
    }
}

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
template<class OutputIterator, class InputIterator, class ActivationFunc>
void NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const {
    for (NeuralLayerBase const* layer: m_layers) {
        layer->activate(output, input, activation);
    }
}

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
NeuralLayerBase* NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::operator[](size_t index) {
    return m_layers[index];
}

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::mutate(double mutation_odd) {
    for (NeuralLayerBase * layer: m_layers) {
        layer->mutate(mutation_odd);
    }
}

#endif // __NEURALNETWORK_HPP__