#include "Key.hpp"
#include "Renderer.hpp"

Key::Key(KeyType _type) : Miscellaneous("Key", 5)
{
	keyType = _type;

	switch (keyType)
	{
		case KeyType::PORTAL_KEY:
			name = "Door Key";
			stack = 5;
			description = "A common door key.";
			sprite = Sprite::KEY_0;
			break;

		case KeyType::SECRET_KEY:
			name = "Secret Chamber Key";
			stack = 1;
			description = "When carried by living beings, it reacts with nearby concealment spells, revealing runic inscriptions which any torch flame would dim its glow.";
			sprite = Sprite::KEY_1;
			break;

		case KeyType::CHEST_KEY:
			name = "Chest Key";
			stack = 3;
			description = "Opens a chest.";
			sprite = Sprite::KEY_2;
			break;
	}
}

Key::~Key()
{

}