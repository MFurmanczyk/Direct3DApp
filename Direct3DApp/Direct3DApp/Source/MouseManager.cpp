#include "../Include/MouseManager.h"
#include "../Include/WindowHeader.h"

std::optional<MouseManager::RawDelta> MouseManager::ReadRawDelta() noexcept
{
	if (RawDeltaBuffer.empty())
	{
		return std::nullopt;
	}
	const RawDelta Delta = RawDeltaBuffer.front();
	RawDeltaBuffer.pop();
	return Delta;
}

std::optional<MouseManager::Event> MouseManager::Read() noexcept
{
	if (Buffer.size() > 0u)
	{
		MouseManager::Event Event = Buffer.front();
		Buffer.pop();
		return Event;
	}
	return std::optional<MouseManager::Event>();
}

void MouseManager::Flush() noexcept
{
	Buffer = std::queue<MouseManager::Event>();
}

void MouseManager::OnMouseMove(int x, int y) noexcept
{
	this->x = x;
	this->y = y;

	Buffer.push(MouseManager::Event(MouseManager::Event::EType::Move, *this));
	TrimBuffer();
}

void MouseManager::OnMouseLeave() noexcept
{
	this->InWindow = false;
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::Leave, *this));
	TrimBuffer();
}

void MouseManager::OnMouseEnter() noexcept
{
	this->InWindow = true;
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::Enter, *this));
	TrimBuffer();
}

void MouseManager::OnRawDelta(int dx, int dy) noexcept
{
	RawDeltaBuffer.push({ dx, dy });
	TrimBuffer();
}

void MouseManager::OnLeftPressed(int x, int y) noexcept
{
	this->LeftPressed = true;
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::LPressed, *this));
	TrimBuffer();
}

void MouseManager::OnLeftReleased(int x, int y) noexcept
{
	this->LeftPressed = false;
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::LReleased, *this));
	TrimBuffer();
}

void MouseManager::OnRightPressed(int x, int y) noexcept
{
	this->RightPressed = true;
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::RPressed, *this));
	TrimBuffer();
}

void MouseManager::OnRightReleased(int x, int y) noexcept
{
	this->RightPressed = false;
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::RReleased, *this));
	TrimBuffer();
}

void MouseManager::OnWheelUp(int x, int y) noexcept
{
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::WheelUp, *this));
	TrimBuffer();
}

void MouseManager::OnWheelDown(int x, int y) noexcept
{
	Buffer.push(MouseManager::Event(MouseManager::Event::EType::WheelDown, *this));
	TrimBuffer();
}

void MouseManager::TrimBuffer() noexcept
{
	while (Buffer.size() > BufferSize)
	{
		Buffer.pop();
	}
}

void MouseManager::TrimRawInputBuffer() noexcept
{
	while (RawDeltaBuffer.size() > BufferSize)
	{
		RawDeltaBuffer.pop();
	}
}

void MouseManager::OnWheelDelta(int x, int y, int Delta) noexcept
{
	this->WheelDelta += Delta;
	while (WheelDelta >= WHEEL_DELTA)
	{
		WheelDelta -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (WheelDelta <= -WHEEL_DELTA)
	{
		WheelDelta += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}
