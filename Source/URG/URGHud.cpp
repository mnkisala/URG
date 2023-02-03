// Copyright Epic Games, Inc. All Rights Reserved.

#include "URGHud.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"
#include "URGPawn.h"

// Needed for VR Headset
#include "Engine.h"

#define LOCTEXT_NAMESPACE "VehicleHUD"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

AURGHud::AURGHud() {
  static ConstructorHelpers::FObjectFinder<UFont> Font(
      TEXT("/Engine/EngineFonts/RobotoDistanceField"));
  HUDFont = Font.Object;
}

void AURGHud::DrawHUD() {
  Super::DrawHUD();

  // Calculate ratio from 720p
  const float HUDXRatio = Canvas->SizeX / 1280.f;
  const float HUDYRatio = Canvas->SizeY / 720.f;

  bool bHMDDeviceActive = false;

  // We dont want the onscreen hud when using a HMD device
#if HMD_MODULE_INCLUDED
  bHMDDeviceActive = GEngine->IsStereoscopic3D();
#endif // HMD_MODULE_INCLUDED
  if (bHMDDeviceActive == false) {
    // Get our vehicle so we can check if we are in car. If we are we don't want
    // onscreen HUD
    AURGPawn *Vehicle = Cast<AURGPawn>(GetOwningPawn());
    if ((Vehicle != nullptr) && (Vehicle->bInCarCameraActive == false)) {
      FVector2D ScaleVec(HUDYRatio * 1.4f, HUDYRatio * 1.4f);

      // Speed

      FCanvasTextItem SpeedTextItem(
          FVector2D(HUDXRatio * 805.f, HUDYRatio * 455),
          Vehicle->SpeedDisplayString, HUDFont, FLinearColor::Blue);
      SpeedTextItem.Scale = ScaleVec;
      Canvas->DrawItem(SpeedTextItem);

      // Gear
      FCanvasTextItem GearTextItem(
          FVector2D(HUDXRatio * 805.f, HUDYRatio * 500.f),
          Vehicle->GearDisplayString, HUDFont,
          Vehicle->bInReverseGear == false ? Vehicle->GearDisplayColor
                                           : Vehicle->GearDisplayReverseColor);
      GearTextItem.Scale = ScaleVec;
      Canvas->DrawItem(GearTextItem);
    }
  }
}

#undef LOCTEXT_NAMESPACE
