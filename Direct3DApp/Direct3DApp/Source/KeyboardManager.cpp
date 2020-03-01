#include "../Include/KeyboardManager.h"

std::optional<KeyboardManager::Event> KeyboardManager::ReadKey() noexcept
{
	if (KeyBuffer.size() > 0u)
	{
		KeyboardManager::Event e = KeyBuffer.front();
		KeyBuffer.pop();
		return e;
	}
	return std::optional<KeyboardManager::Event>();
}

bool KeyboardManager::IsKeyEmpty() const noexcept
{
	return KeyBuffer.empty();
}

std::optional<char> KeyboardManager::ReadChar() noexcept
{
	if (CharBuffer.size() > 0u)
	{
		unsigned char charcode = CharBuffer.front();
		CharBuffer.pop();
		return charcode;
	}
	return std::optional<char>();
}

bool KeyboardManager::IsCharEmpty() noexcept
{
	return CharBuffer.empty();
}

void KeyboardManager::FlushChar() noexcept
{
	CharBuffer = std::queue<char>();
}

void KeyboardManager::Flush() noexcept
{
	this->FlushKey();
	this->FlushChar();
}

void KeyboardManager::OnKeyPressed(unsigned char KeyCode) noexcept
{
	KeyStates[KeyCode] = true;
	KeyBuffer.push(KeyboardManager::Event(KeyboardManager::Event::EType::Pressed, KeyCode));
	TrimBuffer(KeyBuffer);
}

void KeyboardManager::OnKeyReleased(unsigned char KeyCode) noexcept
{
	KeyStates[KeyCode] = false;
	KeyBuffer.push(KeyboardManager::Event(KeyboardManager::Event::EType::Released, KeyCode));
	TrimBuffer(KeyBuffer);
}

void KeyboardManager::OnChar(char Character) noexcept
{
	CharBuffer.push(Character);
	TrimBuffer(CharBuffer);
}

void KeyboardManager::ClearState() noexcept
{
	KeyStates.reset();
}