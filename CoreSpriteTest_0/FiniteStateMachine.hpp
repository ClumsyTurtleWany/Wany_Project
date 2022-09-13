#pragma once

// Finite State Machine
class FiniteStateMachine
{
public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

};