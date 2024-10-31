#pragma once
#include <Engine/qScript.h>

class qTestScript : public qScript
{
public:
	CLONE(qTestScript);
	qTestScript();
	~qTestScript();

public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;
};

