#pragma once
#include "Level/Level.h"

using namespace Wanted;

class EndLevel : public Level
{
	RTTI_DECLARATIONS(EndLevel, Level)

public:
	EndLevel();
	~EndLevel();

private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;



};

