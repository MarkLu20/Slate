// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadingTexture.h"
#include "LoadSlateBLF.generated.h"

/**
 * 
 */
UCLASS()
class SLATETEST_API ULoadSlateBLF : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "LoadSlate")
		static void LoadSlate();
	
	
	
	
};
