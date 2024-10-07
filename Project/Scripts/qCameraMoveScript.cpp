#include "pch.h"
#include "qCameraMoveScript.h"

#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>

qCameraMoveScript::qCameraMoveScript()
	: qScript(UINT(SCRIPT_TYPE::CAMERAMOVESCRIPT))
	, m_CamSpeed(500.f)
	, m_clap(false)
{
}

qCameraMoveScript::~qCameraMoveScript()
{
	//DELETE(m_FollowObj);
}

void qCameraMoveScript::Begin()
{
	m_FollowObj = qLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
}



void qCameraMoveScript::Tick()
{
	if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
	{
		OrthoGraphicMove();
	}
	else if (PROJ_TYPE::PERSPECTIVE == Camera()->GetProjType())
	{
		PerspectiveMove();
	}


	// 투영방법 변환키
	if (KEY_TAP(KEY::P))
	{
		if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
		{
			Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		}
		else
		{
			Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		}
	}

}


void qCameraMoveScript::OrthoGraphicMove()
{
	float Speed = m_CamSpeed;
	if (KEY_PRESSED(KEY::LSHIFT))
		Speed *= 3.f;

	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::I))
		vPos.y += DT * Speed;
	if (KEY_PRESSED(KEY::K))
		vPos.y -= DT * Speed;
	if (KEY_PRESSED(KEY::J))
		vPos.x -= DT * Speed;
	if (KEY_PRESSED(KEY::L))
		vPos.x += DT * Speed;

	if (m_FollowObj != nullptr)
	{
		vPos = m_FollowObj->Transform()->GetRelativePos();
	}

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"title")
	{
		vPos = Vec3(0.f, 0.f, 0.f);
	}

	if (pCurLevel->GetName() == L"stage1")
	{

		qGameObject* BackGround = pCurLevel->FindObjectByName(L"BGstage1");

		if (nullptr == BackGround)
			return;

		Vec3 BGScale = BackGround->Transform()->GetRelativeScale();

		Vec3 PlayerPos = m_FollowObj->Transform()->GetRelativePos();

		if (PlayerPos.x <= -465.f)
		{
			vPos.x = -465.f;
		}
		else if (PlayerPos.x >= 465.f)
		{
			vPos.x = 465.f;
		}
		else
		{
			vPos.x = PlayerPos.x;
		}

		//if (PlayerPos.y >= 256.f)
		//{
		//	vPos.y = 556.f;
		//}
		//else
		//{
		//	vPos.y = PlayerPos.y + 300.f;
		//}

		vPos.y = -120.f;

		// Y 좌표 계산
		// 
		//float vDist = vPos.y - PlayerPos.y;
		//if (PlayerPos.y >= -420.f)
		//{
		//	vPos.y = PlayerPos.y;
		//}
		//else
		//{
		//	vPos.y = -200.f;
		//}

		Transform()->SetRelativePos(vPos);
	}

	if (pCurLevel->GetName() == L"stage2")
	{
		Vec3 PlayerPos = m_FollowObj->Transform()->GetRelativePos();

		static bool flag = false;

		if (PlayerPos.x >= 4900.f && !flag)
		{
			fixPos = vPos;

			flag = true;
		}

		if (PlayerPos.x <= -4937.f)
		{
			vPos.x = -4937.f;
		}
		else if (PlayerPos.x >= 4931.f)
		{
			vPos.x = 4931.f;
		}
		else
		{
			vPos.x = PlayerPos.x;
		}

		if (PlayerPos.y >= 256.f)
		{
			vPos.y = 456.f;
		}
		else if (PlayerPos.x >= 5000.f)
		{
			vPos.y = fixPos.y + 200.f;
		}
		else
		{
			vPos.y = PlayerPos.y + 200.f;
		}






		//vPos.y = -120.f;

		// Y 좌표 계산
		// 
		//float vDist = vPos.y - PlayerPos.y;
		//if (PlayerPos.y >= -420.f)
		//{
		//	vPos.y = PlayerPos.y;
		//}
		//else
		//{
		//	vPos.y = -200.f;
		//}

		Transform()->SetRelativePos(vPos);
	}

	if (pCurLevel->GetName() == L"stageboss")
	{
		if (!m_clap)
		{
			Vec3 PlayerPos = m_FollowObj->Transform()->GetRelativePos();

			if (PlayerPos.x <= -390.f)
			{
				vPos.x = -390.f;
			}
			else if (PlayerPos.x >= 390.f)
			{
				vPos.x = 390.f;
			}
			else
			{
				vPos.x = PlayerPos.x;
			}

			vPos.y = 27.f;

			Transform()->SetRelativePos(vPos);
		}
		else if (m_clap)
		{
			Vec3 PlayerPos = m_FollowObj->Transform()->GetRelativePos();

			//if (PlayerPos.x >= -198.f)
			//{
			//	vPos.x = 390.f;
			//}
			//else if (PlayerPos.x >= 390.f)
			//{
			//	vPos.x = 390.f;
			//}

			vPos.x = 390.f;
			vPos.y = 27.f;

			//vPos.x += DT * m_CamSpeed;
			//
			//if (PlayerPos.x >= -198.f)
			//{
			//	if (vPos.x >= 390.f)
			//	{
			//		vPos.x = 390.f;
			//		
			//	}
			//}
			//
			//vPos.y = 27.f;

			

			Transform()->SetRelativePos(vPos);
		}
	}

	

	//qGameObject* player = qLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");


	//if (nullptr != player)
	//{
	//	vPos = player->Transform()->GetRelativePos();
	//}




	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
}

void qCameraMoveScript::PerspectiveMove()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}


	Vec3 vFront = Transform()->GetWorldDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetWorldDir(DIR::RIGHT);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront* DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= vRight * DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += vRight * DT * Speed;
	}

	Transform()->SetRelativePos(vPos);


	if (KEY_PRESSED(KEY::RBTN))
	{
		qKeyMgr::GetInst()->MouseCapture(true);

		// 마우스가 이동하는 방향
		// vDir.x; ==>  y축 회전
		// vDir.y; ==>  x축 회전
		Vec2 vDir = qKeyMgr::GetInst()->GetDragDir();

		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += vDir.x * XM_PI * DT * 10.f;
		vRot.x += vDir.y * XM_PI * DT * 10.f;
		Transform()->SetRelativeRotation(vRot);
	}
	else if (KEY_RELEASED(KEY::RBTN))
	{
		qKeyMgr::GetInst()->MouseCapture(false);
	}
}



void qCameraMoveScript::SaveToFile(FILE* _File)
{
	fwrite(&m_CamSpeed, sizeof(float), 1, _File);
	//fwrite(&m_FollowObj, sizeof(qGameObject), 1, _File);
}

void qCameraMoveScript::LoadFromFile(FILE* _File)
{
	fread(&m_CamSpeed, sizeof(float), 1, _File);
	//fread(&m_FollowObj, sizeof(qGameObject), 1, _File);
}

