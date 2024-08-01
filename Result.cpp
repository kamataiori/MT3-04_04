#include "Result.h"

void Result::Initialize()
{
	position = { -0.90f,0.3f,0.0f, };
	angle = 0.0f;
	deltaTime = 0.0f;

	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.acceleration = { 0.0f,-9.8f,0.0f };
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
	 e = 0.8f;
	 worldviewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

	viewMatrix = MakeLookAtMatrix4x4(cameraPosition, cameraTarget, cameraUp);
	worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	viewMatrixProjectionMatrix = Multiply(viewMatrix, projectionMatrix);


	cameraTranslate = { 0.0f,1.9f,-6.49f };
	cameraRotate = { 0.26f,0.0f,0.0f };
	/*sphere.center.x = 0;
	sphere.center.y = 0;
	sphere.center.z = 0;
	sphere.radius = 0.5f;*/
	plane.normal.x = 0.0f;
	plane.normal.y = 1.0f;
	plane.normal.z = 0.0f;
	plane.distance = 0.0f;

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
		ball.velocity =Add(ball.velocity,Multiply(deltaTime, ball.acceleration));
		ball.position = Add(ball.velocity, Multiply(deltaTime,ball.velocity ));
		if (IsCollision(Sphere{ ball.position,ball.radius }, plane))
		{
			Vector3 reflected = Reflect(ball.velocity, plane.normal);
			Vector3 projectNormal = Project(reflected, plane.normal);
			Vector3 movingDirection = Subtract(reflected , projectNormal);
			ball.velocity = Add(Multiply(e,projectNormal) , movingDirection);
		}
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
	DrawPlane(plane, worldviewProjectionMatrix, viewportMatrix, WHITE);

	DrawGrid(viewProjectionMatrix, viewportMatrix);
}
