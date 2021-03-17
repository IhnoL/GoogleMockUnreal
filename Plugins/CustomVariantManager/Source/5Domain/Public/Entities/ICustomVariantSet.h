#pragma once

struct ICustomVariant;

enum class EVariantSetType
{
	None = 0,
    Geometry = 1,
    Material = 2,
    Camera = 3,
	Package = 4,
    Other = 5,
    Num = 6, // Must always be at the end!
};

struct ICustomVariantSet
{
	virtual ~ICustomVariantSet() = default;	
	virtual FString GetName() const = 0;
	virtual EVariantSetType GetType() const = 0;
	virtual bool AddVariantAsset(ICustomVariant* Variant) = 0;
	virtual bool RemoveVariantAsset(ICustomVariant* Variant) = 0;
	virtual TArray<ICustomVariant*> GetVariants() const = 0;
};