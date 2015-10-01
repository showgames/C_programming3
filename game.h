#define BLOCK_NUMBER 9 /*盤面のサイズ*/

#define MAX_TESUU 9 /*手数の最大値(盤面は9マスなので)*/

#define EMPTY 0 /*空マス*/

typedef struct _game_state{
	int board[BLOCK_NUMBER]; /*盤面*/
	int teban; /*手番*/
	int tesuu; /*手数*/
	int te; /*手*/
}GAME_STATE;

/*ゲーム状態を操作する関数群*/
void init(GAME_STATE* game); /*ゲームを初期化する関数*/
void get_move(GAME_STATE* game); /*プレイヤーが手を入力する関数*/
int check_legal_move(GAME_STATE* game); /*合法手を判定する関数*/
void make_move(GAME_STATE* game);/*手によって状態を変更する関数*/
void disp_board(GAME_STATE* game); /*ディスプレイに盤面の状態を出力する関数*/
int check_finish_game(GAME_STATE* game); /*ゲームの終局を判定する関数*/
void change_teban(GAME_STATE* game); /*手番を交代する*/

/*AIの関数*/
void think_move(GAME_STATE* game); /*コンピュータが手を選ぶ関数*/
