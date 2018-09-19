#include "RenderableComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TransformComponent.h"

//-----------------------------------------------------------

CRenderableComponent::CRenderableComponent()
	: CComponent(this, sizeof(CRenderableComponent))
{
}

//-----------------------------------------------------------

void CRenderableComponent::OnCreated(void * aInParams)
{
	SRenderableComponentParam inParam = CastToCustomInParams<SRenderableComponentParam>(aInParams);

	myRendererToUse = inParam.myRenderer;
	mySprite.setTexture(*inParam.myTexture);
}

//-----------------------------------------------------------

void CRenderableComponent::Tick(float aDT)
{
	CGameObject& owner = GetOwner();

	CTransformComponent* transformComponent = GetComponentOfType(GetOwner(), CTransformComponent);

	mySprite.setPosition(transformComponent->GetPosition());

	myRendererToUse->PushRenderCommand(mySprite);
}

//-----------------------------------------------------------

void CRenderableComponent::OnDestroy()
{
}

//-----------------------------------------------------------

ComponentType CRenderableComponent::GetType() const
{
	return typeid(CRenderableComponent);
}

//-----------------------------------------------------------