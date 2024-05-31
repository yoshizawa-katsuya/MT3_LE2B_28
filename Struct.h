#pragma once

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct intVector2 {
	int x;
	int y;
};

struct Vector2 {
	float x;
	float y;
};

struct Vector3{
	float x;
	float y;
	float z;
};

struct Matrix3x3
{
	float m[3][3];
};

struct Matrix4x4
{
	float m[4][4];
};

struct Ball
{

	Vector2 pos;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float radius;
	unsigned int color;

};

struct Box
{
	Vector2 pos;
	Vector2 size;
	Vector2 valocity;
	Vector2 acceleration;
	float mass;
	unsigned int color;
};

struct Sphere {
	Vector3 center;
	float radius;
};

struct Line {
	Vector3 origin;
	Vector3 diff;
};

struct Ray {
	Vector3 origin;
	Vector3 diff;
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
};

struct Plane {
	Vector3 normal;	//法線
	float distance;	//距離
};

struct Triangle {
	Vector3 vertices[3];	//頂点
};

struct AABB {
	Vector3 min;
	Vector3 max;
};