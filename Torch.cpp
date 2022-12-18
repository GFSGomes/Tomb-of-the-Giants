#include "Torch.hpp"

Torch::Torch() : Item("Torch",1)
{
	sprite = Sprite::TORCH;
}

Torch::~Torch()
{

}

void Torch::Use()
{
	PLAYER.torchDuration += rand() % 50 + 5;
}