// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadSlateBLF.h"

void ULoadSlateBLF::LoadSlate()
{
	LoadFunction *slateTexture;
	slateTexture = new LoadFunction();
	//TSharedPtr<LoadFunction> slateTexture = MakeShareable(new LoadFunction());
	slateTexture->CreateScreen();
}
