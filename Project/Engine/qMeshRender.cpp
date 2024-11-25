#include "pch.h"
#include "qMeshRender.h"

#include "qTransform.h"
#include "qFlipBookComponent.h"
#include "qSprite.h"

qMeshRender::qMeshRender()
	: qRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

qMeshRender::~qMeshRender()
{
}

void qMeshRender::FinalTick()
{
}

void qMeshRender::Render()
{

	// FlipBookComponent 가 있으면 현재 재생중인 Sprite 정보를 Binding 하게 한다.
	if (FlipBookComponent())
		FlipBookComponent()->Binding();
	else
		qFlipBookComponent::Clear();

	// 위치, 크기, 회전 상태정보 바인딩
	Transform()->Binding();

	// 재질 바인딩 (재질 상수, 쉐이더 등등)
	GetMaterial(0)->Binding();

	for (UINT i = 0; i < GetMesh()->GetSubsetCount(); ++i)
	{
		// 재질 바인딩(재질 상수, 쉐이더 등등)
		if (!GetMaterial(i))
			continue;

		GetMaterial(i)->Binding();

		// 버텍스버퍼, 인덱스버퍼 바인딩 및 렌더링 호출
		GetMesh()->Render(i);
	}
}


void qMeshRender::SaveToFile(FILE* _File)
{
	SaveDataToFile(_File);
}

void qMeshRender::LoadFromFile(FILE* _File)
{
	LoadDataFromFile(_File);
}
