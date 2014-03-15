////////////////////////////////////////////////////////////////////////////////
// Filename: Game.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> //needed to create and destroy windows and call Win32 functions
#include <chrono>

#include "Arraylist.h"
#include "Graphics.h"

#define  NUMPLAYERS 4 //USED FOR POTENTIAL PLAYER LOOPS ONLY

using namespace std::chrono;

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
////////////////////////////////////////////////////////////////////////////////
class Camera;
class ControllerInputManager;
class Graphics;
class IViewModel;
class KeyInput;
class ModelManager;
class Player;
class Playfield;
class TextureManager;
class CollisionManager;

////////////////////////////////////////////////////////////////////////////////
// Class name: Game
////////////////////////////////////////////////////////////////////////////////
class Game
{
	friend class Playfield;

	public:
		Game(); 
		Game(const Game&);
		~Game();

		bool Initialize();
		void Shutdown();
		void Run();

		// Manager Getter/Setters
		KeyInput*               getKeyInput()			{ return keyInput; }
		ControllerInputManager* getControllerManager()	{ return conInput; }
		ModelManager*			getModelManager()		{ return modelManager; }
		TextureManager*			getTextureManager()		{ return textureManager; }
		ID3D11Device*			getDevice()				{ return graphics->getDevice(); }
		CollisionManager*		getCollisionManager()	{ return collisionManager; }

		ArrayList<Player>* GetPlayers();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		//Functions
		bool  Frame();
		void  InitializeWindows(int&, int&);
		void  ShutdownWindows();
		float getElapsedTime(float timeModifier = 1.0f);

		//Member Variables
		LPCWSTR   applicationName;
		HINSTANCE hinstance;
		HWND      hwnd;  //handle to the Windows window (client window for the application)

		ArrayList<Player>* players;
		ArrayList<KeyInput>*    playerKeys;
		Graphics*               graphics; //our graphics object that encapsulates the graphics pipeline
		Camera*					camera; //our encapsulation of where the camera is looking at our world
		milliseconds            start;
		

		// Managers
		ControllerInputManager* conInput; //Yay! Input from a controller!
		KeyInput*               keyInput; //keyboard input object from which to obtain user inputs
		ModelManager*			modelManager;
		TextureManager*			textureManager;
		CollisionManager*		collisionManager;

		//Game World Items
		Playfield*		   playfield;

		ArrayList<IViewModel>* gameModels; //container to hold all our game world models - change to be in modelmanager class?


};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////

//This is where windows will direct messages to.
//This will get set to our Game object when 
//System intialize is called.
static Game* ApplicationHandle = 0;
