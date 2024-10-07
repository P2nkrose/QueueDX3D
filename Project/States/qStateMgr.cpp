#include "pch.h"
#include "qStateMgr.h"

#include "qBookEffectState.h"
#include "qBossBleedState.h"
#include "qBossBleedWaveState.h"
#include "qBossDeathState.h"
#include "qBossHitState.h"
#include "qBossIdleState.h"
#include "qBossIntroState.h"
#include "qBossPunchState.h"
#include "qBossRunState.h"
#include "qBossSlamFistState.h"
#include "qBossSlamState.h"
#include "qBossStayState.h"
#include "qBossUturnState.h"
#include "qClapState.h"
#include "qDeathSoulState.h"
#include "qDoorCloseState.h"
#include "qDoorOpenState.h"
#include "qDoorStayState.h"
#include "qDrownedAttackState.h"
#include "qDrownedDeathState.h"
#include "qDrownedHitState.h"
#include "qDrownedIdleState.h"
#include "qDrownedRunState.h"
#include "qDrownedUturnState.h"
#include "qElevatorCloseState.h"
#include "qElevatorOpenState.h"
#include "qElevatorStayState.h"
#include "qFireState.h"
#include "qGhostAttackState.h"
#include "qGhostDeathState.h"
#include "qGhostHitState.h"
#include "qGhostIdleState.h"
#include "qGhostRunState.h"
#include "qGhostUturnState.h"
#include "qLoading1State.h"
#include "qLoadingState.h"
#include "qLogoState.h"
#include "qPlayerBookShootState.h"
#include "qPlayerBumpState.h"
#include "qPlayerCombo1State.h"
#include "qPlayerCombo2State.h"
#include "qPlayerCombo3State.h"
#include "qPlayerCombo4State.h"
#include "qPlayerCrashState.h"
#include "qPlayerDashState.h"
#include "qPlayerEffectState.h"
#include "qPlayerElevatorOutState.h"
#include "qPlayerFallingState.h"
#include "qPlayerGetItemState.h"
#include "qPlayerIdleState.h"
#include "qPlayerIdleToRunState.h"
#include "qPlayerIdleUTurnState.h"
#include "qPlayerJumpState.h"
#include "qPlayerKrushState.h"
#include "qPlayerLandingState.h"
#include "qPlayerNullState.h"
#include "qPlayerRangeState.h"
#include "qPlayerRunState.h"
#include "qPlayerRunToIdleState.h"
#include "qPlayerRunUTurnState.h"
#include "qPlayerTeleportFinishState.h"
#include "qPlayerTeleportState.h"
#include "qPlayerWaitState.h"
#include "qPostCloseState.h"
#include "qPostOpenState.h"
#include "qSkeletonAttackState.h"
#include "qSkeletonDeathState.h"
#include "qSkeletonIdleState.h"
#include "qWarningState.h"

void qStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qBookEffectState");
	_vec.push_back(L"qBossBleedState");
	_vec.push_back(L"qBossBleedWaveState");
	_vec.push_back(L"qBossDeathState");
	_vec.push_back(L"qBossHitState");
	_vec.push_back(L"qBossIdleState");
	_vec.push_back(L"qBossIntroState");
	_vec.push_back(L"qBossPunchState");
	_vec.push_back(L"qBossRunState");
	_vec.push_back(L"qBossSlamFistState");
	_vec.push_back(L"qBossSlamState");
	_vec.push_back(L"qBossStayState");
	_vec.push_back(L"qBossUturnState");
	_vec.push_back(L"qClapState");
	_vec.push_back(L"qDeathSoulState");
	_vec.push_back(L"qDoorCloseState");
	_vec.push_back(L"qDoorOpenState");
	_vec.push_back(L"qDoorStayState");
	_vec.push_back(L"qDrownedAttackState");
	_vec.push_back(L"qDrownedDeathState");
	_vec.push_back(L"qDrownedHitState");
	_vec.push_back(L"qDrownedIdleState");
	_vec.push_back(L"qDrownedRunState");
	_vec.push_back(L"qDrownedUturnState");
	_vec.push_back(L"qElevatorCloseState");
	_vec.push_back(L"qElevatorOpenState");
	_vec.push_back(L"qElevatorStayState");
	_vec.push_back(L"qFireState");
	_vec.push_back(L"qGhostAttackState");
	_vec.push_back(L"qGhostDeathState");
	_vec.push_back(L"qGhostHitState");
	_vec.push_back(L"qGhostIdleState");
	_vec.push_back(L"qGhostRunState");
	_vec.push_back(L"qGhostUturnState");
	_vec.push_back(L"qLoading1State");
	_vec.push_back(L"qLoadingState");
	_vec.push_back(L"qLogoState");
	_vec.push_back(L"qPlayerBookShootState");
	_vec.push_back(L"qPlayerBumpState");
	_vec.push_back(L"qPlayerCombo1State");
	_vec.push_back(L"qPlayerCombo2State");
	_vec.push_back(L"qPlayerCombo3State");
	_vec.push_back(L"qPlayerCombo4State");
	_vec.push_back(L"qPlayerCrashState");
	_vec.push_back(L"qPlayerDashState");
	_vec.push_back(L"qPlayerEffectState");
	_vec.push_back(L"qPlayerElevatorOutState");
	_vec.push_back(L"qPlayerFallingState");
	_vec.push_back(L"qPlayerGetItemState");
	_vec.push_back(L"qPlayerIdleState");
	_vec.push_back(L"qPlayerIdleToRunState");
	_vec.push_back(L"qPlayerIdleUTurnState");
	_vec.push_back(L"qPlayerJumpState");
	_vec.push_back(L"qPlayerKrushState");
	_vec.push_back(L"qPlayerLandingState");
	_vec.push_back(L"qPlayerNullState");
	_vec.push_back(L"qPlayerRangeState");
	_vec.push_back(L"qPlayerRunState");
	_vec.push_back(L"qPlayerRunToIdleState");
	_vec.push_back(L"qPlayerRunUTurnState");
	_vec.push_back(L"qPlayerTeleportFinishState");
	_vec.push_back(L"qPlayerTeleportState");
	_vec.push_back(L"qPlayerWaitState");
	_vec.push_back(L"qPostCloseState");
	_vec.push_back(L"qPostOpenState");
	_vec.push_back(L"qSkeletonAttackState");
	_vec.push_back(L"qSkeletonDeathState");
	_vec.push_back(L"qSkeletonIdleState");
	_vec.push_back(L"qWarningState");
}

qState * qStateMgr::GetState(const wstring& _strStateName)
{
	if (L"qBookEffectState" == _strStateName)
		return new qBookEffectState;
	if (L"qBossBleedState" == _strStateName)
		return new qBossBleedState;
	if (L"qBossBleedWaveState" == _strStateName)
		return new qBossBleedWaveState;
	if (L"qBossDeathState" == _strStateName)
		return new qBossDeathState;
	if (L"qBossHitState" == _strStateName)
		return new qBossHitState;
	if (L"qBossIdleState" == _strStateName)
		return new qBossIdleState;
	if (L"qBossIntroState" == _strStateName)
		return new qBossIntroState;
	if (L"qBossPunchState" == _strStateName)
		return new qBossPunchState;
	if (L"qBossRunState" == _strStateName)
		return new qBossRunState;
	if (L"qBossSlamFistState" == _strStateName)
		return new qBossSlamFistState;
	if (L"qBossSlamState" == _strStateName)
		return new qBossSlamState;
	if (L"qBossStayState" == _strStateName)
		return new qBossStayState;
	if (L"qBossUturnState" == _strStateName)
		return new qBossUturnState;
	if (L"qClapState" == _strStateName)
		return new qClapState;
	if (L"qDeathSoulState" == _strStateName)
		return new qDeathSoulState;
	if (L"qDoorCloseState" == _strStateName)
		return new qDoorCloseState;
	if (L"qDoorOpenState" == _strStateName)
		return new qDoorOpenState;
	if (L"qDoorStayState" == _strStateName)
		return new qDoorStayState;
	if (L"qDrownedAttackState" == _strStateName)
		return new qDrownedAttackState;
	if (L"qDrownedDeathState" == _strStateName)
		return new qDrownedDeathState;
	if (L"qDrownedHitState" == _strStateName)
		return new qDrownedHitState;
	if (L"qDrownedIdleState" == _strStateName)
		return new qDrownedIdleState;
	if (L"qDrownedRunState" == _strStateName)
		return new qDrownedRunState;
	if (L"qDrownedUturnState" == _strStateName)
		return new qDrownedUturnState;
	if (L"qElevatorCloseState" == _strStateName)
		return new qElevatorCloseState;
	if (L"qElevatorOpenState" == _strStateName)
		return new qElevatorOpenState;
	if (L"qElevatorStayState" == _strStateName)
		return new qElevatorStayState;
	if (L"qFireState" == _strStateName)
		return new qFireState;
	if (L"qGhostAttackState" == _strStateName)
		return new qGhostAttackState;
	if (L"qGhostDeathState" == _strStateName)
		return new qGhostDeathState;
	if (L"qGhostHitState" == _strStateName)
		return new qGhostHitState;
	if (L"qGhostIdleState" == _strStateName)
		return new qGhostIdleState;
	if (L"qGhostRunState" == _strStateName)
		return new qGhostRunState;
	if (L"qGhostUturnState" == _strStateName)
		return new qGhostUturnState;
	if (L"qLoading1State" == _strStateName)
		return new qLoading1State;
	if (L"qLoadingState" == _strStateName)
		return new qLoadingState;
	if (L"qLogoState" == _strStateName)
		return new qLogoState;
	if (L"qPlayerBookShootState" == _strStateName)
		return new qPlayerBookShootState;
	if (L"qPlayerBumpState" == _strStateName)
		return new qPlayerBumpState;
	if (L"qPlayerCombo1State" == _strStateName)
		return new qPlayerCombo1State;
	if (L"qPlayerCombo2State" == _strStateName)
		return new qPlayerCombo2State;
	if (L"qPlayerCombo3State" == _strStateName)
		return new qPlayerCombo3State;
	if (L"qPlayerCombo4State" == _strStateName)
		return new qPlayerCombo4State;
	if (L"qPlayerCrashState" == _strStateName)
		return new qPlayerCrashState;
	if (L"qPlayerDashState" == _strStateName)
		return new qPlayerDashState;
	if (L"qPlayerEffectState" == _strStateName)
		return new qPlayerEffectState;
	if (L"qPlayerElevatorOutState" == _strStateName)
		return new qPlayerElevatorOutState;
	if (L"qPlayerFallingState" == _strStateName)
		return new qPlayerFallingState;
	if (L"qPlayerGetItemState" == _strStateName)
		return new qPlayerGetItemState;
	if (L"qPlayerIdleState" == _strStateName)
		return new qPlayerIdleState;
	if (L"qPlayerIdleToRunState" == _strStateName)
		return new qPlayerIdleToRunState;
	if (L"qPlayerIdleUTurnState" == _strStateName)
		return new qPlayerIdleUTurnState;
	if (L"qPlayerJumpState" == _strStateName)
		return new qPlayerJumpState;
	if (L"qPlayerKrushState" == _strStateName)
		return new qPlayerKrushState;
	if (L"qPlayerLandingState" == _strStateName)
		return new qPlayerLandingState;
	if (L"qPlayerNullState" == _strStateName)
		return new qPlayerNullState;
	if (L"qPlayerRangeState" == _strStateName)
		return new qPlayerRangeState;
	if (L"qPlayerRunState" == _strStateName)
		return new qPlayerRunState;
	if (L"qPlayerRunToIdleState" == _strStateName)
		return new qPlayerRunToIdleState;
	if (L"qPlayerRunUTurnState" == _strStateName)
		return new qPlayerRunUTurnState;
	if (L"qPlayerTeleportFinishState" == _strStateName)
		return new qPlayerTeleportFinishState;
	if (L"qPlayerTeleportState" == _strStateName)
		return new qPlayerTeleportState;
	if (L"qPlayerWaitState" == _strStateName)
		return new qPlayerWaitState;
	if (L"qPostCloseState" == _strStateName)
		return new qPostCloseState;
	if (L"qPostOpenState" == _strStateName)
		return new qPostOpenState;
	if (L"qSkeletonAttackState" == _strStateName)
		return new qSkeletonAttackState;
	if (L"qSkeletonDeathState" == _strStateName)
		return new qSkeletonDeathState;
	if (L"qSkeletonIdleState" == _strStateName)
		return new qSkeletonIdleState;
	if (L"qWarningState" == _strStateName)
		return new qWarningState;
	return nullptr;
}

qState * qStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::BOOKEFFECTSTATE:
		return new qBookEffectState;
		break;
	case (UINT)STATE_TYPE::BOSSBLEEDSTATE:
		return new qBossBleedState;
		break;
	case (UINT)STATE_TYPE::BOSSBLEEDWAVESTATE:
		return new qBossBleedWaveState;
		break;
	case (UINT)STATE_TYPE::BOSSDEATHSTATE:
		return new qBossDeathState;
		break;
	case (UINT)STATE_TYPE::BOSSHITSTATE:
		return new qBossHitState;
		break;
	case (UINT)STATE_TYPE::BOSSIDLESTATE:
		return new qBossIdleState;
		break;
	case (UINT)STATE_TYPE::BOSSINTROSTATE:
		return new qBossIntroState;
		break;
	case (UINT)STATE_TYPE::BOSSPUNCHSTATE:
		return new qBossPunchState;
		break;
	case (UINT)STATE_TYPE::BOSSRUNSTATE:
		return new qBossRunState;
		break;
	case (UINT)STATE_TYPE::BOSSSLAMFISTSTATE:
		return new qBossSlamFistState;
		break;
	case (UINT)STATE_TYPE::BOSSSLAMSTATE:
		return new qBossSlamState;
		break;
	case (UINT)STATE_TYPE::BOSSSTAYSTATE:
		return new qBossStayState;
		break;
	case (UINT)STATE_TYPE::BOSSUTURNSTATE:
		return new qBossUturnState;
		break;
	case (UINT)STATE_TYPE::CLAPSTATE:
		return new qClapState;
		break;
	case (UINT)STATE_TYPE::DEATHSOULSTATE:
		return new qDeathSoulState;
		break;
	case (UINT)STATE_TYPE::DOORCLOSESTATE:
		return new qDoorCloseState;
		break;
	case (UINT)STATE_TYPE::DOOROPENSTATE:
		return new qDoorOpenState;
		break;
	case (UINT)STATE_TYPE::DOORSTAYSTATE:
		return new qDoorStayState;
		break;
	case (UINT)STATE_TYPE::DROWNEDATTACKSTATE:
		return new qDrownedAttackState;
		break;
	case (UINT)STATE_TYPE::DROWNEDDEATHSTATE:
		return new qDrownedDeathState;
		break;
	case (UINT)STATE_TYPE::DROWNEDHITSTATE:
		return new qDrownedHitState;
		break;
	case (UINT)STATE_TYPE::DROWNEDIDLESTATE:
		return new qDrownedIdleState;
		break;
	case (UINT)STATE_TYPE::DROWNEDRUNSTATE:
		return new qDrownedRunState;
		break;
	case (UINT)STATE_TYPE::DROWNEDUTURNSTATE:
		return new qDrownedUturnState;
		break;
	case (UINT)STATE_TYPE::ELEVATORCLOSESTATE:
		return new qElevatorCloseState;
		break;
	case (UINT)STATE_TYPE::ELEVATOROPENSTATE:
		return new qElevatorOpenState;
		break;
	case (UINT)STATE_TYPE::ELEVATORSTAYSTATE:
		return new qElevatorStayState;
		break;
	case (UINT)STATE_TYPE::FIRESTATE:
		return new qFireState;
		break;
	case (UINT)STATE_TYPE::GHOSTATTACKSTATE:
		return new qGhostAttackState;
		break;
	case (UINT)STATE_TYPE::GHOSTDEATHSTATE:
		return new qGhostDeathState;
		break;
	case (UINT)STATE_TYPE::GHOSTHITSTATE:
		return new qGhostHitState;
		break;
	case (UINT)STATE_TYPE::GHOSTIDLESTATE:
		return new qGhostIdleState;
		break;
	case (UINT)STATE_TYPE::GHOSTRUNSTATE:
		return new qGhostRunState;
		break;
	case (UINT)STATE_TYPE::GHOSTUTURNSTATE:
		return new qGhostUturnState;
		break;
	case (UINT)STATE_TYPE::LOADING1STATE:
		return new qLoading1State;
		break;
	case (UINT)STATE_TYPE::LOADINGSTATE:
		return new qLoadingState;
		break;
	case (UINT)STATE_TYPE::LOGOSTATE:
		return new qLogoState;
		break;
	case (UINT)STATE_TYPE::PLAYERBOOKSHOOTSTATE:
		return new qPlayerBookShootState;
		break;
	case (UINT)STATE_TYPE::PLAYERBUMPSTATE:
		return new qPlayerBumpState;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO1STATE:
		return new qPlayerCombo1State;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO2STATE:
		return new qPlayerCombo2State;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO3STATE:
		return new qPlayerCombo3State;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO4STATE:
		return new qPlayerCombo4State;
		break;
	case (UINT)STATE_TYPE::PLAYERCRASHSTATE:
		return new qPlayerCrashState;
		break;
	case (UINT)STATE_TYPE::PLAYERDASHSTATE:
		return new qPlayerDashState;
		break;
	case (UINT)STATE_TYPE::PLAYEREFFECTSTATE:
		return new qPlayerEffectState;
		break;
	case (UINT)STATE_TYPE::PLAYERELEVATOROUTSTATE:
		return new qPlayerElevatorOutState;
		break;
	case (UINT)STATE_TYPE::PLAYERFALLINGSTATE:
		return new qPlayerFallingState;
		break;
	case (UINT)STATE_TYPE::PLAYERGETITEMSTATE:
		return new qPlayerGetItemState;
		break;
	case (UINT)STATE_TYPE::PLAYERIDLESTATE:
		return new qPlayerIdleState;
		break;
	case (UINT)STATE_TYPE::PLAYERIDLETORUNSTATE:
		return new qPlayerIdleToRunState;
		break;
	case (UINT)STATE_TYPE::PLAYERIDLEUTURNSTATE:
		return new qPlayerIdleUTurnState;
		break;
	case (UINT)STATE_TYPE::PLAYERJUMPSTATE:
		return new qPlayerJumpState;
		break;
	case (UINT)STATE_TYPE::PLAYERKRUSHSTATE:
		return new qPlayerKrushState;
		break;
	case (UINT)STATE_TYPE::PLAYERLANDINGSTATE:
		return new qPlayerLandingState;
		break;
	case (UINT)STATE_TYPE::PLAYERNULLSTATE:
		return new qPlayerNullState;
		break;
	case (UINT)STATE_TYPE::PLAYERRANGESTATE:
		return new qPlayerRangeState;
		break;
	case (UINT)STATE_TYPE::PLAYERRUNSTATE:
		return new qPlayerRunState;
		break;
	case (UINT)STATE_TYPE::PLAYERRUNTOIDLESTATE:
		return new qPlayerRunToIdleState;
		break;
	case (UINT)STATE_TYPE::PLAYERRUNUTURNSTATE:
		return new qPlayerRunUTurnState;
		break;
	case (UINT)STATE_TYPE::PLAYERTELEPORTFINISHSTATE:
		return new qPlayerTeleportFinishState;
		break;
	case (UINT)STATE_TYPE::PLAYERTELEPORTSTATE:
		return new qPlayerTeleportState;
		break;
	case (UINT)STATE_TYPE::PLAYERWAITSTATE:
		return new qPlayerWaitState;
		break;
	case (UINT)STATE_TYPE::POSTCLOSESTATE:
		return new qPostCloseState;
		break;
	case (UINT)STATE_TYPE::POSTOPENSTATE:
		return new qPostOpenState;
		break;
	case (UINT)STATE_TYPE::SKELETONATTACKSTATE:
		return new qSkeletonAttackState;
		break;
	case (UINT)STATE_TYPE::SKELETONDEATHSTATE:
		return new qSkeletonDeathState;
		break;
	case (UINT)STATE_TYPE::SKELETONIDLESTATE:
		return new qSkeletonIdleState;
		break;
	case (UINT)STATE_TYPE::WARNINGSTATE:
		return new qWarningState;
		break;
	}
	return nullptr;
}

const wchar_t * qStateMgr::GetStateName(qState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::BOOKEFFECTSTATE:
		return L"qBookEffectState";
		break;

	case STATE_TYPE::BOSSBLEEDSTATE:
		return L"qBossBleedState";
		break;

	case STATE_TYPE::BOSSBLEEDWAVESTATE:
		return L"qBossBleedWaveState";
		break;

	case STATE_TYPE::BOSSDEATHSTATE:
		return L"qBossDeathState";
		break;

	case STATE_TYPE::BOSSHITSTATE:
		return L"qBossHitState";
		break;

	case STATE_TYPE::BOSSIDLESTATE:
		return L"qBossIdleState";
		break;

	case STATE_TYPE::BOSSINTROSTATE:
		return L"qBossIntroState";
		break;

	case STATE_TYPE::BOSSPUNCHSTATE:
		return L"qBossPunchState";
		break;

	case STATE_TYPE::BOSSRUNSTATE:
		return L"qBossRunState";
		break;

	case STATE_TYPE::BOSSSLAMFISTSTATE:
		return L"qBossSlamFistState";
		break;

	case STATE_TYPE::BOSSSLAMSTATE:
		return L"qBossSlamState";
		break;

	case STATE_TYPE::BOSSSTAYSTATE:
		return L"qBossStayState";
		break;

	case STATE_TYPE::BOSSUTURNSTATE:
		return L"qBossUturnState";
		break;

	case STATE_TYPE::CLAPSTATE:
		return L"qClapState";
		break;

	case STATE_TYPE::DEATHSOULSTATE:
		return L"qDeathSoulState";
		break;

	case STATE_TYPE::DOORCLOSESTATE:
		return L"qDoorCloseState";
		break;

	case STATE_TYPE::DOOROPENSTATE:
		return L"qDoorOpenState";
		break;

	case STATE_TYPE::DOORSTAYSTATE:
		return L"qDoorStayState";
		break;

	case STATE_TYPE::DROWNEDATTACKSTATE:
		return L"qDrownedAttackState";
		break;

	case STATE_TYPE::DROWNEDDEATHSTATE:
		return L"qDrownedDeathState";
		break;

	case STATE_TYPE::DROWNEDHITSTATE:
		return L"qDrownedHitState";
		break;

	case STATE_TYPE::DROWNEDIDLESTATE:
		return L"qDrownedIdleState";
		break;

	case STATE_TYPE::DROWNEDRUNSTATE:
		return L"qDrownedRunState";
		break;

	case STATE_TYPE::DROWNEDUTURNSTATE:
		return L"qDrownedUturnState";
		break;

	case STATE_TYPE::ELEVATORCLOSESTATE:
		return L"qElevatorCloseState";
		break;

	case STATE_TYPE::ELEVATOROPENSTATE:
		return L"qElevatorOpenState";
		break;

	case STATE_TYPE::ELEVATORSTAYSTATE:
		return L"qElevatorStayState";
		break;

	case STATE_TYPE::FIRESTATE:
		return L"qFireState";
		break;

	case STATE_TYPE::GHOSTATTACKSTATE:
		return L"qGhostAttackState";
		break;

	case STATE_TYPE::GHOSTDEATHSTATE:
		return L"qGhostDeathState";
		break;

	case STATE_TYPE::GHOSTHITSTATE:
		return L"qGhostHitState";
		break;

	case STATE_TYPE::GHOSTIDLESTATE:
		return L"qGhostIdleState";
		break;

	case STATE_TYPE::GHOSTRUNSTATE:
		return L"qGhostRunState";
		break;

	case STATE_TYPE::GHOSTUTURNSTATE:
		return L"qGhostUturnState";
		break;

	case STATE_TYPE::LOADING1STATE:
		return L"qLoading1State";
		break;

	case STATE_TYPE::LOADINGSTATE:
		return L"qLoadingState";
		break;

	case STATE_TYPE::LOGOSTATE:
		return L"qLogoState";
		break;

	case STATE_TYPE::PLAYERBOOKSHOOTSTATE:
		return L"qPlayerBookShootState";
		break;

	case STATE_TYPE::PLAYERBUMPSTATE:
		return L"qPlayerBumpState";
		break;

	case STATE_TYPE::PLAYERCOMBO1STATE:
		return L"qPlayerCombo1State";
		break;

	case STATE_TYPE::PLAYERCOMBO2STATE:
		return L"qPlayerCombo2State";
		break;

	case STATE_TYPE::PLAYERCOMBO3STATE:
		return L"qPlayerCombo3State";
		break;

	case STATE_TYPE::PLAYERCOMBO4STATE:
		return L"qPlayerCombo4State";
		break;

	case STATE_TYPE::PLAYERCRASHSTATE:
		return L"qPlayerCrashState";
		break;

	case STATE_TYPE::PLAYERDASHSTATE:
		return L"qPlayerDashState";
		break;

	case STATE_TYPE::PLAYEREFFECTSTATE:
		return L"qPlayerEffectState";
		break;

	case STATE_TYPE::PLAYERELEVATOROUTSTATE:
		return L"qPlayerElevatorOutState";
		break;

	case STATE_TYPE::PLAYERFALLINGSTATE:
		return L"qPlayerFallingState";
		break;

	case STATE_TYPE::PLAYERGETITEMSTATE:
		return L"qPlayerGetItemState";
		break;

	case STATE_TYPE::PLAYERIDLESTATE:
		return L"qPlayerIdleState";
		break;

	case STATE_TYPE::PLAYERIDLETORUNSTATE:
		return L"qPlayerIdleToRunState";
		break;

	case STATE_TYPE::PLAYERIDLEUTURNSTATE:
		return L"qPlayerIdleUTurnState";
		break;

	case STATE_TYPE::PLAYERJUMPSTATE:
		return L"qPlayerJumpState";
		break;

	case STATE_TYPE::PLAYERKRUSHSTATE:
		return L"qPlayerKrushState";
		break;

	case STATE_TYPE::PLAYERLANDINGSTATE:
		return L"qPlayerLandingState";
		break;

	case STATE_TYPE::PLAYERNULLSTATE:
		return L"qPlayerNullState";
		break;

	case STATE_TYPE::PLAYERRANGESTATE:
		return L"qPlayerRangeState";
		break;

	case STATE_TYPE::PLAYERRUNSTATE:
		return L"qPlayerRunState";
		break;

	case STATE_TYPE::PLAYERRUNTOIDLESTATE:
		return L"qPlayerRunToIdleState";
		break;

	case STATE_TYPE::PLAYERRUNUTURNSTATE:
		return L"qPlayerRunUTurnState";
		break;

	case STATE_TYPE::PLAYERTELEPORTFINISHSTATE:
		return L"qPlayerTeleportFinishState";
		break;

	case STATE_TYPE::PLAYERTELEPORTSTATE:
		return L"qPlayerTeleportState";
		break;

	case STATE_TYPE::PLAYERWAITSTATE:
		return L"qPlayerWaitState";
		break;

	case STATE_TYPE::POSTCLOSESTATE:
		return L"qPostCloseState";
		break;

	case STATE_TYPE::POSTOPENSTATE:
		return L"qPostOpenState";
		break;

	case STATE_TYPE::SKELETONATTACKSTATE:
		return L"qSkeletonAttackState";
		break;

	case STATE_TYPE::SKELETONDEATHSTATE:
		return L"qSkeletonDeathState";
		break;

	case STATE_TYPE::SKELETONIDLESTATE:
		return L"qSkeletonIdleState";
		break;

	case STATE_TYPE::WARNINGSTATE:
		return L"qWarningState";
		break;

	}
	return nullptr;
}