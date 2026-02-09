#pragma once

#include "Common/Common.h"
#include <Windows.h>

namespace Wanted
{
	// 콘솔에 텍스트 색상 등을 지정할 때 사용할
	// 색상 열거형.
	enum class WANTED_API Color : unsigned short
	{
		Black = 0,
		Blue = FOREGROUND_BLUE,
		Green = FOREGROUND_GREEN,
		Red = FOREGROUND_RED,
		Cyan = Blue | Green,             // 하늘색 (파랑 + 초록)
		Magenta = Blue | Red,               // 자주색 (파랑 + 빨강)
		YELLOW = Red | Green,
		White = Blue | Green | Red,

	};
}