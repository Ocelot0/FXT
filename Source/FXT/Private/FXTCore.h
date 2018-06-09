//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"

//Enginee Header
#include "Runtime/Launch/Resources/Version.h"	//provide current engine version info
#include "Editor.h"
#include "Engine.h"
#include "LevelUtils.h"
#include "ActorEditorUtils.h"
#include "IPluginManager.h"
#include "EditorStyleSet.h"			//provide FEditorStyle
#include "EditorFontGlyphs.h"		//provide icons as FText
#include "EditorViewportClient.h"

//Engine Slate Widgets
#include "SBox.h"		//SlateWidget : Box
#include "SOverlay.h"	//SlateWidget : Overlay
#include "SBoxPanel.h"	//SlateWidget : BoxPanel : provide Vertical and Horizontal Box
#include "SBorder.h"	//SlateWidget : Border
#include "STextBlock.h"	//SlateWidget : TextBlock
#include "SButton.h"	//SlateWidget : Button
#include "SComboBox.h"	//SlateWidget : ComboBox
#include "STextComboBox.h"	//SlateWidget : TextComboBox
#include "SSeparator.h"

//Style set
#include "FXTStyle.h"

//FXT SlateWidget
#include "SRowButton.h"
#include "SFXTButton.h"
#include "SFXTMain.h"
#include "SFXTMainToolbar.h"
#include "SFXTParent.h"

//FXT Class
#include "FXTParent.h"

//*Paths
#define PLUGIN_RESOUCRES_PATH IPluginManager::Get().FindPlugin("FXT")->GetBaseDir() / TEXT("Resources")

//* Strings
#define FULLNAME "Realtime Effect Tool"
#define SHORTNAME "FXT"

//Tab string
#define TOOLBARBUTTON_LABEL "FXT"
#define TOOLBARBUTTON_TOOLTIP "Open Realtime Effect Tool"
#define TAB_LABEL "Realtime Effect Tool"
#define TOOLBAREXTENTIONHOOK "Compile"

//Button tooltips
#define BTN_CREATEPARENT_TOOLTIP "Create New Parent"
#define BTN_HIDDENTOGGLE_TOOLTIP "Hide child actors"
#define BTN_ADDCHILDFROMSELECTED_TOOLTIP "Add childs from selected"
#define BTN_EDITCHILD_TOOLTIP "Edit child list"
#define BTN_RESETCHILDLIST_TOOLTIP "Remove all child from list"
#define BTN_REMOVECHILD_TOOLTIP "Remove from list"

//*FXT Versions
#define FXT_MAJOR_VERSION 1
#define FXT_MINOR_VERSION 1
#define FXT_PATCH_VERSION 0
#define FXT_DESCRIPTION_VERSION TEXT("Dev")

//*Tool Name
#define FXT_TOOLNAME_PARENT "Parent Tool"

UENUM()
enum class EFXTToolType
{
	EDefault,
	EParent
};

//*Static Functions
struct FFXTCore
{
	//*FText Utils
	//Blank text
	FORCEINLINE static FText GetBlankText() { return FText::ChangeKey("FXT", "BlankText", FText::FromString("Blank")); }

	//FText from string
	static FText T(FString Str, FString Key = "NULL");

	//Get Version
	static FString GetVersionString(bool bEngineVersion = true);
	static FText GetFullVersionText();

	//Get Copyright
	static FString GetCopyrightString();
	static FText GetCopyrightText();

	//*Actor Util
	static bool chkA(AActor* inActor);

	//World Iterator, return result array's num
	template< class T >
	static int32 Itr(TArray<T*>& outArray) {
		//should empty array
		if (outArray.Num() > 0) return false;

		for (TObjectIterator<T> i; i; ++i) {
			if (chkA(*i)) {
				outArray.Add(*i);
			}
		}

		return outArray.Num();
	}

	template< class T >
	static T* GetActorByLabel(FString InLabel) {
		for (TObjectIterator<T> i; i; ++i) {
			T* A = Cast<T>(*i);
			if (chkA(A) && A->GetActorLabel() == InLabel) {
				return A;
			}
		}

		return nullptr;
	}

	template< class T >
	static T* AddActor(FTransform SpawnTransform = FTransform()) {
		UWorld* const World = GEditor->GetEditorWorldContext().World();

		if (World) {
			return Cast<T>(GEditor->AddActor(World->GetCurrentLevel(), T::StaticClass(), SpawnTransform));
		}

		return nullptr;
	}

	//*Data Util
	static int32 CompareNumeric(const FString& A, const FString& B);
};

//*Typedefs
typedef FFXTStyle FXTStyle;
typedef FFXTCore FXTC;