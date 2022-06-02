#include "TicTacToe.h"
#include <vector>
#include <cstdint>

TicTacToe::TicTacToe(void): m_winner(Cell::NONE)
{
    std::fill(std::begin(m_board), std::end(m_board), Cell::NONE);
}

Cell TicTacToe::getWinner(Cell player, size_t index) const
{
    return m_winner;    
}

bool TicTacToe::isOver(Cell player, size_t index) const
{
    if (m_winner != Cell::NONE) {
        return true;
    }
    for (Cell c: m_board) {
        if (c == Cell::NONE) {
            return false;
        }
    }
    return true;
}

bool TicTacToe::play(Cell player, size_t index)
{
    static std::vector<std::vector<uint8_t>> lines {

    }
    if (index >= m_board.size() || m_board[index] != Cell::NONE || player == Cell::NONE) {
        return false;
    }
    m_board[index] = player;

}

void TicTacToe::reset(void)
{
    std::fill(std::begin(m_board), std::end(m_board), Cell::NONE);
    m_winner = Cell::NONE;
}