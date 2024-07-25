#include "Result.h"

void Result::Initialize()
{
	position = { -0.90f,0.3f,0.0f, };
	angle = 0.0f;
	deltaTime = 0.0f;

	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	cameraRotate = { 0.0f,0.0f,0.0f };

	cameraTranslate = { 0.0f,0.0f,0.0f };
	cameraPosition = SphericalToCartesian(radius, theta, phi);
	cameraTarget = { 0.0f, 0.0f, 0.0f };
	cameraUp = { 0.0f, 1.0f, 0.0f };

	viewMatrix = MakeLookAtMatrix4x4(cameraPosition, cameraTarget, cameraUp);
	worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	viewMatrixProjectionMatrix = Multiply(viewMatrix, projectionMatrix);

}

void Result::Update()
{
	ImGui::Begin("start");
	if (ImGui::Button("Start"))
	{
		start = true;
	}
	ImGui::End();
	if (start)
	{
		ball.velocity += ball.acceleration * deltaTime;
		ball.position += ball.velocity * deltaTime;
		
	}

}

void Result::Draw()
{
	/*DrawGrid(viewMatrixProjectionMatrix, viewportMatrix);
	screenBall = Transform(Transform(ball.position, viewMatrixProjectionMatrix), viewportMatrix);
	screenSpring = Transform(Transform(spring.anchor, viewMatrixProjectionMatrix), viewportMatrix);
	Transform(spring.anchor, worldViewProjectionMatrix);
	DrawSphere({ ball.position, ball.radius }, viewMatrixProjectionMatrix, viewportMatrix, ball.color);
	Novice::DrawLine((int)screenBall.x, (int)screenBall.y, (int)screenSpring.x, (int)screenSpring.y, WHITE);*/

	DrawSphere({ position,sphere.radius }, viewProjectionMatrix, viewportMatrix, sphere.color);


	DrawGrid(viewProjectionMatrix, viewportMatrix);
}
