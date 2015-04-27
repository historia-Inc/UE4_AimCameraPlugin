#pragma once

#include "AimCameraTickInEditorComponent.generated.h"


UCLASS()
class UAimCameraTickInEditorComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	// UActorComponent interface 
#if WITH_EDITOR
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#endif
};
