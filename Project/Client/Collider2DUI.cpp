#include "pch.h"
#include "Collider2DUI.h"

#include <Engine/qGameObject.h>
#include <Engine/qCollider2D.h>


Collider2DUI::Collider2DUI()
	: ComponentUI(COMPONENT_TYPE::COLLIDER2D)
{
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::Update()
{
	Title();

	qCollider2D* pCol = GetTargetObject()->Collider2D();
	Vec3 vScale = pCol->GetScale();
	Vec3 vOffset = pCol->GetOffset();

	// Offset Scale
	ImGui::Text("Collider2D Scale");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Collider2D Scale", vScale);

	// Offset Pos
	ImGui::Text("Collider2D Offset");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Collider2D Offset", vOffset);

	// Independent Scale CheckBox
	bool IS = pCol->IsIndependentScale();

	ImGui::Text("Ignore Parent");
	ImGui::SameLine(100);
	if (ImGui::Checkbox("##TransIS", &IS))
	{
		pCol->SetIndependentScale(IS);
	}

	pCol->SetScale(vScale);
	pCol->SetOffset(vOffset);

}
