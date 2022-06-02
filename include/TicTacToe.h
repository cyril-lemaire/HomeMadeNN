#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

#include <array>
#include <cstddef>

enum Cell {
    P1, P2, NONE
};

class TicTacToe {
private:
    std::array<Cell, 9> m_board;
    Cell m_winner;

public:
    TicTacToe(void);

    bool play(Cell player, size_t index);
    Cell getWinner(Cell player, size_t index) const;
    bool isOver(Cell player, size_t index) const;
    void reset(void);
};


#endif // __TICTACTOE_H__