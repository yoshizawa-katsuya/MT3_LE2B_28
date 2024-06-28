#include <Novice.h>
#include "Matrix.h"
#include "Vector.h"
#include "Curve.h"
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

	Vector3 translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f},
	};

	Vector3 rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f},
	};

	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
	};
	
	Matrix4x4 worldMatrixS;
	Matrix4x4 worldMatrixE;
	Matrix4x4 worldMatrixH;


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

		worldMatrixS = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		worldMatrixE = Multiply(MakeAffineMatrix(scales[1], rotates[1], translates[1]), worldMatrixS);
		worldMatrixH = Multiply(MakeAffineMatrix(scales[2], rotates[2], translates[2]), worldMatrixE);

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("translate[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);
		ImGui::DragFloat3("translate[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
		ImGui::DragFloat3("translate[2]", &translates[2].x, 0.01f);
		ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);

		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(ViewProjectionMatrix, viewportMatrix);

		Vector3 line[3];
		line[0] = { worldMatrixS.m[3][0], worldMatrixS.m[3][1], worldMatrixS.m[3][2] };
		line[1] = { worldMatrixE.m[3][0], worldMatrixE.m[3][1], worldMatrixE.m[3][2] };
		line[2] = { worldMatrixH.m[3][0], worldMatrixH.m[3][1], worldMatrixH.m[3][2] };

		line[0] = Transform(Transform(line[0], ViewProjectionMatrix), viewportMatrix);
		line[1] = Transform(Transform(line[1], ViewProjectionMatrix), viewportMatrix);
		line[2] = Transform(Transform(line[2], ViewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(static_cast<int>(line[0].x), static_cast<int>(line[0].y), static_cast<int>(line[1].x), static_cast<int>(line[1].y), WHITE);
		Novice::DrawLine(static_cast<int>(line[1].x), static_cast<int>(line[1].y), static_cast<int>(line[2].x), static_cast<int>(line[2].y), WHITE);

		
		DrawSphere({ {worldMatrixS.m[3][0], worldMatrixS.m[3][1], worldMatrixS.m[3][2]}, 0.1f }, ViewProjectionMatrix, viewportMatrix, RED);
		DrawSphere({ {worldMatrixE.m[3][0], worldMatrixE.m[3][1], worldMatrixE.m[3][2]}, 0.1f }, ViewProjectionMatrix, viewportMatrix, GREEN);
		DrawSphere({ {worldMatrixH.m[3][0], worldMatrixH.m[3][1], worldMatrixH.m[3][2]}, 0.1f }, ViewProjectionMatrix, viewportMatrix, BLUE);

		
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
