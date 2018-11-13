// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "EyesController.h"
#include "CapturePawn.generated.h"



UCLASS()
class CAPTUREDEMO_API ACapturePawn : public APawn
{
	GENERATED_BODY()

protected:
	float scale = 1.01;
	int32 HFOV = 90;
	int32 VFOV = 90;
	int32 HNum = 4;

	TArray<FCustomCaptureData> CaptureData;
	TArray<TSharedRef<FCustomCaptureMap>> CaptureMap;
	int32 OSize;
	int32 FullSize; // size = FullSize * (0.5 FullSize)
	USceneComponent* RootCom;
public:


	void InitCaptureComponent();
	void InitSize(int32 _FullSize);
	void BuildCapureMap();
	void GetImage(TArray<FColor>& RawData);
	void SetEyes(FCustomEyesData& EyesData);
};
