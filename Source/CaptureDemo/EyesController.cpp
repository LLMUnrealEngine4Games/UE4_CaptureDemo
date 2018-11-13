
#include "CaptureDemo.h"
#include "EyesController.h"
#include "CapturePawn.h"
#include "ImageSaver.h"
#include "Interfaces/IImageWrapperModule.h"

AEyesController::AEyesController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEyesController::BeginPlay()
{
	Super::BeginPlay();
	eyes = GetWorld()->SpawnActor<ACapturePawn>();
	eyes->InitCaptureComponent();
}

void AEyesController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bimage)
	{
		GetImage(eyesindex - 1);
		bimage = false;
		if (eyesindex >= Tdata.Num())
		{
			eyes->Destroy();
			GetWorld()->ForceGarbageCollection(true);
		}
	}
	if (beyes)
	{
		if (eyesindex < Tdata.Num())
		{
			SetEyes(Tdata[eyesindex]);
			bimage = true;
			eyesindex++;
		}
		else
		{
			beyes = false;
		}
	}
}

void AEyesController::CaptureImage(const TArray<FCustomEyesData>& _Tdata, const int32 _FullSize)
{
	Tdata = _Tdata;
	beyes = true;
	FullSize = _FullSize;
	eyesindex = 0;
	eyes->InitSize(FullSize);
	eyes->BuildCapureMap();
}

static IImageWrapperPtr GetImageExtention(EMyImageFormat ImageFormat)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	if (ImageFormat == EMyImageFormat::JPG) return ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	if (ImageFormat == EMyImageFormat::PNG) return ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	if (ImageFormat == EMyImageFormat::BMP) return nullptr;
	return ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
}

void AEyesController::GetImage(int32 index)
{
	TArray<FColor> RawData;
	eyes->GetImage(RawData);



	IImageWrapperPtr ImageWrapper = GetImageExtention(EMyImageFormat::JPG);

	FCustomFrameData Data;
	Data.ColorBuffer.Append(RawData);
	Data.Format = EMyImageFormat::JPG;
	Data.BufferSize = FIntPoint(FullSize, FullSize/2);
	Data.CompressionQuality = 90;
	Data.SaveName = FString::FromInt(index);

	UImageSaver* saver = NewObject<UImageSaver>();
	saver->SaveImageAsync(Data, ImageWrapper);
	
}

void AEyesController::SetEyes(FCustomEyesData & data)
{
	eyes->SetEyes(data);
}




