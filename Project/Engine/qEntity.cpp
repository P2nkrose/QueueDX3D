#include "pch.h"
#include "qEntity.h"

// 정적 멤버 초기화
UINT qEntity::g_ID = 0;

qEntity::qEntity()
	: m_ID(g_ID++)
{
}

qEntity::qEntity(const qEntity& _Other)
	: m_ID(g_ID++)
	, m_Name(_Other.m_Name)
{

}

qEntity::~qEntity()
{
}
