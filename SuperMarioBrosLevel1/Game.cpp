//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Goomba.h"
#include "Spawner.h"
#include "PlayerMove.h"
#include "Player.h"
#include "Block.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "WrappingMove.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>

Game::Game()
{
	mGameIsRunning = true;
	mPrevTick = 0;
	mDirection = 0;
	mWindow = nullptr;
	mRenderer = nullptr;
	mDeltaTime = 0.0f;
	mImgInt = 0;
	mMario = nullptr;
	mGoal = nullptr;
	mCol = nullptr;
	mBackgroundMusic = 0;
}

bool Game::Initialize()
{
	Random::Init();
	//init audio and video
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
	{
		return false;
	}
	//create window
	mWindow = SDL_CreateWindow("ITP 380: Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							   WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (mWindow == nullptr)
	{
		Shutdown();
		SDL_Quit();
		return false;
	}
	//create renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1,
								   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr)
	{
		Shutdown();
		SDL_Quit();
		return false;
	}
	mImgInt = IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	LoadData();
	//if everything is initalized correcntly return true
	return true;
}

void Game::Shutdown()
{
	UnloadData();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	IMG_Quit();
}

void Game::AddActor(class Actor* actor)
{
	mActors.push_back(actor);
}

void Game::RemoveActor(class Actor* actor)
{
	std::vector<class Actor*>::iterator it;
	it = find(mActors.begin(), mActors.end(), actor);
	if (it != mActors.end())
	{
		mActors.erase(it);
	}
}

void Game::RunLoop()
{
	//main game loop, get key input
	//update game according to input
	//generate output according to updates
	while (mGameIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mGameIsRunning = false;
			break;
		default:
			break;
		}
	}
	const Uint8* keyArray = SDL_GetKeyboardState(NULL);
	if (keyArray[SDL_SCANCODE_ESCAPE])
	{
		mGameIsRunning = false;
	}

	std::vector<class Actor*> copyActors = mActors;
	for (size_t i = 0; i < copyActors.size(); i++)
	{
		copyActors[i]->ProcessInput(keyArray);
	}
}

void Game::UpdateGame()
{
	while (SDL_GetTicks() < (mPrevTick + 16))
	{
	}
	float dTime = (SDL_GetTicks() - mPrevTick) / 1000.0f;
	mPrevTick = SDL_GetTicks();
	if (dTime > 0.033)
	{
		dTime = static_cast<float>(0.033);
	}
	mDeltaTime = dTime;
	std::vector<class Actor*> copyActors = mActors;
	for (size_t i = 0; i < copyActors.size(); i++)
	{
		copyActors[i]->Update(dTime);
	}

	std::vector<class Actor*> destroyActors;
	for (size_t i = 0; i < mActors.size(); i++)
	{
		if (mActors[i]->GetState() == ActorState::Destroy)
		{
			destroyActors.push_back(mActors[i]);
		}
	}
	for (size_t i = 0; i < destroyActors.size(); i++)
	{
		delete destroyActors[i];
	}
}

void Game::GenerateOutput()
{
	SDL_RenderClear(mRenderer);
	//set walls to black
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	for (size_t i = 0; i < mSprites.size(); i++)
	{
		if (mSprites[i]->IsVisible())
		{
			mSprites[i]->Draw(mRenderer);
		}
	}
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	Actor* background = new Actor(this);
	mBackgroundMusic = Mix_PlayChannel(-1, GetSound("Assets/Sounds/Music.ogg"), -1);
	Vector2 pos3(3392, WINDOW_HEIGHT / 2);
	background->SetPosition(pos3);
	SpriteComponent* sc4 = new SpriteComponent(background, 50);
	sc4->SetTexture(GetTexture("Assets/Background.png"));
}
void Game::UnloadData()
{
	for (auto& pair : mSoundMap)
	{
		Mix_FreeChunk(pair.second);
	}
	mSoundMap.clear();
	while (!mActors.empty())
	{
		size_t back = mActors.size() - 1;
		delete mActors[back];
		//mActors.pop_back();
	}
	for (auto it = mTextureMap.begin(); it != mTextureMap.end();)
	{
		SDL_DestroyTexture(it->second);
		it = mTextureMap.erase(it);
	}
}

SDL_Texture* Game::GetTexture(const std::string& key)
{
	auto it = mTextureMap.find(key);
	if (it != mTextureMap.end())
	{
		return it->second;
	}
	else
	{
		const char* cKey = key.c_str();
		SDL_Surface* x = IMG_Load(cKey);
		if (x == nullptr)
		{
			SDL_Log("FAILED");
		}
		SDL_Texture* y = SDL_CreateTextureFromSurface(mRenderer, x);
		SDL_FreeSurface(x);
		mTextureMap.insert(std::make_pair(key, y));
		return y;
	}
}
void Game::AddSprite(class SpriteComponent* sprite)
{
	mSprites.push_back(sprite);
	std::sort(mSprites.begin(), mSprites.end(),
			  [](class SpriteComponent* a, class SpriteComponent* b) {
				  return a->GetDrawOrder() < b->GetDrawOrder();
			  });
}

void Game::RemoveSprite(class SpriteComponent* sprite)
{
	std::vector<class SpriteComponent*>::iterator it;
	it = find(mSprites.begin(), mSprites.end(), sprite);
	if (it != mSprites.end())
	{
		mSprites.erase(it);
	}
}

void Game::ReadFile(std::string fileName)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		int lineCount = 1;
		while (std::getline(file, line))
		{
			for (int i = 0; i < line.length(); i++)
			{
				char symbol = line[i];
				if (symbol == 'A' || symbol == 'B' || symbol == 'C' || symbol == 'D' ||
					symbol == 'E' || symbol == 'F' || symbol == 'G' || symbol == 'H' ||
					symbol == 'I')
				{
					new Block(this, symbol, i, lineCount);
				}
				if (symbol == 'P')
				{
					mMario = new Player(this);
					Vector2 pos3(i * 32 + 16, lineCount * 32 - 16);
					mMario->SetPosition(pos3);
				}
				if (symbol == 'Y')
				{
					Spawner* spawn = new Spawner(this);
					Vector2 pos3(i * 32 + 16, lineCount * 32 - 16);
					spawn->SetPosition(pos3);
				}
			}
			lineCount++;
		}
		file.close();
	}
}
std::vector<class Block*>& Game::GetBlock()
{
	return mBlocks;
}
void Game::AddBlock(class Block* b)
{
	mBlocks.push_back(b);
}
void Game::DeleteBlock(class Block* b)
{
	std::vector<class Block*>::iterator it;
	it = find(mBlocks.begin(), mBlocks.end(), b);
	if (it != mBlocks.end())
	{
		mBlocks.erase(it);
	}
}
Vector2& Game::GetCameraPos()
{
	return mCameraPos;
}
std::vector<class Goomba*>& Game::GetEnemies()
{
	return mEnemies;
}
void Game::AddEnemie(class Goomba* e)
{
	mEnemies.push_back(e);
}
void Game::DeleteEnemie(class Goomba* e)
{
	std::vector<class Goomba*>::iterator it;
	it = find(mEnemies.begin(), mEnemies.end(), e);
	if (it != mEnemies.end())
	{
		mEnemies.erase(it);
	}
}

Mix_Chunk* Game::GetSound(const std::string& filename)
{
	auto it = mSoundMap.find(filename);
	if (it != mSoundMap.end())
	{
		return it->second;
	}
	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
	if (sound == nullptr)
	{
		return nullptr;
	}
	mSoundMap[filename] = sound;
	return sound;
}

int Game::GetBackgroundChannel() const
{
	return mBackgroundMusic;
}

class Player* Game::GetMario()
{
	return mMario;
}
class Actor* Game::GetGoal()
{
	return mGoal;
}
class CollisionComponent* Game::GetColComp()
{
	return mCol;
}