#pragma once

struct UI
{
	bool active;
	char  input;
	short index;

	UI();
	virtual ~UI() = 0;

	virtual bool Initialize() = 0;
};