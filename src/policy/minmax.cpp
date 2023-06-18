#include <cstdlib>
#include <iostream>
#include "../state/state.hpp"
#include "./minmax.hpp"

//int tes=0;
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 * 
 */
int playertempp;
Move minmax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
    playertempp=state->player;
   // int val=makechild(state,depth,0);
   depth=4;
  // std::cout << "PLAYER "<< state->player << std::endl;

    makechild(state,depth,state->player);
   // std::cout << "STATE VALUE: "<<state->statevalue << std::endl;
   // std::cout << "TES: " <<tes << std::endl;
    return state->subtree->curr;
}

int minmax::makechild(State *state, int depth, int player) {
    //std::cout << "ASMDFSDF" << std::endl;
       // tes++;

   
    if (state->legal_actions.size()<=0)
        state->get_legal_actions();
    if (state->legal_actions.size() == 0) return state->evaluate();
    if(state->game_state==WIN){
         //return player==0 ? 500:-500;
    }
     if (depth == 0){
        int eval=state->evaluate();
         return eval;
    }
    if (player == 0) {
        int max = -10000000;
        for (auto i : state->legal_actions) {

            State* tmp = state->next_state(i);
            tmp->player=1;
            int val = makechild(tmp, depth - 1, 1);
            if (val > max){ 
                //std::cout << "val: "<< val  << " depth: "<< depth  << " player: " << player<< std::endl;
                if(state->subtree)delete state->subtree;
                max = val;
                state->subtree=tmp;
                state->statevalue = max;
                             //   std::cout << "max: " << max << std::endl;
            }else{
               delete tmp;

            }
        }
        return max;
    } else {
        int min = 10000000;
        for (auto i : state->legal_actions) {
            State* tmp = state->next_state(i);
            tmp->player=0;
            int val = makechild(tmp, depth - 1, 0);
            if (val < min) {
              //  std::cout << "val: "<< val  << " depth: "<< depth  << " player: " << player<< std::endl;
                if(state->subtree)delete state->subtree;
                min = val;
                state->subtree=tmp;
                state->statevalue = min;
              //  std::cout << "min: " << min << std::endl
            }else{
                delete tmp;
            }
        }
                
        return min;
    }
}
  