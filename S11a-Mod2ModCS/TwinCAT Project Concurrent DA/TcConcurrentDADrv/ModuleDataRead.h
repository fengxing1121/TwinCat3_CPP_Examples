///////////////////////////////////////////////////////////////////////////////
// ModuleDataRead.h
#pragma once

#include "TcConcurrentDADrvInterfaces.h"

class CModuleDataRead 
	: public ITComObject
	, public ITcADI
	, public ITcWatchSource
///<AutoGeneratedContent id="InheritanceList">
	, public ITcCyclic
///</AutoGeneratedContent>
{
public:
	DECLARE_IUNKNOWN()
	DECLARE_IPERSIST(CID_TcConcurrentDADrvCModuleDataRead)
	DECLARE_ITCOMOBJECT_LOCKOP()
	DECLARE_ITCADI()
	DECLARE_ITCWATCHSOURCE()
	DECLARE_OBJPARAWATCH_MAP()
	DECLARE_OBJDATAAREA_MAP()

	CModuleDataRead();
	virtual	~CModuleDataRead();


///<AutoGeneratedContent id="InterfaceMembers">
	// ITcCyclic
	virtual HRESULT TCOMAPI CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context);

///</AutoGeneratedContent>

protected:
	DECLARE_ITCOMOBJECT_SETSTATE();

	HRESULT AddModuleToCaller();
	VOID RemoveModuleFromCaller();

///<AutoGeneratedContent id="Members">
	TcTraceLevel m_TraceLevelMax;
	ULONG m_DataReadCounterModulo;
	ModuleDataReadRead m_Read;
	ITcCyclicCallerInfoPtr m_spCyclicCaller;
	IDataReadPtr m_spDataRead;
///</AutoGeneratedContent>

	// Tracing
	CTcTrace m_Trace;

	// TODO: Custom variable
	UINT m_counter;
};
