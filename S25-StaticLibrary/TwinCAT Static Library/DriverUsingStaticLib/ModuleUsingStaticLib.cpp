///////////////////////////////////////////////////////////////////////////////
// ModuleUsingStaticLib.cpp
#include "TcPch.h"
#pragma hdrstop

#include "ModuleUsingStaticLib.h"
#include "..\StaticLib\StaticFunction.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DEFINE_THIS_FILE()

///////////////////////////////////////////////////////////////////////////////
// CModuleUsingStaticLib
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Collection of interfaces implemented by module CModuleUsingStaticLib
BEGIN_INTERFACE_MAP(CModuleUsingStaticLib)
	INTERFACE_ENTRY_ITCOMOBJECT()
	INTERFACE_ENTRY(IID_ITcADI, ITcADI)
	INTERFACE_ENTRY(IID_ITcWatchSource, ITcWatchSource)
///<AutoGeneratedContent id="InterfaceMap">
	INTERFACE_ENTRY(IID_ITcCyclic, ITcCyclic)
///</AutoGeneratedContent>
END_INTERFACE_MAP()

IMPLEMENT_ITCOMOBJECT(CModuleUsingStaticLib)
IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP2(CModuleUsingStaticLib)
IMPLEMENT_ITCADI(CModuleUsingStaticLib)
IMPLEMENT_ITCWATCHSOURCE(CModuleUsingStaticLib)


///////////////////////////////////////////////////////////////////////////////
// Set parameters of CModuleUsingStaticLib 
BEGIN_SETOBJPARA_MAP(CModuleUsingStaticLib)
	SETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="SetObjectParameterMap">
	SETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	SETOBJPARA_VALUE(PID_ModuleUsingStaticLibParameter, m_Parameter)
	SETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
///</AutoGeneratedContent>
END_SETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get parameters of CModuleUsingStaticLib 
BEGIN_GETOBJPARA_MAP(CModuleUsingStaticLib)
	GETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="GetObjectParameterMap">
	GETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	GETOBJPARA_VALUE(PID_ModuleUsingStaticLibParameter, m_Parameter)
	GETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
///</AutoGeneratedContent>
END_GETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get watch entries of CModuleUsingStaticLib
BEGIN_OBJPARAWATCH_MAP(CModuleUsingStaticLib)
	OBJPARAWATCH_DATAAREA_MAP()
///<AutoGeneratedContent id="ObjectParameterWatchMap">
///</AutoGeneratedContent>
END_OBJPARAWATCH_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get data area members of CModuleUsingStaticLib
BEGIN_OBJDATAAREA_MAP(CModuleUsingStaticLib)
///<AutoGeneratedContent id="ObjectDataAreaMap">
	OBJDATAAREA_VALUE(0, m_Inputs)
	OBJDATAAREA_VALUE(1, m_Outputs)
///</AutoGeneratedContent>
END_OBJDATAAREA_MAP()


///////////////////////////////////////////////////////////////////////////////
CModuleUsingStaticLib::CModuleUsingStaticLib()
	: m_Trace(m_TraceLevelMax, m_spSrv)
	, m_counter(0)
{
	memset(&m_Parameter, 0, sizeof(m_Parameter)); 
	memset(&m_Inputs, 0, sizeof(m_Inputs)); 
	memset(&m_Outputs, 0, sizeof(m_Outputs)); 
}

///////////////////////////////////////////////////////////////////////////////
CModuleUsingStaticLib::~CModuleUsingStaticLib() 
{
}


///////////////////////////////////////////////////////////////////////////////
// State Transitions 
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_IP_PI(CModuleUsingStaticLib)

///////////////////////////////////////////////////////////////////////////////
// State transition from PREOP to SAFEOP
//
// Initialize input parameters 
// Allocate memory
HRESULT CModuleUsingStaticLib::SetObjStatePS(PTComInitDataHdr pInitData)
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;
	IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData);

	// TODO: Add initialization code

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to OP
//
// Register with other TwinCAT objects
HRESULT CModuleUsingStaticLib::SetObjStateSO()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	// TODO: Add any additional initialization


	// If following call is successful the CycleUpdate method will be called, 
	// eventually even before method has been left.
	hr = FAILED(hr) ? hr : AddModuleToCaller(); 

	// Cleanup if transition failed at some stage
	if ( FAILED(hr) )
	{
		RemoveModuleFromCaller(); 
	}

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from OP to SAFEOP
HRESULT CModuleUsingStaticLib::SetObjStateOS()
{
	m_Trace.Log(tlVerbose, FENTERA);

	HRESULT hr = S_OK;

	RemoveModuleFromCaller(); 

	// TODO: Add any additional deinitialization

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to PREOP
HRESULT CModuleUsingStaticLib::SetObjStateSP()
{
	HRESULT hr = S_OK;
	m_Trace.Log(tlVerbose, FENTERA);

	// TODO: Add deinitialization code

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///<AutoGeneratedContent id="ImplementationOf_ITcCyclic">
HRESULT CModuleUsingStaticLib::CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context)
{
	HRESULT hr = S_OK;


	m_counter+=m_Inputs.Value;
	m_Outputs.Value=m_counter;

	//call a static method from StaticLib-Project
	hr = ComputeSomething(m_Inputs.Operand1, m_Inputs.Operand2, m_Outputs.CSResult );
	if(hr != S_OK) return hr;
	//call a object instance's method from the StaticLib-Project
	hr = mc.SampleMultiplicationMethod(m_Inputs.Operand1, m_Inputs.Operand2, m_Outputs.MResult );
	return hr;
}
///</AutoGeneratedContent>

///////////////////////////////////////////////////////////////////////////////
HRESULT CModuleUsingStaticLib::AddModuleToCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);

	HRESULT hr = S_OK;
	if ( m_spCyclicCaller.HasOID() )
	{
		if ( SUCCEEDED_DBG(hr = m_spSrv->TcQuerySmartObjectInterface(m_spCyclicCaller)) )
		{
			if ( FAILED(hr = m_spCyclicCaller->AddModule(m_spCyclicCaller, THIS_CAST(ITcCyclic))) )
			{
				m_spCyclicCaller = NULL;
			}
		}
	}
	else
	{
		hr = ADS_E_INVALIDOBJID; 
		SUCCEEDED_DBGT(hr, "Invalid OID specified for caller task");
	}

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
VOID CModuleUsingStaticLib::RemoveModuleFromCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);

	if ( m_spCyclicCaller )
	{
		m_spCyclicCaller->RemoveModule(m_spCyclicCaller);
	}
	m_spCyclicCaller	= NULL;

	m_Trace.Log(tlVerbose, FLEAVEA);
}

