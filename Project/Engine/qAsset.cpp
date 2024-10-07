#include "pch.h"
#include "qAsset.h"

qAsset::qAsset(ASSET_TYPE _Type)
	: m_Type(_Type)
	, m_RefCount(0)
	, m_Engine(false)
{
}

qAsset::qAsset(const qAsset& _Other)
	: qEntity(_Other)
	, m_Key(_Other.m_Key)
	, m_RelativePath(_Other.m_RelativePath)
	, m_Type(_Other.m_Type)
	, m_RefCount(0)
{
}

qAsset::~qAsset()
{
}
