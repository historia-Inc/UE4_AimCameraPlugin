#include "AimCameraPrivatePCH.h"
#include "AimCamera.h"

#if WITH_EDITOR
#include "Editor.h"
#include "LevelEditorViewport.h"
#endif

#include "AimCameraTickInEditorComponent.h"


namespace
{
	FVector GetAimTargetLocation(AActor* TargetActor, FName SocketName)
	{
		if((NULL == TargetActor->GetRootComponent()) || SocketName.IsNone())
		{
			return TargetActor->GetActorLocation();
		}

		if(TargetActor->GetRootComponent()->DoesSocketExist(SocketName))
		{
			return TargetActor->GetRootComponent()->GetSocketTransform(SocketName, RTS_World).GetTranslation();
		}

		USkinnedMeshComponent* SkinnedMesh = Cast<USkinnedMeshComponent>(TargetActor->GetRootComponent());
		if(SkinnedMesh)
		{
			int32 BoneIndex = SkinnedMesh->GetBoneIndex(SocketName);
			if(INDEX_NONE != BoneIndex)
			{
				return SkinnedMesh->GetBoneTransform(BoneIndex).GetTranslation();
			}
		}

		return TargetActor->GetActorLocation();
	}
}

AAimCamera::AAimCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	ObjectInitializer.CreateDefaultSubobject<UAimCameraTickInEditorComponent>(RootComponent, TEXT("InEditorTicker"));

#if WITH_EDITOR
	ViewportCameraMovedHandle = FEditorDelegates::OnEditorCameraMoved.AddUObject(this, &AAimCamera::OnViewportCameraMoved);
#endif
}
void AAimCamera::Destroyed()
{
#if WITH_EDITOR
	FEditorDelegates::OnEditorCameraMoved.Remove(ViewportCameraMovedHandle);
#endif
	Super::Destroyed();
}


#if WITH_EDITOR
void AAimCamera::EditorApplyTranslation(const FVector& DeltaTranslation, bool bAltDown, bool bShiftDown, bool bCtrlDown)
{
	Super::EditorApplyTranslation(DeltaTranslation, bAltDown, bShiftDown, bCtrlDown);
	UpdateCameraTransform();
}
void AAimCamera::EditorApplyRotation(const FRotator & DeltaRotation, bool bAltDown, bool bShiftDown, bool bCtrlDown)
{
	Super::EditorApplyRotation(DeltaRotation, bAltDown, bShiftDown, bCtrlDown);
	UpdateCameraTransform();
}
void AAimCamera::OnViewportCameraMoved(const FVector&, const FRotator&, ELevelViewportType, int32)
{
	for(int32 i = 0; i < GEditor->LevelViewportClients.Num(); ++i)
	{
		if(GEditor->LevelViewportClients[i])
		{
			if(CameraComponent == GEditor->LevelViewportClients[i]->GetCameraComponentForView())
			{
				UpdateCameraTransform();
				break;
			}
		}
	}
}
#endif


void AAimCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCameraTransform();
}


void AAimCamera::UpdateCameraTransform()
{
	if(AimTargetActor)
	{
		if(UpTargetActor)
		{
			SetActorRotation(FRotationMatrix::MakeFromXZ(
				(GetAimTargetLocation(AimTargetActor, AimTargetSocketName) - GetActorLocation()),
				(GetAimTargetLocation(UpTargetActor,  UpTargetSocketName)  - GetActorLocation())
				).Rotator()
				);
		}
		else
		{
			SetActorRotation((GetAimTargetLocation(AimTargetActor, AimTargetSocketName) - GetActorLocation()).Rotation());
		}
	}
}
