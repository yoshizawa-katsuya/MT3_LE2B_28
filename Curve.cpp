#include "Curve.h"
#include "Matrix.h"
#include "Vector.h"

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t)
{

	Vector2 p0p1 = Leap(p0, p1, t);

	Vector2 p1p2 = Leap(p1, p2, t);

	Vector2 p = Leap(p0p1, p1p2, t);

	return p;
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Vector3 line[2];
	float t = 0.0f;

	line[0] = Bezier(controlPoint0, controlPoint1, controlPoint2, t);
	line[0] = Transform(Transform(line[0], viewProjectionMatrix), viewportMatrix);

	while (true)
	{
		t += 0.01f;
		if (t > 1.0f) {
			t = 1.0f;
		}
		line[1] = Bezier(controlPoint0, controlPoint1, controlPoint2, t);
		line[1] = Transform(Transform(line[1], viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(static_cast<int>(line[0].x), static_cast<int>(line[0].y), static_cast<int>(line[1].x), static_cast<int>(line[1].y), color);

		line[0] = line[1];

		if (t >= 1.0f) {
			break;
		}

	}

}

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3 p2, float t) {

	Vector3 p0p1 = Leap(p0, p1, t);

	Vector3 p1p2 = Leap(p1, p2, t);

	Vector3 p = Leap(p0p1, p1p2, t);

	return p;

}

Vector2 CatmullRom(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, float t)
{

	Vector2 anser;

	anser.x = (1.0f / 2.0f) * ((-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * (t * t * t) +
						(2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * (t * t) +
						(-p0.x + p2.x) * t + 2.0f * p1.x);

	anser.y = (1.0f / 2.0f) * ((-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * (t * t * t) +
						(2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * (t * t) +
						(-p0.y + p2.y) * t + 2.0f * p1.y);

	return anser;

}

void DrawCatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Vector3& controlPoint3, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{


	Vector3 line[2];
	float t = 0.0f;

	line[0] = CatmullRom(controlPoint0, controlPoint1, controlPoint2, controlPoint3, t);
	line[0] = Transform(Transform(line[0], viewProjectionMatrix), viewportMatrix);

	while (true)
	{
		t += 0.01f;
		if (t > 1.0f) {
			t = 1.0f;
		}
		line[1] = CatmullRom(controlPoint0, controlPoint1, controlPoint2, controlPoint3, t);
		line[1] = Transform(Transform(line[1], viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(static_cast<int>(line[0].x), static_cast<int>(line[0].y), static_cast<int>(line[1].x), static_cast<int>(line[1].y), color);

		line[0] = line[1];

		if (t >= 1.0f) {
			break;
		}

	}


}

Vector3 CatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t)
{

	Vector3 p = Multiply(0.5f, Add(Add(Add(Multiply((t * t * t), Add(Add(Add(Multiply(-1.0f, p0), Multiply(3.0f, p1)), Multiply(-3.0f, p2)), p3)), 
								Multiply((t * t), Add(Add(Add(Multiply(2.0f, p0), Multiply(-5.0f, p1)), Multiply(4.0f, p2)), Multiply(-1.0f, p3)))), 
								Multiply(t, Add(Multiply(-1.0f, p0), p2))), Multiply(2.0f, p1)));

	return p;

}
