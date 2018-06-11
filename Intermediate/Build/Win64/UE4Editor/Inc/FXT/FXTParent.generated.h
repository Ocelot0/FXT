// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef FXT_FXTParent_generated_h
#error "FXTParent.generated.h already included, missing '#pragma once' in FXTParent.h"
#endif
#define FXT_FXTParent_generated_h

#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execAddChildFromSelectedActors) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddChildFromSelectedActors(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveChildByLabel) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_TargetLabel); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->RemoveChildByLabel(Z_Param_TargetLabel); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetChildList) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ResetChildList(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRefreshChildList) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->RefreshChildList(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetNumOfChilds) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=P_THIS->GetNumOfChilds(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildList) \
	{ \
		P_GET_TARRAY_REF(AActor*,Z_Param_Out_outchildlist); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->GetChildList(Z_Param_Out_outchildlist); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetChildHidden) \
	{ \
		P_GET_UBOOL(Z_Param_NewHidden); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetChildHidden(Z_Param_NewHidden); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildHidden) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->GetChildHidden(); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAddChildFromSelectedActors) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->AddChildFromSelectedActors(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveChildByLabel) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_TargetLabel); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->RemoveChildByLabel(Z_Param_TargetLabel); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execResetChildList) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->ResetChildList(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRefreshChildList) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->RefreshChildList(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetNumOfChilds) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=P_THIS->GetNumOfChilds(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildList) \
	{ \
		P_GET_TARRAY_REF(AActor*,Z_Param_Out_outchildlist); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->GetChildList(Z_Param_Out_outchildlist); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetChildHidden) \
	{ \
		P_GET_UBOOL(Z_Param_NewHidden); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetChildHidden(Z_Param_NewHidden); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetChildHidden) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->GetChildHidden(); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFXTParent(); \
	friend FXT_API class UClass* Z_Construct_UClass_AFXTParent(); \
public: \
	DECLARE_CLASS(AFXTParent, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/FXT"), NO_API) \
	DECLARE_SERIALIZER(AFXTParent) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAFXTParent(); \
	friend FXT_API class UClass* Z_Construct_UClass_AFXTParent(); \
public: \
	DECLARE_CLASS(AFXTParent, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/FXT"), NO_API) \
	DECLARE_SERIALIZER(AFXTParent) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AFXTParent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AFXTParent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFXTParent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFXTParent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFXTParent(AFXTParent&&); \
	NO_API AFXTParent(const AFXTParent&); \
public:


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFXTParent(AFXTParent&&); \
	NO_API AFXTParent(const AFXTParent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFXTParent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFXTParent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFXTParent)


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__bChildHidden() { return STRUCT_OFFSET(AFXTParent, bChildHidden); } \
	FORCEINLINE static uint32 __PPO__ChildList() { return STRUCT_OFFSET(AFXTParent, ChildList); }


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_9_PROLOG
#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_RPC_WRAPPERS \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_INCLASS \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_FXT_Source_FXT_Public_FXTParent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
