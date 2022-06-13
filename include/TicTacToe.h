#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

#include <array>
#include <cstddef>

enum Player {
    P1, P2, NONE
};

enum ActionBase {    
};

struct TicTacToeAction {
    Player p;
    size_t cell;
};

class GameBase {
public:
    bool play(ActionBase * action);
    Player get_winner(void) const;
    bool is_over(void) const;
    void reset(void);
};

class TicTacToe: public GameBase {
private:
    std::array<Player, 9> m_board;
    Player m_winner;

public:
    TicTacToe(void);

    bool play(Player player, size_t index);
    Player get_winner(void) const;
    bool is_over(void) const;
    void reset(void);
};


#endif // __TICTACTOE_H__