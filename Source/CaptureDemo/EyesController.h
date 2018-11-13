// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "EyesController.generated.h"

UENUM(BlueprintType)
enum class EMyImageFormat : uint8
{
	JPG UMETA(DisplayName = "JPG"),
	PNG UMETA(DisplayName = "PNG"),
	BMP UMETA(DisplayName = "BMP"),
};
struct FCustomCaptureData
{
	USceneCaptureComponent2D* Capture;
	FTransform T;
	FVector FowardVector;
	FVector UpVector;
	int32 SizeX;
	int32 SizeY;
	float fu;
	float fv;
};

struct FCustomCaptureMap
{
	int32 FullIndex;
	int32 face;
	int32 FaceIndex;
};

struct FCustomFrameData
{
	TArray<FColor> ColorBuffer;
	FIntPoint BufferSize;
	FString SaveName;
	int32 CompressionQuality;
	EMyImageFormat Format;
};


USTRUCT(BlueprintType)
struct FCustomEyesData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EyesData)
		FVector Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EyesData)
		FRotator Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EyesData)
		float Gamma = 1.0;

};



UCLASS()
class CAPTUREDEMO_API AEyesController : public AActor
{
	GENERATED_BODY()

public:
	AEyesController();

	class ACapturePawn* eyes;

	int32 FullSize;
	TArray<FCustomEyesData> Tdata;

	bool beyes = false;
	bool bimage = false;
	int32 eyesindex = 0;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Capture")
	void CaptureImage(const TArray<FCustomEyesData>& _Tdata,const int32 _FullSize);

	void GetImage(int32 index);
	void SetEyes(FCustomEyesData& EyesData);
};

