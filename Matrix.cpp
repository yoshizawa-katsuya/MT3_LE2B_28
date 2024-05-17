#include "Matrix.h"
#include "Vector.h"

Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 matrix;

	matrix.m[0][0] = 1;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[1][0] = 0;
	matrix.m[1][1] = 1;
	matrix.m[1][2] = 0;
	matrix.m[2][0] = translate.x;
	matrix.m[2][1] = translate.y;
	matrix.m[2][2] = 1;

	return matrix;
}

Matrix3x3 Invarse(Matrix3x3 matrix) {
	Matrix3x3 invarse;
	float A_1 = 1 / (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]
		- matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	invarse.m[0][0] = A_1 * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	invarse.m[0][1] = A_1 * -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	invarse.m[0][2] = A_1 * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	invarse.m[1][0] = A_1 * -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	invarse.m[1][1] = A_1 * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	invarse.m[1][2] = A_1 * -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);
	invarse.m[2][0] = A_1 * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	invarse.m[2][1] = A_1 * -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	invarse.m[2][2] = A_1 * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return invarse;
}

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 matrix;

	matrix.m[0][0] = 2 / (right - left);
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[1][0] = 0;
	matrix.m[1][1] = 2 / (top - bottom);
	matrix.m[1][2] = 0;
	matrix.m[2][0] = (left + right) / (left - right);
	matrix.m[2][1] = (top + bottom) / (bottom - top);
	matrix.m[2][2] = 1;

	return matrix;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float wigth, float height) {
	Matrix3x3 matrix;

	matrix.m[0][0] = wigth / 2;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[1][0] = 0;
	matrix.m[1][1] = -(height / 2);
	matrix.m[1][2] = 0;
	matrix.m[2][0] = left + (wigth / 2);
	matrix.m[2][1] = top + (height / 2);
	matrix.m[2][2] = 1;

	return matrix;


}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 matrix;

	matrix.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	matrix.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	matrix.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
	matrix.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	matrix.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	matrix.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
	matrix.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	matrix.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	matrix.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];

	return matrix;
}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;

	return result;
}

Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 Anser;

	Anser.m[0][0] = cosf(theta);
	Anser.m[0][1] = sinf(theta);
	Anser.m[0][2] = 0;
	Anser.m[1][0] = -sinf(theta);
	Anser.m[1][1] = cosf(theta);
	Anser.m[1][2] = 0;
	Anser.m[2][0] = 0;
	Anser.m[2][1] = 0;
	Anser.m[2][2] = 1;

	return Anser;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 matrix;

	matrix.m[0][0] = m1.m[0][0] + m2.m[0][0];
	matrix.m[0][1] = m1.m[0][1] + m2.m[0][1];
	matrix.m[0][2] = m1.m[0][2] + m2.m[0][2];
	matrix.m[0][3] = m1.m[0][3] + m2.m[0][3];

	matrix.m[1][0] = m1.m[1][0] + m2.m[1][0];
	matrix.m[1][1] = m1.m[1][1] + m2.m[1][1];
	matrix.m[1][2] = m1.m[1][2] + m2.m[1][2];
	matrix.m[1][3] = m1.m[1][3] + m2.m[1][3];

	matrix.m[2][0] = m1.m[2][0] + m2.m[2][0];
	matrix.m[2][1] = m1.m[2][1] + m2.m[2][1];
	matrix.m[2][2] = m1.m[2][2] + m2.m[2][2];
	matrix.m[2][3] = m1.m[2][3] + m2.m[2][3];

	matrix.m[3][0] = m1.m[3][0] + m2.m[3][0];
	matrix.m[3][1] = m1.m[3][1] + m2.m[3][1];
	matrix.m[3][2] = m1.m[3][2] + m2.m[3][2];
	matrix.m[3][3] = m1.m[3][3] + m2.m[3][3];

	return matrix;

}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 matrix;

	matrix.m[0][0] = m1.m[0][0] - m2.m[0][0];
	matrix.m[0][1] = m1.m[0][1] - m2.m[0][1];
	matrix.m[0][2] = m1.m[0][2] - m2.m[0][2];
	matrix.m[0][3] = m1.m[0][3] - m2.m[0][3];

	matrix.m[1][0] = m1.m[1][0] - m2.m[1][0];
	matrix.m[1][1] = m1.m[1][1] - m2.m[1][1];
	matrix.m[1][2] = m1.m[1][2] - m2.m[1][2];
	matrix.m[1][3] = m1.m[1][3] - m2.m[1][3];

	matrix.m[2][0] = m1.m[2][0] - m2.m[2][0];
	matrix.m[2][1] = m1.m[2][1] - m2.m[2][1];
	matrix.m[2][2] = m1.m[2][2] - m2.m[2][2];
	matrix.m[2][3] = m1.m[2][3] - m2.m[2][3];

	matrix.m[3][0] = m1.m[3][0] - m2.m[3][0];
	matrix.m[3][1] = m1.m[3][1] - m2.m[3][1];
	matrix.m[3][2] = m1.m[3][2] - m2.m[3][2];
	matrix.m[3][3] = m1.m[3][3] - m2.m[3][3];

	return matrix;

}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 matrix;

	matrix.m[0][0] = (m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) + (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0]);
	matrix.m[0][1] = (m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) + (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1]);
	matrix.m[0][2] = (m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) + (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2]);
	matrix.m[0][3] = (m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) + (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3]);

	matrix.m[1][0] = (m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) + (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0]);
	matrix.m[1][1] = (m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) + (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1]);
	matrix.m[1][2] = (m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) + (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2]);
	matrix.m[1][3] = (m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) + (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3]);

	matrix.m[2][0] = (m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) + (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0]);
	matrix.m[2][1] = (m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) + (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1]);
	matrix.m[2][2] = (m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) + (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2]);
	matrix.m[2][3] = (m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) + (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3]);

	matrix.m[3][0] = (m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) + (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0]);
	matrix.m[3][1] = (m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) + (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1]);
	matrix.m[3][2] = (m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) + (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2]);
	matrix.m[3][3] = (m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) + (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3]);

	return matrix;

}

Matrix4x4 Inverse(const Matrix4x4& m) {

	Matrix4x4 inverse;
	float A_1 = 1 / ((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])
		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])
		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]));


	inverse.m[0][0] = A_1 * ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2])
						   - (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2]));
	inverse.m[0][1] = A_1 * (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
						    + (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2]));
	inverse.m[0][2] = A_1 * ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2])
						   - (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2]));
	inverse.m[0][3] = A_1 * (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2])
						    + (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2]));

	inverse.m[1][0] = A_1 * (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2])
							+ (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2]));
	inverse.m[1][1] = A_1 * ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2])
						   - (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2]));
	inverse.m[1][2] = A_1 * (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
							+ (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2]));
	inverse.m[1][3] = A_1 * ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2])
						   - (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2]));

	inverse.m[2][0] = A_1 * ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1])
						   - (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1]));
	inverse.m[2][1] = A_1 * (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
							+ (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1]));
	inverse.m[2][2] = A_1 * ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1])
						   - (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1]));
	inverse.m[2][3] = A_1 * (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
							+ (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1]));

	inverse.m[3][0] = A_1 * (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
							+ (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1]));
	inverse.m[3][1] = A_1 * ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1])
						   - (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1]));
	inverse.m[3][2] = A_1 * (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
							+ (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1]));
	inverse.m[3][3] = A_1 * ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1])
						   - (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1]));

	return inverse;

}

Matrix4x4 Transpose(const Matrix4x4& m) {

	Matrix4x4 matrix;

	matrix.m[0][0] = m.m[0][0];
	matrix.m[0][1] = m.m[1][0];
	matrix.m[0][2] = m.m[2][0];
	matrix.m[0][3] = m.m[3][0];

	matrix.m[1][0] = m.m[0][1];
	matrix.m[1][1] = m.m[1][1];
	matrix.m[1][2] = m.m[2][1];
	matrix.m[1][3] = m.m[3][1];

	matrix.m[2][0] = m.m[0][2];
	matrix.m[2][1] = m.m[1][2];
	matrix.m[2][2] = m.m[2][2];
	matrix.m[2][3] = m.m[3][2];

	matrix.m[3][0] = m.m[0][3];
	matrix.m[3][1] = m.m[1][3];
	matrix.m[3][2] = m.m[2][3];
	matrix.m[3][3] = m.m[3][3];

	return matrix;
}

Matrix4x4 MakeIdentity4x4() {

	Matrix4x4 matrix = { 0 };

	matrix.m[0][0] = 1;
	matrix.m[1][1] = 1;
	matrix.m[2][2] = 1;
	matrix.m[3][3] = 1;

	return matrix;

}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {

	Matrix4x4 m = { 0 };

	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;

	m.m[3][0] = translate.x;
	m.m[3][1] = translate.y;
	m.m[3][2] = translate.z;

	return m;

}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {

	Matrix4x4 m = { 0 };

	m.m[0][0] = scale.x;
	m.m[1][1] = scale.y;
	m.m[2][2] = scale.z;
	m.m[3][3] = 1;

	return m;

}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;

}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

Matrix4x4 MakeRotateXMatrix(float radian) {

	Matrix4x4 m = { 0 };

	m.m[0][0] = 1;
	m.m[3][3] = 1;

	m.m[1][1] = std::cos(radian);
	m.m[1][2] = std::sin(radian);
	m.m[2][1] = -std::sin(radian);
	m.m[2][2] = std::cos(radian);

	return m;

}

Matrix4x4 MakeRotateYMatrix(float radian) {

	Matrix4x4 m = { 0 };

	m.m[1][1] = 1;
	m.m[3][3] = 1;

	m.m[0][0] = std::cos(radian);
	m.m[0][2] = -std::sin(radian);
	m.m[2][0] = std::sin(radian);
	m.m[2][2] = std::cos(radian);

	return m;

}

Matrix4x4 MakeRotateZMatrix(float radian) {

	Matrix4x4 m = { 0 };

	m.m[2][2] = 1;
	m.m[3][3] = 1;

	m.m[0][0] = std::cos(radian);
	m.m[0][1] = std::sin(radian);
	m.m[1][0] = -std::sin(radian);
	m.m[1][1] = std::cos(radian);

	return m;

}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 m;

	Matrix4x4 scalematrix = MakeScaleMatrix(scale);

	Matrix4x4 rotatematrix = Multiply(Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)), MakeRotateZMatrix(rotate.z));

	Matrix4x4 translatematrix = MakeTranslateMatrix(translate);

	m = Multiply(Multiply(scalematrix, rotatematrix), translatematrix);

	return m;

}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {

	Matrix4x4 m = { 0 };

	m.m[0][0] = (1 / aspectRatio) * (1 / std::tan(fovY / 2));
	m.m[1][1] = 1 / std::tan(fovY / 2);
	m.m[2][2] = farClip / (farClip - nearClip);
	m.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	m.m[2][3] = 1;

	return m;

}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {

	Matrix4x4 m = { 0 };

	m.m[0][0] = 2 / (right - left);
	m.m[1][1] = 2 / (top - bottom);
	m.m[2][2] = 1 / (farClip - nearClip);
	m.m[3][3] = 1;

	m.m[3][0] = (left + right) / (left - right);
	m.m[3][1] = (top + bottom) / (bottom - top);
	m.m[3][2] = nearClip / (nearClip - farClip);

	return m;

}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {

	Matrix4x4 m = { 0 };

	m.m[0][0] = width / 2;
	m.m[1][1] = -(height / 2);
	m.m[2][2] = maxDepth - minDepth;
	m.m[3][3] = 1;

	m.m[3][0] = left + (width / 2);
	m.m[3][1] = top + (height / 2);
	m.m[3][2] = minDepth;

	return m;

}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		Vector3 starting{ -kGridHalfWidth + (kGridEvery * xIndex), 0.0f, -kGridHalfWidth };
		starting = Transform(starting, viewProjectionMatrix);
		starting = Transform(starting, viewportMatrix);


		Vector3 end{ -kGridHalfWidth + (kGridEvery * xIndex), 0.0f, kGridHalfWidth };
		end = Transform(end, viewProjectionMatrix);
		end = Transform(end, viewportMatrix);

		if (kSubdivision / 2 != xIndex) {
			Novice::DrawLine(int(starting.x), int(starting.y), int(end.x), int(end.y), 0xAAAAAAFF);
		}
		else {
			Novice::DrawLine(int(starting.x), int(starting.y), int(end.x), int(end.y), BLACK);
		}
	}
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		Vector3 starting{ -kGridHalfWidth, 0.0f, -kGridHalfWidth + (kGridEvery * xIndex) };
		starting = Transform(starting, viewProjectionMatrix);
		starting = Transform(starting, viewportMatrix);


		Vector3 end{ kGridHalfWidth, 0.0f, -kGridHalfWidth + (kGridEvery * xIndex) };
		end = Transform(end, viewProjectionMatrix);
		end = Transform(end, viewportMatrix);

		if (kSubdivision / 2 != xIndex) {
			Novice::DrawLine(int(starting.x), int(starting.y), int(end.x), int(end.y), 0xAAAAAAFF);
		}
		else {
			Novice::DrawLine(int(starting.x), int(starting.y), int(end.x), int(end.y), BLACK);
		}
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const uint32_t kSubdivision = 10;
	const float kLonEvery = float(2.0f * M_PI) / kSubdivision;
	const float kLatEvery = float(M_PI) / kSubdivision;
	
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = float(-M_PI) / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			Vector3 a, b, c;

			a = { sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon), sphere.center.y + sphere.radius * std::sin(lat), sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon) };
			b = { sphere.center.x + sphere.radius * std::cos(lat + kLatEvery) * std::cos(lon), sphere.center.y + sphere.radius * std::sin(lat + kLatEvery), sphere.center.z + sphere.radius * std::cos(lat + kLatEvery) * std::sin(lon) };
			c = { sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon + kLonEvery), sphere.center.y + sphere.radius * std::sin(lat), sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon + kLonEvery) };

			a = Transform(a, viewProjectionMatrix);
			a = Transform(a, viewportMatrix);

			b = Transform(b, viewProjectionMatrix);
			b = Transform(b, viewportMatrix);

			c = Transform(c, viewProjectionMatrix);
			c = Transform(c, viewportMatrix);

			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);

		}
	}

}

void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);

}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);

}

bool IsCollision(const Sphere& s1, const Sphere& s2) {

	//2つの球の中心点間の距離を求める
	float distance = Length(Subtract(s2.center, s1.center));
	//半径の合計よりも短ければ衝突
	if (!(distance <= s1.radius + s2.radius)) {
		return false;
	}
	return true;
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {

	float k = Dot(plane.normal, sphere.center) - plane.distance;
	if (k < 0) {
		k *= -1;
	}

	if (!(k <= sphere.radius)) {
		return false;
	}
	return true;
}

bool IsCollision(const Line& line, const Plane& plane) {

	float dot = Dot(line.diff, plane.normal);
	if (dot == 0.0f) {
		return false;
	}
	return true;

}

bool IsCollision(const Ray& ray, const Plane& plane) {

	float dot = Dot(ray.diff, plane.normal);
	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(ray.origin, plane.normal)) / dot;
	if (0 <= t) {
		return true;
	}
	return false;


}

bool IsCollision(const Segment& segment, const Plane& plane) {

	float dot = Dot(segment.diff, plane.normal);
	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
	if (0 <= t && t <= 1) {
		return true;
	}
	return false;

}