// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

class FXT_API SFXTInfo : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFXTInfo)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

public:
	//*Wiki page hyperlink
	FReply OnCliked_WikiPage();

public:
	//*License
	//ListView Widget
	TSharedPtr< SListView<TSharedPtr<FString>> > LicenseTextListView;

	//ListView item data array
	TArray< TSharedPtr<FString> > LicenseTextListSrc;

	//Generate List View Row
	TSharedRef<ITableRow> OnGenerateRowLicenseText(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	//On Selection Changed
	void OnSelectionChangedLicenseText(TSharedPtr<FString> InItem, ESelectInfo::Type SelectInfo);

};
