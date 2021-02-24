#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#define BowX 50
#define BowY 400
#define BowRadius 100
#define ArrowLength 150
#define ArrowSize 10
#define CircleRadius 50

struct limits {
	int leftlimit;
	int rightlimit;
};
class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void InitObjectsDissapear();
	void InitRangeLimitsObjects();
	void InitPositionObjects();
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void RenderBow();
	void RenderArrow(float deltaTimeSeconds);
	void RenderRedBallon(float deltaTimeSeconds);
	void RenderYellowBallon(float deltaTimeSeconds);
	void RenderShuriken(float deltaTimeSeconds);
	void RenderPowerBar();
	void RenderLives();
	void CheckCollisionArrowBallon();
	void CheckCollisionBowShuriken();
	void CheckCollisionArrowShuriken();
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	glm::mat3 modelMatrix1;
	// bow
	float angularStepBow;
	float translateBow; 
	float translateY;
	// arrow
	float angularStepArrow;
	float arrowposY;
	float arrow_speed;
	float arrowposX;
	float translateArrow;
	float arrowcirclex;
	float arrowcircley;
	float arrowcircleradius = 4;
	// red balloons
	float redBalloonPosX[6];
	float redBalloonPosY[6];
	float redBalloonScaleX[6];
	float redBalloonScaleY[6];
	bool redBalloonDissapear[6];
	limits vecBallonLimits[6];
	// yellow balloons
	float yellowBalloonPosX[3];
	float yellowBalloonPosY[3];
	float yellowBalloonScaleX[3];
	float yellowBalloonScaleY[3];
	bool yellowBalloonDissapear[6];
	limits vecBallonLimitsYell[3];
	// shurikens
	float angularStepShuriken;
	float shurikenPosX[4];
	float shurikenPosY[4];
	float shurikenScaleX[4];
	float shurikenScaleY[4];
	bool shurikenDissapear[4];
	limits vecShuriken[4];


	float scalepowerBarX;
	int numberoflives;

	bool ishold = false;
	bool isrelease = false;
	int score = 0;
	int balloonscore = 1;
	int shurikenscore = 5;
};
