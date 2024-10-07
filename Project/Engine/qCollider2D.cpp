#include "pch.h"
#include "qCollider2D.h"

#include "qTransform.h"
#include "qScript.h"


qCollider2D::qCollider2D()
	: qComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_OverlapCount(0)
	, m_Scale(Vec3(1.f, 1.f, 1.f))
	, m_Active(true)
	, m_SemiDeactive(false)
	, m_IndependentScale(false)
{
}

qCollider2D::qCollider2D(const qCollider2D& _Origin)
	: qComponent(_Origin)
	, m_Offset(_Origin.m_Offset)
	, m_Scale(_Origin.m_Scale)
	, m_Active(_Origin.m_Active)
	, m_SemiDeactive(_Origin.m_SemiDeactive)
	, m_OverlapCount(0)
	, m_IndependentScale(_Origin.m_IndependentScale)
{
}

qCollider2D::~qCollider2D()
{
}

void qCollider2D::Activate()
{
	m_Active = true;
}

void qCollider2D::FinalTick()
{
	// 비활성화 예정 상태라면, 비활성화 시킨다
	if (m_SemiDeactive)
	{
		tTask task = {};
		task.Type = TASK_TYPE::COLLIDER2D_DEACTIVE;
		task.Param_0 = (DWORD_PTR)this;
		qTaskMgr::GetInst()->AddTask(task);
	}

	// 비활성화된 충돌체는 계산하지 않는다.
	else if (!m_Active)
		return;


	Matrix matTranslation = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);
	Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	// 크기, 회전, 이동
	Matrix matObjectScaleInv = XMMatrixIdentity();

	if (m_IndependentScale)
	{
		Vec3 vObjectScale = GetOwner()->Transform()->GetWorldScale();
		matObjectScaleInv = XMMatrixScaling(vObjectScale.x, vObjectScale.y, vObjectScale.z);
		matObjectScaleInv = XMMatrixInverse(nullptr, matObjectScaleInv);
	}

	m_matColWorld = matScale * matTranslation * matObjectScaleInv * GetOwner()->Transform()->GetWorldMat();


	// 충돌했을 시 색깔 변경
	// Debug 렌더링으로 충돌체의 위치를 표시
	if(m_OverlapCount)
		DrawDebugRect(m_matColWorld, Vec4(1.f, 0.f, 0.f, 1.f), 0.f, false);
	else
		DrawDebugRect(m_matColWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f, false);

}



void qCollider2D::BeginOverlap(qCollider2D* _Other)
{
	m_OverlapCount += 1;

	const vector<qScript*> vecScripts = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->BeginOverlap(this, _Other->GetOwner(), _Other);
	}
}

void qCollider2D::Overlap(qCollider2D* _Other)
{
	const vector<qScript*> vecScripts = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->Overlap(this, _Other->GetOwner(), _Other);
	}
}

void qCollider2D::EndOverlap(qCollider2D* _Other)
{
	m_OverlapCount -= 1;

	const vector<qScript*> vecScripts = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->EndOverlap(this, _Other->GetOwner(), _Other);
	}
}



void qCollider2D::Deactivate()
{
	tTask task = {};
	task.Type = TASK_TYPE::COLLIDER2D_SEMI_DEACTIVE;
	task.Param_0 = (DWORD_PTR)this;
	qTaskMgr::GetInst()->AddTask(task);
}



void qCollider2D::SaveToFile(FILE* _File)
{
	fwrite(&m_Offset, sizeof(Vec3), 1, _File);
	fwrite(&m_Scale, sizeof(Vec3), 1, _File);
	fwrite(&m_IndependentScale, sizeof(bool), 1, _File);
}

void qCollider2D::LoadFromFile(FILE* _File)
{
	fread(&m_Offset, sizeof(Vec3), 1, _File);
	fread(&m_Scale, sizeof(Vec3), 1, _File);
	fread(&m_IndependentScale, sizeof(bool), 1, _File);
}