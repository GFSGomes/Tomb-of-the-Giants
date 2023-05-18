#include "Key.hpp"
#include "Renderer.hpp"

Key::Key(KeyType _type) : Item("Key", 5)
{
	key_type = _type;

	switch (key_type)
	{
		case KeyType::PORTAL_KEY:
			name = "Door Key";
			description = "A common door key.";
			sprite = Sprite::KEY_0;
			break;
		case KeyType::SECRET_KEY:
			name = "Secret Door Revealer Key";
			description = "When held in living hands it make a secret door sligh glow in the darkness.";
			sprite = Sprite::KEY_2;
			break;
		case KeyType::CHEST_KEY:
			name = "Hidden Chest Revealer Key";
			description = "Makes a hidden chest sligh glow.";
			sprite = Sprite::KEY_1;
			break;
	}
}

Key::~Key()
{

}