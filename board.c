#include <stdlib.h>
#include <stdio.h>
#include <time.h> // rand\srand
#include "board.h"

/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author Emma Croq
 */



/**@{
* \name Definition structure
*/

typedef struct{
    player pieces[4];
} location;


struct board_s{
    location board[3][3]; 
};

/**@}*/




/**@{
 * \name Creation/deletion functionalities.
 */

player next_player(player current_player){
    if (current_player == PLAYER_2) return PLAYER_1;
    else return PLAYER_2;
}


board new_game(){
    // memory allocation for the board (leave it as is)
    board new_board = malloc(sizeof(struct board_s));
    return new_board;
}


board copy_game(board game){
    return game;
}


void destroy_game(board game){
    for(int i=0; i<3; i++){ 
        for(int j = 0; j<3; j++){
            for(int k = 0; k<3; k++){
                (*game).board[i][j].pieces[k] = NONE;   // réinitialise le plateau

            }
        }
    }
    // freeing memory, necessary for memory allocated with malloc (leave as is)
    free(game);
}

/**@}*/




/**@{
 * \name Accessing game data functionalities.
 */

player get_place_holder(board game, int line, int column){
    int i = 3;
    player status = NO_PLAYER;
    for (int i = 0; i < 4; i++) {
        if ((*game).board[line][column].pieces[i-1] != NONE){   //      Regarde s'il y a une pièce
            status = (*game).board[line][column].pieces[i-1];   //      1 ou 2 comme valeur
        }
    }
    return status;
}


size get_piece_size(board game, int line, int column){
    size result = NONE;
    for (int i = 0; i < 3; i++) {
        if ((*game).board[line][column].pieces[i] != NONE) {    //      La valeur dans pieces[i]=0
            result = i+1;
        }
    }
    return result;
}

int verif(player winner, board game, int lig1, int colA, int lig2, int colB, int lig3, int colC){
        //  Verifie case 1 non nul, puis compare case1=case2 et case2=case3
    if (get_place_holder(game, lig1, colA) != NONE && get_place_holder(game, lig1, colA) == get_place_holder(game, lig2, colB) && get_place_holder(game, lig2, colB) == get_place_holder(game, lig3, colC)) {
        if (winner == 0){
            winner = get_place_holder(game, lig1, colA);
        }else if( get_place_holder(game, lig1, colA) != winner ){
            winner = 0;
        }
    }
    return winner;
}


player get_winner(board game){
    player winner = NO_PLAYER;
        for (int i = 0; i < 3; i++){
            winner = verif (winner, game, i, 0, i, 1, i, 2);    //      Verifie les lignes
            winner = verif (winner, game, 0, i, 1, i, 2, i);    //      Verifie les colonnes
        }
        winner = verif (winner, game, 0, 0, 1, 1, 2, 2);
        winner = verif (winner, game, 0, 2, 1, 1, 2, 0);    //      Verifie les deux diagonales
    return winner;
}


int get_nb_piece_in_house(board game, player checked_player, size piece_size){
    int n = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){    //      Teste toutes les cases
            if ((*game).board[i][j].pieces[piece_size-1] == checked_player){   //  Donc renvoie le nombre de pièces de la taille donnée qu'il reste dans la maison du joueur donné
                n++;
            }
        }
    }
    return NB_INITIAL_PIECES-n;
}

/**@}*/




/**@{
 * \name Playing functionalities
 */

int place_piece(board game, player current_player, size piece_size, int line, int column){
    int endResult;
    if (line < 3 && column < 3){
        if (get_nb_piece_in_house(game, current_player, piece_size) <= 2) {
            if (piece_size > get_piece_size(game, line, column)) {
                (*game).board[line][column].pieces[piece_size-1] = current_player;
                endResult = 0;      //      Si cela fonctionne
            }else{  //  Sinon liste les erreurs
                endResult = 1;
            }
        }else{
            endResult = 2;
        }
    }else {
        endResult = 3;
    }
    return endResult;
}



int move_piece(board game, int source_line, int source_column, int target_line, int target_column){
    int endResult;
    if (source_column < 3 && source_line < 3 && target_column < 3 && target_line < 3) {     //      Prise en compte de la case d'origine
        if (get_piece_size(game, source_line, source_column) != 0){
            if (get_piece_size(game, source_line, source_column) > get_piece_size(game, target_line, target_column)) {
                (*game).board[target_line][target_column].pieces[get_piece_size(game, source_line, source_column)-1] = (*game).board[source_line][source_column].pieces[get_piece_size(game, source_line, source_column)-1];
                (*game).board[source_line][source_column].pieces[get_piece_size(game, source_line, source_column)-1] = 0;
                endResult = 0;      //      Si cela fonctionne
            }else {      //  Sinon liste les erreurs
                endResult = 1;
            }
        }else {
            endResult = 2;
        }
    }else {
        endResult = 3;
    }
    return endResult;
}

/**@}*/


/**@{
 * \name My own fonctionalities
 */

void spaces(int nbr){   //  Espaces 
    for (int i = 0; i < nbr; i++)
    {
        printf(" ");
    }
}
void line_break(int nbr){   //  Saut de ligne
    for (int i = 0; i < nbr; i++)
    {
        printf("\n");
    }
}


int verifier(player current_player, board game, int lig1, int colA, int lig2, int colB, int lig3, int colC){    //  regarde si il y a deux pieces d'un même joueur sur une ligne, colonne ou diagonal

    if (get_place_holder(game, lig1, colA) == get_place_holder(game, lig3, colC)) {     //  case 1 = case 3
        return (get_place_holder(game, lig1,colA));
    }else if (get_place_holder(game, lig1, colA) == get_place_holder(game, lig2, colB)){    //  case 1 = case 2
        return (get_place_holder(game, lig1,colA)); 
    }else if (get_place_holder(game, lig2, colB) == get_place_holder(game, lig3, colC)){    // case 2 = case 3
        return (get_place_holder(game, lig1,colA));
    }else
        return NO_PLAYER;
}

player Test_de_ligne(player current_player, board game, int lig1, int colA, int lig2, int colB, int lig3, int colC){
    if(verifier (current_player, game, lig1, colA, lig2, colB, lig3, colC)== current_player){
        if (get_place_holder(game, lig1,colA)==current_player){
           if (place_piece==0){     // s'il arrive a placer une piece et que ça ne renvoie pas d'erreur
                return 1;   // retourne 1 pour dire qu'il a réussi (dans main)
            } 
        }
        if (get_place_holder(game, lig2,colB)==current_player){
           if (place_piece==0){
                return 1;
            } 
        }
        if (get_place_holder(game, lig3,colC)==current_player){
           if (place_piece==0){
                return 1;
            } 
        }
    }
}

player DeuxPieces(board game){

        /*  Analyse du joueur 2, le bot, pour savoir s'il peut gagner  */

        //pour les lignes
    Test_de_ligne(PLAYER_2, game, 1, 1, 1, 2, 1, 3);
    Test_de_ligne(PLAYER_2, game, 2, 1, 2, 2, 2, 3);
    Test_de_ligne(PLAYER_2, game, 3, 1, 3, 2, 3, 3);
        // pour les colonnes
    Test_de_ligne(PLAYER_2, game, 1, 1, 2, 1, 3, 1);
    Test_de_ligne(PLAYER_2, game, 1, 2, 2, 2, 3, 2);
    Test_de_ligne(PLAYER_2, game, 1, 3, 2, 3, 3, 3);
        // pour les diagonales
    Test_de_ligne(PLAYER_2, game, 1, 1, 2, 2, 3, 3);
    Test_de_ligne(PLAYER_2, game, 1, 3, 2, 2, 3, 1);


        /*  Analyse du joueur 1, pour savoir s'il peut le bloquer  */

        //pour les lignes
    Test_de_ligne(PLAYER_1, game, 1, 1, 1, 2, 1, 3);
    Test_de_ligne(PLAYER_1, game, 2, 1, 2, 2, 2, 3);
    Test_de_ligne(PLAYER_1, game, 3, 1, 3, 2, 3, 3);
        // pour les colonnes
    Test_de_ligne(PLAYER_1, game, 1, 1, 2, 1, 3, 1);
    Test_de_ligne(PLAYER_1, game, 1, 2, 2, 2, 3, 2);
    Test_de_ligne(PLAYER_1, game, 1, 3, 2, 3, 3, 3);
        // pour les diagonales
    Test_de_ligne(PLAYER_1, game, 1, 1, 2, 2, 3, 3);
    Test_de_ligne(PLAYER_1, game, 1, 3, 2, 2, 3, 1);


    return 0;

}

/**@}*/

