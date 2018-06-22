//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "FXTStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "SlateGameResources.h"
#include "IPluginManager.h"

#include "EditorStyleSet.h"
#include "EditorFontGlyphs.h"

TSharedPtr< FSlateStyleSet > FFXTStyle::StyleInstance = NULL;

void FFXTStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FFXTStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FFXTStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("FXTStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon12x12(12.0f, 12.0f);
const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon24x24(24.0f, 24.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon64x64(64.0f, 64.0f);

TSharedRef< FSlateStyleSet > FFXTStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("FXTStyle"));

	//*FXT Icons
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("FXT")->GetBaseDir() / TEXT("Resources"));
	Style->Set("FXT.Icon64", new IMAGE_BRUSH(TEXT("FXT_Main_64"), Icon64x64));
	Style->Set("FXT.OpenPluginWindow", new IMAGE_BRUSH(TEXT("FXT_Main_40"), Icon40x40));
	Style->Set("FXT.Icon24", new IMAGE_BRUSH(TEXT("FXT_Main_24"), Icon24x24));
	Style->Set("FXT.Icon20", new IMAGE_BRUSH(TEXT("FXT_Main_24"), Icon20x20));
	Style->Set("FXT.Icon16", new IMAGE_BRUSH(TEXT("FXT_Main_16"), Icon16x16));
	Style->Set("FXT.GotoSeq", new IMAGE_BRUSH(TEXT("FXT_GotoSeq_12"), Icon12x12));
	
	//*Engine Icons
	Style->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	Style->Set("EditorIcon.Detail", new IMAGE_BRUSH(TEXT("Icons/icon_tab_SelectionDetails_16x"), Icon16x16));
	Style->Set("EditorIcon.SceneOutliner", new IMAGE_BRUSH(TEXT("Icons/icon_tab_SceneOutliner_16x"), Icon16x16));
	Style->Set("EditorIcon.GenericLOD", new IMAGE_BRUSH(TEXT("Icons/icon_Cascade_GenericLOD_40x"), Icon40x40));

	Style->Set("RowIcon.Default", new IMAGE_BRUSH(TEXT("Icons/AssetIcons/Default_16x"), Icon16x16));
	Style->Set("RowIcon.Actor", new IMAGE_BRUSH(TEXT("Icons/AssetIcons/Actor_16x"), Icon16x16));
	Style->Set("RowIcon.LevelSequenceActor", new IMAGE_BRUSH(TEXT("Icons/AssetIcons/LevelSequence_16x"), Icon16x16));
	Style->Set("RowIcon.StaticMeshActor", new IMAGE_BRUSH(TEXT("Icons/AssetIcons/StaticMesh_16x"), Icon16x16));
	Style->Set("RowIcon.SkeletalMeshActor", new IMAGE_BRUSH(TEXT("Icons/AssetIcons/SkeletalMesh_16x"), Icon16x16));
	Style->Set("RowIcon.Emitter", new IMAGE_BRUSH(TEXT("Icons/AssetIcons/ParticleSystem_16x"), Icon16x16));
	Style->Set("RowIcon.CineCameraActor", new IMAGE_BRUSH(TEXT("Icons/AssetIcons/CineCameraActor_16x"), Icon16x16));

	//*Text Block Style (TBStyle)
	const FTextBlockStyle FooterText = FTextBlockStyle()
		.SetFont(FEditorStyle::Get().GetFontStyle("FontAwesome.9"))
		.SetColorAndOpacity(FSlateColor(FColor(128, 128, 128, 255)));
	Style->Set("FooterText", FooterText);

	const FTextBlockStyle WarningMessageText = FTextBlockStyle()
		.SetFont(FEditorStyle::Get().GetFontStyle("FontAwesome.11"))
		.SetColorAndOpacity(FSlateColor(FColor(255, 255, 255, 255)));
	Style->Set("WarningText", WarningMessageText);

	const FTextBlockStyle ButtonText = FTextBlockStyle()
		.SetFont(FEditorStyle::Get().GetFontStyle("FontAwesome.11"))
		.SetColorAndOpacity(FSlateColor(FColor(255, 255, 255, 255)));
	Style->Set("ButtonText", ButtonText);

	const FTextBlockStyle ButtonTextDark = FTextBlockStyle()
		.SetFont(FEditorStyle::Get().GetFontStyle("FontAwesome.11"))
		.SetColorAndOpacity(FSlateColor(FColor(32, 32, 32, 255)));
	Style->Set("ButtonText.Dark", ButtonTextDark);

	const FTextBlockStyle ListViewTextRow = FTextBlockStyle()
		.SetFont(FEditorStyle::Get().GetFontStyle("FontAwesome.10"))
		.SetColorAndOpacity(FSlateColor(FColor(255, 255, 255, 255)));
	Style->Set("ListViewText.Row", ListViewTextRow);

	const FTextBlockStyle ListViewTextRowButton = FTextBlockStyle()
		.SetFont(FEditorStyle::Get().GetFontStyle("FontAwesome.9"))
		.SetColorAndOpacity(FSlateColor(FColor(255, 255, 255, 255)));
	Style->Set("ListViewText.RowButton", ListViewTextRowButton);

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FFXTStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FFXTStyle::Get()
{
	return *StyleInstance;
}
