﻿#pragma once
#include "Struct.h"
#include <Novice.h>

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

//内積
float Dot(const Vector3& v1, const Vector3& v2);

//長さ(ノルム)
float Length(const Vector3& v);

//正規化
Vector3 Normalize(const Vector3& v);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

//正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2);

//最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);