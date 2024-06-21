#include <Novice.h>
#include "Matrix.h"
#include "Vector.h"
#include <ImGuiManager.h>
#include <imgui.h>

const char kWindowTitle[] = "LE2B_28_ヨシザワ_カツヤ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 ViewProjectionMatrix;
	Matrix4x4 viewportMatrix;


	Vector3 rotate1{ 0.0f, 0.0f, 0.0f };
	Vector3 rotate2{ -0.05f, -2.49f, 0.15f };
	OBB obb1{
		.center{0.0f, 0.0f, 0.0f},
		.orientations{{1.0f, 0.0f, 0.0f},
					  {0.0f, 1.0f, 0.0f},
					  {0.0f, 0.0f, 1.0f}},
		.size{0.83f, 0.26f, 0.24f}
	};
	OBB obb2{
		.center{0.9f, 0.66f, 0.78f},
		.orientations{{1.0f, 0.0f, 0.0f},
					  {0.0f, 1.0f, 0.0f},
					  {0.0f, 0.0f, 1.0f}},
		.size{0.5f, 0.37f, 0.5f}
	};
	
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		ViewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		//回転行列を作成
		Matrix4x4 rotateMatrix1 = Multiply(MakeRotateXMatrix(rotate1.x), Multiply(MakeRotateYMatrix(rotate1.y), MakeRotateZMatrix(rotate1.z)));

		//回転行列から軸を抽出
		obb1.orientations[0].x = rotateMatrix1.m[0][0];
		obb1.orientations[0].y = rotateMatrix1.m[0][1];
		obb1.orientations[0].z = rotateMatrix1.m[0][2];

		obb1.orientations[1].x = rotateMatrix1.m[1][0];
		obb1.orientations[1].y = rotateMatrix1.m[1][1];
		obb1.orientations[1].z = rotateMatrix1.m[1][2];

		obb1.orientations[2].x = rotateMatrix1.m[2][0];
		obb1.orientations[2].y = rotateMatrix1.m[2][1];
		obb1.orientations[2].z = rotateMatrix1.m[2][2];

		//回転行列を作成
		Matrix4x4 rotateMatrix2 = Multiply(MakeRotateXMatrix(rotate2.x), Multiply(MakeRotateYMatrix(rotate2.y), MakeRotateZMatrix(rotate2.z)));

		//回転行列から軸を抽出
		obb2.orientations[0].x = rotateMatrix2.m[0][0];
		obb2.orientations[0].y = rotateMatrix2.m[0][1];
		obb2.orientations[0].z = rotateMatrix2.m[0][2];

		obb2.orientations[1].x = rotateMatrix2.m[1][0];
		obb2.orientations[1].y = rotateMatrix2.m[1][1];
		obb2.orientations[1].z = rotateMatrix2.m[1][2];

		obb2.orientations[2].x = rotateMatrix2.m[2][0];
		obb2.orientations[2].y = rotateMatrix2.m[2][1];
		obb2.orientations[2].z = rotateMatrix2.m[2][2];

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("OBBcenter1", &obb1.center.x, 0.01f);
		ImGui::DragFloat3("rotate1", &rotate1.x, 0.01f);
		ImGui::DragFloat3("OBB1.orientations[0]", &obb1.orientations[0].x, 0.01f);
		ImGui::DragFloat3("OBB1.orientations[1]", &obb1.orientations[1].x, 0.01f);
		ImGui::DragFloat3("OBB1.orientations[2]", &obb1.orientations[2].x, 0.01f);
		ImGui::DragFloat3("OBB1.size", &obb1.size.x, 0.01f);
		ImGui::DragFloat3("OBB2center", &obb2.center.x, 0.01f);
		ImGui::DragFloat3("rotate2", &rotate2.x, 0.01f);
		ImGui::DragFloat3("OBB2.orientations[0]", &obb2.orientations[0].x, 0.01f);
		ImGui::DragFloat3("OBB2.orientations[1]", &obb2.orientations[1].x, 0.01f);
		ImGui::DragFloat3("OBB2.orientations[2]", &obb2.orientations[2].x, 0.01f);
		ImGui::DragFloat3("OBB2.size", &obb2.size.x, 0.01f);

		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(ViewProjectionMatrix, viewportMatrix);

		
		DrawOBB(obb1, ViewProjectionMatrix, viewportMatrix, WHITE);
		
		if (IsCollision(obb1, obb2)) {
			DrawOBB(obb2, ViewProjectionMatrix, viewportMatrix, RED);

		}
		else {
			DrawOBB(obb2, ViewProjectionMatrix, viewportMatrix, WHITE);
		}
		
		///
		/// ↑描画処理ここまで
		///

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
