//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <map>
#include "Math.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

class Game
{
public:
	Game();
	bool Initialize();
	void Shutdown();
	void RunLoop();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void ReadFile(std::string fileName);
	SDL_Texture* GetTexture(const std::string& key);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	std::vector<class Block*>& GetBlock();
	void AddBlock(class Block* b);
	void DeleteBlock(class Block* b);
	std::vector<class Goomba*>& GetEnemies();
	void AddEnemie(class Goomba* e);
	void DeleteEnemie(class Goomba* e);
	Mix_Chunk* GetSound(const std::string& filename);
	Vector2& GetCameraPos();
	int GetBackgroundChannel() const;
	class Player* GetMario();
	class Actor* GetGoal();
	class CollisionComponent* GetColComp();
	//constants
	static const int WINDOW_WIDTH = 600;
	static const int WINDOW_HEIGHT = 448;

private:
	//functions
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	//data
	std::vector<class Actor*> mActors;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mPrevTick;
	bool mGameIsRunning;
	int mDirection;
	std::unordered_map<std::string, SDL_Texture*> mTextureMap;
	std::vector<class SpriteComponent*> mSprites;
	float mDeltaTime;
	int mImgInt;
	std::vector<class Block*> mBlocks;
	std::vector<class Goomba*> mEnemies;
	std::map<std::string, Mix_Chunk*> mSoundMap;
	Vector2 mCameraPos;
	int mBackgroundMusic;
	class Player* mMario;
	class Actor* mGoal;
	class CollisionComponent* mCol;
};