#ifndef DBCC_TEXTURE_ATLAS_H
#define DBCC_TEXTURE_ATLAS_H

#include "DragonBonesHeaders.h"
#include "cocos2d.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class DBCCTextureAtlas : public ITextureAtlas
{
public:
#if (DRAGON_BONES_ENABLE_KD == 1)
    std::vector<std::string> _pListFileList;
    std::vector<std::string> _textureFileList;
    std::string name;
#endif
    
public:
    DBCCTextureAtlas() :
    name("")
    {
        textureAtlasData = nullptr;
    }
    virtual ~DBCCTextureAtlas()
    {
        dispose();
    }
    virtual void dispose() override
    {
        _pListFileList.clear();
        _textureFileList.clear();
        if (textureAtlasData)
        {
            textureAtlasData->dispose();
            textureAtlasData = nullptr;
        }
    }

#if (DRAGON_BONES_ENABLE_KD == 0)
    virtual cocos2d::Texture2D* getTexture(cocos2d::Texture2D::PixelFormat textureformat)
    {

        if (!textureAtlasData) return nullptr;

        auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
        auto texture = textureCache->getTextureForKey(textureAtlasData->imagePath);
        if (!texture)
        {
            cocos2d::Texture2D::PixelFormat old = cocos2d::Texture2D::getDefaultAlphaPixelFormat();
            cocos2d::Texture2D::PixelFormat now = old;
            switch (textureAtlasData->format)
            {
            case PixelFormat::RGBA8888:
                now = cocos2d::Texture2D::PixelFormat::RGBA8888;
                break;
            case PixelFormat::BGRA8888:
                now = cocos2d::Texture2D::PixelFormat::BGRA8888;
                break;
            case PixelFormat::RGBA4444:
                now = cocos2d::Texture2D::PixelFormat::RGBA4444;
                break;
            case PixelFormat::RGB888:
                now = cocos2d::Texture2D::PixelFormat::RGB888;
                break;
            case PixelFormat::RGB565:
                now = cocos2d::Texture2D::PixelFormat::RGB565;
                break;
            case PixelFormat::RGBA5551:
                now = cocos2d::Texture2D::PixelFormat::RGB5A1;
                break;
            }
            cocos2d::Texture2D::setDefaultAlphaPixelFormat(now);
            texture = textureCache->addImage(textureAtlasData->imagePath);
            cocos2d::Texture2D::setDefaultAlphaPixelFormat(old);
        }
        return texture;
    }
#else
    virtual cocos2d::Texture2D* getTexture(const std::string& textureFilePath,cocos2d::Texture2D::PixelFormat textureformat)
    {
        auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
        auto texture = textureCache->getTextureForKey(textureFilePath);
        if (!texture)
        {
            cocos2d::Texture2D::PixelFormat old = cocos2d::Texture2D::getDefaultAlphaPixelFormat();
            cocos2d::Texture2D::setDefaultAlphaPixelFormat(textureformat);
            texture = textureCache->addImage(textureFilePath);
            cocos2d::Texture2D::setDefaultAlphaPixelFormat(old);
        }
        return texture;
    }
#endif
    
    virtual bool addpListFile(const std::string& plist)
    {
        if (cocos2d::FileUtils::getInstance()->isFileExist(plist)){
            std::vector<std::string>::iterator it;
            it = find(_pListFileList.begin(),_pListFileList.end(),plist);
            if (it ==_pListFileList.end()){
                _pListFileList.push_back(plist);
                return true;
            }
        }
        
        return false;
    }
    
    virtual void addSpriteFrames(const std::string& pListFilePath)
    {
        std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(pListFilePath);
        cocos2d::ValueMap dict = cocos2d::FileUtils::getInstance()->getValueMapFromFile(fullPath);
        
        std::string texturePath("");
        
        cocos2d::Texture2D::PixelFormat textureformat = cocos2d::Texture2D::getDefaultAlphaPixelFormat();
        if (dict.find("metadata") != dict.end())
        {
            cocos2d::ValueMap& metadataDict = dict["metadata"].asValueMap();
            // try to read  texture file name from meta data
            textureformat = (cocos2d::Texture2D::PixelFormat)(metadataDict["textureformat"].asInt());
            texturePath = metadataDict["textureFileName"].asString();
        }
        
        if (!texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = cocos2d::FileUtils::getInstance()->fullPathFromRelativeFile(texturePath.c_str(), fullPath);
            
            _textureFileList.push_back(texturePath);
        }
        
        auto texture = getTexture(texturePath,textureformat);
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(pListFilePath);
        //cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithDictionary(dict,texture);
    }

    virtual void reloadTexture()
    {
#if (DRAGON_BONES_ENABLE_KD == 0)
        return getTexture();
#else
        for (auto it = _pListFileList.begin(); it != _pListFileList.end(); it ++) {
            addSpriteFrames(*it);
        }
#endif
    }
    
    virtual bool removeTexture()
    {
        bool isRemove = false;
        auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
        for (auto it = _textureFileList.begin(); it != _textureFileList.end(); it ++) {
            std::string s = *it;
            auto texture = textureCache->getTextureForKey(s);
            cocos2d::SpriteFrameCache::getInstance()->removeSpriteFramesFromTexture(texture);
            if (texture && texture->getReferenceCount() == 1)
            {
                textureCache->removeTexture(texture);
                isRemove = true;
                
            }
        }
        
        return isRemove;
    }
    
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(DBCCTextureAtlas);
};
NAME_SPACE_DRAGON_BONES_END

#endif  // DBCC_TEXTURE_ATLAS_H