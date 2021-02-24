#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects2D
{
	Mesh* MakePowerBar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
	Mesh* MakeHeart(std::string name, glm::vec3 center1, float radius, glm::vec3 color);
	Mesh* MakeCircle(std::string name, glm::vec3 centre, float radius, glm::vec3 color);
	Mesh* MakeArrow(std::string name, glm::vec3 leftBottomCorner, float length, float side, glm::vec3 color);
	Mesh* MakeBow(std::string name, glm::vec3 centre, float radius, glm::vec3 color);
	Mesh* MakeShuriken(std::string name, glm::vec3 centre, float lenght, glm::vec3 color);
	Mesh* MakePoliline(std::string name, glm::vec3 start, float length, glm::vec3 color);
}