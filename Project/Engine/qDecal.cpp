#include "pch.h"
#include "qDecal.h"

#include "qTransform.h"

qDecal::qDecal()
	: qRenderComponent(COMPONENT_TYPE::DECAL)
{
}

qDecal::~qDecal()
{
}

void qDecal::FinalTick()
{
	DrawDebugCube(Transform()->GetWorldMat(), Vec4(0.f, 1.f, 0.f, 1.f), 0, true);
}

void qDecal::Render()
{
}

void qDecal::SaveToFile(FILE* _File)
{
}

void qDecal::LoadFromFile(FILE* _File)
{
}
