#include "Torch.hpp"
#include "Renderer.hpp"
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
	PLAYER.torchDuration += rand() % 10 + 5;
}