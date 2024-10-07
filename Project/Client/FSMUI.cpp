#include "pch.h"
#include "FSMUI.h"

FSMUI::FSMUI()
	: ComponentUI(COMPONENT_TYPE::STATEMACHINE)
{
}

FSMUI::~FSMUI()
{
}

void FSMUI::Update()
{
	Title();
}
