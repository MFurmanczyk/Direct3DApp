#include "KeyboardManager.h"

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
