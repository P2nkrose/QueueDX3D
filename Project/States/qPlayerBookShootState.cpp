#include "pch.h"
#include "qPlayerBookShootState.h"

#include <Scripts/qPlayerScript.h>

qPlayerBookShootState::qPlayerBookShootState()
	: qState((UINT)STATE_TYPE::PLAYERBOOKSHOOTSTATE)
{
}

qPlayerBookShootState::~qPlayerBookShootState()
{
}

void qPlayerBookShootState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(17, 15, false);


}

void qPlayerBookShootState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}



}

void qPlayerBookShootState::Exit()
{

}
