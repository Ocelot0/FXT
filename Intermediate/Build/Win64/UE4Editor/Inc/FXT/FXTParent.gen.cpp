// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/FXTParent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFXTParent() {}
// Cross Module References
	FXT_API UClass* Z_Construct_UClass_AFXTParent_NoRegister();
	FXT_API UClass* Z_Construct_UClass_AFXTParent();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FXT();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_AddChildFromSelectedActors();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_GetChildHidden();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_GetChildList();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_GetNumOfChilds();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_RefreshChildList();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_RemoveChildByLabel();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_ResetChildList();
	FXT_API UFunction* Z_Construct_UFunction_AFXTParent_SetChildHidden();
	ENGINE_API UClass* Z_Construct_UClass_UBillboardComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
// End Cross Module References
	void AFXTParent::StaticRegisterNativesAFXTParent()
	{
		UClass* Class = AFXTParent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddChildFromSelectedActors", &AFXTParent::execAddChildFromSelectedActors },
			{ "GetChildHidden", &AFXTParent::execGetChildHidden },
			{ "GetChildList", &AFXTParent::execGetChildList },
			{ "GetNumOfChilds", &AFXTParent::execGetNumOfChilds },
			{ "RefreshChildList", &AFXTParent::execRefreshChildList },
			{ "RemoveChildByLabel", &AFXTParent::execRemoveChildByLabel },
			{ "ResetChildList", &AFXTParent::execResetChildList },
			{ "SetChildHidden", &AFXTParent::execSetChildHidden },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_AFXTParent_AddChildFromSelectedActors()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "AddChildFromSelectedActors", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, 0, nullptr, 0, 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AFXTParent_GetChildHidden()
	{
		struct FXTParent_eventGetChildHidden_Parms
		{
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((FXTParent_eventGetChildHidden_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(FXTParent_eventGetChildHidden_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "GetChildHidden", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(FXTParent_eventGetChildHidden_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AFXTParent_GetChildList()
	{
		struct FXTParent_eventGetChildList_Parms
		{
			TArray<AActor*> outchildlist;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_outchildlist = { UE4CodeGen_Private::EPropertyClass::Array, "outchildlist", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(FXTParent_eventGetChildList_Parms, outchildlist), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_outchildlist_Inner = { UE4CodeGen_Private::EPropertyClass::Object, "outchildlist", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_outchildlist,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_outchildlist_Inner,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "GetChildList", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00420401, sizeof(FXTParent_eventGetChildList_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AFXTParent_GetNumOfChilds()
	{
		struct FXTParent_eventGetNumOfChilds_Parms
		{
			int32 ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Int, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(FXTParent_eventGetNumOfChilds_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "GetNumOfChilds", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(FXTParent_eventGetNumOfChilds_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AFXTParent_RefreshChildList()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
				{ "ToolTip", "refresh child list. remove nulls" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "RefreshChildList", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, 0, nullptr, 0, 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AFXTParent_RemoveChildByLabel()
	{
		struct FXTParent_eventRemoveChildByLabel_Parms
		{
			FString TargetLabel;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_TargetLabel = { UE4CodeGen_Private::EPropertyClass::Str, "TargetLabel", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(FXTParent_eventRemoveChildByLabel_Parms, TargetLabel), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_TargetLabel,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "RemoveChildByLabel", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(FXTParent_eventRemoveChildByLabel_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AFXTParent_ResetChildList()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "ResetChildList", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, 0, nullptr, 0, 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AFXTParent_SetChildHidden()
	{
		struct FXTParent_eventSetChildHidden_Parms
		{
			bool NewHidden;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_NewHidden_SetBit = [](void* Obj){ ((FXTParent_eventSetChildHidden_Parms*)Obj)->NewHidden = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_NewHidden = { UE4CodeGen_Private::EPropertyClass::Bool, "NewHidden", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(FXTParent_eventSetChildHidden_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_NewHidden_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_NewHidden,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AFXTParent, "SetChildHidden", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x00020401, sizeof(FXTParent_eventSetChildHidden_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AFXTParent_NoRegister()
	{
		return AFXTParent::StaticClass();
	}
	UClass* Z_Construct_UClass_AFXTParent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AActor,
				(UObject* (*)())Z_Construct_UPackage__Script_FXT,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_AFXTParent_AddChildFromSelectedActors, "AddChildFromSelectedActors" }, // 1487904293
				{ &Z_Construct_UFunction_AFXTParent_GetChildHidden, "GetChildHidden" }, // 1672320201
				{ &Z_Construct_UFunction_AFXTParent_GetChildList, "GetChildList" }, // 2844894768
				{ &Z_Construct_UFunction_AFXTParent_GetNumOfChilds, "GetNumOfChilds" }, // 1674721755
				{ &Z_Construct_UFunction_AFXTParent_RefreshChildList, "RefreshChildList" }, // 1055911788
				{ &Z_Construct_UFunction_AFXTParent_RemoveChildByLabel, "RemoveChildByLabel" }, // 2159575066
				{ &Z_Construct_UFunction_AFXTParent_ResetChildList, "ResetChildList" }, // 2944112121
				{ &Z_Construct_UFunction_AFXTParent_SetChildHidden, "SetChildHidden" }, // 2512428607
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "FXTParent.h" },
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ChildList_MetaData[] = {
				{ "Category", "FXT" },
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ChildList = { UE4CodeGen_Private::EPropertyClass::Array, "ChildList", RF_Public|RF_Transient|RF_MarkAsNative, 0x0040000000020001, 1, nullptr, STRUCT_OFFSET(AFXTParent, ChildList), METADATA_PARAMS(NewProp_ChildList_MetaData, ARRAY_COUNT(NewProp_ChildList_MetaData)) };
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ChildList_Inner = { UE4CodeGen_Private::EPropertyClass::Object, "ChildList", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000020000, 1, nullptr, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bChildHidden_MetaData[] = {
				{ "Category", "FXT" },
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			auto NewProp_bChildHidden_SetBit = [](void* Obj){ ((AFXTParent*)Obj)->bChildHidden = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bChildHidden = { UE4CodeGen_Private::EPropertyClass::Bool, "bChildHidden", RF_Public|RF_Transient|RF_MarkAsNative, 0x0040000000020001, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(AFXTParent), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_bChildHidden_SetBit)>::SetBit, METADATA_PARAMS(NewProp_bChildHidden_MetaData, ARRAY_COUNT(NewProp_bChildHidden_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EditorBillboardComponent_MetaData[] = {
				{ "Category", "FXT" },
				{ "EditInline", "true" },
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_EditorBillboardComponent = { UE4CodeGen_Private::EPropertyClass::Object, "EditorBillboardComponent", RF_Public|RF_Transient|RF_MarkAsNative, 0x001000000008001c, 1, nullptr, STRUCT_OFFSET(AFXTParent, EditorBillboardComponent), Z_Construct_UClass_UBillboardComponent_NoRegister, METADATA_PARAMS(NewProp_EditorBillboardComponent_MetaData, ARRAY_COUNT(NewProp_EditorBillboardComponent_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RComp_MetaData[] = {
				{ "Category", "FXT" },
				{ "EditInline", "true" },
				{ "ModuleRelativePath", "Public/FXTParent.h" },
			};
#endif
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RComp = { UE4CodeGen_Private::EPropertyClass::Object, "RComp", RF_Public|RF_Transient|RF_MarkAsNative, 0x001000000008001c, 1, nullptr, STRUCT_OFFSET(AFXTParent, RComp), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(NewProp_RComp_MetaData, ARRAY_COUNT(NewProp_RComp_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ChildList,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ChildList_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_bChildHidden,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_EditorBillboardComponent,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_RComp,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AFXTParent>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AFXTParent::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFXTParent, 2451219188);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFXTParent(Z_Construct_UClass_AFXTParent, &AFXTParent::StaticClass, TEXT("/Script/FXT"), TEXT("AFXTParent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFXTParent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
