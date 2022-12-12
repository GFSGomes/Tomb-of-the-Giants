#include "Torch.hpp"

Torch::Torch()
{
	renderer.sprite = Sprite::TORCH;
}

Torch::~Torch()
{

}

void Torch::Use()
{
	short duration = rand() % 50 + 5;

	//player.torchDuration += duration;
}