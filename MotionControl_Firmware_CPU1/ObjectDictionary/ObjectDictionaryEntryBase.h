/******************************************************************************
 * Copyright (C) 2017 by Yifan Jiang                                          *
 * jiangyi@student.ethz.com                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 ******************************************************************************/

/*
* Control process base class
* control processes to be executed by the CPU should be derived from this one
*/

#ifndef _OBJ_ENTRY_BASE_H
#define _OBJ_ENTRY_BASE_H

#include "stdint.h"
#include "CiATypeDef.h"

typedef struct ObdAccessHandleTypedef{
  uint16_t AccessType     :  8;
  uint16_t AccessResult   :  8;
  union {
      float32_t DataFloat32;
      int32_t   DataInt32;
      uint32_t  DataUint32;
      int16_t   DataInt16[3];
      uint16_t  DataUint16[3];
  } Data;

} ObdAccessHandle;

class ObjectDictionaryEntryBase{

  public:

    ObjectDictionaryEntryBase(){};
    ~ObjectDictionaryEntryBase(){};

    virtual void AccessObject(ObdAccessHandle*){};

  protected:
    bool _ProcessCompleted;

  private:

};

#endif
