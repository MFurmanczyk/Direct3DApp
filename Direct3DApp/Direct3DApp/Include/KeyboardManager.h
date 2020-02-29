#pragma once

#include <queue>
#include <bitset>
#include <optional>

class KeyboardManager
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class EType
		{
			Pressed,
			Released,
			Invalid
		};
	private:
		EType Type;
		unsigned char Code;
	public:
		Event() : Type(EType::Invalid), Code(0u) {}
		Event(EType pType, unsigned char pCode) noexcept : Type(pType), Code(pCode) {}
		inline bool IsPressed() const noexcept { return Type == EType::Pressed; }
		inline bool IsReleased() const noexcept { return Type == EType::Released; }
		inline bool IsValid() const noexcept { return Type != EType::Invalid; }
		inline char GetCode() const noexcept { return this->Code; }
	};
public:
	KeyboardManager() = default;
	KeyboardManager(const KeyboardManager&) = delete;
	KeyboardManager& operator= (const KeyboardManager&) = delete;
	//Key events
	inline bool IsKeyPressed(unsigned char KeyCode) noexcept { return KeyStates[KeyCode]; };
	std::optional<Event> ReadKey() noexcept;
	bool IsKeyEmpty() const noexcept;
	inline void FlushKey() noexcept { KeyBuffer = std::queue<Event>(); };
	//Char events
	std::optional<char>ReadChar() noexcept;
	bool IsCharEmpty() noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;
	//Autorepeat
	inline void EnableAutorepeat() noexcept { AutorepeatEnabled = true; };
	inline void DisableAutorepeat() noexcept { AutorepeatEnabled = false; };
	inline bool IsAutorepeatEnabled() const noexcept { return this->AutorepeatEnabled; };
private:
	void OnKeyPressed(unsigned char KeyCode) noexcept;
	void OnKeyReleased(unsigned char KeyCode) noexcept;
	void OnChar(char Character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& Buffer) noexcept;
private:
	static constexpr unsigned nKeys = 256u;
	static constexpr unsigned BufferSize = 16u;
	bool AutorepeatEnabled = false;
	std::bitset<nKeys> KeyStates;
	std::queue<Event> KeyBuffer;
	std::queue<char> CharBuffer;

};
