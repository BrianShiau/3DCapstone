// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef AKAUDIO_AkAmbientSound_generated_h
#error "AkAmbientSound.generated.h already included, missing '#pragma once' in AkAmbientSound.h"
#endif
#define AKAUDIO_AkAmbientSound_generated_h

#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_16_GENERATED_BODY \
	friend AKAUDIO_API class UScriptStruct* Z_Construct_UScriptStruct_FAkAmbSoundCheckpointRecord(); \
	AKAUDIO_API static class UScriptStruct* StaticStruct();


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execStopAmbientSound) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->StopAmbientSound(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStartAmbientSound) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->StartAmbientSound(); \
		P_NATIVE_END; \
	}


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execStopAmbientSound) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->StopAmbientSound(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStartAmbientSound) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->StartAmbientSound(); \
		P_NATIVE_END; \
	}


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAAkAmbientSound(); \
	friend AKAUDIO_API class UClass* Z_Construct_UClass_AAkAmbientSound(); \
	public: \
	DECLARE_CLASS(AAkAmbientSound, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(AAkAmbientSound) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_INCLASS \
	private: \
	static void StaticRegisterNativesAAkAmbientSound(); \
	friend AKAUDIO_API class UClass* Z_Construct_UClass_AAkAmbientSound(); \
	public: \
	DECLARE_CLASS(AAkAmbientSound, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(AAkAmbientSound) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAkAmbientSound(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAkAmbientSound) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAkAmbientSound); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAkAmbientSound); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAkAmbientSound(AAkAmbientSound&&); \
	NO_API AAkAmbientSound(const AAkAmbientSound&); \
public:


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAkAmbientSound(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAkAmbientSound(AAkAmbientSound&&); \
	NO_API AAkAmbientSound(const AAkAmbientSound&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAkAmbientSound); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAkAmbientSound); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAkAmbientSound)


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_PRIVATE_PROPERTY_OFFSET
#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_33_PROLOG
#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_PRIVATE_PROPERTY_OFFSET \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_RPC_WRAPPERS \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_INCLASS \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_PRIVATE_PROPERTY_OFFSET \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_INCLASS_NO_PURE_DECLS \
	ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h_36_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class AkAmbientSound."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShotgunPrincess_Plugins_Wwise_Source_AkAudio_Classes_AkAmbientSound_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
