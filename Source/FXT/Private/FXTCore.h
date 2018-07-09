//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"

//Engine Header
#include "Runtime/Launch/Resources/Version.h"	//provide current engine version info
#include "Editor.h"
#include "Engine.h"
#include "LevelUtils.h"
#include "LevelEditor.h"
#include "ILevelViewport.h"
#include "ActorEditorUtils.h"
#include "IPluginManager.h"
#include "EditorStyleSet.h"			//provide FEditorStyle
#include "EditorFontGlyphs.h"		//provide icons as FText
#include "EditorViewportClient.h"
#include "Dialogs.h"
#include "AssetEditorManager.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "Particles/ParticleLODLevel.h"
#include "Particles/ParticleModuleRequired.h"

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
#include "SCheckBox.h"
#include "SSpinBox.h"
#include "SSlider.h"

//Style set
#include "FXTStyle.h"
#include "FXTGameMode.h"

//FXT SlateWidget
#include "SRowButton.h"
#include "SFXTButton.h"
#include "SFXTMain.h"
#include "SFXTMainToolbar.h"
#include "SFXTParent.h"
#include "SFXTInfo.h"
#include "SFXTComboButton.h"
#include "SRowComboButton.h"
#include "SPIETool.h"
#include "SInPIE.h"
#include "SEmitterBatchTool.h"
#include "SAssetPicker.h"

//FXT Class
#include "FXTParent.h"

//*Paths
#define PLUGIN_RESOUCRES_PATH IPluginManager::Get().FindPlugin("FXT")->GetBaseDir() / TEXT("Resources")

//* Strings
#define FULLNAME "FX Tool"
#define SHORTNAME "FXT"

//Tab string
#define TOOLBARBUTTON_LABEL "FXT"
#define TOOLBARBUTTON_TOOLTIP "Open FX Tool"
#define TAB_LABEL "FX Tool"
#define TOOLBAREXTENTIONHOOK "Compile"

//Button tooltips
#define BTN_CREATEPARENT_TOOLTIP "Create a new Pineapple\nAt view loaction"
#define BTN_HIDDENTOGGLE_TOOLTIP "Hide child actors"
#define BTN_ADDCHILDFROMSELECTED_TOOLTIP "Add childs from selected"
#define BTN_DESTROYPARENT_TOOLTIP "Destroy"
#define BTN_EDITCHILD_TOOLTIP "Edit child list"
#define BTN_RESETCHILDLIST_TOOLTIP "Remove all child from list"
#define BTN_REMOVECHILD_TOOLTIP "Remove from list"
#define BTN_GOTOCHILD_TOOLTIP "Goto"
#define BTN_GOTOPARENT_TOOLTIP "Goto"
#define BTN_GOTOSEQ_TOOLTIP "Goto sequencer"
#define BTN_CREATEPARENT_WIKIPAGE "Wiki page"
#define BTN_PLAY_TOOLTIP "PIE: Play, ActiveViewport"
#define BTN_SIMULATE_TOOLTIP "PIE: Simulate, ActiveViewport"
#define BTN_PLAYNEWWINDOW_TOOLTIP "PIE: Play, NewWindow"
#define BTN_STOPPIE_TOOLTIP "Stop PIE"

//tooltips
#define TB_NEWPARENTNAME_TOOLTIP "This will be used as the name of the new parent"
#define SB_NEWPARENTVIEWOFFSET_TOOLTIP " Offset \n New parent location = View + ViewDirection * Offset"
#define CB_GOTOSEQOPENSEQ_TOOLTIP " Goto Sequencer \n Open Sequencer Editor?"
#define CB_GOTOSEQFOCUS_TOOLTIP "Goto Sequencer \n Move camera to target?"

//PIE
#define DESC_PIEMODE_0 "Unable to use FXT while running PIE"
#define DESC_PIEMODE_1 "Use stop button or ESC key to exit PIE"
#define CB_IMMERSIVEONPIE "Toggle immersive on PIE"

//Sequencer autoplay
#define CB_SEQUENCERAUTOPLAY "Play sequencer on PIE"
#define CB_SEQUENCERAUTOPLAY_TOOLTIP "Level sequencer actor\nto play on PIE"
#define CB_SEQUENCERAUTOPLAY_DEFAULT "Select Sequence"
#define SB_HOWMANYTIMESLOOP "How many times play sequencer? -1:Infinite 0:Once 1+:Additional play counts(999 maximum)"
#define SB_HOWMANYTIMESLOOP_TOOLTIP "Num Loops\n-1:Infinite\n0:Once\n1+:Additional play counts"

//Sequencer controller
#define BTN_SEQGOTOFRONT_TOOLTIP "Goto front"
#define BTN_SEQPLAY_TOOLTIP "Play"
#define BTN_SEQPAUSE_TOOLTIP "Pause"

//*Tool Name
#define FXT_TOOLNAME_PARENT "Parent Tool"
#define FXT_TOOLNAME_PIE "PIE Tool"
#define FXT_TOOLNAME_EMITTERBATCH "Emitter Batch Tool"
#define FXT_TOOLNAME_INFO "Information"

UENUM()
enum class EFXTToolType
{
	EDefault,
	EParent,
	EPIE,
	EEmitterBatch,
	EInfo
};

struct FFXTDelegate
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAutoSequencePlay, ALevelSequenceActor*)

	static FOnAutoSequencePlay OnAutoSequencePlay;
};

//*Static Functions
struct FFXTCore
{
	//*FText Utils
	//Blank text
	FORCEINLINE static FText GetBlankText() { return FText::ChangeKey("FXT", "BlankText", FText::FromString("Blank")); }

	//FText from string
	static FText T(FString Str, FString Key = "NULL");
	static FText T_FName(FName Name, FString Key = "NULL");

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

//*License
struct FLicense
{
	static bool GetLicense(TArray<FString>& outLisence) {
		if (outLisence.Num() > 0) return false;

		outLisence.Add("MIT License");
		outLisence.Add("");
		outLisence.Add("Copyright (c) 2018 LeeGilSu");
		outLisence.Add("");
		outLisence.Add("Permission is hereby granted, free of charge, to any person obtaining a copy");
		outLisence.Add("of this software and associated documentation files (the ''Software''), to deal");
		outLisence.Add("in the Software without restriction, including without limitation the rights");
		outLisence.Add("to use, copy, modify, merge, publish, distribute, sublicense, and/or sell");
		outLisence.Add("copies of the Software, and to permit persons to whom the Software is");
		outLisence.Add("furnished to do so, subject to the following conditions:");
		outLisence.Add("");
		outLisence.Add("The above copyright notice and this permission notice shall be included in all");
		outLisence.Add("copies or substantial portions of the Software.");
		outLisence.Add("");
		outLisence.Add("THE SOFTWARE IS PROVIDED ''AS IS'', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
		outLisence.Add("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
		outLisence.Add("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE");
		outLisence.Add("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
		outLisence.Add("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
		outLisence.Add("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
		outLisence.Add("SOFTWARE.");
		outLisence.Add("");

		return true;
	}
};

//*Typedefs
typedef FFXTStyle FXTStyle;
typedef FFXTCore FXTC;