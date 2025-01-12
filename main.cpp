#include <Novice.h>
#include "enum.h"
#include "structure.h"
#include "map.h"
#include <corecrt_math.h>

const char kWindowTitle[] = "計算迷宮";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	///// 画像の読み取り /////
	//blocks
	int blocks_image = Novice::LoadTexture("./Resources/images/blocks.png");

	//numberBoxs
	int numberBoxs_image = Novice::LoadTexture("./Resources/images/numberBoxs.png");

	//player
	int player_image = Novice::LoadTexture("./Resources/images/player.png");

	///// 初期化 /////
	//画面幅
	//横
	float screenBeside = 280.0f;

	//画面切り替え
	int scene = title;

	//計算記号の切り替え
	int calculation = add;

	//初期化のフラグ
	bool initializationFlag = false;

	// セレクト画面の変数
	int stageNum = 1;
	int stageNumMax = 10;

	//loadMap
	int map[9][9];
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			map[y][x] = stage1(y, x);
		}
	}

	//block
	float blockSize = 80.0f;
	Vector2 blockPos[9][9];
	Vector2 blockRadius[9][9];
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			blockRadius[y][x] = { blockSize / 2.0f,blockSize / 2.0f };
			blockPos[y][x].x = blockSize * x + blockRadius[y][x].x;
			blockPos[y][x].y = blockSize * y + blockRadius[y][x].y;
		}
	}

	//player
	float playerSize = 80.0f;
	Player player;
	player.radius = { playerSize / 2,playerSize / 2 };
	player.pos = { 0.0f,0.0f };
	player.Nextpos = { 0.0f,0.0f };
	player.status.velocity = playerSize;
	player.now = { 0,0 };
	player.next = { 0,0 };
	player.isAlive = true;

	//NumberBox
	int const kNumberBoxNumber = 10;//ブロックの数
	float numberBoxSize = 80.0f;
	NumberBox numberBox[kNumberBoxNumber];
	for (int i = 0; i < kNumberBoxNumber; i++) {
		numberBox[i].radius = { numberBoxSize / 2,numberBoxSize / 2 };
		numberBox[i].pos = { 0.0f,0.0f };
		numberBox[i].Nextpos = { 0.0f,0.0f };
		numberBox[i].status.velocity = numberBoxSize;
		numberBox[i].now = { 0,0 };
		numberBox[i].next = { 0,0 };
		numberBox[i].isAlive = false;
		numberBox[i].number = 0;
	}

	//EnemyBox
	int const kEnemyBoxNumber = 5;//お邪魔ブロックの数
	float enemyBoxSize = 80.0f;
	NumberBox enemyBox[kEnemyBoxNumber];
	for (int i = 0; i < kEnemyBoxNumber; i++) {
		enemyBox[i].radius = { enemyBoxSize / 2,enemyBoxSize / 2 };
		enemyBox[i].pos = { 0.0f,0.0f };
		enemyBox[i].Nextpos = { 0.0f,0.0f };
		enemyBox[i].status.velocity = enemyBoxSize;
		enemyBox[i].now = { 0,0 };
		enemyBox[i].next = { 0,0 };
		enemyBox[i].isAlive = false;
		enemyBox[i].number = 0;
	}

	//targetNumber(目的の数字)
	int targetNumber = 60;

	//長さ
	float a[3] = { 0 };
	float b[3] = { 0 };
	float distance[3] = { 0 };

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///// ↓↓処理↓↓ /////
		//初期化の処理
		if (initializationFlag) {
			///// リセット /////
			//計算記号
			calculation = add;
			//プレイヤーの生存
			player.isAlive = true;
			//ナンバーボックス
			for (int i = 0; i < kNumberBoxNumber; i++) {
				//ナンバーボックスの有無
				numberBox[i].isAlive = false;
				//ナンバーボックスのスポーン位置
				numberBox[i].pos = { blockPos[0][0].x,blockPos[0][0].y };
				//ナンバーボックスの保有数字
				numberBox[i].number = 0;
			}
			
			switch (stageNum) {
			case -1:
				///// 初期化の見本 /////
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage0(y, x);
					}
				}
				//目的の数字
				targetNumber = 0;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[0][0].x,blockPos[0][0].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[0][0].x,blockPos[0][0].y };
				numberBox[1].pos = { blockPos[0][0].x,blockPos[0][0].y };
				numberBox[2].pos = { blockPos[0][0].x,blockPos[0][0].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 0;
				numberBox[1].number = 0;
				numberBox[2].number = 0;
				//お邪魔ブロックの有無
				enemyBox[0].isAlive = true;
				//お邪魔ブロックのスポーン位置
				enemyBox[0].pos = { blockPos[0][0].x,blockPos[0][0].y };
				//お邪魔ブロックの保有数字
				enemyBox[0].number = 0;
				break;
			case 1:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage1(y, x);
					}
				}
				//目的の数字
				targetNumber = 5;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[1][3].x,blockPos[1][3].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[1][4].x,blockPos[1][4].y };
				numberBox[1].pos = { blockPos[2][3].x,blockPos[2][3].y };
				numberBox[2].pos = { blockPos[4][4].x,blockPos[4][4].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 2;
				numberBox[1].number = 4;
				numberBox[2].number = 3;
				//お邪魔ブロックの有無
				enemyBox[0].isAlive = true;
				//お邪魔ブロックのスポーン位置
				enemyBox[0].pos = { blockPos[6][4].x,blockPos[6][4].y };
				//お邪魔ブロックの保有数字
				enemyBox[0].number = -1;
				break;
			case 2:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage2(y, x);
					}
				}
				//目的の数字
				targetNumber = 15;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[4][6].x,blockPos[4][6].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[3][2].x,blockPos[3][2].y };
				numberBox[1].pos = { blockPos[4][4].x,blockPos[4][4].y };
				numberBox[2].pos = { blockPos[5][3].x,blockPos[5][3].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 5;
				numberBox[1].number = 3;
				numberBox[2].number = 7;
				break;
			case 3:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage3(y, x);
					}
				}
				//目的の数字
				targetNumber = 9;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[2][3].x,blockPos[2][3].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				numberBox[3].isAlive = true;
				numberBox[4].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[2][2].x,blockPos[2][2].y };
				numberBox[1].pos = { blockPos[3][3].x,blockPos[3][3].y };
				numberBox[2].pos = { blockPos[3][4].x,blockPos[3][4].y };
				numberBox[3].pos = { blockPos[4][4].x,blockPos[4][4].y };
				numberBox[4].pos = { blockPos[4][2].x,blockPos[4][2].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 3;
				numberBox[1].number = 1;
				numberBox[2].number = 1;
				numberBox[3].number = 3;
				numberBox[4].number = 2;
				break;
			case 4:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage4(y, x);
					}
				}
				//目的の数字
				targetNumber = 16;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[2][3].x,blockPos[2][3].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[3][2].x,blockPos[3][2].y };
				numberBox[1].pos = { blockPos[3][3].x,blockPos[3][3].y };
				numberBox[2].pos = { blockPos[3][4].x,blockPos[3][4].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 2;
				numberBox[1].number = 3;
				numberBox[2].number = 5;
				break;
			case 5:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage5(y, x);
					}
				}
				//目的の数字
				targetNumber = 13;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[5][4].x,blockPos[5][4].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				numberBox[3].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[2][2].x,blockPos[2][2].y };
				numberBox[1].pos = { blockPos[3][3].x,blockPos[3][3].y };
				numberBox[2].pos = { blockPos[4][2].x,blockPos[4][2].y };
				numberBox[3].pos = { blockPos[4][4].x,blockPos[4][4].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 3;
				numberBox[1].number = 2;
				numberBox[2].number = 3;
				numberBox[3].number = 4;
				break;
			case 6:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage6(y, x);
					}
				}
				//目的の数字
				targetNumber = 12;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[4][4].x,blockPos[4][4].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				numberBox[3].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[3][4].x,blockPos[3][4].y };
				numberBox[1].pos = { blockPos[5][4].x,blockPos[5][4].y };
				numberBox[2].pos = { blockPos[7][3].x,blockPos[7][3].y };
				numberBox[3].pos = { blockPos[1][5].x,blockPos[1][5].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 2;
				numberBox[1].number = 1;
				numberBox[2].number = 5;
				numberBox[3].number = 4;
				break;
			case 7:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage7(y, x);
					}
				}
				//目的の数字
				targetNumber = 16;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[2][4].x,blockPos[2][4].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[3][3].x,blockPos[3][3].y };
				numberBox[1].pos = { blockPos[4][5].x,blockPos[4][5].y };
				numberBox[2].pos = { blockPos[5][2].x,blockPos[5][2].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 3;
				numberBox[1].number = 7;
				numberBox[2].number = 3;
				break;
			case 8:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage8(y, x);
					}
				}
				//目的の数字
				targetNumber = 13;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[3][5].x,blockPos[3][5].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				numberBox[3].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[3][4].x,blockPos[3][4].y };
				numberBox[1].pos = { blockPos[3][6].x,blockPos[3][6].y };
				numberBox[2].pos = { blockPos[4][3].x,blockPos[4][3].y };
				numberBox[3].pos = { blockPos[4][5].x,blockPos[4][5].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 3;
				numberBox[1].number = 7;
				numberBox[2].number = 2;
				numberBox[3].number = 4;
				break;
			case 9:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage9(y, x);
					}
				}
				//目的の数字
				targetNumber = 9;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[2][1].x,blockPos[2][1].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				numberBox[3].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[3][2].x,blockPos[3][2].y };
				numberBox[1].pos = { blockPos[4][3].x,blockPos[4][3].y };
				numberBox[2].pos = { blockPos[4][4].x,blockPos[4][4].y };
				numberBox[3].pos = { blockPos[2][5].x,blockPos[2][5].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 2;
				numberBox[1].number = 1;
				numberBox[2].number = 4;
				numberBox[3].number = 3;
				break;
			case 10:
				//マップのロード
				for (int x = 0; x < 9; x++) {
					for (int y = 0; y < 9; y++) {
						map[y][x] = stage10(y, x);
					}
				}
				//目的の数字
				targetNumber = 11;
				//プレイヤーのスポーン位置
				player.pos = { blockPos[6][4].x,blockPos[6][4].y };
				//ナンバーボックスの有無
				numberBox[0].isAlive = true;
				numberBox[1].isAlive = true;
				numberBox[2].isAlive = true;
				//ナンバーボックスのスポーン位置
				numberBox[0].pos = { blockPos[5][3].x,blockPos[5][3].y };
				numberBox[1].pos = { blockPos[5][4].x,blockPos[5][4].y };
				numberBox[2].pos = { blockPos[5][5].x,blockPos[5][5].y };
				//ナンバーボックスの保有数字
				numberBox[0].number = 2;
				numberBox[1].number = 4;
				numberBox[2].number = 7;
				break;
			}

			//初期化フラグを閉じる
			initializationFlag = false;
		}
		
		switch (scene) {
		case title:
			///// ↓↓更新処理↓↓ /////
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = stageSelect;
			}
			///// ↑↑更新処理↑↑ /////
			///// ↓↓描画処理↓↓ /////

			Novice::ScreenPrintf(550, 300, "      KEISAN MEIKYU      ");
			Novice::ScreenPrintf(550, 350, "Push Space to stageSelect");

			///// ↑↑描画処理↑↑ /////
			break;
		case stageSelect:
			///// ↓↓更新処理↓↓ /////
			//前のステージへ
			if (keys[DIK_A] && !preKeys[DIK_A] && stageNum != 1) {
				stageNum -= 1;
			}

			//次のステージへ
			if (keys[DIK_D] && !preKeys[DIK_D] && stageNum != stageNumMax) {
				stageNum += 1;
			}

			//ゲームへ
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				//初期化フラグ
				initializationFlag = true;

				scene = game;
			}

			///// ↑↑更新処理↑↑ /////
			///// ↓↓描画処理↓↓ /////
			//中央の数字と四角
			Novice::ScreenPrintf(600, 360, "stage%d", stageNum);
			Novice::DrawBox(140, 200, 1000, 400, 0.0f, WHITE, kFillModeWireFrame);
			Novice::ScreenPrintf(550, 450, "Push Space to Start");

			//左の数字と三角
			if (stageNum != 1) {
				Novice::ScreenPrintf(50, 360, "stage%d", stageNum - 1);
				Novice::ScreenPrintf(50, 380, "Push A");
				Novice::DrawTriangle(20, 380, 120, 300, 120, 460, WHITE, kFillModeWireFrame);
			}

			//右の数字と三角
			if (stageNum != stageNumMax) {
				Novice::ScreenPrintf(1170, 360, "stage%d", stageNum + 1);
				Novice::ScreenPrintf(1170, 380, "Push D");
				Novice::DrawTriangle(1250, 380, 1160, 300, 1160, 460, WHITE, kFillModeWireFrame);
			}

			///// ↑↑描画処理↑↑ /////
			break;
		case game:
			///// ↓↓更新処理↓↓ /////

			//足し算と掛け算の変更
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				if (calculation == add) {
					calculation = multiply;
				} else if (calculation == multiply) {
					calculation = add;
				}
			}

			//ステージのリセット
			if (keys[DIK_R] && !preKeys[DIK_R]) {
				initializationFlag = true;
			}

			//ステージセレクトに戻る
			if (keys[DIK_Q] && !preKeys[DIK_Q]) {
				scene = stageSelect;
			}

			///// playerの移動キー /////
			if (keys[DIK_W] && !preKeys[DIK_W] && !keys[DIK_S]) {
				//仮のposに代入 <player.Nextpos>
				player.Nextpos.x = player.pos.x;
				player.Nextpos.y = player.pos.y - player.status.velocity;

				//場所決め <player.now>
				player.now.beside = int(player.pos.x / playerSize);
				player.now.vertical = int(player.pos.y / playerSize);

				//場所決め <player.next>
				player.next.beside = int(player.Nextpos.x / playerSize);
				player.next.vertical = int(player.Nextpos.y / playerSize);

				for (int i = 0; i < kNumberBoxNumber; i++) {
					//仮のposに代入 <numberBox.Nextpos>
					numberBox[i].Nextpos.x = numberBox[i].pos.x;
					numberBox[i].Nextpos.y = numberBox[i].pos.y - numberBox[i].status.velocity;

					//場所決め <numberBox.now>
					numberBox[i].now.beside = int(numberBox[i].pos.x / numberBoxSize);
					numberBox[i].now.vertical = int(numberBox[i].pos.y / numberBoxSize);

					//場所決め <numberBox.next>
					numberBox[i].next.beside = int(numberBox[i].Nextpos.x / numberBoxSize);
					numberBox[i].next.vertical = int(numberBox[i].Nextpos.y / numberBoxSize);
				}

				//playerの移動
				if (map[player.next.vertical][player.next.beside] == 0) {
					player.pos.y -= player.status.velocity;
				}

				//当たり判定
				for (int i = 0; i < kNumberBoxNumber; i++) {
					if (numberBox[i].isAlive) {
						if (player.next.vertical == numberBox[i].now.vertical && player.next.beside == numberBox[i].now.beside) {
							if (map[numberBox[i].next.vertical][numberBox[i].next.beside] == 0) {
								numberBox[i].pos.y -= numberBox[i].status.velocity;
							} else {
								player.pos.y += player.status.velocity;
							}
						}
					}
				}

			} else if (keys[DIK_S] && !preKeys[DIK_S] && !keys[DIK_W]) {
				//仮のposに代入 <player.Nextpos>
				player.Nextpos.x = player.pos.x;
				player.Nextpos.y = player.pos.y + player.status.velocity;

				//場所決め <player.now>
				player.now.beside = int(player.pos.x / playerSize);
				player.now.vertical = int(player.pos.y / playerSize);

				//場所決め <player.next>
				player.next.beside = int(player.Nextpos.x / playerSize);
				player.next.vertical = int(player.Nextpos.y / playerSize);

				for (int i = 0; i < kNumberBoxNumber; i++) {
					//仮のposに代入 <numberBox.Nextpos>
					numberBox[i].Nextpos.x = numberBox[i].pos.x;
					numberBox[i].Nextpos.y = numberBox[i].pos.y + numberBox[i].status.velocity;

					//場所決め <numberBox.now>
					numberBox[i].now.beside = int(numberBox[i].pos.x / numberBoxSize);
					numberBox[i].now.vertical = int(numberBox[i].pos.y / numberBoxSize);

					//場所決め <numberBox.next>
					numberBox[i].next.beside = int(numberBox[i].Nextpos.x / numberBoxSize);
					numberBox[i].next.vertical = int(numberBox[i].Nextpos.y / numberBoxSize);
				}

				//playerの移動
				if (map[player.next.vertical][player.next.beside] == 0) {
					player.pos.y += player.status.velocity;
				}

				//当たり判定
				for (int i = 0; i < kNumberBoxNumber; i++) {
					if (numberBox[i].isAlive) {
						if (player.next.vertical == numberBox[i].now.vertical && player.next.beside == numberBox[i].now.beside) {
							if (map[numberBox[i].next.vertical][numberBox[i].next.beside] == 0) {
								numberBox[i].pos.y += numberBox[i].status.velocity;
							} else {
								player.pos.y -= player.status.velocity;
							}
						}
					}
				}

			} else if (keys[DIK_A] && !preKeys[DIK_A] && !keys[DIK_D]) {
				//仮のposに代入 <player.Nextpos>
				player.Nextpos.x = player.pos.x - player.status.velocity;
				player.Nextpos.y = player.pos.y;

				//場所決め <player.now>
				player.now.beside = int(player.pos.x / playerSize);
				player.now.vertical = int(player.pos.y / playerSize);

				//場所決め <player.next>
				player.next.beside = int(player.Nextpos.x / playerSize);
				player.next.vertical = int(player.Nextpos.y / playerSize);

				for (int i = 0; i < kNumberBoxNumber; i++) {
					//仮のposに代入 <numberBox.Nextpos>
					numberBox[i].Nextpos.x = numberBox[i].pos.x - numberBox[i].status.velocity;
					numberBox[i].Nextpos.y = numberBox[i].pos.y;

					//場所決め <numberBox.now>
					numberBox[i].now.beside = int(numberBox[i].pos.x / numberBoxSize);
					numberBox[i].now.vertical = int(numberBox[i].pos.y / numberBoxSize);

					//場所決め <numberBox.next>
					numberBox[i].next.beside = int(numberBox[i].Nextpos.x / numberBoxSize);
					numberBox[i].next.vertical = int(numberBox[i].Nextpos.y / numberBoxSize);
				}

				//playerの移動
				if (map[player.next.vertical][player.next.beside] == 0) {
					player.pos.x -= player.status.velocity;
				}

				//当たり判定
				for (int i = 0; i < kNumberBoxNumber; i++) {
					if (numberBox[i].isAlive) {
						if (player.next.vertical == numberBox[i].now.vertical && player.next.beside == numberBox[i].now.beside) {
							if (map[numberBox[i].next.vertical][numberBox[i].next.beside] == 0) {
								numberBox[i].pos.x -= numberBox[i].status.velocity;
							} else {
								player.pos.x += player.status.velocity;
							}
						}
					}
				}

			} else if (keys[DIK_D] && !preKeys[DIK_D] && !keys[DIK_A]) {
				//仮のposに代入 <player.Nextpos>
				player.Nextpos.x = player.pos.x + player.status.velocity;
				player.Nextpos.y = player.pos.y;

				//場所決め <player.now>
				player.now.beside = int(player.pos.x / playerSize);
				player.now.vertical = int(player.pos.y / playerSize);

				//場所決め <player.next>
				player.next.beside = int(player.Nextpos.x / playerSize);
				player.next.vertical = int(player.Nextpos.y / playerSize);

				for (int i = 0; i < kNumberBoxNumber; i++) {
					//仮のposに代入 <numberBox.Nextpos>
					numberBox[i].Nextpos.x = numberBox[i].pos.x + numberBox[i].status.velocity;
					numberBox[i].Nextpos.y = numberBox[i].pos.y;

					//場所決め <numberBox.now>
					numberBox[i].now.beside = int(numberBox[i].pos.x / numberBoxSize);
					numberBox[i].now.vertical = int(numberBox[i].pos.y / numberBoxSize);

					//場所決め <numberBox.next>
					numberBox[i].next.beside = int(numberBox[i].Nextpos.x / numberBoxSize);
					numberBox[i].next.vertical = int(numberBox[i].Nextpos.y / numberBoxSize);
				}

				//playerの移動
				if (map[player.next.vertical][player.next.beside] == 0) {
					player.pos.x += player.status.velocity;
				}

				//当たり判定
				for (int i = 0; i < kNumberBoxNumber; i++) {
					if (numberBox[i].isAlive) {
						if (player.next.vertical == numberBox[i].now.vertical && player.next.beside == numberBox[i].now.beside) {
							if (map[numberBox[i].next.vertical][numberBox[i].next.beside] == 0) {
								numberBox[i].pos.x += numberBox[i].status.velocity;
							} else {
								player.pos.x -= player.status.velocity;
							}
						}
					}
				}

			}

			///// numberBox同士の当たり判定 /////
			for (int i = 0; i < kNumberBoxNumber; i++) {
				for (int j = 0; j < kNumberBoxNumber; j++) {
					if (numberBox[i].isAlive && numberBox[j].isAlive && i != j) {
						//長さの計算
						a[0] = numberBox[i].pos.x - numberBox[j].pos.x;
						b[0] = numberBox[i].pos.y - numberBox[j].pos.y;
						distance[0] = sqrtf(a[0] * a[0] + b[0] * b[0]);

						//実際の当たり判定
						if (distance[0] < numberBox[i].radius.x + numberBox[j].radius.x) {
							numberBox[i].isAlive = false;
							if (calculation == add) {
								numberBox[j].number += numberBox[i].number;
							} else {
								numberBox[j].number *= numberBox[i].number;
							}
							numberBox[i].number = 0;
						}
					}
				}
			}

			///// playerとenemyBoxの当たり判定 /////
			for (int i = 0; i < kEnemyBoxNumber; i++) {
				if (enemyBox[i].isAlive) {
					//長さの計算
					a[1] = player.pos.x - enemyBox[i].pos.x;
					b[1] = player.pos.y - enemyBox[i].pos.y;
					distance[1] = sqrtf(a[1] * a[1] + b[1] * b[1]);

					//実際の当たり判定
					if (distance[1] < player.radius.x + enemyBox[i].radius.x) {
						player.isAlive = false;
						initializationFlag = true;
					}
				}
			}

			///// numberBoxとenemyBoxの当たり判定 /////
			for (int i = 0; i < kNumberBoxNumber; i++) {
				for (int j = 0; j < kEnemyBoxNumber; j++) {
					if (numberBox[i].isAlive && enemyBox[j].isAlive) {
						//長さの計算
						a[2] = numberBox[i].pos.x - enemyBox[j].pos.x;
						b[2] = numberBox[i].pos.y - enemyBox[j].pos.y;
						distance[2] = sqrtf(a[2] * a[2] + b[2] * b[2]);

						//実際の当たり判定
						if (distance[2] < numberBox[i].radius.x + enemyBox[j].radius.x) {
							enemyBox[j].isAlive = false;
							if (calculation == add) {
								numberBox[i].number += enemyBox[j].number;
							} else {
								numberBox[i].number *= enemyBox[j].number;
							}
							enemyBox[j].number = 0;
						}
					}
				}
			}

			//クリア条件の処理
			for (int i = 0; i < kNumberBoxNumber; i++) {
				if (targetNumber == numberBox[i].number) {
					scene = gameClear;
				}
			}

			//ScreenPrintf
			/*for (int i = 0; i < kNumberBoxNumber; i++) {
				Novice::ScreenPrintf(10, 20 * i + 100, "numberBox[%d] = %d ,flag = [%s]", i, numberBox[i].number, numberBox[i].isAlive ? "true" : "false");
			}*/
			Novice::ScreenPrintf(60, 10, "calculation = [ %s ]", calculation ? "multiply" : "add");
			Novice::ScreenPrintf(60, 30, "targetNumber = [ %d ]", targetNumber);
			Novice::ScreenPrintf(350, 10, "[      movePlayer     ] : press to [W][A][S][D]");
			Novice::ScreenPrintf(350, 30, "[ ChangeToCalculation ] : press to [SPACE]");
			Novice::ScreenPrintf(860, 10, "[        Reset        ] : press to [R]");
			Novice::ScreenPrintf(860, 30, "[ ReturnToStageSelect ] : press to [Q]");

			///// ↑↑更新処理↑↑ /////
			///// ↓↓描画処理↓↓ /////

			//背景(計算記号で変わる)
			if (calculation == add) {
				Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x94b8b1FF, kFillModeSolid);
			} else {
				Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xc79f9fFF, kFillModeSolid);
			}

			//blocksの表示
			for (int x = 0; x < 9; x++) {
				for (int y = 0; y < 9; y++) {
					Novice::DrawQuad(
						int(blockPos[y][x].x - blockRadius[y][x].x + screenBeside), int(blockPos[y][x].y - blockRadius[y][x].y),
						int(blockPos[y][x].x + blockRadius[y][x].x + screenBeside), int(blockPos[y][x].y - blockRadius[y][x].y),
						int(blockPos[y][x].x - blockRadius[y][x].x + screenBeside), int(blockPos[y][x].y + blockRadius[y][x].y),
						int(blockPos[y][x].x + blockRadius[y][x].x + screenBeside), int(blockPos[y][x].y + blockRadius[y][x].y),
						map[y][x] * int(blockSize), 0, int(blockSize), int(blockSize), blocks_image, WHITE
					);
				}
			}

			//EnemyBoxの表示
			for (int i = 0; i < kEnemyBoxNumber; i++) {
				if (enemyBox[i].isAlive) {
					Novice::DrawQuad(
						int(enemyBox[i].pos.x - enemyBox[i].radius.x + screenBeside), int(enemyBox[i].pos.y - enemyBox[i].radius.y),
						int(enemyBox[i].pos.x + enemyBox[i].radius.x + screenBeside), int(enemyBox[i].pos.y - enemyBox[i].radius.y),
						int(enemyBox[i].pos.x - enemyBox[i].radius.x + screenBeside), int(enemyBox[i].pos.y + enemyBox[i].radius.y),
						int(enemyBox[i].pos.x + enemyBox[i].radius.x + screenBeside), int(enemyBox[i].pos.y + enemyBox[i].radius.y),
						100 * int(enemyBoxSize), 0, int(enemyBoxSize), int(enemyBoxSize), numberBoxs_image, WHITE
					);
				}
			}

			//NumberBoxの表示
			for (int i = 0; i < kNumberBoxNumber; i++) {
				if (numberBox[i].isAlive) {
					Novice::DrawQuad(
						int(numberBox[i].pos.x - numberBox[i].radius.x + screenBeside), int(numberBox[i].pos.y - numberBox[i].radius.y),
						int(numberBox[i].pos.x + numberBox[i].radius.x + screenBeside), int(numberBox[i].pos.y - numberBox[i].radius.y),
						int(numberBox[i].pos.x - numberBox[i].radius.x + screenBeside), int(numberBox[i].pos.y + numberBox[i].radius.y),
						int(numberBox[i].pos.x + numberBox[i].radius.x + screenBeside), int(numberBox[i].pos.y + numberBox[i].radius.y),
						numberBox[i].number * int(numberBoxSize), 0, int(numberBoxSize), int(numberBoxSize), numberBoxs_image, WHITE
					);
				}
			}

			//playerの表示
			if (player.isAlive) {
				Novice::DrawSprite(int(player.pos.x - player.radius.x + screenBeside), int(player.pos.y - player.radius.y), player_image, 1, 1, 0.0f, WHITE);
			}
			
			///// ↑↑描画処理↑↑ /////
			break;
		case gameClear:
			///// ↓↓更新処理↓↓ /////
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = stageSelect;
			}
			///// ↑↑更新処理↑↑ /////
			///// ↓↓描画処理↓↓ /////
			Novice::ScreenPrintf(580, 360, "STAGE %d  CLEAR!", stageNum);
			Novice::ScreenPrintf(550, 400, "Push SPACE to StageSelect...");
			///// ↑↑描画処理↑↑ /////
			break;
		}

		///// ↑↑処理↑↑ /////

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
