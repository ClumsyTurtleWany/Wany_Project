#pragma once

class FiniteStateMachine
{
public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};