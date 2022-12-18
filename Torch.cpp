#include "Torch.hpp"
#include "Player.hpp"

Torch::Torch() : Item("Torch",1)
{
	sprite = Sprite::TORCH;
}

Torch::~Torch()
{

}

void Torch::Use()
{
	short bonus = rand() % 50 + 5;
	PLAYER.torchDuration += bonus;
}