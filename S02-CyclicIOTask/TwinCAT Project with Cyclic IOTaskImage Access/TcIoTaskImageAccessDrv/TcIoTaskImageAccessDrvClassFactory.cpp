///////////////////////////////////////////////////////////////////////////////
// TcIoTaskImageAccessDrvClassFactory.cpp
#include "TcPch.h"
#pragma hdrstop

#include "TcIoTaskImageAccessDrvClassFactory.h"
#include "TcIoTaskImageAccessDrvServices.h"
#include "IoTaskImageAccessModule.h"

BEGIN_CLASS_MAP(CTcIoTaskImageAccessDrvClassFactory)
///<AutoGeneratedContent id="ClassMap">
	CLASS_ENTRY(CID_TcIoTaskImageAccessDrvCIoTaskImageAccessModule, SRVNAME_TCIOTASKIMAGEACCESSDRV "!CIoTaskImageAccessModule", CIoTaskImageAccessModule)
///</AutoGeneratedContent>
END_CLASS_MAP()

CTcIoTaskImageAccessDrvClassFactory::CTcIoTaskImageAccessDrvClassFactory() : CObjClassFactory()
{
	TcDbgUnitSetImageName(TCDBG_UNIT_IMAGE_NAME(SRVNAME_TCIOTASKIMAGEACCESSDRV)); 
}

