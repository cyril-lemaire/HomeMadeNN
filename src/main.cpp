#include "NeuralNetwork.hpp"
#include "TicTacToe.h"
#include <array>
#include <map>
#include <algorithm>
#include <iostream>
#define DEBUG

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
class BrainTinder {
public:
    BrainTinder(void);
    std::array<double, pop_size> fitnesses(void) const;
    void breed(void);

protected:
    std::array<NeuralNetwork<input_size, hidden_size, output_size, hidden_count>, pop_size> m_pop;
    std::array<double, pop_size> m_scores;
    std::array<size_t, pop_size> m_matches;

    void crossover(
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p2,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c1,
        NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c2);
    void mutate(size_t index, double mutation_odd);
    void evaluate(size_t index);
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
std::array<double, pop_size> BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::fitnesses(void) const {
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
        m_scores[index] += p1_score.at(result);
        m_scores[op] += p2_score.at(result);
        result = match(m_pop[op], m_pop[index]);
        m_scores[index] += p2_score.at(result);
        m_scores[op] += p1_score.at(result);
        m_matches[index] += 2;
        m_matches[op] += 2;
    }
}

template<size_t pop_size, size_t input_size, size_t hidden_size, size_t output_size, size_t hidden_count>
void BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count>::breed(void) {
    NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p1 = nullptr;
    NeuralNetwork<input_size, hidden_size, output_size, hidden_count> const* p2 = nullptr;
    NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c1 = nullptr;
    NeuralNetwork<input_size, hidden_size, output_size, hidden_count> * c2 = nullptr;
    auto const fitnesses = this->fitnesses();
    double total_fitness = 0.0;
    double total_rev_fitness = 0.0;
    double cum_fitness;
    double cum_rev_fitness;

    for (size_t i = 0; i < pop_size; ++i) {
        total_fitness += fitnesses.at(i);
        total_rev_fitness += 1.0 / (1.0 + fitnesses.at(i));
    }
    double c1_rev_fit = std::rand() * total_rev_fitness;
    double c2_rev_fit = std::rand() * total_rev_fitness;
    double p1_fit = std::rand() * total_fitness;
    double p2_fit = std::rand() * total_fitness;

    for (size_t i = 0; i < pop_size; ++i) {
        cum_fitness += fitnesses.at(i);
        cum_rev_fitness += 1.0 / (1.0 + fitnesses.at(i));
        if (p1 == nullptr && cum_fitness >= p1_fit) {
            p1 = &m_pop[i];
        }
        if (p2 == nullptr && cum_fitness >= p2_fit) {
            p2 = &m_pop[i];
        }
        if (c1 == nullptr && cum_rev_fitness >= c1_rev_fit) {
            c1 = &m_pop[i];
        }
        if (c2 == nullptr && cum_rev_fitness >= c2_rev_fit) {
            c2 = &m_pop[i];
        }
    }
}

int main(int argc, char **argv) {
    constexpr size_t pop_size = 1024;
    constexpr size_t input_size = 18;
    constexpr size_t hidden_size = 32;
    constexpr size_t output_size = 9;
    constexpr size_t hidden_count = 1;

    BrainTinder<pop_size, input_size, hidden_size, output_size, hidden_count> tinder;
    
    while (true) {
        tinder.breed();

#ifdef DEBUG
        auto fitnesses = tinder.fitnesses();
        std::sort(std::begin(fitnesses), std::end(fitnesses));
        std::cout << std::max_element(std::begin(fitnesses), std::end(fitnesses));
#endif // DEBUG
    }
    return 0;
}