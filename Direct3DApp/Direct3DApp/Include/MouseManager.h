#pragma once
#include <queue>
#include <optional>

class MouseManager
{
	friend class Window;
public:
	struct RawDelta
	{
		int x;
		int y;
	};
	class Event
	{
	public:
		enum class EType
		{
			LPressed,
			LReleased,
			RPressed,
			RReleased,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave
		};
	private:
		EType Type;
		bool LeftPressed;
		bool RightPressed;
		int x;
		int y;
	public:
		Event(EType Type, const MouseManager& Parent) noexcept :
			Type(Type),
			LeftPressed(Parent.LeftPressed),
			RightPressed(Parent.RightPressed), 
			x(Parent.x),
			y(Parent.y) 
		{
		
		};
		EType GetType() const noexcept { return this->Type; };
		std::pair<int, int> GetPosition() const noexcept { return std::pair<int, int>(this->x, this->y); };
		int GetPositionX() const noexcept { return this->x; };
		int GetPositionY() const noexcept { return this->y; };
		bool IsLeftPressed() const noexcept { return this->LeftPressed; };
		bool IsRightPressed() const noexcept { return this->RightPressed; };
	};
public:
	MouseManager() = default;
	MouseManager(const MouseManager&) = delete;
	MouseManager& operator=(const MouseManager&) = delete;
	std::pair<int, int> GetPosition() const noexcept { return std::pair<int, int>(this->x, this->y); };
	std::optional<RawDelta> ReadRawDelta() noexcept;
	int GetPositionX() const noexcept { return this->x; };
	int GetPositionY() const noexcept { return this->y; };
	bool IsInWindow() const noexcept { return this->InWindow; };
	bool IsLeftPressed() const noexcept { return this->LeftPressed; };
	bool IsRightPressed() const noexcept { return this->RightPressed; };
	std::optional<MouseManager::Event> Read() noexcept;
	bool IsEmpty() const noexcept { return Buffer.empty(); }
	void Flush() noexcept;
	void EnableRaw() noexcept { this->RawEnabled = true; };
	void DisableRaw() noexcept { this->RawEnabled = false; };
	bool IsRawEnabled() const noexcept { return this->RawEnabled; };
private:
	void OnMouseMove(int x, int y) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnRawDelta(int dx, int dy) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;
	void TrimRawInputBuffer() noexcept;
	void OnWheelDelta(int x, int y, int Delta) noexcept;

private:
	static constexpr unsigned BufferSize = 16u;
	int x;
	int y;
	bool LeftPressed = false;
	bool RightPressed = false;
	bool InWindow = false;
	int WheelDelta = 0;
	bool RawEnabled = false;
	std::queue<Event> Buffer;
	std::queue<RawDelta> RawDeltaBuffer;
};