/*
 * $Id: OPAtomContentPackage.cpp,v 1.2 2009/10/23 09:05:21 philipn Exp $
 *
 * Holds the essence data for each track in the clip
 *
 * Copyright (C) 2009  British Broadcasting Corporation.
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 */

#include <libMXF++/MXFException.h>

#include "OPAtomContentPackage.h"

using namespace std;
using namespace mxfpp;



OPAtomContentElement::OPAtomContentElement()
{
    mIsPicture = true;
    mMaterialTrackId = 0;
    mEssenceOffset = 0;
}




OPAtomContentPackage::OPAtomContentPackage()
{
    mPosition = 0;
}

OPAtomContentPackage::~OPAtomContentPackage()
{
    size_t i;
    for (i = 0; i < mEssenceDataVector.size(); i++)
        delete mEssenceDataVector[i];
    
    // mEssenceData contains copies of content elements
}

bool OPAtomContentPackage::HaveEssenceData(uint32_t mp_track_id) const
{
    return GetEssenceData(mp_track_id, false) != 0;
}

const OPAtomContentElement* OPAtomContentPackage::GetEssenceData(uint32_t mp_track_id) const
{
    return GetEssenceData(mp_track_id, true);
}

const unsigned char* OPAtomContentPackage::GetEssenceDataBytes(uint32_t mp_track_id) const
{
    const OPAtomContentElement *element = GetEssenceData(mp_track_id);
    
    return element->GetBytes();
}

uint32_t OPAtomContentPackage::GetEssenceDataSize(uint32_t mp_track_id) const
{
    const OPAtomContentElement *element = GetEssenceData(mp_track_id);
    
    return element->GetSize();
}

const OPAtomContentElement* OPAtomContentPackage::GetEssenceDataI(size_t index) const
{
    MXFPP_ASSERT(index < mEssenceDataVector.size());
    
    return mEssenceDataVector[index];
}

const unsigned char* OPAtomContentPackage::GetEssenceDataIBytes(size_t index) const
{
    const OPAtomContentElement *element = GetEssenceDataI(index);
    
    return element->GetBytes();
}

uint32_t OPAtomContentPackage::GetEssenceDataISize(size_t index) const
{
    const OPAtomContentElement *element = GetEssenceDataI(index);
    
    return element->GetSize();
}

OPAtomContentElement* OPAtomContentPackage::GetEssenceData(uint32_t mp_track_id, bool check) const
{
    map<uint32_t, OPAtomContentElement*>::const_iterator result = mEssenceData.find(mp_track_id);
    if (result == mEssenceData.end()) {
        if (check)
            MXFPP_ASSERT(result != mEssenceData.end());
        return 0;
    }
    
    return result->second;
}

OPAtomContentElement* OPAtomContentPackage::AddElement(uint32_t mp_track_id)
{
    MXFPP_ASSERT(!GetEssenceData(mp_track_id, false));
    
    mEssenceDataVector.push_back(new OPAtomContentElement());
    mEssenceData[mp_track_id] = mEssenceDataVector.back();
    
    return GetEssenceData(mp_track_id, true);
}

