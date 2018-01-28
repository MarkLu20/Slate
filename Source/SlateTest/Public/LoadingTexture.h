
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "SThrobber.h"
#include "SCompoundWidget.h"

struct FLoadingTexture :public FSlateDynamicImageBrush, public FGCObject
{
	FLoadingTexture(const FName InTextureName, const FVector2D &InImageSize)
		:FSlateDynamicImageBrush(InTextureName, InImageSize)
	{

		ResourceObject = LoadObject<UObject>(nullptr, *InTextureName.ToString());
	}
	virtual void AddReferencedObjects(FReferenceCollector &Collertor)
	{

		if (ResourceObject)
		{
			Collertor.AddReferencedObject(ResourceObject);
		}
	}


};

class SloadingTexture :public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SloadingTexture) {}
	SLATE_END_ARGS()
		void Construct(const FArguments &InArgs)
	{
		TSharedPtr<FSlateDynamicImageBrush> LoadingTextureBrush;
		static const FName LoadTexturName(TEXT("/Game/UI/Menu/LoadingScreen.LoadingScreen"));
		LoadingTextureBrush = MakeShareable(new FLoadingTexture(LoadTexturName, FVector2D(1920, 1080)));
		ChildSlot
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(LoadingTextureBrush.Get())

			]
		+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[

				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(FMargin(10.0f))
			[
				SNew(SThrobber)
				.Visibility(this, &SloadingTexture::GetLoadingThrobberVisibility)

			]
			]

			];
	}
private:
	EVisibility GetLoadingThrobberVisibility() const
	{
		bool Vis = GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;

	}
	void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.WidgetLoadingScreen = SNew(SloadingTexture);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		GetMoviePlayer()->PlayMovie();


	}

};
class LoadFunction
{

public:
	void CreateScreen()
	{
		//force load for cooker reference
		LoadObject<UObject>(nullptr, TEXT("/Game/UI/Menu/LoadingScreen.LoadingScreen")/*, nullptr, LOAD_None, nullptr*/);
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.WidgetLoadingScreen = SNew(SloadingTexture);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);

	
	}




};