#include "Tema1.h"
#include "Objects2D.h"
#include "Transform2D.h"
#include <vector>
#include <iostream>
#include <time.h> 
#include <Core/Engine.h>

using namespace std;

Tema1::Tema1()
{
	translateBow = 0;
	translateY = 0;
	angularStepBow = 0;
	angularStepArrow = 0;
	angularStepShuriken = 0;
	arrowposY = BowY;
	arrow_speed = 0;
	arrowposX = BowX;
	translateArrow = 0;
	scalepowerBarX = 1;
	numberoflives = 3;
}

Tema1::~Tema1()
{

}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	srand(time(0));
	//creating the bow mesh
	{
		Mesh* mesh = Objects2D::MakeBow("bow", glm::vec3(BowX, BowY, 0), BowRadius, glm::vec3(0, 0, 0));
		AddMeshToList(mesh);
		
	}
	// creating tje arrow mesh
	{
		Mesh* mesh = Objects2D::MakeArrow("arrow", glm::vec3(BowX, BowY, 0), ArrowLength, ArrowSize, glm::vec3(0.5, 0.2, 0.1));
		AddMeshToList(mesh);
	}
	// creating the red circle mesh
	{
		Mesh* mesh = Objects2D::MakeCircle("redcircle", glm::vec3(0, 0, 0), CircleRadius, glm::vec3(1, 0, 0));
		AddMeshToList(mesh);
	}
	// creating the yellow mesh
	{
		Mesh* mesh = Objects2D::MakeCircle("yellowcircle", glm::vec3(0, 0, 0), CircleRadius, glm::vec3(1, 1, 0));
		AddMeshToList(mesh);
	}
	// creating the shuriken mesh
	{
		Mesh* mesh = Objects2D::MakeShuriken("shuriken", glm::vec3(0, 0, 0), 50, glm::vec3(1, 1, 1));
		AddMeshToList(mesh);
	}
	// creating the powerbar mesh
	{
		Mesh* mesh = Objects2D::MakePowerBar("powerbar", glm::vec3(BowX, BowY - 150, 0), 10, glm::vec3(0, 1, 0));
		AddMeshToList(mesh);
	}
	// creating the lives mesh
	{
		Mesh* mesh = Objects2D::MakeHeart("lives", glm::vec3(0, 0, 0), 7, glm::vec3(1, 0, 0));
		AddMeshToList(mesh);

	}
	// creating the polyline mesh
	{
		Mesh* mesh = Objects2D::MakePoliline("polyline", glm::vec3(0, 0, 0), 20 ,glm::vec3(0, 0, 0));
		AddMeshToList(mesh);

	}
	
	InitObjectsDissapear();
	InitRangeLimitsObjects();
	InitPositionObjects();
}
// init the disappearance vectors of the objects as false
void Tema1::InitObjectsDissapear() {
	// red balloons
	for (int i = 0; i < 6; i++) {
		redBalloonDissapear[i] = false;
	}
	// yellow balloons
	for (int i = 0; i < 4; i++) {
		shurikenDissapear[i] = false;
	}
	// shurikens
	for (int i = 0; i < 3; i++) {
		yellowBalloonDissapear[i] = false;
	}
}
//setting ranges for each object appearance
void Tema1::InitRangeLimitsObjects() {
	// red balloons - on OX axis
	int x = 570;
	for (int i = 0; i < 6; i++) {
		vecBallonLimits[i].leftlimit = x;
		vecBallonLimits[i].rightlimit = x + 100;
		x += 100;
	}
	// yellow balloons - on OX axis
	x = 620;
	for (int i = 0; i < 3; i++) {
		vecBallonLimitsYell[i].leftlimit = x;
		x += 100;
		vecBallonLimitsYell[i].rightlimit = x;
		x += 100;
	}
	// shurikens - on OY axis
	x = 200;
	for (int i = 0; i < 4; i++) {
		vecShuriken[i].leftlimit = x;
		vecShuriken[i].rightlimit = x + 100;
		x += 100;
	}
}
// initialization of positions and scaling for each object
void Tema1::InitPositionObjects() {
	// red balloons
	for (int i = 0; i < 6; i++) {
		// random selection from the previously set range
		redBalloonPosX[i] = (rand() % (vecBallonLimits[i].rightlimit - vecBallonLimits[i].leftlimit + 1)) + vecBallonLimits[i].leftlimit;
		redBalloonPosY[i] = (rand() % (1000 - 0 + 1)) + 0 - 1000;
		// range 0.5- 1 for scaling
		redBalloonScaleX[i] = 0.5 + ((double)rand() / RAND_MAX) * (1 - 0.5);
		redBalloonScaleY[i] = redBalloonScaleX[i];
	}
	// yellow balloons
	for (int i = 0; i < 3; i++) {
		// random selection from the previously set range
		yellowBalloonPosX[i] = (rand() % (vecBallonLimitsYell[i].rightlimit - vecBallonLimitsYell[i].leftlimit + 1)) + vecBallonLimitsYell[i].leftlimit;
		yellowBalloonPosY[i] = (rand() % (2000 - 0 + 1)) + 0 - 2000;
		// range 0.5- 1 for scaling
		yellowBalloonScaleX[i] = 0.5 + ((double)rand() / RAND_MAX) * (1 - 0.5);
		yellowBalloonScaleY[i] = yellowBalloonScaleX[i];
	}
	// shuriken
	for (int i = 0; i < 4; i++) {
		shurikenPosX[i] = (rand() % (3000 - 1500 + 1)) + 1500;
		// random selection from the previously set range
		shurikenPosY[i] = (rand() % (vecShuriken[i].rightlimit - vecShuriken[i].leftlimit + 1)) + vecShuriken[i].leftlimit;
		shurikenScaleX[i] = 1;
		shurikenScaleY[i] = 1;
	}
}
void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0.7, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	RenderBow();
	RenderArrow(deltaTimeSeconds);
	RenderRedBallon(deltaTimeSeconds);
	RenderYellowBallon(deltaTimeSeconds);
	RenderShuriken(deltaTimeSeconds);
	RenderPowerBar();
	RenderLives();
	CheckCollisionArrowBallon();
	CheckCollisionBowShuriken();
	CheckCollisionArrowShuriken();
}
void Tema1::RenderBow() {
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, translateBow);
	// rotate the bow after cursor
	modelMatrix *= Transform2D::Translate(BowX, BowY);
	modelMatrix *= Transform2D::Rotate(angularStepBow);
	modelMatrix *= Transform2D::Translate(-BowX, -BowY);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
}
void Tema1::RenderArrow(float deltaTimeSeconds) {
	// if the arrow translate on window
	if (isrelease) {
		modelMatrix = glm::mat3(1);
		// adding speed to the position on the oX axis
		arrowposX += arrow_speed * deltaTimeSeconds;
		//calculating the position of the imaginary circle around the tip of the collision arrow
		double l = ArrowLength + 2 * ArrowSize;
		arrowcirclex = BowX + (l + arrowposX) * cos(angularStepArrow);
		arrowcircley = BowY + translateArrow + 3 + (l + arrowposX) * sin(angularStepArrow);
		// translation at an angle
		modelMatrix *= Transform2D::Rotate(angularStepArrow);
		modelMatrix *= Transform2D::Translate(arrowposX, translateArrow);
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
		// if the arrow is no longer in the window
		//  respawn it to the initial position
		if (arrowposX > 1200) {
			isrelease = false;
			arrowposX = BowX;
			arrowposY = BowY;
			arrow_speed = 0;
			translateArrow = 0;
		}
	}
	else {
		modelMatrix = glm::mat3(1);
		// rotate the arrow after cursor
		modelMatrix *= Transform2D::Translate(0, translateBow);
		modelMatrix *= Transform2D::Translate(arrowposX, arrowposY);
		modelMatrix *= Transform2D::Rotate(angularStepBow);
		modelMatrix *= Transform2D::Translate(-arrowposX, -arrowposY);
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::RenderRedBallon(float deltaTimeSeconds) {
	for (int i = 0; i < 6; i++) {
		// increase the position on Y for translation
		redBalloonPosY[i] += 50 * deltaTimeSeconds;
		//if the balloon is in the window
		if (redBalloonPosY[i] > -50 && redBalloonPosY[i] < 750) {
			modelMatrix = glm::mat3(1);
			modelMatrix1 = glm::mat3(1);
			// needs to be destroyed
			if (redBalloonDissapear[i]) {
				redBalloonScaleX[i] -= 0.05;
				redBalloonScaleY[i] -= 0.05;
				// if he disappeared, we respawn him
				if (redBalloonScaleX[i] <= 0.1) {
					redBalloonDissapear[i] = false;
					redBalloonPosX[i] = (rand() % (vecBallonLimits[i].rightlimit - vecBallonLimits[i].leftlimit + 1)) + vecBallonLimits[i].leftlimit;
					redBalloonPosY[i] = (rand() % (1000 - 0 + 1)) + 0 - 1000;
					redBalloonScaleX[i] = 0.5 + ((double)rand() / RAND_MAX) * (1 - 0.5);
					redBalloonScaleY[i] = redBalloonScaleX[i];

				}
			}
			// translating the balloon
			modelMatrix *= Transform2D::Translate(redBalloonPosX[i], redBalloonPosY[i]);
			// translating the polyline
			modelMatrix1 *= Transform2D::Translate(redBalloonPosX[i], redBalloonPosY[i] - 3*CircleRadius);
			// scaling the balloon
			modelMatrix *= Transform2D::Scale(redBalloonScaleX[i], redBalloonScaleY[i]);
			// scaling the polyline
			modelMatrix1 *= Transform2D::Scale(1, redBalloonScaleY[i]);
			RenderMesh2D(meshes["redcircle"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
		}
		// if the balloon is no longer in the window
		else if (redBalloonPosY[i] > 900) {
			// respawn him
			redBalloonPosX[i] = (rand() % (vecBallonLimits[i].rightlimit - vecBallonLimits[i].leftlimit + 1)) + vecBallonLimits[i].leftlimit;
			redBalloonPosY[i] = (rand() % (1000 - 0 + 1)) + 0 - 1000;
			redBalloonScaleX[i] = 0.5 + ((double)rand() / RAND_MAX) * (1 - 0.5);
			redBalloonScaleY[i] = redBalloonScaleX[i];
		}
	}
}
void Tema1::RenderYellowBallon(float deltaTimeSeconds) {
	for (int i = 0; i < 3; i++) {
		// increase the position on Y for translation
		yellowBalloonPosY[i] += 50 * deltaTimeSeconds;
		//if the balloon is in the window
		if (yellowBalloonPosY[i] > 50 && yellowBalloonPosY[i] < 750) {
			modelMatrix = glm::mat3(1);
			modelMatrix1 = glm::mat3(1);
			// needs to be destroyed
			if (yellowBalloonDissapear[i]) {
				yellowBalloonScaleX[i] -= 0.01;
				yellowBalloonScaleY[i] -= 0.01;
				// if he disappeared, we respawn him
				if (yellowBalloonScaleX[i] <= 0.1) {
					yellowBalloonDissapear[i] = false;
					yellowBalloonPosX[i] = (rand() % (vecBallonLimitsYell[i].rightlimit - vecBallonLimitsYell[i].leftlimit + 1)) + vecBallonLimitsYell[i].leftlimit;
					yellowBalloonPosY[i] = (rand() % (1000 - 0 + 1)) + 0 - 1000;
					yellowBalloonScaleX[i] = 0.5 + ((double)rand() / RAND_MAX) * (1 - 0.5);
					yellowBalloonScaleY[i] = yellowBalloonScaleX[i];
				}
			}
			// translating the balloon
			modelMatrix *= Transform2D::Translate(yellowBalloonPosX[i], yellowBalloonPosY[i]);
			// translating the polyline
			modelMatrix1 *= Transform2D::Translate(yellowBalloonPosX[i], yellowBalloonPosY[i] - 3 * CircleRadius);
			// scaling the balloon
			modelMatrix *= Transform2D::Scale(yellowBalloonScaleX[i], yellowBalloonScaleY[i]);
			// scaling the polyline
			modelMatrix1 *= Transform2D::Scale(1, yellowBalloonScaleY[i]);
			RenderMesh2D(meshes["yellowcircle"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
		}
		// if the balloon is no longer in the window
		else if (yellowBalloonPosY[i] > 900) {
			//respawn him
			yellowBalloonPosX[i] = (rand() % (vecBallonLimitsYell[i].rightlimit - vecBallonLimitsYell[i].leftlimit + 1)) + vecBallonLimitsYell[i].leftlimit;
			yellowBalloonPosY[i] = (rand() % (1000 - 0 + 1)) + 0 - 1000;
			yellowBalloonScaleX[i] = 0.5 + ((double)rand() / RAND_MAX) * (1 - 0.5);
			yellowBalloonScaleY[i] = yellowBalloonScaleX[i];
		}
	}
}
void Tema1::RenderShuriken(float deltaTimeSeconds) {
	//  increase the angular for rotate
	angularStepShuriken += 2 * deltaTimeSeconds;
	for (int i = 0; i < 4; i++) {
		shurikenPosX[i] -= 60 * deltaTimeSeconds;
		// if the shuriken is in the window
		if (shurikenPosX[i] < 1280 && shurikenPosX[i] > -50) {
			// needs to be destroyed
			modelMatrix = glm::mat3(1);
			if (shurikenDissapear[i]) {
				shurikenScaleX[i] -= 0.05;
				shurikenScaleY[i] -= 0.05;
				// if he disappeared, we respawn him
				if (shurikenScaleX[i] <= 0.1) {
					shurikenDissapear[i] = false;
					shurikenPosX[i] = (rand() % (3000 - 1500 + 1)) + 1500;
					shurikenPosY[i] = (rand() % (vecShuriken[i].rightlimit - vecShuriken[i].leftlimit + 1)) + vecShuriken[i].leftlimit;
					shurikenScaleX[i] = 1;
					shurikenScaleY[i] = 1;
				}
			}
			// translating the shuriken
			modelMatrix *= Transform2D::Translate(shurikenPosX[i], shurikenPosY[i]);
			// rotate the shuriken
			modelMatrix *= Transform2D::Rotate(angularStepShuriken);
			// scaling the shuriken
			modelMatrix *= Transform2D::Scale(shurikenScaleX[i], shurikenScaleY[i]);
			RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
		}
		// if the shuriken is no longer in the window
		else if (shurikenPosX[i] < -50) {
			// respawn him
			shurikenPosX[i] = (rand() % (3000 - 1500 + 1)) + 1500;
			shurikenPosY[i] = (rand() % (vecShuriken[i].rightlimit - vecShuriken[i].leftlimit + 1)) + vecShuriken[i].leftlimit;
		}
	}
}
void Tema1::RenderPowerBar() {
	modelMatrix = glm::mat3(1);
	// translate the power bar
	modelMatrix *= Transform2D::Translate(0, translateBow);
	modelMatrix *= Transform2D::Translate(BowX, BowY - 150);
	// scale the power bar
	modelMatrix *= Transform2D::Scale(scalepowerBarX, 1);
	modelMatrix *= Transform2D::Translate(-BowX, -BowY + 150);
	RenderMesh2D(meshes["powerbar"], shaders["VertexColor"], modelMatrix);
}
void Tema1::RenderLives() {
	int x = 0;
	if (numberoflives == 0) {
		std::cout << "YOU LOST! Your final score is: " << score <<std::endl;
		exit(0);
	}
	// render the lives on window
	for (int i = 1; i <= numberoflives; i++) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(50 + x, 680);
		RenderMesh2D(meshes["lives"], shaders["VertexColor"], modelMatrix);
		x += 40;
	}
}
void Tema1::CheckCollisionArrowBallon() {
	float dx = 0, dy = 0, distance = 0;
	//red ballons
	for (int i = 0; i < 6; i++) {
		dx = redBalloonPosX[i] - arrowcirclex;
		dy = redBalloonPosY[i] - arrowcircley;
		distance = sqrt(dx * dx + dy * dy);
		// if is collision
		if ( distance < arrowcircleradius + redBalloonScaleX[i] * CircleRadius) {
			// set the balloon to disappear only the first time
			if (!redBalloonDissapear[i]) {
				redBalloonDissapear[i] = true;
				score += balloonscore;
				std::cout << "Nice! Your score is: " << score << std::endl;
			}
		}
	}
	// yellow ballons
	for (int i = 0; i < 3; i++) {
		dx = yellowBalloonPosX[i] - arrowcirclex;
		dy = yellowBalloonPosY[i] - arrowcircley;
		distance = sqrt(dx * dx + dy * dy);
		// if is collision
		if (distance < arrowcircleradius + yellowBalloonScaleX[i] * CircleRadius) {
			// set the balloon to disappear only the first time
			if (!yellowBalloonDissapear[i]) {
				yellowBalloonDissapear[i] = true;
				score -= balloonscore;
				std::cout << "Ups :(. Your score is: " << score << std::endl;
			}
		}
	}
}
void Tema1::CheckCollisionBowShuriken() {
	float dx = 0, dy = 0, distance = 0;
	for (int i = 0; i < 4; i++) {
		dx = shurikenPosX[i] - BowX;
		dy = shurikenPosY[i] - BowY - translateBow;
		distance = sqrt(dx * dx + dy * dy);
		// if is collision
		if (distance < 50 + 100) {
			// respawn the shuriken and decrease the life
			shurikenPosX[i] = (rand() % (3000 - 1500 + 1)) + 1500;
			shurikenPosY[i] = (rand() % (vecShuriken[i].rightlimit - vecShuriken[i].leftlimit + 1)) + vecShuriken[i].leftlimit;
			numberoflives--;
		}
	}

}
void Tema1::CheckCollisionArrowShuriken() {
	float dx = 0, dy = 0, distance = 0;
	for (int i = 0; i < 4; i++) {
		dx = shurikenPosX[i] - arrowcirclex;
		dy = shurikenPosY[i] - arrowcircley;
		distance = sqrt(dx * dx + dy * dy);
		// if is collision
		if (distance < arrowcircleradius + 50) {
			// set the shuriken to disappear only the first time
			if (!shurikenDissapear[i]) {
				shurikenDissapear[i] = true;
				score += shurikenscore;
				std::cout << "Good job! Your score is: " << score << std::endl;
			}
		}
	}

}
void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{	// decrease the translate on OY-axis
	if (window->KeyHold(GLFW_KEY_S)) {
		translateBow -= 100* deltaTime;

	}
	// increase the translate on OY-axis
	if (window->KeyHold(GLFW_KEY_W)) {
		translateBow += 100 *deltaTime;
	}
	// for arrow
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		// if the arrow is in initial positions
		if (arrowposY == BowY) {
			ishold = true;
			// increase the arrow speed
			arrow_speed += 10;
			// increase the scale for power bar
			if (scalepowerBarX <= 10) {
				scalepowerBarX += 0.1f;
			}
		}

	}
	// the arrow is release
	else if (ishold == true) {
		ishold = false;
		isrelease = true;
		// save the angular an translation 
		// in order not to change during the translation
		angularStepArrow = angularStepBow;
		translateArrow = translateBow; 
		arrowposY = 0;
		scalepowerBarX = 1;
	}

}

void Tema1::OnKeyPress(int key, int mods)
{

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::ivec2 resolution = window->GetResolution();
	// calculate the angle between the bow and the cursor
	angularStepBow = glm::atan((float)(resolution.y - BowY - mouseY - translateBow), (float)(mouseX - BowX));
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
