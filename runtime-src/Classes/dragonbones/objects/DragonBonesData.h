#ifndef OBJECTS_DRADON_BONES_DATA_H
#define OBJECTS_DRADON_BONES_DATA_H

#include "../DragonBones.h"
#include "ArmatureData.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class DragonBonesData
{
public:
    bool autoSearch;
    std::string name;
    std::vector<ArmatureData*> armatureDataList;
    
    std::vector<std::string> _dbFileList;
    
public:
    DragonBonesData()
    {
        autoSearch = false;
    }
    DragonBonesData(const DragonBonesData &copyData)
    {
        operator=(copyData);
    }
    DragonBonesData& operator=(const DragonBonesData &copyData)
    {
        dispose();
        autoSearch = copyData.autoSearch;
        name = copyData.name;
        armatureDataList.reserve(copyData.armatureDataList.size());
        
        for (size_t i = 0, l = armatureDataList.size(); i < l; ++i)
        {
            armatureDataList.push_back(new ArmatureData());
            *(armatureDataList[i]) = *(copyData.armatureDataList[i]);
        }
        
        return *this;
    }
    virtual ~DragonBonesData()
    {
        dispose();
    }
    void dispose()
    {
        for (size_t i = 0, l = armatureDataList.size(); i < l; ++i)
        {
            armatureDataList[i]->dispose();
            delete armatureDataList[i];
        }
        
        armatureDataList.clear();
        
        _dbFileList.clear();
    }
    
    ArmatureData* getArmatureData(const std::string &armatureName) const
    {
        for (size_t i = 0, l = armatureDataList.size(); i < l; ++i)
        {
            if (armatureDataList[i]->name == armatureName)
            {
                return armatureDataList[i];
            }
        }
        
        return nullptr;
    }
    
    void addArmatureData(DragonBonesData* addDBData){
        for (size_t i = 0, l = addDBData->armatureDataList.size(); i < l; i++)
        {
            armatureDataList.push_back(addDBData->armatureDataList[i]);
        }
        addDBData->armatureDataList.clear();
    }
    
    bool addDBFile(const std::string &dbFile){
        std::vector<std::string>::iterator it;
        it = find(_dbFileList.begin(),_dbFileList.end(),dbFile);
        if (it ==_dbFileList.end()){
            _dbFileList.push_back(dbFile);
            return true;
        }
        return false;
    }
};
NAME_SPACE_DRAGON_BONES_END
#endif  // OBJECTS_DRADON_BONES_DATA_H
