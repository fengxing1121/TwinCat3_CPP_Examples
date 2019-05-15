///////////////////////////////////////////////////////////////////////////////
// SEHSampleServices.h

#pragma once

#include "TcServices.h"

const ULONG DrvID_SEHSample = 0x3F000000;
#define SRVNAME_SEHSAMPLE "SEHSample"

///<AutoGeneratedContent id="ClassIDs">
const CTCID CID_SEHSampleCSEHModule = {0x24f48ecb,0x4871,0x44d7,{0x8d,0xd7,0x9b,0x15,0xee,0xd8,0x34,0x07}};
///</AutoGeneratedContent>

///<AutoGeneratedContent id="ParameterIDs">
const PTCID PID_SEHModuleSampleType = 0x00000001;
///</AutoGeneratedContent>

///<AutoGeneratedContent id="DataTypes">
#if !defined(_TC_TYPE_A4C8CAA0_5C8F_4B63_8C06_A0237315DF79_INCLUDED_)
#define _TC_TYPE_A4C8CAA0_5C8F_4B63_8C06_A0237315DF79_INCLUDED_
enum ESampleType : SHORT {
	SampleType_NullPtr = 0,
	SampleType_NullPtrFilter = 1,
	SampleType_Finally = 2,
	SampleType_CustomException = 3,
	SampleType_ContinueException = 4,
	SampleType_None = 5
};
#endif // !defined(_TC_TYPE_A4C8CAA0_5C8F_4B63_8C06_A0237315DF79_INCLUDED_)

///</AutoGeneratedContent>



///<AutoGeneratedContent id="DataAreaIDs">
///</AutoGeneratedContent>

///<AutoGeneratedContent id="InterfaceIDs">
///</AutoGeneratedContent>
