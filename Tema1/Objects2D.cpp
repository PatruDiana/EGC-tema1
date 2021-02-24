#include "Objects2D.h"
#include <Core/Engine.h>
#include <iostream>
# define pi (3.15159265359f)

Mesh* Objects2D::MakePowerBar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	indices.push_back(0);
	indices.push_back(2);

	square->InitFromData(vertices, indices);

	return square;
}

Mesh* Objects2D::MakeHeart(std::string name, glm::vec3 center1, float radius, glm::vec3 color) {
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float arg, x, y;
	glm::vec3 center = center1;
	Mesh* heart = new Mesh(name);
	vertices.emplace_back(center, color);
	for (int i = 0; i <= 50; i++) {
		arg = 2 * pi * i / 50;
		x = cos(arg) * radius;
		y = sin(arg) * radius;
		vertices.push_back(VertexFormat(center + glm::vec3(x, y, 0), color));
		indices.push_back(i);
	}
	indices.push_back(51);
	indices.push_back(0);
	glm::vec3 center2 = glm::vec3(center1.x + 2 * radius, center1.y, 0);
	vertices.emplace_back(center2, color);
	for (int i = 52; i <= 100; i++) {
		arg = 2 * pi * i / 48;
		x = cos(arg) * radius;
		y = sin(arg) * radius;
		vertices.push_back(VertexFormat(center2 + glm::vec3(x, y, 0), color));
		indices.push_back(i);
	}
	vertices.push_back(VertexFormat(center + glm::vec3(radius, -3 *radius, 0), color));
	indices.push_back(33);
	indices.push_back(102);
	indices.push_back(102);
	indices.push_back(93);
	heart->SetDrawMode(GL_TRIANGLE_FAN);
	heart->InitFromData(vertices, indices);
	return heart;

}
Mesh* Objects2D::MakeBow(std::string name, glm::vec3 circleCentre, float radius, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float arg, x, y;
	glm::vec3 center = circleCentre;
	Mesh* bow = new Mesh(name);
	vertices.emplace_back(circleCentre, color);
	for (int i = 0; i <= 101; i++) {
		arg = pi * i / 100;
		x = sin(arg) * radius;
		y = cos(arg) * radius;
		vertices.push_back(VertexFormat(center + glm::vec3(x, y, 0), color));
		indices.push_back(i);
	}
	indices.push_back(101);
	indices.push_back(0);
	bow->SetDrawMode(GL_LINE_LOOP);
	bow->InitFromData(vertices, indices);
	return bow;
}
Mesh* Objects2D::MakeArrow(std::string name, glm::vec3 leftBottomCorner, float length, float side, glm::vec3 color) {
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, 6, 0), color),
		VertexFormat(corner + glm::vec3(length,  6, 0), color),
		VertexFormat(corner + glm::vec3(length, 6 + side, 0), color),
		VertexFormat(corner + glm::vec3(length, -side, 0), color),
		VertexFormat(corner + glm::vec3(length + 2*side , 3, 0), color),

	};
	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											1, 2, 3,
											4 , 5, 6 };

	arrow->InitFromData(vertices, indices);
	return arrow;

}

Mesh* Objects2D::MakeCircle(std::string name, glm::vec3 circleCentre, float radius, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float arg, x, y;
	glm::vec3 center = circleCentre;
	Mesh* circle = new Mesh(name);
	vertices.emplace_back(circleCentre, color);
	for (int i = 0; i <= 101; i++) {
		arg = 2 * pi * i / 100;
		x = sin(arg) * radius;
		y = cos(arg) * radius;
		vertices.push_back(VertexFormat(center + glm::vec3(x, y, 0), color));
		indices.push_back(i);
	}
	indices.push_back(101);
	indices.push_back(0);
	vertices.push_back(VertexFormat(center + glm::vec3(0, - radius, 0), color));
	vertices.push_back(VertexFormat(center + glm::vec3(10, -radius -10, 0), color));
	vertices.push_back(VertexFormat(center + glm::vec3(-10, -radius -10, 0), color));
	indices.push_back(102);
	indices.push_back(103);
	indices.push_back(104);
	indices.push_back(105);
	circle->SetDrawMode(GL_TRIANGLE_FAN);
	circle->InitFromData(vertices, indices);
	return circle;
}
Mesh* Objects2D::MakeShuriken(std::string name, glm::vec3 centre, float length, glm::vec3 color) {
	glm::vec3 corner = centre;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(-length, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color),
		VertexFormat(corner + glm::vec3(length -10, length - 10, 0), color),
		VertexFormat(corner + glm::vec3(-length + 10, -length + 10, 0), color),
		VertexFormat(corner + glm::vec3(-length + 10, length - 10, 0), color),
		VertexFormat(corner + glm::vec3(length - 10,  -length + 10, 0), color),

	};
	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 5,
											0, 3, 7, 
											0, 2, 6,
											0, 4, 8};

	shuriken->InitFromData(vertices, indices);
	return shuriken;
}
Mesh* Objects2D::MakePoliline(std::string name, glm::vec3 start, float length, glm::vec3 color) {
	glm::vec3 corner = start - glm::vec3(10, 0, 0);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	for (int i = 0, j = 0; i < 8 * 4; i+=8, j+= 2) {
			vertices.push_back(VertexFormat(corner + glm::vec3(0, j*(-length), 0), color));
			vertices.push_back(VertexFormat(corner + glm::vec3(2, j * (-length), 0), color));
			vertices.push_back(VertexFormat(corner + glm::vec3(14, -length * (j + 1), 0), color));
			vertices.push_back(VertexFormat(corner + glm::vec3(12, -length * (j + 1), 0), color));
			vertices.push_back(VertexFormat(corner + glm::vec3(14, -length * (j + 1), 0), color));
			vertices.push_back(VertexFormat(corner + glm::vec3(12, -length * (j + 1), 0), color));
			vertices.push_back(VertexFormat(corner + glm::vec3(0, - length * (j + 2), 0), color));
			vertices.push_back(VertexFormat(corner + glm::vec3(2, - length * (j + 2), 0), color));
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
			indices.push_back(i);
			indices.push_back(i + 2);
			indices.push_back(i + 3);

			indices.push_back(i + 4);
			indices.push_back(i + 4 + 1);
			indices.push_back(i + 4 + 2);
			indices.push_back(i + 4);
			indices.push_back(i + 4 + 2);
			indices.push_back(i + 4 + 3);
	}
	
	Mesh* poliline = new Mesh(name);
	poliline->InitFromData(vertices, indices);

	return poliline;
}