#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Universe Maker - Zwanckaert, Ibn - 1DAE11" };

// Change the window dimensions here
float g_WindowWidth{ 1024 };
float g_WindowHeight{ 768 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
staticUtils util{};
Point2 g_GalaxyOffset{0,0}, g_MousePos{};
const int g_SqaureSize{32};
bool g_Pressed{ false }, g_SystemUI{};
StarSystem g_CurrentStar{0,0};
// Declare your own functions here
void MakeUniverse();
void DrawSystemUI(StarSystem star);
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling