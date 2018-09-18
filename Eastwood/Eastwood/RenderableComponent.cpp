#include "RenderableComponent.h"
#include "GameObject.h"
#include "Renderer.h"

CRenderableComponent::CRenderableComponent()
	: CComponent(this, sizeof(CRenderableComponent))
{
}

void CRenderableComponent::OnCreated(void * aInParams)
{
	SRenderableComponentParam inParam = CastToCustomInParams<SRenderableComponentParam>(aInParams);

	myRendererToUse = inParam.myRenderer;
	mySprite.setTexture(*inParam.myTexture);
}

void CRenderableComponent::Tick(float aDT)
{
	CGameObject& owner = GetOwner();

	mySprite.setPosition(owner.GetPosition());

	myRendererToUse->PushRenderCommand(mySprite);
}
