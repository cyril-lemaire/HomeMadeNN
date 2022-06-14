#include "NeuralNetwork.hpp"
#include "TicTacToe.h"
#include <array>
#include <map>
#include <algorithm>
#include <iostream>

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
class BrainTinder {
protected:
    BrainTinder(void);
    std::array<std::unique_ptr<NeuralNetwork<input_size, hidden_size, output_size, hidden_count>>, pop_size> m_pop;
    std::array<double, pop_size> m_scores;
    std::array<size_t, pop_size> m_matches;

    void crossover(
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p2,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c2);
    void mutate(size_t index, double mutation_odd);

public:
    std::array<double, pop_size> fitnesses(void) const;
    void evaluate(void);
    void breed(void);
};
template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::BrainTinder(void): m_scores{0.0}, m_matches{0} {
    for (size_t i = 0; i < pop_size; ++i) {
        evaluate(i);
    }
}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::crossover(
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p2,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c2) {
    (void)(p1);
    (void)(p2);
    (void)(c1);
    (void)(c2);
}
template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::std::array<double, pop_size> fitnesses(void) const {
    std::array<double, pop_size> f;
    for (size_t i = 0; i < pop_size; ++i) {
        f[i] = m_scores[i] / m_matches[i];
    }
    return f;
}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::mutate(size_t index, double mutation_odd) {
    m_pop[index].mutate(mutation_odd);
}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::evaluate(size_t index) {
    Player result;
    const std::map<Player, double> p1_score {{Player::P1, 1}, {Player::P2, 0}, {Player::NONE, 0.5}};
    const std::map<Player, double> p2_score {{Player::P1, 0}, {Player::P2, 1}, {Player::NONE, 0.5}};

    for (size_t op = 0; op < pop_size; ++op) {
        if (op == index) {
            continue;
        }
        result = match(m_pop[index], m_pop[op]);
        m_fitnesses[index] += p1_score[result];
        m_fitnesses[op] += p2_score[result];
        result = match(m_pop[op], m_pop[index]);
        m_fitnesses[index] += p2_score[result];
        m_fitnesses[op] += p1_score[result];
        m_matches[index] += 2;
        m_matches[op] += 2;
    }
}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::breed(void) {
    auto fitnesses = this->fitnesses();
    double total_fitness = 0.0;
    double total_rev_fitness = 0.0;
    for (size_t i = 0; i < pop_size; ++i) {
        total_fitness += fitnesses[i];
        total_rev_fitness += 1.0 / (1.0 + fitnesses[i]);
    }
    double c1_rev_fit = std::rand() * total
}

int main(int argc, char **argv) {
    constexpr size_t pop_size = 256;
    constexpr size_t input_size = 18;
    constexpr size_t hidden_size = 32;
    constexpr size_t output_size = 9;
    constexpr size_t hidden_count = 1;
    BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count> tinder;
    
    while (true) {
        tinder.breed();
        cout << std::max_element(tinder.fitnesses());
    }
    return 0;
}