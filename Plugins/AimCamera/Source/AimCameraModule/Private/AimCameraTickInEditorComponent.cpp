#include "AimCameraPrivatePCH.h"
#include "AimCameraTickInEditorComponent.h"

#include "AimCamera.h"


UAimCameraTickInEditorComponent::UAimCameraTickInEditorComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
	bTickInEditor = true;
	bAutoActivate = true;
#else
	PrimaryComponentTick.bCanEverTick = false;
#endif
}

#if WITH_EDITOR
void UAimCameraTickInEditorComponent::TickComponent(float DeltaTime, enum ELevelTick /*TickType*/, FActorComponentTickFunction* /*ThisTickFunction*/)
{
	AAimCamera* OwnerCamera = Cast<AAimCamera>(GetOwner());
	if(OwnerCamera)
	{
		OwnerCamera->UpdateCameraTransform();
	}
}
#endif