#include "Application Manager/ApplicationManager.h"
#include<Windows.h>
#include<windot11.h>
#include<mmsystem.h>
#include<string>
int main(void)
{
	std::unique_ptr<ApplicationManager> appManager (new ApplicationManager());
			PlaySound(TEXT("airplanes.wav"),NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
	if(appManager->InitalizeApplication(1080,1024) == true)
	{

		appManager->StartMainLoop();
		appManager->CloseApplication();
	}
}


