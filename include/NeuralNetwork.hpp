#ifndef __NEURALNETWORK_HPP__
#define __NEURALNETWORK_HPP__

#include <cstddef>
#include <array>
#include "NeuronLayer.hpp"
#include <memory>

/**
 * @brief A Neural Network with simple possibilities
 * 
 * @tparam input_size 
 * @tparam hidden_size 
 * @tparam output_size 
 * @tparam hidden_count Must be at least 1
 */
template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
class NeuralNetwork {
protected:
    std::array<std::shared_ptr<NeuronLayerBase>, hidden_count + 1> m_layers;

public:
    NeuralNetwork(void);

    template<class OutputIterator, class InputIterator, class ActivationFunc>
    void activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const;
};
template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::NeuralNetwork(void) {
    if constexpr (hidden_count == 0) {
        // One-Layer network
        m_layers.front() = new NeuronLayer<output_size, input_size>();
    } else {
        m_layers.front() = new NeuronLayer<hidden_size, input_size>();
        for (size_t i = 0; i < hidden_count - 1; ++i) {
            m_layers[i+1] = new NeuronLayer<hidden_size, hidden_size>();
        }
        m_layers.back() = new NeuronLayer<output_size, hidden_size>();
    }
}
template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
template<class OutputIterator, class InputIterator, class ActivationFunc>
void NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const {
    for (auto const layer: m_layers) {
        layer.activate(output, input, activation);
    }
}

#endif // __NEURALNETWORK_HPP__