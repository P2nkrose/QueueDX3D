#pragma once


#define SINGLE(Type) private:\
						Type();\
						~Type();\
						friend class qSingleton<Type>;

#define DEVICE qDevice::GetInst()->GetDevice()
#define CONTEXT qDevice::GetInst()->GetContext()
#define MAX_LAYER 32

#define DT qTimeMgr::GetInst()->GetDeltaTime()
#define EngineDT qTimeMgr::GetInst()->GetEngineDeltaTime()

#define KEY_CHECK(KEY, STATE) qKeyMgr::GetInst()->GetKeyState(KEY) == STATE
#define KEY_TAP(KEY) qKeyMgr::GetInst()->GetKeyState(KEY) == KEY_STATE::TAP
#define KEY_PRESSED(KEY) qKeyMgr::GetInst()->GetKeyState(KEY) == KEY_STATE::PRESSED
#define KEY_RELEASED(KEY) qKeyMgr::GetInst()->GetKeyState(KEY) == KEY_STATE::RELEASED

#define CLONE(Type) virtual Type* Clone() { return new Type(*this); }
#define CLONE_DISABLE(Type) virtual Type* Clone() { return nullptr; }

#define DELETE(p) if(nullptr != p) delete p; p = nullptr;


typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;