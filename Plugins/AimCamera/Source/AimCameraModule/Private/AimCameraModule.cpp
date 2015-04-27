#include "AimCameraPrivatePCH.h"
#include "AimCameraModule.h"

DEFINE_LOG_CATEGORY(LogAimCamera);


class FAimCameraModule : public IAimCameraModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FAimCameraModule, AimCameraModule)



void FAimCameraModule::StartupModule()
{
}


void FAimCameraModule::ShutdownModule()
{
}



