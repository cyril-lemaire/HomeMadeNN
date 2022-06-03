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
    NeuralLayerBase * operator[](size_t index);
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
    std::array<std::shared_ptr<NeuralLayerBase>, hidden_count + 1> m_layers;

public:
    NeuralNetwork(void);

    template<class OutputIterator, class InputIterator, class ActivationFunc>
    void activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const override;
    shared_ptr<NeuralLayerBase> operator[](size_t index) override;
};

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::NeuralNetwork(void) {
    if constexpr (hidden_count == 0) {
        // One-Layer network
        m_layers.front().reset(new NeuralLayer<output_size, input_size>());
    } else {
        m_layers.front().reset(new NeuralLayer<hidden_size, input_size>());
        for (size_t i = 0; i < hidden_count - 1; ++i) {
            m_layers[i+1].reset(new NeuralLayer<hidden_size, hidden_size>());
        }
        m_layers.back().reset(new NeuralLayer<output_size, hidden_size>());
    }
}

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
template<class OutputIterator, class InputIterator, class ActivationFunc>
void NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const {
    for (auto const layer: m_layers) {
        layer.activate(output, input, activation);
    }
}

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
std::shared_ptr<NeuralLayerBase> operator[](size_t index) {
    return m_layers[index];
}

#endif // __NEURALNETWORK_HPP__