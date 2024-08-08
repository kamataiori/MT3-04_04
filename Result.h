#pragma once
#include "MathFunc.h"
class Result
{

public:

	Plane plane
	{
		Normalize({-0.2f,0.9f,-0.3f}),
		0.0f
	};

	Ball ball
	{
		{0.8f,1.2f,0.3f},
		{0,0,0},
		{0,0,0},
		2.0f,
		0.05f,
		WHITE
	};

	Sphere sphere
	{
		{0,0,0},
		0.08f
	};

	float e = 0.8f;

	unsigned int color = WHITE;

	float deltaTime = 1.0f / 60.0f;

	bool isStart = false;

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	float cameraSpeed = 0.01f;

	Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, (float)kWindowWidth / (float)kWindowHeight, 0.1f, 100.0f);
	Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, (float)kWindowWidth, (float)kWindowHeight, 0.0f, 1.0f);





	void Initialize();


	void Update();


	void Draw();

};

