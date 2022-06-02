#ifndef __NEURALNETWORK_HPP__
#define __NEURALNETWORK_HPP__

#include <cstddef>
#include <array>
#include "NeuralLayer.hpp"
#include <memory>

/**
 * @brief A Neural Network with simple possibilities
 * 
 * @tparam input_size
 * @tparam hidden_size
 * @tparam output_size
 */
template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
class NeuralNetwork {
protected:
    std::array<std::shared_ptr<NeuralLayerBase>, hidden_count + 1> m_layers;

public:
    NeuralNetwork(void);

    template<class OutputIterator, class InputIterator, class ActivationFunc>
    void activate(OutputIterator & output, InputIterator & input, ActivationFunc activation) const;

    /**
     * Delta of hidden layer based on its output, weights to next layer and next layer's delta
     * δ[j] = o[j]*(1 - o[j]) * (δ[k1]*w[j, k1] + δ[k2]*w[j, k2] + ... + δ[kn]*w[j, kn])
     */
    template<class OutputIterator, class InputIterator>
    static void hidden_deltas(OutputIterator & deltas, InputIterator & next_deltas,
                       InputIterator outputs);
    /**
     * Delta of output layer based on its output and the expected output (supervised learning)
     * delta[k] = outputs[k] * (1 - outputs[k]) * (outputs[k] - expected[k])
     * δ[k] = o[k] * (1 - o[k]) * (o[k] - tk)
     */
    static void output_deltas(vector<double> & deltas, vector<double> const& outputs, vector<double> const& expected);
};

template<size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
NeuralNetwork<input_size, hidden_size, output_size, hidden_count>::NeuralNetwork(void) {
    if constexpr (hidden_count == 0) {
        // One-Layer network
        m_layers.front() = new NeuralLayer<output_size, input_size>();
    } else {
        m_layers.front() = new NeuralLayer<hidden_size, input_size>();
        for (size_t i = 0; i < hidden_count - 1; ++i) {
            m_layers[i+1] = new NeuralLayer<hidden_size, hidden_size>();
        }
        m_layers.back() = new NeuralLayer<output_size, hidden_size>();
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