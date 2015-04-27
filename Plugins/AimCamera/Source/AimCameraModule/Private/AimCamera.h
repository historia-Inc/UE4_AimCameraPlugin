#pragma once

#if WITH_EDITOR
#include "Editor/UnrealEdTypes.h"
#endif

#include "AimCamera.generated.h"


UCLASS(ClassGroup=AimCamera)
class AAimCamera : public ACameraActor
{
	GENERATED_UCLASS_BODY()

public:
	// AActor interface 
	virtual void Tick(float DeltaSeconds) override;	
	virtual void Destroyed() override;
#if WITH_EDITOR
	virtual void EditorApplyTranslation(const FVector& DeltaTranslation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	virtual void EditorApplyRotation(const FRotator & DeltaRotation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
#endif


#if WITH_EDITOR
	void OnViewportCameraMoved(const FVector&, const FRotator&, ELevelViewportType, int32);
#endif

	void UpdateCameraTransform();

public:
	UPROPERTY(EditAnywhere, Category=AimCamera, BlueprintReadWrite)
	AActor* AimTargetActor;

	UPROPERTY(EditAnywhere, Category=AimCamera, BlueprintReadWrite)
	FName AimTargetSocketName;

	UPROPERTY(EditAnywhere, Category=AimCamera, BlueprintReadWrite)
	AActor* UpTargetActor;

	UPROPERTY(EditAnywhere, Category=AimCamera, BlueprintReadWrite)
	FName UpTargetSocketName;

private:
#if WITH_EDITOR
	FDelegateHandle ViewportCameraMovedHandle;
#endif
};
