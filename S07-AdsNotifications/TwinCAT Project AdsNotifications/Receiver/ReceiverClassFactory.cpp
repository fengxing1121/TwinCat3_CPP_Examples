///////////////////////////////////////////////////////////////////////////////
// ReceiverClassFactory.cpp
#include "TcPch.h"
#pragma hdrstop

#include "ReceiverClassFactory.h"
#include "ReceiverServices.h"
#include "ModuleReceiver.h"

BEGIN_CLASS_MAP(CReceiverClassFactory)
///<AutoGeneratedContent id="ClassMap">
	CLASS_ENTRY(CID_ReceiverCModuleReceiver, SRVNAME_RECEIVER "!CModuleReceiver", CModuleReceiver)
///</AutoGeneratedContent>
END_CLASS_MAP()

CReceiverClassFactory::CReceiverClassFactory() : CObjClassFactory()
{
	TcDbgUnitSetImageName(TCDBG_UNIT_IMAGE_NAME(SRVNAME_RECEIVER)); 
}
