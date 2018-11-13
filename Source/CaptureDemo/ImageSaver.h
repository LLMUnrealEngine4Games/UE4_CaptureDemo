#pragma once

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "EyesController.h"
#include "ImageSaver.generated.h"



UCLASS()
class CAPTUREDEMO_API UImageSaver : public UObject
{
	GENERATED_BODY()

public:

	static TFuture<void> SaveImageAsync(FCustomFrameData data, IImageWrapperPtr ImageWrapper);

	static void SaveImage(FCustomFrameData data, IImageWrapperPtr ImageWrapper);

};