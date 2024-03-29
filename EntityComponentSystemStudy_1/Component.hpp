#pragma once
#include "ECSCommon.hpp"

namespace ECS
{
	class Component
	{
	public:
		Component() {};
		virtual ~Component() {};
	};

	template<typename T>
	class ComponentContainer : public Component
	{
	public:
		T Data;

	public:
		ComponentContainer() {};
		ComponentContainer(const T& data) : Data(data) {};
		virtual ~ComponentContainer() {};
	};
}