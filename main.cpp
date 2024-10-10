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
	int blocks_image = Novice::LoadTexture("./Resources/images/blocks.png");

	///// 初期化 /////
	//画面幅
	//横
	float screenBeside = 320.0f;
	float screenvertical = 40.0f;
	
	//画面切り替え
	int scene = game;

	//loadMap
	int map[8][8];
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			map[y][x] = stage1(y, x);
		}
	}

	//block
	float blockSize = 80.0f;
	Vector2 blockPos[8][8];
	Vector2 blockRadius[8][8];
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			blockRadius[y][x] = { blockSize / 2.0f,blockSize / 2.0f };
			blockPos[y][x].x = blockSize * x + blockRadius[y][x].x + screenBeside;
			blockPos[y][x].y = blockSize * y + blockRadius[y][x].y + screenvertical;
		}
	}


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

				///// ↑↑更新処理↑↑ /////
				///// ↓↓描画処理↓↓ /////

				//blocksの表示
				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {
						Novice::DrawQuad(
							int(blockPos[y][x].x - blockRadius[y][x].x), int(blockPos[y][x].y - blockRadius[y][x].y),
							int(blockPos[y][x].x + blockRadius[y][x].x), int(blockPos[y][x].y - blockRadius[y][x].y),
							int(blockPos[y][x].x - blockRadius[y][x].x), int(blockPos[y][x].y + blockRadius[y][x].y),
							int(blockPos[y][x].x + blockRadius[y][x].x), int(blockPos[y][x].y + blockRadius[y][x].y),
							map[y][x] * int(blockSize), 0, int(blockSize), int(blockSize), blocks_image, WHITE
						);
					}
				}

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
