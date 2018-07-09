//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "PropertyCustomizationHelpers.h"

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

class FXT_API SAssetPicker : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAssetPicker)
		: _ThumbnailSize(64)
		, _ThumbnailRes(128)
		, _Size(FVector2D(200, 350))
	{}

	SLATE_ARGUMENT(int32, ThumbnailSize)
	SLATE_ARGUMENT(int32, ThumbnailRes)
	SLATE_ARGUMENT(FVector2D, Size)

	SLATE_EVENT(FOnGetAllowedClasses, OnGetAllowedClasses)
	SLATE_EVENT(FOnAssetSelected, OnAssetSelected)

	SLATE_END_ARGS()

	~SAssetPicker();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//*Menu Anchor
	//Open AssetPicker
	FReply btn_OpenAssetPicker();

	//Menu Anchor Widget
	TSharedPtr<class SMenuAnchor> AssetPickerAnchor;

	//Generate callback
	TSharedRef<SWidget> OnGenerateAssetPicker();

	//Select event callback
	void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);

private:
	//*AssetPicker
	//Size of widget
	FVector2D AssetPickerSize;

	//AssetPicker Filter Class Getter
	FOnGetAllowedClasses OnGetAllowedClasses;

	//Selection event callback
	FOnAssetSelected OnAssetSelected;

	//Last selected asset name
	FName LastSelectedAssetName;

private:
	//*Tumbnail
	//pool
	TSharedPtr<class FAssetThumbnailPool> AssetThumbnailPool;

	//Thumbnail obejct
	TSharedPtr<FAssetThumbnail> AssetThumbnail;

};
