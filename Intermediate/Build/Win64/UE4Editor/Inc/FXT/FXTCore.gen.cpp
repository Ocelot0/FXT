// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Private/FXTCore.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFXTCore() {}
// Cross Module References
	FXT_API UEnum* Z_Construct_UEnum_FXT_EFXTToolType();
	UPackage* Z_Construct_UPackage__Script_FXT();
// End Cross Module References
	static UEnum* EFXTToolType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FXT_EFXTToolType, Z_Construct_UPackage__Script_FXT(), TEXT("EFXTToolType"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EFXTToolType(EFXTToolType_StaticEnum, TEXT("/Script/FXT"), TEXT("EFXTToolType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FXT_EFXTToolType_CRC() { return 412010740U; }
	UEnum* Z_Construct_UEnum_FXT_EFXTToolType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FXT();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EFXTToolType"), 0, Get_Z_Construct_UEnum_FXT_EFXTToolType_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EFXTToolType::EDefault", (int64)EFXTToolType::EDefault },
				{ "EFXTToolType::EParent", (int64)EFXTToolType::EParent },
				{ "EFXTToolType::EInfo", (int64)EFXTToolType::EInfo },
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ModuleRelativePath", "Private/FXTCore.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FXT,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"EFXTToolType",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::EnumClass,
				"EFXTToolType",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
