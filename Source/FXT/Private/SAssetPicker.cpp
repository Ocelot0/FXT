//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SAssetPicker.h"
#include "SlateOptMacros.h"

#include "SBox.h"
#include "SButton.h"
#include "SMenuAnchor.h"

#include "EditorStyleSet.h"
#include "EditorFontGlyphs.h"

#include "AssetData.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "PropertyCustomizationHelpers.h"
#include "Engine.h"

SAssetPicker::~SAssetPicker()
{
	//AssetThumbnailPool->ReleaseResources();
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SAssetPicker::Construct(const FArguments& InArgs)
{
	//*Thumbnail
	//Thumbnail size
	TAttribute<FOptionalSize> ThumbnailSize = FOptionalSize(InArgs._ThumbnailSize);

	//Thumbnail Res
	int32 ThumbnailRes = InArgs._ThumbnailRes;

	//Create Thumbnail Pool
	AssetThumbnailPool = MakeShareable(new FAssetThumbnailPool(1024, true));
	//Create Thumbnail Object
	AssetThumbnail = MakeShareable(new FAssetThumbnail(FAssetData(), ThumbnailRes, ThumbnailRes, AssetThumbnailPool));

	//Thumbnail default asset load
	AssetThumbnail->SetAsset(FAssetData(
		TEXT("/Engine/EditorMeshes/EditorHelp"),
		TEXT("/Engine/EditorMeshes"),
		TEXT("EditorHelp"), TEXT("StaticMesh")));

	//Thumbnail Config
	FAssetThumbnailConfig ThumbnailConfig;
	ThumbnailConfig.bAllowFadeIn = true;

	//Create Thumbnail Widget
	TSharedRef<SWidget> ThumbnailWidget = AssetThumbnail->MakeThumbnailWidget(ThumbnailConfig);

	//*Asset Picker
	//Size
	AssetPickerSize = InArgs._Size;

	//Callbacks
	OnAssetSelected = InArgs._OnAssetSelected;
	OnGetAllowedClasses = InArgs._OnGetAllowedClasses;

	//AssetPicker Label
	LastSelectedAssetName = TEXT("Asset Picker");
	auto LastSelectedAssetName_Lam = [this] {
		return FText::FromString(LastSelectedAssetName.ToString());
	};
	TAttribute<FText> LastSelectedAssetName_Attr = TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateLambda(LastSelectedAssetName_Lam));

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Right)[
			//AssetPicker Anchor
			SAssignNew(AssetPickerAnchor, SMenuAnchor)
			.Placement(MenuPlacement_AboveRightAnchor)
			.OnGetMenuContent(this, &SAssetPicker::OnGenerateAssetPicker)
		]
		+ SVerticalBox::Slot().FillHeight(1)[
			//AssetPicker button
			SNew(SButton)
			.ButtonStyle(&FEditorStyle::Get(), "EditorViewportToolBar.MenuButton")
			.OnClicked(this, &SAssetPicker::btn_OpenAssetPicker)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)[
					SNew(SBox).MaxDesiredHeight(ThumbnailSize).MaxDesiredWidth(ThumbnailSize)[
						ThumbnailWidget
					]
				]
				//Selected Asset Label
				+ SVerticalBox::Slot().Padding(.0f, 1.5f).AutoHeight().HAlign(HAlign_Center)[
					SNew(SBox).MaxDesiredWidth(ThumbnailSize)[
						SNew(STextBlock)
						.Text(LastSelectedAssetName_Attr)
						.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.10"))
						.ColorAndOpacity(FSlateColor(FColor(32, 32, 32, 255)))
					]
				]
			]
		]

	];

}

FReply SAssetPicker::btn_OpenAssetPicker()
{
	//*Open Asset Picker
	AssetPickerAnchor->SetIsOpen(true);

	return FReply::Handled();
}

TSharedRef<SWidget> SAssetPicker::OnGenerateAssetPicker()
{
	TArray<const UClass*> AllowedClasses;
	OnGetAllowedClasses.ExecuteIfBound(AllowedClasses);

	if(AllowedClasses.Num() == 0){
		//*Assume all classes are allowed
		AllowedClasses.Add(UObject::StaticClass());
	}
	FContentBrowserModule& CBModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	FAssetPickerConfig AssetPickerConfig;
	for (auto ClassIt = AllowedClasses.CreateConstIterator(); ClassIt; ++ClassIt) {
		const UClass* Class = (*ClassIt);
		AssetPickerConfig.Filter.ClassNames.Add(Class->GetFName());
	}

	//Allow child classes
	AssetPickerConfig.Filter.bRecursiveClasses = true;

	//Set a delegate for setting the asset from the picker
	AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateSP(this, &SAssetPicker::OnAssetSelectedFromPicker);
	AssetPickerConfig.bAllowDragging = false;

	//Use the list view by default
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;

	TSharedRef<SWidget> MenuContent =
		SNew(SBox).WidthOverride(AssetPickerSize.X).HeightOverride(AssetPickerSize.Y)
		[
			SNew(SBorder).BorderImage(FEditorStyle::GetBrush("Menu.Background"))
			[
				CBModule.Get().CreateAssetPicker(AssetPickerConfig)
			]
		];

	return MenuContent;
}

void SAssetPicker::OnAssetSelectedFromPicker(const FAssetData& AssetData)
{
	//*Close AssetPicker
	AssetPickerAnchor->SetIsOpen(false);

	//*Update Thumbnail
	AssetThumbnail->SetAsset(AssetData);

	//*Update Thumbnail Label
	LastSelectedAssetName = AssetData.AssetName;

	//*Select event callback execute
	OnAssetSelected.ExecuteIfBound(AssetData.GetAsset());
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
