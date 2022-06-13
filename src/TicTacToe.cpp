#include "TicTacToe.h"
#include <vector>
#include <cstdint>

TicTacToe::TicTacToe(void): m_winner(Player::NONE) {
    std::fill(std::begin(m_board), std::end(m_board), Player::NONE);
}

Player TicTacToe::get_winner(void) const {
    return m_winner;    
}

bool TicTacToe::is_over(void) const {
    if (m_winner != Player::NONE) {
        return true;
    }
    for (Player c: m_board) {
        if (c == Player::NONE) {
            return false;
        }
    }
    return true;
}

bool TicTacToe::play(Player player, size_t index) {
    static const std::vector<std::vector<std::array<uint8_t, 2>>> lines {
        {
            {1, 2}, {3, 6}, {4, 8},
        },{
            {0, 2}, {4, 7},
        },{
            {0, 1}, {4, 6}, {5, 8},
        },{
            {0, 6}, {4, 5},
        },{
            {0, 8}, {1, 7}, {2, 6}, {3, 5},
        },{
            {2, 8}, {3, 4},
        },{
            {0, 3}, {2, 4}, {7, 8},
        },{
            {1, 4}, {6, 8},
        },{
            {0, 4}, {2, 5}, {6, 7},
        }
    };

    if (index >= m_board.size() || m_board[index] != Player::NONE || player == Player::NONE) {
        return false;
    }
    m_board[index] = player;
    for (auto const& line: lines[index]) {
        if (m_board[line[0]] == player && m_board[line[1]] == player) {
            m_winner = player;
            break;
        }
    }
    return true;
}

void TicTacToe::reset(void) {
    std::fill(std::begin(m_board), std::end(m_board), Player::NONE);
    m_winner = Player::NONE;
}