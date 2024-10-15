#include <Novice.h>
#include "enum.h"
#include "structure.h"
#include "map.h"

const char kWindowTitle[] = "計算迷宮";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	///// 画像の読み取り /////
	//blocks
	int blocks_image = Novice::LoadTexture("./Resources/images/blocks.png");

	//player
	int player_image = Novice::LoadTexture("./Resources/images/player.png");

	///// 初期化 /////
	//画面幅
	//横
	float screenBeside = 280.0f;
	
	//画面切り替え
	int scene = game;

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
	player.pos = { blockPos[1][1].x,blockPos[1][1].y };
	player.Nextpos = { 0.0f,0.0f };
	player.status.velocity = playerSize;
	player.now = { 0,0 };
	player.next = { 0,0 };

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///// ↓↓処理↓↓ /////
		switch (scene) {
			case title:
				///// ↓↓更新処理↓↓ /////

				///// ↑↑更新処理↑↑ /////
				///// ↓↓描画処理↓↓ /////

				///// ↑↑描画処理↑↑ /////
				break;
			case stageselect:
				///// ↓↓更新処理↓↓ /////

				///// ↑↑更新処理↑↑ /////
				///// ↓↓描画処理↓↓ /////

				///// ↑↑描画処理↑↑ /////
				break;
			case game:
				///// ↓↓更新処理↓↓ /////

				///// playerの移動キー /////
				if (keys[DIK_W] && !preKeys[DIK_W] && !keys[DIK_S]) {
					//仮のposに代入
					player.Nextpos.x = player.pos.x;
					player.Nextpos.y = player.pos.y - player.status.velocity;

					//場所決め
					player.next.beside = int(player.Nextpos.x / playerSize);
					player.next.vertical = int(player.Nextpos.y / playerSize);

					//もしも空白ならば
					if (map[player.next.vertical][player.next.beside] == 0) {
						player.pos.y -= player.status.velocity;
					}

				} else if (keys[DIK_S] && !preKeys[DIK_S] && !keys[DIK_W]) {
					//仮のposに代入
					player.Nextpos.x = player.pos.x;
					player.Nextpos.y = player.pos.y + player.status.velocity;

					//場所決め
					player.next.beside = int(player.Nextpos.x / playerSize);
					player.next.vertical = int(player.Nextpos.y / playerSize);

					//もしも空白ならば
					if (map[player.next.vertical][player.next.beside] == 0) {
						player.pos.y += player.status.velocity;
					}

				} else if (keys[DIK_D] && !preKeys[DIK_D] && !keys[DIK_A]) {
					//仮のposに代入
					player.Nextpos.x = player.pos.x + player.status.velocity;
					player.Nextpos.y = player.pos.y;

					//場所決め
					player.next.beside = int(player.Nextpos.x / playerSize);
					player.next.vertical = int(player.Nextpos.y / playerSize);

					//もしも空白ならば
					if (map[player.next.vertical][player.next.beside] == 0) {
						player.pos.x += player.status.velocity;
					}

				} else if (keys[DIK_A] && !preKeys[DIK_A] && !keys[DIK_D]) {
					//仮のposに代入
					player.Nextpos.x = player.pos.x - player.status.velocity;
					player.Nextpos.y = player.pos.y;

					//場所決め
					player.next.beside = int(player.Nextpos.x / playerSize);
					player.next.vertical = int(player.Nextpos.y / playerSize);

					//もしも空白ならば
					if (map[player.next.vertical][player.next.beside] == 0) {
						player.pos.x -= player.status.velocity;
					}

				}

				///// playerの場所決め /////
				player.now.beside = int(player.pos.x / playerSize);
				player.now.vertical = int(player.pos.y / playerSize);

				///// ↑↑更新処理↑↑ /////
				///// ↓↓描画処理↓↓ /////

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

				Novice::DrawSprite(int(player.pos.x - player.radius.x + screenBeside), int(player.pos.y - player.radius.y), player_image, 1, 1, 0.0f, WHITE);

				///// ↑↑描画処理↑↑ /////
				break;
			case gameclear:
				///// ↓↓更新処理↓↓ /////

				///// ↑↑更新処理↑↑ /////
				///// ↓↓描画処理↓↓ /////

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
