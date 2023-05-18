#include "Portal.hpp"

Portal::Portal(
	short _posX, short _posY, 
	std::shared_ptr<Scene> _origin, std::shared_ptr<Scene> _destiny, 
	bool _is_locked, KeyType _key_type )
	: 
	origin{_origin}, destiny{_destiny}, key_type{_key_type}, is_locked{_is_locked}
{
	SpawnAt(_posX, _posY);
}

Portal::~Portal()
{

}