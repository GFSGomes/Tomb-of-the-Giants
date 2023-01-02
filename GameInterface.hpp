#pragma once
#include "GUI.hpp"
#include "Player.hpp"


struct Controls : GUI
{
	Controls();
	~Controls();

	void Initialize() override;
	void Initialize(std::shared_ptr<Player>);
	void Input(std::shared_ptr<Player>);
};

extern Controls GUI_Controls;