#include "pch.h"
#include "qGameObjectEx.h"

#include <Engine/components.h>

void qGameObjectEx::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != GetComponent((COMPONENT_TYPE)i))
			GetComponent((COMPONENT_TYPE)i)->FinalTick();
	}


	// 자식 오브젝트
	vector<qGameObject*>::const_iterator iter = GetChildren().begin();
	for (; iter != GetChildren().end(); ++iter)
	{
		(*iter)->FinalTick();
	}
}
