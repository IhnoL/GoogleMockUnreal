#pragma once

#include "Entities/ICustomVariantSet.h"

class UMaterialInstance;
class UCameraComponent;
class UMaterialInterface;

struct ICustomCameraVariantSet;
struct ICustomPackageVariantSet;
struct ICustomMaterialVariantSet;
struct ICustomGeometryVariantSet;

struct ICustomGeometryVariant;
struct ICustomMaterialVariant;
struct ICustomPackageVariant;
struct ICustomCameraVariant;

struct ICustomPackageVariantSetConnection;

struct ICustomVariantSet;
struct ICustomVariant;

enum class EVariantManagerServiceResult
{
	Success,
	Error
};

struct IVariantManagerService
{
	virtual ~IVariantManagerService() = default;
	virtual ICustomVariantSet* CreateVariantSet(const EVariantSetType& VariantSetType) = 0;
	virtual TArray<ICustomVariantSet*> GetAllVariantSets() = 0;
	virtual ICustomVariantSet* GetVariantSetByName(FString VariantSetName) = 0;
	virtual ICustomVariant* FetchVariantByName(ICustomVariantSet* SelectedVariantSet, const FString& VariantName) = 0;
	virtual EVariantManagerServiceResult RenameVariantSet(ICustomVariantSet* VariantSet, const FString& NewVariantSetName) = 0;
	virtual EVariantManagerServiceResult DeleteVariantSet(ICustomVariantSet* VariantSet) = 0;
	virtual EVariantManagerServiceResult RenameVariant(ICustomVariantSet* VariantSet, ICustomVariant* Variant, const FString& NewVariantName) = 0;
	virtual EVariantManagerServiceResult DeleteVariant(ICustomVariantSet* VariantSet, ICustomVariant* Variant) = 0;
	virtual EVariantManagerServiceResult ActivateVariant(ICustomVariantSet* VariantSet, ICustomVariant* Variant) = 0;
	virtual EVariantManagerServiceResult RefreshVariantSet(ICustomVariantSet* VariantSet) = 0;
	virtual EVariantManagerServiceResult RefreshAllVariantSets() = 0;
	virtual EVariantManagerServiceResult RefreshVariantThumbnailFromEditorViewPort(ICustomVariantSet* VariantSet, ICustomVariant* Variant) = 0;
	virtual EVariantManagerServiceResult RefreshVariantThumbnailFromFile(ICustomVariantSet* VariantSet, ICustomVariant* Variant, const FString& SourceImagePath) = 0;
	virtual EVariantManagerServiceResult ClearVariantThumbnail(ICustomVariantSet* VariantSet, ICustomVariant* Variant) = 0;

	/* Geometry Specific */
	virtual TArray<ICustomGeometryVariant*> GetAllGeometryVariants(ICustomGeometryVariantSet* GeometryVariantSet) = 0;
	virtual ICustomGeometryVariant* CreateGeometryVariant(ICustomGeometryVariantSet* GeometryVariantSet, const FString& Tag) = 0;
	virtual ICustomGeometryVariant* CreateGeometryAllOffVariant(ICustomGeometryVariantSet* VariantSet) = 0;
};

Expose_TNameOf(IVariantManagerService)
