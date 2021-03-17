#pragma once

class UTexture2D;

struct ICustomVariant
{
	virtual ~ICustomVariant() = default;
	
	virtual FString GetName() const = 0;
	
	virtual UTexture2D* GetThumbnail() const = 0;
	
	virtual bool GetIsActive() const = 0;
};