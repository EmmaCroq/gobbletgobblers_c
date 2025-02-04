#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdbool.h>

/**
 * \file board.h
 *
 * \brief Gobblet game engine functions.
 *
 * In this file, all the function for having a game of gobblets or of gobblet-gobblers 
 * run are defined.
 *  
 * \author Dorbec
 *
 */

/**
 * \mainpage Project 2019-2020 for IUT Grand Ouest Normandie, computer science department
 * \section descritpion Description of the project
 * This project is aimed to implement a two players game, 
 * close to the Tic-Tac-Toe game. 
 * The rules of the games are described below.
 * 
 * The project is divided into various files. Mostly, the engine of the game,
 * implementing the detailed rules, is provided in the files board.c and board.h
 *
 * \section rules Detailed rules of the game.
 * 
 * The game is played by two players on a three by three squares board, 
 * though variants may be played on larger boards.
 * Each player has control of a set of six pieces whose owner is easily 
 * identifiable, for example by the shape or the color of the piece.
 * The pieces are of three different
 * sizes (big, medium, small), each player having two of each size. 
 * 
 * During the course of the game, players alternately make a move that consists 
 * in either:
 * - adding a piece from their collection on the board.
 * - moving one of his visible pieces already on the board to another square.
 * 
 * A piece can be placed either on an empty square, 
 * or on a square containing only smaller pieces, 
 * independently of who owns the piece.
 * In that latter case, the piece covers and hide the smaller pieces.
 * When a piece placed over other pieces is moved from a square, 
 * the largest piece covered is revealed and can be played in a later turn.
 * 
 * The game is won by the first player who manages to make a visible line of 
 * his pieces across the board (on a line, a column, 
 * or a diagonal, like for Tic-Tac-Toe.)
 *
 */

/**
 * @brief Game dimension.
 *
 * For being general in terms of dimensions,
 * they are defined in a general parameter.
 * In the following, all indices are given from 0 to DIMENSIONS - 1.
 */
#define DIMENSIONS 3

/**
 * @brief Pointer to the structure that holds the game. 
 *
 * Details of the content are not necessary for its use, so the structure is not 
 * included here.
 */
typedef struct board_s* board;

/**
 * @brief the different sizes of pieces.
 *
 * This set includes reference to an 'empty' size, for representing no piece at all. 
 * They are ordered by increasing size, so that they canbe compared with < or >.
 */
enum sizes_e {NONE, SMALL, MEDIUM, LARGE};

/**
 * @brief the different sizes of pieces.
 *
 * This also includes a empty size for having a same type when there is no piece 
 * in a place.
 */
typedef enum sizes_e size;

/**
 * @brief number of sizes for robustness if the enumeration is modified.
 */
#define NB_SIZE 3

/**
 * @brief the different players for further reference. 
 * NONE is used when informing that a square is empty.
 */
enum players_e {NO_PLAYER, PLAYER_1, PLAYER_2};

typedef enum players_e player;

/**
 * @brief number of players in the game.
 */
#define NB_PLAYERS 2

/**
 * @brief return the next player
 * 
 * @param player the player to change
 * @return the next player
 */
player next_player(player current_player);

/**
 * @brief number of pieces of each size per player at the beginning.
 */
#define NB_INITIAL_PIECES 2

/**@{
 * \name Creation/deletion functionalities.
 */

/**
 * @brief Defines a new empty board for starting a game of gobblet-gobblers.
 */
board new_game();

/**
 * @brief Makes a deep copy of the game.
 * @param original_game the game to copy.
 * @return a new copy fully independent of the original game.
 */
board copy_game(board original_game);

/**
 * @brief Delete the game and frees all required memory.
 * @param game the game to destroy.
 */
void destroy_game(board game);

/**@}*/

/**@{
 * \name Accessing game data functionalities.
 */

/**
 * @brief returns the player holding the indicated place.
 * @param game the game from which to collect information
 * @param line the line number
 * @column column the columne number
 * @return the player holding the biggest piece of that square, NONE if no player
 * is holding the place or if the request is misplaced.
 */

player get_place_holder(board game, int line, int column);

/**
 * @brief returns the visible piece size.
 * @param game the game from which to collect information.
 * @param line the line number.
 * @param column the column number.
 * @return the size of the holding piece, or NONE if there are no pieces on the board or is the request is misplaced.
 */
size get_piece_size(board game, int line, int column);

/**
 * @brief Tells if the game has a winner
 *
 * Recall that winning condition is to have a full row, column or diagonal covered with visible pieces.
 * If both players fulfill the winning condition, this function returns NO_PLAYER.
 * One possible interpretation is that the game should continue until only 
 * one player is winning.
 * @param game the game to test.
 * @return the player index or NO_PLAYER depending on who wins.
 */
player get_winner(board game);

/**
 * @brief Collect data about the pieces in a player's house.
 * 
 * Returns the number of pieces of the given size there are left
 * in the given player's house.
 * 
 * @param game the game to check
 * @param checked_player whose player house is to check
 * @param piece_size which piece size is to check
 * @return the number of pieces in the house, 0 if anything is suspect.
 */

int get_nb_piece_in_house(board game, player checked_player, size piece_size);


/**@}*/

/**@{
 * \name Playing functionalities
 */

/**
 * @brief Adds a piece on the board if possible.
 *
 * The piece is taken from the player's house. 
 * Whether the piece is available is tested. 
 * The piece is then placed on the board, 
 * provided all the pieces on that place are smaller than the current piece, 
 * covering any existing smaller piece.
 * 
 * If placing the piece is not possible, this returns a positive integer
 * encoding the problem identified: 
 *   1. stands for (source): the piece is not available in the player's house.
 *   2. stands for (target): the piece is to small to be put there.
 *   3. stands for illegal entries: e.g. a too large line number.
 *
 * Otherwise, returns a (standard) 0 for success.
 *
 * @param game the game where to add a piece.
 * @param current_player the player whose piece to add.
 * @param piece_size the size of the piece to add.
 * @param line the line number of where to place the piece.
 * @param column the column number of where to place the piece.
 * @return an integer encoding the result of the placement, 0 if things went smoothly.
 */
int place_piece(board game, player current_player, size piece_size, int line, int column);

/**
 * @brief Moves a piece from a place to another, if possible.
 *
 * If placing the piece is not possible, returns a positive integer encoding the problem 
 * identified. 
 *   1. stands for (source): there is no piece at the initial place.
 *   2. stands for (target): the piece is too small to be put 
 *   at the target place.
 *   3. stands for illegal entries: e.g. a too large line number.
 *
 * Otherwise, returns a (standard) 0 for success.
 *
 * @param game the game where to move a piece.
 * @param source_line the line number of where to move the piece from.
 * @param source_column the column number of where to move the piece from.
 * @param target_line the line number of where to move the piece to.
 * @param target_column the column number of where to move the piece to.
 * @return an integer encoding the result of the placement, 0 if things went smoothly.
 */
int move_piece(board game, int source_line, int source_column, int target_line, int target_column);

/**@}*/

/**@{
 * \name My own fonctionalities
 */

int beginning();

int menu();

int submenu();

void gameSet(board game);

void piece(player display_player, size display_size, int space);

void house(board game, player checked_player);

void menu_two_players();

void menu_one_player();

int action_choice();

int play(board game, player current_player);

void rules();

int easy_bot(board game, player current_player);

int medium_bot(board game, player current_player);

int principal(int cas);

void spaces(int nbr);

void line_break(int nbr);

int two_pieces(board game);

void bots_game(board game);

player DeuxPieces(board game);

int verifier(player current_player, board game, int lig1, int colA, int lig2, int colB, int lig3, int colC);

/**@}*/

#endif /*_BOARD_H_*/
