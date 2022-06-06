#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	
}

void Draw()
{
	ClearBackground(0,0,0);	
	MakeUniverse();
}

void Update(float elapsedSec)
{
}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
	switch (key) {
	case SDLK_a:
		g_GalaxyOffset.x--;
		break;
	case SDLK_d:
		g_GalaxyOffset.x++;
		break;
	case SDLK_w:
		g_GalaxyOffset.y++;
		break;
	case SDLK_s:
		g_GalaxyOffset.y--;
		break;
	}
}

void OnKeyUpEvent(SDL_Keycode key)
{
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_MousePos.x = e.x;
	g_MousePos.y = e.y;
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	if(e.button == 1)g_Pressed = true;
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == 1)g_Pressed = false;
}
#pragma endregion inputHandling

#pragma region ownDefinitions

void MakeUniverse() {
	util.nProcGen = 0;
	bool FoundStar{};
	for (int y = 0; y < g_WindowHeight / g_SqaureSize; y++)
	{
		for (int x = 0; x < g_WindowWidth / g_SqaureSize; x++)
		{
			uint32_t seed1 = (uint32_t)g_GalaxyOffset.x + (uint32_t)x;
			uint32_t seed2 = (uint32_t)g_GalaxyOffset.y + (uint32_t)y;

			StarSystem star(seed1, seed2);
			if (star.starExists)
			{
				SetColor(star.c);
				FillEllipse(x * g_SqaureSize + g_SqaureSize / 2, y * g_SqaureSize + g_SqaureSize / 2, star.starDiameter / 2, star.starDiameter / 2);

				if (g_MousePos.x / g_SqaureSize == x && ((int)g_WindowHeight - g_MousePos.y) / g_SqaureSize == y) {
					SetColor(252 / 255.0, 232 / 255.0, 3 / 255.0);
					DrawEllipse(x * g_SqaureSize + g_SqaureSize / 2, y * g_SqaureSize + g_SqaureSize / 2, star.starDiameter / 2 + 4, star.starDiameter / 2 + 4);

					if (g_Pressed) {
						g_SystemUI = true;
						g_CurrentStar = StarSystem(seed1, seed2, true);
						FoundStar = true;
					}
				}
				else {
					if (!FoundStar && g_Pressed) g_SystemUI = false;
				}
			}
		}
	}
	if (g_SystemUI) {
		DrawSystemUI(g_CurrentStar);
	}
}

void DrawSystemUI(StarSystem star) {
	const int margin{ 20 }, BoxNormal{ margin + margin / 2 }, middleOfBox{ BoxNormal + 25 + (300 - margin) / 2 };
	const Point2 HabitableZone{500,650};

	//UI background
	SetColor(0.9,0.9,0.9);
	FillRect(margin, margin, g_WindowWidth - margin * 2, 300);
	SetColor(115 / 255.0, 189 / 255.0, 180 / 255.0);
	FillRect(margin + margin/2, margin + margin / 2, g_WindowWidth - margin * 3, 300 - margin);

	//star
	SetColor(star.c);
	int middleStar{ BoxNormal + margin / 2 + int(star.starDiameter * 3)};
	FillEllipse(middleStar, middleOfBox, star.starDiameter * 3, star.starDiameter * 3);

	//planets
	int LeftPos{ middleStar + (int)star.starDiameter * 3 + margin};
	for (int i = 0; i < star.Planets.size(); i++)
	{
		//is it habitable
		if (star.Planets[i].distance > HabitableZone.x && star.Planets[i].distance < HabitableZone.y) {
			SetColor(0,0.7,0);
			FillRect(LeftPos - margin/2, BoxNormal, star.Planets[i].radius * 4 + margin , 300 - margin);
		}

		//DrawPlanet
		SetColor(0.5,0.5,0.5);
		Point2 MidPlanet{ LeftPos + int(star.Planets[i].radius * 2), middleOfBox };
		//has ring
		if (star.Planets[i].ring) {
			FillEllipse(MidPlanet.x, MidPlanet.y, star.Planets[i].radius * 2 * 1.3, star.Planets[i].radius * 2 * 1.3);
			SetColor(115 / 255.0, 189 / 255.0, 180 / 255.0);
			FillEllipse(MidPlanet.x, MidPlanet.y, star.Planets[i].radius * 2 * 1.1, star.Planets[i].radius * 2 * 1.1);
		}
		SetColor(0.5, 0.5, 0.5);
		FillEllipse(MidPlanet.x, MidPlanet.y, star.Planets[i].radius * 2, star.Planets[i].radius * 2);

		//moons
		for (int m = 0; m < star.Planets[i].vMoons.size(); m++)
		{
			SetColor(1,1,1);
			FillEllipse(MidPlanet.x, MidPlanet.y - star.Planets[i].radius * 2 - margin - 35 * m, star.Planets[i].vMoons[m] * 2, star.Planets[i].vMoons[m] * 2);
		}

		//offset for next planet
		if(!star.Planets[i].ring) LeftPos += star.Planets[i].radius * 4 + margin;
		else {
			LeftPos += star.Planets[i].radius * 4 * 1.3 + margin;
		}
	}
}
#pragma endregion ownDefinitions