#pragma once
#include "Actor/Actor.h"
#include "Engine/Engine.h"
#include "Util/Util.h"

using namespace Wanted;

class UseItemEffect : public Actor
{
	RTTI_DECLARATIONS(UseItemEffect, Actor)

		
public:
	UseItemEffect(Vector2 pos, float DirX, float DirY, float spd, Color color);
	~UseItemEffect();

	void EffectShot(float deltaTime);

private:
	virtual void Tick(float deltaTime) override;

	float lifeTime = 0.5f; // 0.5초 동안만 존재
	float timer = 0.0f;
	Vector2 direction;     // 날아갈 방향
	float speed;

	float DirX = 0.0f;
	float DirY = 0.0f;

	float xPosition = 0.0f;
	float yPosition = 0.0f;

};

