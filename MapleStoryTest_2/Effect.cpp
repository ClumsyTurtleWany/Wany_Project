#include "Effect.hpp"

Effect::Effect()
{

}

Effect::Effect(const Rect2f& _rect)
{

}

Effect::~Effect()
{

}

bool Effect::initialize()
{
	return true;
}

bool Effect::frame() 
{
	return true;
}

bool Effect::render()
{
	return true;
}

bool Effect::release()
{
	return true;
}
