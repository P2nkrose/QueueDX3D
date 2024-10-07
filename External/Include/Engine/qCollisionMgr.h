#pragma once

class qCollider2D;

union COLLIDER_ID
{
	struct 
	{
		DWORD LeftID;
		DWORD RightID;
	};
	ULONGLONG ID;
};


class qCollisionMgr : public qSingleton<qCollisionMgr>
{
public:
	SINGLE(qCollisionMgr);

public:
	void Tick();

public:
	void CollisionCheck(UINT Layer1, UINT Layer2);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(UINT) * MAX_LAYER); }


private:
	void CollisionBtwLayer(UINT _Left, UINT _Right);
	bool IsCollision(qCollider2D* _Left, qCollider2D* _Right);


private:
	UINT						m_Matrix[MAX_LAYER];
	map<ULONGLONG, bool>		m_mapCollisionInfo;

};

