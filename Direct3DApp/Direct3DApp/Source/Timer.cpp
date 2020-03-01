#include "../Include/Timer.h"

Timer::Timer()
{
	this->Last = std::chrono::steady_clock::now();
}

float Timer::Mark()
{
	const auto Old = this->Last;
	this->Last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> DeltaTime = this->Last - Old;
	return DeltaTime.count();
}

float Timer::Peek() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - this->Last).count();
}
