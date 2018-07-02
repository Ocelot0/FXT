//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SFXTButton.h"
#include "SlateOptMacros.h"

#include "SBoxPanel.h"
#include "SButton.h"
#include "STextBlock.h"
#include "SImage.h"

#include "EditorStyleSet.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFXTButton::Construct(const FArguments& InArgs)
{
	FMargin TextPadding = InArgs._Icon.Get().IsEmpty() ? FMargin(0.f) : FMargin(2.f, 0.f);

	//*Visibility
	auto Vis_Image_Lam = [InArgs] {
		return InArgs._bUseImage ? EVisibility::Visible : EVisibility::Collapsed;
	};
	auto Vis_Image_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Image_Lam));

	auto Vis_Icon_Lam = [InArgs] {
		return InArgs._Icon.Get().IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
	};
	auto Vis_Icon_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Icon_Lam));

	auto Vis_Text_Lam = [InArgs] {
		return InArgs._Text.Get().IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
	};
	auto Vis_Text_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Text_Lam));

	ChildSlot
	[
		SNew(SButton).ButtonStyle(InArgs._ButtonStyle).OnClicked(InArgs._OnClicked).ContentPadding(0.f)
		[
			SNew(SHorizontalBox)
			//image
			+ SHorizontalBox::Slot().AutoWidth()	
			[
				SNew(SImage).Visibility(Vis_Image_Attr)
				.Image(InArgs._Image)
				.ColorAndOpacity(InArgs._InitialColor)
			]
			//icon
			+ SHorizontalBox::Slot().AutoWidth()
			[
				SNew(STextBlock).Visibility(Vis_Icon_Attr)
				.TextStyle(InArgs._TextStyle)
				.ColorAndOpacity(InArgs._InitialColor)
				.Text(InArgs._Icon)
			]
			//ButtonText
			+ SHorizontalBox::Slot().Padding(TextPadding).AutoWidth()
			[
				SNew(STextBlock).Visibility(Vis_Text_Attr)
				.TextStyle(InArgs._TextStyle)
				.ColorAndOpacity(InArgs._InitialColor)
				.Text(InArgs._Text)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
