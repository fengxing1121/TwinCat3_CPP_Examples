///////////////////////////////////////////////////////////////////////////////
// SEHModule.cpp
#include "TcPch.h"
#pragma hdrstop

#include "SEHModule.h"
#include "TcStructuredExceptionHandling.h"

#define FACILITY_SEH 0x1
#define STATUS_TCSEH_CUSTOM_EXCEPTION1 ((NTSTATUS)(0xE0000000L) | (FACILITY_SEH)<<16 | 0x0001)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DEFINE_THIS_FILE()

///////////////////////////////////////////////////////////////////////////////
// CSEHModule
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Collection of interfaces implemented by module CSEHModule
BEGIN_INTERFACE_MAP(CSEHModule)
	INTERFACE_ENTRY_ITCOMOBJECT()
	INTERFACE_ENTRY(IID_ITcADI, ITcADI)
	INTERFACE_ENTRY(IID_ITcWatchSource, ITcWatchSource)
///<AutoGeneratedContent id="InterfaceMap">
	INTERFACE_ENTRY(IID_ITcCyclic, ITcCyclic)
///</AutoGeneratedContent>
END_INTERFACE_MAP()

IMPLEMENT_ITCOMOBJECT(CSEHModule)
IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP2(CSEHModule)
IMPLEMENT_ITCADI(CSEHModule)
IMPLEMENT_ITCWATCHSOURCE(CSEHModule)


///////////////////////////////////////////////////////////////////////////////
// Set parameters of CSEHModule 
BEGIN_SETOBJPARA_MAP(CSEHModule)
	SETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="SetObjectParameterMap">
	SETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	SETOBJPARA_VALUE(PID_SEHModuleSampleType, m_SampleType)
	SETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
///</AutoGeneratedContent>
END_SETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get parameters of CSEHModule 
BEGIN_GETOBJPARA_MAP(CSEHModule)
	GETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="GetObjectParameterMap">
	GETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	GETOBJPARA_VALUE(PID_SEHModuleSampleType, m_SampleType)
	GETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
///</AutoGeneratedContent>
END_GETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get watch entries of CSEHModule
BEGIN_OBJPARAWATCH_MAP(CSEHModule)
	OBJPARAWATCH_DATAAREA_MAP()
///<AutoGeneratedContent id="ObjectParameterWatchMap">
///</AutoGeneratedContent>
END_OBJPARAWATCH_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get data area members of CSEHModule
BEGIN_OBJDATAAREA_MAP(CSEHModule)
///<AutoGeneratedContent id="ObjectDataAreaMap">
///</AutoGeneratedContent>
END_OBJDATAAREA_MAP()


///////////////////////////////////////////////////////////////////////////////
CSEHModule::CSEHModule()
	: m_Trace(m_TraceLevelMax, m_spSrv)
	, m_counter(0)
{
///<AutoGeneratedContent id="MemberInitialization">
	m_TraceLevelMax = tlAlways;
	m_SampleType = SampleType_NullPtr;
///</AutoGeneratedContent>
}

///////////////////////////////////////////////////////////////////////////////
CSEHModule::~CSEHModule() 
{
}


///////////////////////////////////////////////////////////////////////////////
// State Transitions 
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_IP_PI(CSEHModule)

///////////////////////////////////////////////////////////////////////////////
// State transition from PREOP to SAFEOP
//
// Initialize input parameters 
// Allocate memory
HRESULT CSEHModule::SetObjStatePS(PTComInitDataHdr pInitData)
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
HRESULT CSEHModule::SetObjStateSO()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	// TODO: Add any additional initialization


	// If following call is successful the CycleUpdate method will be called, 
	// possibly even before method has been left.
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
HRESULT CSEHModule::SetObjStateOS()
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
HRESULT CSEHModule::SetObjStateSP()
{
	HRESULT hr = S_OK;
	m_Trace.Log(tlVerbose, FENTERA);

	// TODO: Add deinitialization code

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Exception filter method
// This is used on different sample types 
// EXCEPTION_CONTINUE_SEARCH is returned, iff no custom exception was detected and continueSearch is TRUE

int CSEHModule::FilterException(const char* func, EXCEPTION_POINTERS* pExceptionPointers, bool continueSearch)
{
	m_Trace.Log(tlInfo, "%s / %s ExceptionCode=0x%08x at address 0x%p", 
		this->TcGetObjectName(), 
		func, 
		pExceptionPointers->ExceptionRecord->ExceptionCode,
		pExceptionPointers->ExceptionRecord->ExceptionAddress);

		if (pExceptionPointers->ExceptionRecord->ExceptionCode == STATUS_TCSEH_CUSTOM_EXCEPTION1)
		{
			if (pExceptionPointers->ExceptionRecord->NumberParameters > 0)
			{
				m_Trace.Log(tlInfo, "Exception message: %s", pExceptionPointers->ExceptionRecord->ExceptionInformation[0]);
			}
			//should be handled locally
			return EXCEPTION_EXECUTE_HANDLER;
		} 
		else if (continueSearch) 
		{
			//simulate to dont know how to handle this ...should be handled upwards
			return EXCEPTION_CONTINUE_SEARCH; 
		}
		return EXCEPTION_EXECUTE_HANDLER;
}
///<AutoGeneratedContent id="ImplementationOf_ITcCyclic">
HRESULT CSEHModule::CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context)
{
	HRESULT hr = S_OK;
	m_counter++;
	
switch(m_SampleType) {
	case SampleType_NullPtr: 
		// NULL pointer access, simple handling
		TcTry
		{	
			if ((m_counter % 95) == 0)
			{
			PBYTE pNull = NULL;
			*pNull = static_cast<BYTE>(m_counter);
			}
		}
		TcExcept(EXCEPTION_EXECUTE_HANDLER)
		{
			m_Trace.Log(tlInfo, "%s: Simple Exception handling in cycle %d", this->TcGetObjectName(), m_counter);
		}
		break; 

	case SampleType_NullPtrFilter: 
		//NULL pointer access, with filter
		TcTry
		{
			// NULL pointer access
			if ((m_counter % 90) == 0)
			{
				PBYTE pNull = NULL;
				*pNull = static_cast<BYTE>(m_counter);
			}
		}
		TcExcept(FilterException(FNAMEA, GetExceptionInformation()))
		{
			m_Trace.Log(tlInfo, "%s: Exception handling with filter occurred in cycle %d", this->TcGetObjectName(), m_counter);
		}
		break; 

	case SampleType_Finally: 
		TcTry
		{
			// TcTry/TcFinally ensures that critical section is always left 
			m_csInstance.EnterCriticalSection();
			
			m_Trace.Log(tlInfo, "%s: Entered critical section %d", this->TcGetObjectName(), m_counter);
			// TcTry/TcExcept catches a NULLPrt access here 
			TcTry
			{
				// NULL pointer access
				if ((m_counter % 10) == 0)
				{
					PBYTE pNull = NULL;
					*pNull = static_cast<BYTE>(m_counter);
				}
			}
			TcFinally
			{
				m_csInstance.LeaveCriticalSection();
				m_Trace.Log(tlInfo, "%s: Left critical section %d", this->TcGetObjectName(), m_counter);
			}
		}
		TcExcept(FilterException(FNAMEA, GetExceptionInformation()))
		{
			m_Trace.Log(tlInfo, "%s: Exception occurred in cycle %d", this->TcGetObjectName(), m_counter);
		}
		break; 

	case SampleType_CustomException: 
		TcTry
		{
			// Custom exception
			if ((m_counter % 97) == 0)
			{
				// prepare exception information
				ULONG_PTR exceptionParams[] = { reinterpret_cast<ULONG_PTR>("Custom raised exception info: Multiple of 97") };
				// Raise custom exception
				TcRaiseException(STATUS_TCSEH_CUSTOM_EXCEPTION1, 0, ARRAYSIZE(exceptionParams), exceptionParams); 
			}
		}
		TcExcept(FilterException(FNAMEA, GetExceptionInformation()))
		{
			m_Trace.Log(tlInfo, "%s: Exception occurred in cycle %d", this->TcGetObjectName(), m_counter);
		}
		break; 

	case SampleType_ContinueException: 
		TcTry 
		{
			TcTry
			{
			// Custom exception
				if ((m_counter % 98) == 0)
				{
					PBYTE pNull = NULL;
					*pNull = static_cast<BYTE>(m_counter);
				}
			}
			TcExcept(FilterException(FNAMEA, GetExceptionInformation(), true))
			{
				m_Trace.Log(tlInfo, "This could handle customer exception, but a null ptr exception was executed so EXCEPTION_CONTINUE_SEARCH is used to search for a handling upstream");
			}
		}
		TcExcept(EXCEPTION_EXECUTE_HANDLER)
		{
			m_Trace.Log(tlInfo, "%s: Upper Except: Exception occurred in cycle %d", this->TcGetObjectName(), m_counter);
		}
		break; 
	default: 
		if ((m_counter % 100) == 0)
		{
			m_Trace.Log(tlInfo, "%s: No Sample Type selected for demonstration of SEH", this->TcGetObjectName());
		}
		break; 
	} //end switch 

	return hr;
}
///</AutoGeneratedContent>

///////////////////////////////////////////////////////////////////////////////
HRESULT CSEHModule::AddModuleToCaller()
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
VOID CSEHModule::RemoveModuleFromCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);

	if ( m_spCyclicCaller )
	{
		m_spCyclicCaller->RemoveModule(m_spCyclicCaller);
	}
	m_spCyclicCaller	= NULL;

	m_Trace.Log(tlVerbose, FLEAVEA);
}

