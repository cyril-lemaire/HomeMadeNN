#include "NeuralNetwork.hpp"

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
class BrainTinder {
protected:
    std::array<std::unique_ptr<NeuralNetwork<input_size, hidden_size, output_size, hidden_count>>, pop_size> m_pop;
    void crossover(
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p2,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c2);
    void mutate(size_t index, double mutation_odd);

public:
    void evaluate(void);
    void breed(void);
};

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::crossover(
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p2,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c2) {
    
}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::mutate(size_t index, double mutation_odd) {
    m_pop[index].mutate(mutation_odd);
}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::evaluate(void) {

}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::breed(void) {
    
}

int main(int argc, char **argv) {
    constexpr size_t pop_size = 256;
    constexpr size_t input_size = 18;
    constexpr size_t hidden_size = 32;
    constexpr size_t output_size = 9;
    constexpr size_t hidden_count = 1;
    BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count> tinder;
    
    while (true) {
        tinder.evaluate();
        tinder.breed();
    }
    return 0;
}