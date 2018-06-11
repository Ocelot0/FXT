//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "FXTCore.h"

FText FFXTCore::T(FString Str, FString Key)
{
	if (Key == "NULL") return FText::FromString(Str);
	return FText::ChangeKey("FXT", Key, FText::FromString(Str));
}

FString FFXTCore::GetVersionString(bool bEngineVersion)
{
	if (bEngineVersion)
	{
		return FString::FromInt(ENGINE_MAJOR_VERSION) + FString(TEXT("."))
			+ FString::FromInt(ENGINE_MINOR_VERSION) + FString(TEXT("."))
			+ FString::FromInt(ENGINE_PATCH_VERSION) + FString(TEXT("_"))
			+ FString::FromInt(BUILT_FROM_CHANGELIST);
	}

	return FString(SHORTNAME) + FString(TEXT("(")) + FString(FULLNAME) + FString(TEXT(") "))
		+ FString::FromInt(FXT_MAJOR_VERSION) + FString(TEXT("."))
		+ FString::FromInt(FXT_MINOR_VERSION) + FString(TEXT("."))
		+ FString::FromInt(FXT_PATCH_VERSION) + FString(TEXT("_"))
		+ FString(FXT_DESCRIPTION_VERSION);
}

FText FFXTCore::GetFullVersionText()
{
	return FText::ChangeKey("FXT", "VersionText",
		FText::FromString(
			GetVersionString(false) +
			FString(TEXT("(compatible with UE")) +
			GetVersionString() +
			FString(TEXT(")")))
	);
}

FString FFXTCore::GetCopyrightString()
{
	return FString(TEXT("Copyright ")) +
		FEditorFontGlyphs::Copyright.ToString() +
		FString(TEXT(" 2018 Lee Gil Su, All rights reserved. ")) +
		FEditorFontGlyphs::Envelope_O.ToString() +
		FString(TEXT("devcontact90@gmail.com"));
}

FText FFXTCore::GetCopyrightText()
{
	return FText::ChangeKey("FXT", "CopyrightText", FText::FromString(GetCopyrightString()));
}

bool FFXTCore::chkA(AActor * inActor)
{
	if (inActor == nullptr) return false;	// inActor is not nullpointer

	return
		!inActor->IsActorBeingDestroyed()		// actor is not destroyed
		&& !inActor->IsPendingKill()			// actor is not pending kill
		&& inActor->IsEditable()				// actor allowed to be selected and drawn in editor
		&& inActor->IsListedInSceneOutliner()	// actor listed in Sceneoutliner
		&& FLevelUtils::IsLevelVisible(inActor->GetLevel())	// actor in visible level
		&& inActor->IsValidLowLevel()
		&& inActor->IsSelectable();
}

int32 FFXTCore::CompareNumeric(const FString & A, const FString & B)
{
	const TCHAR* CharA = *A, *CharB = *B;
	const TCHAR* EndA = CharA + A.Len(), *EndB = CharB + B.Len();

	while (CharA < EndA && CharB < EndB)
	{
		// Ignore underscores
		if (*CharA == '_')
		{
			++CharA;
			continue;
		}
		if (*CharB == '_')
		{
			++CharB;
			continue;
		}

		TCHAR *IntAEnd = nullptr;
		const uint64 IntA = FCString::Strtoui64(CharA, &IntAEnd, 10);

		TCHAR *IntBEnd = nullptr;
		const uint64 IntB = FCString::Strtoui64(CharB, &IntBEnd, 10);

		const bool AIsNum = (IntAEnd != CharA), BIsNum = (IntBEnd != CharB);
		if (AIsNum != BIsNum)
		{
			// At the current CharA/CharB position, either (but not both) of the strings is an integer
			// Numbers are considered less than characters
			return AIsNum ? -1 : 1;
		}
		else if (AIsNum)
		{
			CharA = IntAEnd;
			CharB = IntBEnd;

			if (IntA != IntB)
			{
				return IntA < IntB ? -1 : 1;
			}
		}
		else if (int32 Cmp = (*FCString::Strnicmp)(CharA, CharB, 1))
		{
			return Cmp;
		}
		else
		{
			++CharA;
			++CharB;
		}
	}

	if (CharA == EndA && CharB == EndB)
	{
		// Strings compared equal, return shortest first
		if (const int32 LengthDifference = A.Len() - B.Len())
		{
			return LengthDifference / FMath::Abs(LengthDifference);
		}
		else
		{
			return 0;
		}
	}

	// Strings are different comparative lengths, return shortest
	return CharA == EndA ? -1 : 1;
}