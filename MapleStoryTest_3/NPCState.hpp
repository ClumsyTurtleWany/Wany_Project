#pragma once

class NPC;

// Finite State Machine
class NPCState
{
protected:
	NPC* npc;

public:
	NPCState(NPC* _user);
	virtual ~NPCState();

public:
	virtual bool initialize() = 0;
	virtual bool frame() = 0;
	virtual bool render() = 0;
	virtual bool release() = 0;

};