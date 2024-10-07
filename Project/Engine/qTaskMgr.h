#pragma once


class qTaskMgr : public qSingleton<qTaskMgr>
{
	SINGLE(qTaskMgr)

public:
	void Tick();
	void AddTask(const tTask& _Task);

private:
	void ClearGC();
	void ExecuteTask();	


private:
	vector<tTask>			m_vecTask;
	vector<qGameObject*>	m_GC; // Garbage Collector;
};

