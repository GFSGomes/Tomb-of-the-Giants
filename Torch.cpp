#include "Torch.hpp"
#include "Renderer.hpp"

Torch::Torch() : Consumable("Torch", 1)
{
	sprite = Sprite::TORCH;
}

Torch::~Torch()
{

}