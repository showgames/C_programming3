#include <stdio.h>
#include "game.h"

/*探索ライン*/
const int LINE[8][3] = {
	{0,1,2}, {3,4,5}, {6,7,8}, /*横のライン*/
	{0,3,6}, {1,4,7}, {2,5,8}, /*縦のライン*/
	{0,4,8}, {2,4,6},};        /*斜めのライン*/
	
void
init(GAME_STATE* game){
	/*ゲーム開始状態に初期化する*/
	game->teban = 1;
	game->tesuu = 0;
	game->te = 0;
	
	int i;
	for(i = 0; i < BLOCK_NUMBER; i++){
		game->board[i] = EMPTY;
	}
}
	
void
disp_board(GAME_STATE* game){
	int i;
	int row_count;
	
	for(i = 0, row_count = 1; i < BLOCK_NUMBER; i++, row_count++){
		printf("%d ",game->board[i]);
		if(row_count == 3){ /*3マス表示したら改行する*/
			printf("\n");
			row_count = 0;
		}
	}
	printf("\n");
}

void
get_move(GAME_STATE* game){
	char buf[256];
	
	game->te = 0; /*1から9までの数値の入力を受け付けるので0で初期化しておく*/
	while(!(game->te >= 1 && game->te <= 9)){
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d", &(game->te));
	}
}
	
int
check_legal_move(GAME_STATE* game){
	if(game->board[(game->te - 1)] == EMPTY){
		return 1; /*置ける*/
	}else{
		return 0; /*置けない*/
	}
}
	
void
make_move(GAME_STATE* game){
	game->board[(game->te - 1)] = game->teban; /*盤面に置く*/
	game->tesuu++; /*手数を一増やす*/
}

int
check_finish_game(GAME_STATE* game){
	int i;
	for(i = 0; i < 8; i++){/*8つのどれかのライン上に３つの連続した数字があれば試合終了*/
		if(game->board[(LINE[i][0])] == game->teban && 
			game->board[(LINE[i][1])] == game->teban &&
			 game->board[(LINE[i][2])] == game->teban){
			 	return 1;
	    }
	}
	if(game->tesuu == MAX_TESUU){ /*手数が9手ならば試合終了*/
		return 1;
	}
	return 0;
}
	
	
void
change_teban(GAME_STATE* game){
	game->teban = 3 - game->teban;
}
	
void
think_move(GAME_STATE* game){
	int i;
	int human = (3-game->teban);
	
	/*自分にリーチがかかっている*/
	/*横のライン*/
	for(i = 0; i < 3; i++){
		if(game->board[(LINE[i][0])] == EMPTY && game->board[(LINE[i][1])] ==game->teban
			&& game->board[(LINE[i][2])] == game->teban){
				game->te = (LINE[i][0] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == game->teban && game->board[(LINE[i][1])] == EMPTY
			&& game->board[(LINE[i][2])] == game->teban){
				game->te = (LINE[i][1] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == game->teban && game->board[(LINE[i][1])] == game->teban
			&& game->board[(LINE[i][2])] == EMPTY){
				game->te = (LINE[i][2] + 1);
				return;
		}
	}
	/*縦のライン*/
	for(i = 3; i < 6; i++){
		if(game->board[(LINE[i][0])] == EMPTY && game->board[(LINE[i][1])] ==game->teban
			&& game->board[(LINE[i][2])] == game->teban){
				game->te = (LINE[i][0] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == game->teban && game->board[(LINE[i][1])] == EMPTY
			&& game->board[(LINE[i][2])] == game->teban){
				game->te = (LINE[i][1] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == game->teban && game->board[(LINE[i][1])] == game->teban
			&& game->board[(LINE[i][2])] == EMPTY){
				game->te = (LINE[i][2] + 1);
				return;
		}
	}
	
	/*斜めのライン*/
	for(i = 6; i < 8; i++){
		if(game->board[(LINE[i][0])] == EMPTY && game->board[(LINE[i][1])] ==game->teban
			&& game->board[(LINE[i][2])] == game->teban){
				game->te = (LINE[i][0] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == game->teban && game->board[(LINE[i][1])] == EMPTY
			&& game->board[(LINE[i][2])] == game->teban){
				game->te = (LINE[i][1] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == game->teban && game->board[(LINE[i][1])] == game->teban
			&& game->board[(LINE[i][2])] == EMPTY){
				game->te = (LINE[i][2] + 1);
				return;
		}
	}
	/*相手の勝ちを阻止する*/
	/*横のライン*/
	for(i = 0; i < 3; i++){
		if(game->board[(LINE[i][0])] == EMPTY && game->board[(LINE[i][1])] == human
			&& game->board[(LINE[i][2])] == human){
				game->te = (LINE[i][0] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == human && game->board[(LINE[i][1])] == EMPTY
			&& game->board[(LINE[i][2])] == human){
				game->te = (LINE[i][1] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == human && game->board[(LINE[i][1])] == human
			&& game->board[(LINE[i][2])] == EMPTY){
				game->te = (LINE[i][2] + 1);
				return;
		}
	}
	/*縦のライン*/
	for(i = 3; i < 6; i++){
		if(game->board[(LINE[i][0])] == EMPTY && game->board[(LINE[i][1])] == human
			&& game->board[(LINE[i][2])] == human){
				game->te = (LINE[i][0] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == human && game->board[(LINE[i][1])] == EMPTY
			&& game->board[(LINE[i][2])] == human){
				game->te = (LINE[i][1] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == human && game->board[(LINE[i][1])] == human
			&& game->board[(LINE[i][2])] == EMPTY){
				game->te = (LINE[i][2] + 1);
				return;
		}
	}
	/*斜めのライン*/
	for(i = 6; i < 8; i++){
		if(game->board[(LINE[i][0])] == EMPTY && game->board[(LINE[i][1])] == human
			&& game->board[(LINE[i][2])] == human){
				game->te = (LINE[i][0] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == human && game->board[(LINE[i][1])] == EMPTY
			&& game->board[(LINE[i][2])] == human){
				game->te = (LINE[i][1] + 1);
				return;
		}
		if(game->board[(LINE[i][0])] == human && game->board[(LINE[i][1])] == human
			&& game->board[(LINE[i][2])] == EMPTY){
				game->te = (LINE[i][2] + 1);
				return;
		}
	}
	
	/*相手にも自分にもリーチがかかっていなかった場合*/
	for(i = 0; i < 9; i++){
		if(game->board[i] == EMPTY){
			game->te = (i + 1);
			return;
		}
	}
}
		 
	
