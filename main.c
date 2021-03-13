#include <stdio.h>
#include <stdlib.h>
#include <time.h> // rand\srand
#include <unistd.h> // sleep
#include "board.h"
#define CYAN "\033[0;36m"
#define BLANC "\033[0;37m"
#define BCyan "\033[1;36m"
#define Jaune "\033[0;33m"

/**
 * \file main.c
 *
 * \author Emma Croq
 */






/***        Fonctions d'introduction du jeu, menu y compris       ***/

int beginning(){

    line_break(5);
    printf("Veuillez mettre le terminal en plein écran pour pouvoir jouer correctement\n\n");
    sleep(3);
    system("clear");
    line_break(15);
    spaces(97);
    printf(CYAN"===Welcom to===\n\n");
    sleep(1);
    line_break(7);
    spaces(80);
    printf(BCyan"╔═╗"BLANC"┌─┐┌┐ ┌┐ ┬  ┌─┐┌┬┐"BCyan"        ╔═╗"BLANC"┌─┐┌┐ ┌┐ ┬  ┌─┐┬─┐┌─┐\n");
    sleep(1);
    spaces(80);
    printf(BCyan"║ ╦"BLANC"│ │├┴┐├┴┐│  ├┤  │"BCyan"         ║ ╦"BLANC"│ │├┴┐├┴┐│  ├┤ ├┬┘└─┐\n");
    sleep(1);
    spaces(80);
    printf(BCyan"╚═╝"BLANC"└─┘└─┘└─┘┴─┘└─┘ ┴"BCyan"         ╚═╝"BLANC"└─┘└─┘└─┘┴─┘└─┘┴└─└─┘\n");
    sleep(2);
    line_break(5);
    spaces(101);
    printf(CYAN"THE GAME\n"BLANC"");
    sleep(5);
    menu();
    
}

int menu(){

    system("clear");
    int choixMenu;
    line_break(15);
    spaces(80);
    printf(BLANC"Veuillez selectionner un mode !\n\n");
    spaces(80);
    printf(" 1 : Joueur VS Joueur\n");
    spaces(80);
    printf(" 2 : Joueur VS IA\n");
    spaces(80);
    printf(" 3 : Regles du Gobblets Gobblers\n");
    spaces(80);
    printf(" 4 : Quitter\n\n ");
    spaces(80);
    scanf("%d", &choixMenu);
    line_break(2);

    return choixMenu;
}

int submenu(){

    system("clear");
    int choixMenu;
    line_break(15);
    spaces(80);
    printf("Veuillez selectionner une difficulte !\n\n");
    spaces(80);
    printf(" 1 : Facile\n");
    spaces(80);
    printf(" 2 : Moyen\n\n ");
    spaces(80);
    scanf("%d", &choixMenu);
    line_break(2);

    return choixMenu;
}




//
/***        Fonctions d'affichage       ***/

void gameSet(board game){
    player holder;
    size piece_size;

    line_break(10);
    for(int i=0; i<=2;i++){ // 3 boucles
        spaces(73);
        if (i == 0) { //    Permet d'afficher qu'une fois le haut du plateau_ boucle 1
            printf(BLANC"       ╔═════════╦═════════╦═════════╗\n       ");
        } else {
            printf(BLANC"       ╠═════════╬═════════╬═════════╣\n       "); //   Permet de l'afficher deux fois_ boucle 2 et 3
        }
        spaces(73);
        printf("║         ║         ║         ║\n");
        spaces(78);
        for(int j=0; j<=2;j++){ 
            spaces(2);
            printf("║"); //   Fin de chaque ligne
            spaces(4);
            holder = get_place_holder(game, i, j); //   Sert à placer la piece dans chaque case
            piece_size = get_piece_size(game, i, j); //    Sert à préciser la taille dans les cases
            piece(holder, piece_size, 1); //    Initialise le jeu
        }
        printf("  ║\n");
        spaces(80);
        printf("║         ║         ║         ║\n");
    }
    spaces(73);
    printf("       ╚═════════╩═════════╩═════════╝\n");


}

void piece(player display_player, size display_size, int space){ //     Lie la taille des pieces à des symboles en fonction des maisons
    if(display_player==NO_PLAYER)
        printf(" ");
    else if (display_player==PLAYER_1){
        if (display_size==SMALL)
            printf(CYAN"x");
        else if(display_size==MEDIUM)
            printf(CYAN"X");
        else if(display_size==LARGE)
            printf(CYAN"#");
    }else if (display_player==PLAYER_2){
         if (display_size==SMALL)
            printf(Jaune"o");
        else if(display_size==MEDIUM)
            printf(Jaune"O");
        else if(display_size==LARGE)
            printf(Jaune"@");
    }
    if (space==1) printf(BLANC"  "); //    Laisse vide la case
}

void house(board game, player checked_player){ // Gère les maisons
    int player[3];
    player[0]=get_nb_piece_in_house(game, checked_player, SMALL);
    player[1]=get_nb_piece_in_house(game, checked_player, MEDIUM);
    player[2]=get_nb_piece_in_house(game, checked_player, LARGE);
    line_break(2);
    spaces(40);
    printf(BLANC"Maison joueur %d : ", checked_player);
    for(int i=0; i<=2; i++){ // 3 boucles 
        for(int j=0; j<player[i]; j++){ // Pour chaque taille
            piece(checked_player, i+1, 0); // Affiche les symboles
        }
        printf("  "); // sépare les symboles
    }
    printf("\n");
}






//
/***        Fonctions de gameplay       ***/


void menu_two_players(){
    int retour_action, rejoue=0;

    system("clear");
    board game = new_game(); // Sert à créer un nouveau plateau vide
    player current_player = PLAYER_1; // On commence par le joueur 1
    player winner = NO_PLAYER;

    while(winner == NO_PLAYER){
        line_break(5);
        spaces(87);
        printf(BLANC"=== Joueur %d ===\n\n", current_player);
        gameSet(game); // Affiche le plateau
        house(game, PLAYER_1);   // Et en dessous, affiche les maisons
        house(game, PLAYER_2);     
        printf("\n");
        retour_action = play(game, current_player);    // Lance le gameplay
        system("clear");
        switch (retour_action) {    // Liste les erreurs 
            case 0:
                current_player = next_player(current_player);    // Aucune erreur, cela s'execute
                break;
            case 1:
                printf("Cette piece est indisponible");
                break;
            case 2:
                printf("Votre piece est trop petite pour etre placee ici");
                break;
            case 3:
                printf("Vous venez de placer une piece en dehors du tableau");
                break;
            default:
                printf("Erreur inattendue");
                break;
        }
        printf("\n\n");
        winner = get_winner(game);
    }

    gameSet(game);
    line_break(2);
    spaces(80);
    printf("Le joueur %d a gagne, felicitations !\n\n\n", winner);
    spaces(80);
    printf(BLANC"Voulez-vous rejouer?\n");
    spaces(80);
    printf(" 1. Rejouer\n");
    spaces(80);
    printf(" 2. Changer de mode de jeu\n");
    spaces(80);
    printf(" 3. Quitter\n");
    spaces(81);
    scanf("%d",&rejoue);
    if (rejoue==1)
    {
        menu_two_players();
    }else if (rejoue==2)
    {
        principal(1);
    }else
    destroy_game(game);
}


void menu_one_player(){
    int retour_action, rejoue=0;

    system("clear");
    board game = new_game();
    player current_player = PLAYER_1;   //  Bot considerer comme joueur 2
    player winner = NO_PLAYER;
    int choix=submenu();   //  Difficulté du jeu

    system("clear");
    while(winner == NO_PLAYER){
        line_break(5);
        spaces(87);
        printf(BLANC"=== Joueur %d ===\n\n", current_player);
        gameSet(game);
        house(game, PLAYER_1);
        house(game, PLAYER_2);
        printf("\n");
        if(choix==1){
            retour_action = easy_bot(game, current_player);
        }else if(choix==2){
            retour_action = medium_bot(game, current_player);
        }else{
            printf("/!\x5c erreur\n\n");
            principal(1);
        }
        system("clear");
        switch (retour_action) {
            case 0:
                current_player = next_player(current_player);
                break;
            case 1:
                printf(BLANC"Cette piece est indisponible");
                break;
            case 2:
                printf(BLANC"Votre piece est trop petite pour etre placee ici");
                break;
            case 3:
                printf(BLANC"Vous venez de placer une piece en dehors du tableau");
                break;
            default:
                printf(BLANC"Erreur inattendue");
                break;
        }
        printf("\n\n");
        winner = get_winner(game);
    }

    gameSet(game);
    spaces(80);
    printf("Le joueur %d a gagne, felicitations !\n\n\n", winner);
    spaces(80);
    printf(BLANC"Voulez-vous rejouer?\n");
    spaces(80);
    printf(" 1. Rejouer\n");
    spaces(80);
    printf(" 2. Changer de mode de jeu\n");
    spaces(80);
    printf(" 3. Quitter\n");
    spaces(81);
    scanf("%d",&rejoue);
    if (rejoue==1)
    {
        menu_one_player();
    }else if (rejoue==2)
    {
        principal(1);
    }else
    destroy_game(game);

}

int action_choice(){
    int action=0;
    do{
        spaces(80);
        printf(BLANC"Quelle action voulez vous faire?\n\n");
        spaces(80);
        printf(" 1.Placer une piece?\n");
        spaces(80);
        printf(" 2.Deplacer une piece?\n\n");
        spaces(81);
        scanf("%d",&action);
    }while (action!=1 && action != 2);
    return action;
}

int play(board game, player current_player){   //  Gameplay 
    int action = action_choice();    // Sert à choisir l'action de jeu
    int line,column,taille,source_line,source_column;
    spaces(80);
    printf(BLANC"Sur quelle ligne voulez-vous placer votre piece?:\n\n");
    spaces(81);
    scanf("%d", &line);
    spaces(80);
    printf("Et sur quelle colonne?:\n\n");
    spaces(81);
    scanf("%d", &column);
    if (action==1){     //  Placer une pièce
        spaces(80);
        printf("Quelle taille?:\n");
        spaces(80);
        printf(" 1.PETIT\n");
        spaces(80);
        printf(" 2.MOYEN\n");
        spaces(80);
        printf(" 3.GRAND\n\n");
        spaces(81);
        scanf("%d", &taille);
        return place_piece(game, current_player, taille, line-1, column-1);
    }else{   //  Deplacer une pièce
        spaces(80);
        printf("De quelle ligne voulez-vous prendre votre piece?:\n\n");
        spaces(81);
        scanf("%d", &source_line);
        spaces(80);
        printf("Et de quelle colonne?:\n\n");
        spaces(81);
        scanf("%d", &source_column);
        if (current_player != get_place_holder(game, source_line-1, source_column-1))
            return 1;
        return move_piece(game,source_line-1, source_column-1, line-1, column-1); 
    }

}





//
/***        Texte des regles        ***/


void rules(){
    system("clear");
    printf(CYAN"        ===Description du projet===\n\n");
    printf(BLANC"Ce projet vise à implémenter un jeu à deux joueurs, proche du jeu Tic-Tac-Toe. Les règles des jeux sont décrites ci-dessous.\n\n");

    printf("Le projet est divisé en différents fichiers. Généralement, le moteur du jeu, mettant en œuvre les règles détaillées, est fourni dans les fichiers board.c et board.h\n\n");

    printf(CYAN"        ===Règles détaillées du jeu===\n\n");
    printf(BLANC"Le jeu est joué par deux joueurs sur un plateau de trois par trois carrés, bien que des variantes puissent être jouées sur des plateaux plus grands.\n");
    printf("Chaque joueur a le contrôle d'un ensemble de six pièces dont le propriétaire est facilement identifiable, par exemple par la forme ou la couleur de la pièce.\n");
    printf("Les pièces sont de trois tailles différentes (grande, moyenne, petite), chaque joueur en ayant deux de chaque taille.\n\n");

    printf("Au cours du jeu, les joueurs effectuent alternativement un mouvement qui consiste à:\n\n");

    printf("en ajoutant une pièce de leur collection au tableau.\n");
    printf("déplacer une de ses pièces visibles déjà sur le plateau vers une autre case.\n");
    printf("Une pièce peut être placée soit sur une case vide, soit sur une case contenant uniquement des pièces plus petites, quel que soit le propriétaire de la pièce.\n");
    printf("Dans ce dernier cas, la pièce recouvre et cache les plus petites pièces. Lorsqu'une pièce placée sur d'autres pièces est déplacée d une case, la plus grande pièce couverte est révélée et peut être jouée dans un tour ultérieur.\n\n");

    printf("Le jeu est gagné par le premier joueur qui parvient à faire une ligne visible de ses pièces à travers le plateau (sur une ligne, une colonne ou une diagonale, comme pour Tic-Tac-Toe.)\n");
    printf("x et o: petit | X et O: moyen | # et @: grand\n\n\n");
}





//
/***        Fonctions de l'extension bot       ***/


int easy_bot(board game, player current_player){   //  bot qui joue totalement au hasard

    srand(time(NULL));
    int line,column,taille,source_line,source_column;
    if(current_player==PLAYER_1){   //  Jeu du joueur1
        play(game,current_player);
    }else{  //  Jeu du bot
        int action = rand()%2 +1;
        int line,column,taille,source_line,source_column;
        line = rand()%3 +1;
        column = rand()%3 +1;
        if (action==1){
            taille = rand()%3 +1;//sans le 0
            return place_piece(game, current_player, taille, line-1, column-1);
        }else{
            source_line= rand()%3 +1;
            source_column= rand()%3 +1;
            if (current_player != get_place_holder(game, source_line-1, source_column-1))
                return 1;
            return move_piece(game,source_line-1, source_column-1, line-1, column-1);
        }
    }
}

int medium_bot(board game, player current_player){    //  Jeu du bot légérement plus astucieux

    srand(time(NULL));
    int line,column,taille,source_line,source_column;
    if(current_player==PLAYER_1){   //  Jeu du joueur 1
        play(game,current_player);
    }else{  //  Jeu du bot
        if (DeuxPieces (game)==1){
            next_player(PLAYER_2);   //  Gagne s'il peut gagner, ou bloque s'il peut bloquer
        }else{  //  Sinon il joue au hasard
            int action = rand()%2 +1;
            int line,column,taille,source_line,source_column;
            line = rand()%3 +1;
            column = rand()%3 +1;
            if (action==1){
                taille = rand()%3 +1;//sans le 0
                return place_piece(game, current_player, taille, line-1, column-1);
            }else{
                source_line= rand()%3 +1;
                source_column= rand()%3 +1;
                if (current_player != get_place_holder(game, source_line-1, source_column-1))
                    return 1;
                return move_piece(game,source_line-1, source_column-1, line-1, column-1);
            }  
        }  
    }
}



//
/***        Fonctions du main       ***/


/**
*\name main
*/

int principal(int cas){
    int choix, choix2, sortie=0;
    system("clear");

    if (cas < 1) {  //  Permet d'afficher l'intro du jeu qu'une seule fois
        choix=beginning();
    } else {
        choix=menu();   //  Relance directement sur le menu principal
    }

    printf(BLANC"");
    if (choix==1){
        menu_two_players();
    }
    else if (choix==2){
        menu_one_player();
    }
    else if (choix==3){
        rules();
    }
    else if(choix!=1&&choix!=2&&choix!=3&&choix!=4){
        spaces(80);
        printf("/!\x5c erreur\n\n");
    }

    spaces(80);
    printf("Voulez-vous quitter? [0] quitter [1] continuer\n\n ");  //  Choix 4 inclu
    spaces(80);
    scanf("%d", &sortie);

    if (sortie==0){
         system("clear");
    }else
        principal(1);   //  Retourne au menu principal
    printf(BLANC"");   
}



//


int main(int args, char **argv){
    system("clear");
    principal(0);   //  0 permet d'afficher l'intro du jeu
    
    return 0;
}


