#include "Torch.hpp"

Torch::Torch() : Item("Torch",1)
{
	renderer.sprite = Sprite::TORCH;
}

Torch::~Torch()
{

}

short Torch::Use()
{
	return rand() % 50 + 5;
}