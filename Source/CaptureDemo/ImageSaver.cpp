
#include "CaptureDemo.h"
#include "ImageSaver.h"


TFuture<void> UImageSaver::SaveImageAsync(FCustomFrameData data, IImageWrapperPtr ImageWrapper)
{
	return	Async<void>(EAsyncExecution::ThreadPool, [=]() { return SaveImage(data, ImageWrapper); });

}

void UImageSaver::SaveImage(FCustomFrameData data, IImageWrapperPtr ImageWrapper)
{

	const float Width = data.BufferSize.X;
	const float Height = data.BufferSize.Y;
	FString SavePath;
	switch (data.Format)
	{
	case EMyImageFormat::BMP:
		SavePath = FPaths::GameContentDir() + "Pano/" + data.SaveName + ".BMP";
		FFileHelper::CreateBitmap(*SavePath, Width, Height, data.ColorBuffer.GetData());
		break;
	case EMyImageFormat::PNG:
		for (FColor& Color : data.ColorBuffer)
		{
			Color.A = 255;
		}

		if (ImageWrapper->SetRaw(data.ColorBuffer.GetData(), data.ColorBuffer.Num() * sizeof(FColor), Width, Height, ERGBFormat::BGRA, 8))
		{
			SavePath = FPaths::GameContentDir() + "Pano/" + data.SaveName + ".PNG";
			FFileHelper::SaveArrayToFile(ImageWrapper->GetCompressed(data.CompressionQuality), *SavePath);
		}
		break;

	case EMyImageFormat::JPG:
		if (ImageWrapper->SetRaw(data.ColorBuffer.GetData(), data.ColorBuffer.Num() * sizeof(FColor), Width, Height, ERGBFormat::BGRA, 8))
		{
			SavePath = FPaths::GameContentDir() + "Pano/" + data.SaveName + ".JPG";
			FFileHelper::SaveArrayToFile(ImageWrapper->GetCompressed(data.CompressionQuality), *SavePath);
		}
		break;
	}
}

