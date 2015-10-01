#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int
main(int argc, char** argv){
	GAME_STATE game; /*ゲーム構造体*/
	int legal_move = 0; /*1なら合法手*/
	int finish = 0; /*1になるとゲームが終了となる*/

	/*ゲーム状態の初期化*/
	init(&game);
	/*ディスプレイに盤面を出力*/
	disp_board(&game);
	/*ループ*/
	while(finish != 1){
		legal_move = 0;
		while(legal_move != 1){
			if(game.teban == 1){
				get_move(&game); /*人間側*/
			}else{
				think_move(&game); /*コンピュータ側*/
			}
			/*その手が合法手かを判定*/
			legal_move = check_legal_move(&game);
		}

		/*手によって盤面の状態を変更する*/
		make_move(&game);
	
		/*ディスプレイに盤面を表示*/
		disp_board(&game);

		/*終局判定*/
		finish = check_finish_game(&game);

		/*手番を交代する*/
		change_teban(&game);
	}
	exit(0);
}
