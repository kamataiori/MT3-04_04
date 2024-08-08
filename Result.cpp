#include "Result.h"

void Result::Initialize()
{
	

}

void Result::Update()
{
	if (isStart)
	{
		ball.acceleration = { 0,-9.8f,0 };
	}
	else
	{
		ball =
		{
			{0.8f,1.2f,0.3f},
			{0,0,0},
			{0,0,0},
			2.0f,
			0.05f,
			WHITE
		};
	}

	ball.velocity = ball.velocity + ball.acceleration * deltaTime;
	ball.position = ball.position + ball.velocity * deltaTime;

	sphere.center = ball.position;
	sphere.radius = ball.radius;

	if (IsCollision(sphere, plane))
	{
		Vector3 reflected = Reflect(ball.velocity, plane.normal);
		Vector3 projectToNormal = Project(reflected, plane.normal);
		Vector3 movingrection = reflected - projectToNormal;
		ball.velocity = projectToNormal * e + movingrection;
	}


	ImGui::Begin("window");
	if (ImGui::Button("start"))
	{
		if (!isStart)
		{
			isStart = true;
		}
		else
		{
			isStart = false;
		}
	}
	ImGui::End();

}

void Result::Draw()
{
	/*DrawGrid(viewMatrixProjectionMatrix, viewportMatrix);
	screenBall = Transform(Transform(ball.position, viewMatrixProjectionMatrix), viewportMatrix);
	screenSpring = Transform(Transform(spring.anchor, viewMatrixProjectionMatrix), viewportMatrix);
	Transform(spring.anchor, worldViewProjectionMatrix);
	DrawSphere({ ball.position, ball.radius }, viewMatrixProjectionMatrix, viewportMatrix, ball.color);
	Novice::DrawLine((int)screenBall.x, (int)screenBall.y, (int)screenSpring.x, (int)screenSpring.y, WHITE);*/

	DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, color);
	DrawPlane(plane, viewProjectionMatrix, viewportMatrix, color);

	DrawGrid(viewProjectionMatrix, viewportMatrix);
}
