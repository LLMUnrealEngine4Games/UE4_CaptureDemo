// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptureDemo.h"
#include "CapturePawn.h"





void ACapturePawn::InitCaptureComponent()
{
	FVector Location(0, 0, 0);
	const FName RootName = MakeUniqueObjectName(this, USceneComponent::StaticClass(), TEXT("RootCom"));
	RootCom = NewObject<USceneComponent>(this, RootName);
	RootCom->RegisterComponentWithWorld(GWorld);

	for (size_t i = 0; i < HNum; i++)
	{
		const FName Name = MakeUniqueObjectName(this, USceneCaptureComponent2D::StaticClass(), TEXT("SceneCapture"));

		USceneCaptureComponent2D* CaptureComponent = NewObject<USceneCaptureComponent2D>(this, Name);

		CaptureComponent->SetWorldLocation(Location);
		CaptureComponent->SetVisibility(true);
		CaptureComponent->SetHiddenInGame(false);
		CaptureComponent->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
		CaptureComponent->FOVAngle = 90 * scale;
		CaptureComponent->bCaptureEveryFrame = false;
		if (GetWorld())
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController && PlayerController->PlayerCameraManager)
			{
				CaptureComponent->PostProcessSettings = PlayerController->PlayerCameraManager->CameraCache.POV.PostProcessSettings;
				CaptureComponent->PostProcessBlendWeight = PlayerController->PlayerCameraManager->CameraCache.POV.PostProcessBlendWeight;
			}
		}
		CaptureComponent->PostProcessSettings.bOverride_GrainIntensity = true;
		CaptureComponent->PostProcessSettings.GrainIntensity = 0.0f;
		CaptureComponent->PostProcessSettings.bOverride_MotionBlurAmount = true;
		CaptureComponent->PostProcessSettings.MotionBlurAmount = 0.0f;
		CaptureComponent->PostProcessSettings.bOverride_ScreenSpaceReflectionIntensity = true;
		CaptureComponent->PostProcessSettings.ScreenSpaceReflectionIntensity = 0.0f;
		CaptureComponent->PostProcessSettings.bOverride_VignetteIntensity = true;
		CaptureComponent->PostProcessSettings.VignetteIntensity = 0.0f;


		const FName TargetName = MakeUniqueObjectName(this, UTextureRenderTarget2D::StaticClass(), TEXT("SceneCaptureTextureTarget"));
		CaptureComponent->TextureTarget = NewObject<UTextureRenderTarget2D>(this, TargetName);
		CaptureComponent->TextureTarget->bHDR = false;
		CaptureComponent->TextureTarget->InitCustomFormat(1,1, PF_B8G8R8A8, false);
		CaptureComponent->TextureTarget->ClearColor = FLinearColor::Red;
		CaptureComponent->Activate(false);
		CaptureComponent->RegisterComponentWithWorld(GWorld);

		float angle = i * HFOV + 180.0f;
		FCustomCaptureData CData;
		CData.Capture = CaptureComponent;
		CData.FowardVector = FVector(FMath::Cos(angle), FMath::Sin(angle), 0);
		CData.UpVector = FVector(0, 0, 1);
		CData.T.SetLocation(FVector(FMath::Cos(angle / 180.0f * PI), FMath::Sin(angle / 180.0f * PI), 0));
		CData.T.SetRotation(FQuat(FRotator(0, angle, 0)));
		CData.fu = 1;
		CData.fv = 1;

		CaptureData.Add(CData);

		CaptureComponent->AttachToComponent(RootCom, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		CaptureComponent->SetRelativeRotation(FQuat(FRotator(0, angle, 0)));

	}

	for (size_t i = 0; i < 2; i++)
	{
		const FName Name = MakeUniqueObjectName(this, USceneCaptureComponent2D::StaticClass(), TEXT("SceneCapture"));

		USceneCaptureComponent2D* CaptureComponent = NewObject<USceneCaptureComponent2D>(this, Name);

		CaptureComponent->SetWorldLocation(Location);
		CaptureComponent->SetVisibility(true);
		CaptureComponent->SetHiddenInGame(false);
		CaptureComponent->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
		CaptureComponent->FOVAngle = 90 * scale;

		CaptureComponent->bCaptureEveryFrame = false;
		if (GetWorld())
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController && PlayerController->PlayerCameraManager)
			{
				CaptureComponent->PostProcessSettings = PlayerController->PlayerCameraManager->CameraCache.POV.PostProcessSettings;
				CaptureComponent->PostProcessBlendWeight = PlayerController->PlayerCameraManager->CameraCache.POV.PostProcessBlendWeight;
			}
		}
		CaptureComponent->PostProcessSettings.bOverride_GrainIntensity = true;
		CaptureComponent->PostProcessSettings.GrainIntensity = 0.0f;
		CaptureComponent->PostProcessSettings.bOverride_MotionBlurAmount = true;
		CaptureComponent->PostProcessSettings.MotionBlurAmount = 0.0f;
		CaptureComponent->PostProcessSettings.bOverride_ScreenSpaceReflectionIntensity = true;
		CaptureComponent->PostProcessSettings.ScreenSpaceReflectionIntensity = 0.0f;
		CaptureComponent->PostProcessSettings.bOverride_VignetteIntensity = true;
		CaptureComponent->PostProcessSettings.VignetteIntensity = 0.0f;


		const FName TargetName = MakeUniqueObjectName(this, UTextureRenderTarget2D::StaticClass(), TEXT("SceneCaptureTextureTarget"));
		CaptureComponent->TextureTarget = NewObject<UTextureRenderTarget2D>(this, TargetName);
		CaptureComponent->TextureTarget->bHDR = false;
		CaptureComponent->TextureTarget->InitCustomFormat(1,1, PF_B8G8R8A8, false);
		CaptureComponent->TextureTarget->ClearColor = FLinearColor::Red;
		CaptureComponent->Activate(false);
		CaptureComponent->RegisterComponentWithWorld(GWorld);

		FCustomCaptureData CData;
		CaptureComponent->AttachToComponent(RootCom, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		switch (i)
		{
		case 0:CaptureComponent->SetRelativeRotation(FQuat(FRotator(90, 0, 0))); //top
			CData.Capture = CaptureComponent;
			CData.FowardVector = FVector(0, 0, 1);
			CData.UpVector = FVector(-1, 0, 0);
			CData.T.SetLocation(FVector(0, 0, 1));
			CData.T.SetRotation(FQuat(FRotator(90, 0, 0)));
			CData.fu = 1;
			CData.fv = 1;
			CaptureData.Add(CData);
			break;
		case 1:CaptureComponent->SetRelativeRotation(FQuat(FRotator(270, 0, 0))); //down
			CData.Capture = CaptureComponent;
			CData.FowardVector = FVector(0, 0, -1);
			CData.UpVector = FVector(1, 0, 0);
			CData.T.SetLocation(FVector(0, 0, -1));
			CData.T.SetRotation(FQuat(FRotator(270, 0, 0)));
			CData.fu = 1;
			CData.fv = 1;
			CaptureData.Add(CData);
			break;

		default:
			break;
		}
	}
}

void ACapturePawn::InitSize(int32 _FullSize)
{
	FullSize = _FullSize;
	OSize = FullSize / 2 * scale;
	for (size_t i = 0; i < 6; i++)
	{
		CaptureData[i].Capture->TextureTarget->InitCustomFormat(OSize, OSize, PF_B8G8R8A8, false);
		CaptureData[i].SizeX = OSize;
		CaptureData[i].SizeY = OSize;
	}
}

bool GetPlaneLineIntersectPoint(const FVector planeVector, const FVector planePoint, const FVector lineVector, const FVector linePoint, FVector & ResultPoint)
{
	float t, vpt;
	vpt = lineVector.X * planeVector.X + lineVector.Y * planeVector.Y + lineVector.Z * planeVector.Z;
	//首先判断直线是否与平面平行  
	if (vpt == 0)
	{
		return false;
	}
	else
	{
		t = ((planePoint.X - linePoint.X) * planeVector.X + (planePoint.Y - linePoint.Y) * planeVector.Y + (planePoint.Z - linePoint.Z) * planeVector.Z) / vpt;
		ResultPoint.X = linePoint.X + lineVector.X * t;
		ResultPoint.Y = linePoint.Y + lineVector.Y * t;
		ResultPoint.Z = linePoint.Z + lineVector.Z * t;
		return true;
	}
	return false;
}

void ACapturePawn::BuildCapureMap()
{
	CaptureMap.Empty();
	int32 length = CaptureData.Num();
	for (size_t i = 0; i < FullSize / 2; i++)
	{
		for (size_t j = 0; j < FullSize; j++)
		{

			float lat = (0.5 - ((float(i) / float(FullSize / 2)))) * PI;
			float lon = (0.5 - (float(j) / float(FullSize))) * PI * 2;
			float x = FMath::Cos(lat)* FMath::Cos(lon);
			float y = FMath::Cos(lat)* FMath::Sin(lon);
			float z = FMath::Sin(lat);

			FVector Line(y, x, z);

			FVector NearestPoint;
			int32 NearestFace = -1;
			float NearestDistance = 9999;
			for (size_t k = 0; k < length; k++)
			{
				FVector CachePoint;
				float CacheDistance = 999;
				float cosangle = FVector::DotProduct(CaptureData[k].T.GetLocation(), Line);
				if (cosangle>0 && GetPlaneLineIntersectPoint(CaptureData[k].T.GetLocation(), CaptureData[k].T.GetLocation(), Line, FVector::ZeroVector, CachePoint))
				{
					if (CachePoint.Size() < NearestDistance)
					{
						NearestDistance = CachePoint.Size();
						NearestFace = k;
						NearestPoint = CachePoint;
					}
				}
			}

			FVector UVlocation = CaptureData[NearestFace].T.InverseTransformPosition(NearestPoint);
			float u = 0.5 + (UVlocation.Y / 2 / CaptureData[NearestFace].fu) / 1.0165;
			float v = 0.5 - (UVlocation.Z / 2) / 1.0165;

			int32 location_x = FMath::Clamp(int32(u * CaptureData[NearestFace].SizeX), 0, CaptureData[NearestFace].SizeX - 1);
			int32 location_y = FMath::Clamp(int32(v * CaptureData[NearestFace].SizeY), 0, CaptureData[NearestFace].SizeY - 1);

			TSharedRef<FCustomCaptureMap> m(new FCustomCaptureMap());
			m->FullIndex = i*FullSize + j;
			m->face = NearestFace;
			m->FaceIndex = location_x + location_y* CaptureData[NearestFace].SizeX;

			CaptureMap.Add(m);
		}
	}
}

void ACapturePawn::GetImage(TArray<FColor>& RawData)
{
	TArray<TArray<FColor>> TRawData;
	TRawData.SetNum(6);
	FIntRect InRect = FIntRect(0, 0, OSize, OSize);
	struct FReadSurfaceContext
	{
		FRenderTarget* SrcRenderTarget;
		TArray<FColor>* OutData;
		FIntRect Rect;
		FReadSurfaceDataFlags Flags;
	};
	TArray<FReadSurfaceContext> ReadSurfaceContext;
	for (size_t i = 0; i < 6; i++)
	{
		TRawData[i].Reset();
		FReadSurfaceContext SReadSurfaceContext =
		{
			CaptureData[i].Capture->TextureTarget->GameThread_GetRenderTargetResource(),
			&TRawData[i],
			InRect,
			RCM_UNorm
		};
		ReadSurfaceContext.Add(SReadSurfaceContext);
	}
	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		ReadSurfaceCommand,
		TArray<FReadSurfaceContext>, Context, ReadSurfaceContext,
		{
			for (size_t i = 0; i < 6; i++)
			{
				RHICmdList.ReadSurfaceData(
					Context[i].SrcRenderTarget->GetRenderTargetTexture(),
					Context[i].Rect,
					*Context[i].OutData,
					Context[i].Flags
				);
			}

		});
	FlushRenderingCommands();

	RawData.SetNum(FullSize*FullSize / 2);
	for (auto p : CaptureMap)
	{
		FColor RawColor;
		RawColor.R = TRawData[p->face][p->FaceIndex].R;
		RawColor.G = TRawData[p->face][p->FaceIndex].G;
		RawColor.B = TRawData[p->face][p->FaceIndex].B;
		RawColor.A = 255;
		RawData[p->FullIndex] = RawColor;
	}
}

void ACapturePawn::SetEyes(FCustomEyesData& EyesData)
{
	RootCom->SetWorldLocation(EyesData.Position);
	RootCom->SetWorldRotation(EyesData.Rotation);
	for (size_t i = 0; i < 6; i++)
	{
		CaptureData[i].Capture->TextureTarget->TargetGamma = EyesData.Gamma;
		CaptureData[i].Capture->UpdateContent();
	}
}
