#include "pch.h"
#include "qComponent.h"

qComponent::qComponent(COMPONENT_TYPE _Type)
	: m_Type(_Type)
	, m_Owner(nullptr)
{
}

qComponent::qComponent(const qComponent& _Origin)
	: m_Type(_Origin.m_Type)
	, m_Owner(nullptr)
{
}

qComponent::~qComponent()
{
}

void qComponent::Begin()
{
}

void qComponent::Tick()
{
}
