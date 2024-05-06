#pragma once
#ifndef HUDRENDERER_H
#define HUDRENDERER_H

#include "Player.h"

class HUDRenderer
{
public:
	HUDRenderer(Player* pl);

	void Visualize();
private:
	Player* pl;
	glm::mat4 orthoMat;

	GLuint VAO_cross;
	GLuint VBO_cross;
	GLuint texID_cross;

	GLuint VAO_heart;
	GLuint VBO_heart;
	GLuint texID_heart_f;
	GLuint texID_heart_e;

	GLuint VAO_ammo;
	GLuint VBO_ammo;
	GLuint texID_ammo_f;
	GLuint texID_ammo_e;

	Shader* shd;

	void CreateHUD();

	void CreateHeart();
	void CreateCrosshair();
	void CreateAmmo();

	void VisualizeCrosshair();
	void VisualizeHealth(bool isFilled, float offset);
	void VisualizeAmmo(bool isFilled, float offset);
};


#endif