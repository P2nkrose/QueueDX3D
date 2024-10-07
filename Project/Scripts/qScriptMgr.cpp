#include "pch.h"
#include "qScriptMgr.h"

#include "qBleedScript.h"
#include "qBookScript_Left.h"
#include "qBookScript_Right.h"
#include "qBossHUDScript.h"
#include "qBossScript.h"
#include "qCameraMoveScript.h"
#include "qClapScript.h"
#include "qCollectScript.h"
#include "qComboScript.h"
#include "qCrashScript.h"
#include "qDeathSoulScript.h"
#include "qDoorScript.h"
#include "qDrownedAttackScript.h"
#include "qDrownedScript.h"
#include "qElevatorScript.h"
#include "qGhostAttackScript.h"
#include "qGhostScript.h"
#include "qKrushScript.h"
#include "qMissileScript.h"
#include "qPlatformScript.h"
#include "qPlayerEffectScript.h"
#include "qPlayerHitboxScript.h"
#include "qPlayerHUDScript.h"
#include "qPlayerScript.h"
#include "qPortalScript.h"
#include "qPostScript.h"
#include "qPunchScript.h"
#include "qRangeScript.h"
#include "qSkeletonAttackScript.h"
#include "qSkeletonScript.h"
#include "qSlamScript.h"
#include "qWallScript.h"

void qScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qBleedScript");
	_vec.push_back(L"qBookScript_Left");
	_vec.push_back(L"qBookScript_Right");
	_vec.push_back(L"qBossHUDScript");
	_vec.push_back(L"qBossScript");
	_vec.push_back(L"qCameraMoveScript");
	_vec.push_back(L"qClapScript");
	_vec.push_back(L"qCollectScript");
	_vec.push_back(L"qComboScript");
	_vec.push_back(L"qCrashScript");
	_vec.push_back(L"qDeathSoulScript");
	_vec.push_back(L"qDoorScript");
	_vec.push_back(L"qDrownedAttackScript");
	_vec.push_back(L"qDrownedScript");
	_vec.push_back(L"qElevatorScript");
	_vec.push_back(L"qGhostAttackScript");
	_vec.push_back(L"qGhostScript");
	_vec.push_back(L"qKrushScript");
	_vec.push_back(L"qMissileScript");
	_vec.push_back(L"qPlatformScript");
	_vec.push_back(L"qPlayerEffectScript");
	_vec.push_back(L"qPlayerHitboxScript");
	_vec.push_back(L"qPlayerHUDScript");
	_vec.push_back(L"qPlayerScript");
	_vec.push_back(L"qPortalScript");
	_vec.push_back(L"qPostScript");
	_vec.push_back(L"qPunchScript");
	_vec.push_back(L"qRangeScript");
	_vec.push_back(L"qSkeletonAttackScript");
	_vec.push_back(L"qSkeletonScript");
	_vec.push_back(L"qSlamScript");
	_vec.push_back(L"qWallScript");
}

qScript * qScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"qBleedScript" == _strScriptName)
		return new qBleedScript;
	if (L"qBookScript_Left" == _strScriptName)
		return new qBookScript_Left;
	if (L"qBookScript_Right" == _strScriptName)
		return new qBookScript_Right;
	if (L"qBossHUDScript" == _strScriptName)
		return new qBossHUDScript;
	if (L"qBossScript" == _strScriptName)
		return new qBossScript;
	if (L"qCameraMoveScript" == _strScriptName)
		return new qCameraMoveScript;
	if (L"qClapScript" == _strScriptName)
		return new qClapScript;
	if (L"qCollectScript" == _strScriptName)
		return new qCollectScript;
	if (L"qComboScript" == _strScriptName)
		return new qComboScript;
	if (L"qCrashScript" == _strScriptName)
		return new qCrashScript;
	if (L"qDeathSoulScript" == _strScriptName)
		return new qDeathSoulScript;
	if (L"qDoorScript" == _strScriptName)
		return new qDoorScript;
	if (L"qDrownedAttackScript" == _strScriptName)
		return new qDrownedAttackScript;
	if (L"qDrownedScript" == _strScriptName)
		return new qDrownedScript;
	if (L"qElevatorScript" == _strScriptName)
		return new qElevatorScript;
	if (L"qGhostAttackScript" == _strScriptName)
		return new qGhostAttackScript;
	if (L"qGhostScript" == _strScriptName)
		return new qGhostScript;
	if (L"qKrushScript" == _strScriptName)
		return new qKrushScript;
	if (L"qMissileScript" == _strScriptName)
		return new qMissileScript;
	if (L"qPlatformScript" == _strScriptName)
		return new qPlatformScript;
	if (L"qPlayerEffectScript" == _strScriptName)
		return new qPlayerEffectScript;
	if (L"qPlayerHitboxScript" == _strScriptName)
		return new qPlayerHitboxScript;
	if (L"qPlayerHUDScript" == _strScriptName)
		return new qPlayerHUDScript;
	if (L"qPlayerScript" == _strScriptName)
		return new qPlayerScript;
	if (L"qPortalScript" == _strScriptName)
		return new qPortalScript;
	if (L"qPostScript" == _strScriptName)
		return new qPostScript;
	if (L"qPunchScript" == _strScriptName)
		return new qPunchScript;
	if (L"qRangeScript" == _strScriptName)
		return new qRangeScript;
	if (L"qSkeletonAttackScript" == _strScriptName)
		return new qSkeletonAttackScript;
	if (L"qSkeletonScript" == _strScriptName)
		return new qSkeletonScript;
	if (L"qSlamScript" == _strScriptName)
		return new qSlamScript;
	if (L"qWallScript" == _strScriptName)
		return new qWallScript;
	return nullptr;
}

qScript * qScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BLEEDSCRIPT:
		return new qBleedScript;
		break;
	case (UINT)SCRIPT_TYPE::BOOKSCRIPT_LEFT:
		return new qBookScript_Left;
		break;
	case (UINT)SCRIPT_TYPE::BOOKSCRIPT_RIGHT:
		return new qBookScript_Right;
		break;
	case (UINT)SCRIPT_TYPE::BOSSHUDSCRIPT:
		return new qBossHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSSCRIPT:
		return new qBossScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new qCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CLAPSCRIPT:
		return new qClapScript;
		break;
	case (UINT)SCRIPT_TYPE::COLLECTSCRIPT:
		return new qCollectScript;
		break;
	case (UINT)SCRIPT_TYPE::COMBOSCRIPT:
		return new qComboScript;
		break;
	case (UINT)SCRIPT_TYPE::CRASHSCRIPT:
		return new qCrashScript;
		break;
	case (UINT)SCRIPT_TYPE::DEATHSOULSCRIPT:
		return new qDeathSoulScript;
		break;
	case (UINT)SCRIPT_TYPE::DOORSCRIPT:
		return new qDoorScript;
		break;
	case (UINT)SCRIPT_TYPE::DROWNEDATTACKSCRIPT:
		return new qDrownedAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::DROWNEDSCRIPT:
		return new qDrownedScript;
		break;
	case (UINT)SCRIPT_TYPE::ELEVATORSCRIPT:
		return new qElevatorScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOSTATTACKSCRIPT:
		return new qGhostAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOSTSCRIPT:
		return new qGhostScript;
		break;
	case (UINT)SCRIPT_TYPE::KRUSHSCRIPT:
		return new qKrushScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new qMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new qPlatformScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYEREFFECTSCRIPT:
		return new qPlayerEffectScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHITBOXSCRIPT:
		return new qPlayerHitboxScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHUDSCRIPT:
		return new qPlayerHUDScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new qPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PORTALSCRIPT:
		return new qPortalScript;
		break;
	case (UINT)SCRIPT_TYPE::POSTSCRIPT:
		return new qPostScript;
		break;
	case (UINT)SCRIPT_TYPE::PUNCHSCRIPT:
		return new qPunchScript;
		break;
	case (UINT)SCRIPT_TYPE::RANGESCRIPT:
		return new qRangeScript;
		break;
	case (UINT)SCRIPT_TYPE::SKELETONATTACKSCRIPT:
		return new qSkeletonAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::SKELETONSCRIPT:
		return new qSkeletonScript;
		break;
	case (UINT)SCRIPT_TYPE::SLAMSCRIPT:
		return new qSlamScript;
		break;
	case (UINT)SCRIPT_TYPE::WALLSCRIPT:
		return new qWallScript;
		break;
	}
	return nullptr;
}

const wchar_t * qScriptMgr::GetScriptName(qScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BLEEDSCRIPT:
		return L"qBleedScript";
		break;

	case SCRIPT_TYPE::BOOKSCRIPT_LEFT:
		return L"qBookScript_Left";
		break;

	case SCRIPT_TYPE::BOOKSCRIPT_RIGHT:
		return L"qBookScript_Right";
		break;

	case SCRIPT_TYPE::BOSSHUDSCRIPT:
		return L"qBossHUDScript";
		break;

	case SCRIPT_TYPE::BOSSSCRIPT:
		return L"qBossScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"qCameraMoveScript";
		break;

	case SCRIPT_TYPE::CLAPSCRIPT:
		return L"qClapScript";
		break;

	case SCRIPT_TYPE::COLLECTSCRIPT:
		return L"qCollectScript";
		break;

	case SCRIPT_TYPE::COMBOSCRIPT:
		return L"qComboScript";
		break;

	case SCRIPT_TYPE::CRASHSCRIPT:
		return L"qCrashScript";
		break;

	case SCRIPT_TYPE::DEATHSOULSCRIPT:
		return L"qDeathSoulScript";
		break;

	case SCRIPT_TYPE::DOORSCRIPT:
		return L"qDoorScript";
		break;

	case SCRIPT_TYPE::DROWNEDATTACKSCRIPT:
		return L"qDrownedAttackScript";
		break;

	case SCRIPT_TYPE::DROWNEDSCRIPT:
		return L"qDrownedScript";
		break;

	case SCRIPT_TYPE::ELEVATORSCRIPT:
		return L"qElevatorScript";
		break;

	case SCRIPT_TYPE::GHOSTATTACKSCRIPT:
		return L"qGhostAttackScript";
		break;

	case SCRIPT_TYPE::GHOSTSCRIPT:
		return L"qGhostScript";
		break;

	case SCRIPT_TYPE::KRUSHSCRIPT:
		return L"qKrushScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"qMissileScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"qPlatformScript";
		break;

	case SCRIPT_TYPE::PLAYEREFFECTSCRIPT:
		return L"qPlayerEffectScript";
		break;

	case SCRIPT_TYPE::PLAYERHITBOXSCRIPT:
		return L"qPlayerHitboxScript";
		break;

	case SCRIPT_TYPE::PLAYERHUDSCRIPT:
		return L"qPlayerHUDScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"qPlayerScript";
		break;

	case SCRIPT_TYPE::PORTALSCRIPT:
		return L"qPortalScript";
		break;

	case SCRIPT_TYPE::POSTSCRIPT:
		return L"qPostScript";
		break;

	case SCRIPT_TYPE::PUNCHSCRIPT:
		return L"qPunchScript";
		break;

	case SCRIPT_TYPE::RANGESCRIPT:
		return L"qRangeScript";
		break;

	case SCRIPT_TYPE::SKELETONATTACKSCRIPT:
		return L"qSkeletonAttackScript";
		break;

	case SCRIPT_TYPE::SKELETONSCRIPT:
		return L"qSkeletonScript";
		break;

	case SCRIPT_TYPE::SLAMSCRIPT:
		return L"qSlamScript";
		break;

	case SCRIPT_TYPE::WALLSCRIPT:
		return L"qWallScript";
		break;

	}
	return nullptr;
}