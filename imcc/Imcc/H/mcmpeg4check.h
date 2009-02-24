/********************************************************************
	created:	2004/06/08
	created:	8:6:2004   13:40
	file base:	mcmpeg4check
	file ext:	h
	author:		Peter hesijie
	
	purpose:	
*********************************************************************/
#ifndef MCMPEG4CHECK
#define MCMPEG4CHECK

interface IReferenceClock;
interface IEnumPins;
interface IPin;
interface IFilterGraph;
interface IEnumMediaTypes;

typedef long LONG_PTR;
typedef LONGLONG REFERENCE_TIME;
typedef enum _FilterState {
  State_Stopped   = 0,
  State_Paused    = State_Stopped + 1,
  State_Running   = State_Paused + 1
} FILTER_STATE;

typedef struct _FilterInfo
{
	WCHAR achName[ 128 ];
	IFilterGraph *pGraph;
}FILTER_INFO;

typedef struct _AMMediaType
    {
    GUID majortype;
    GUID subtype;
    BOOL bFixedSizeSamples;
    BOOL bTemporalCompression;
    ULONG lSampleSize;
    GUID formattype;
    IUnknown *pUnk;
    ULONG cbFormat;
    /* [size_is] */ BYTE *pbFormat;
    } 	AM_MEDIA_TYPE;

EXTERN_C const IID IID_IMediaFilter;    
MIDL_INTERFACE("56a86899-0ad4-11ce-b03a-0020af0ba770")
IMediaFilter : public IPersist
{
public:
    virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE Run( 
        REFERENCE_TIME tStart) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE GetState( 
        /* [in] */ DWORD dwMilliSecsTimeout,
        /* [out] */ FILTER_STATE *State) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE SetSyncSource( 
        /* [in] */ IReferenceClock *pClock) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE GetSyncSource( 
        /* [out] */ IReferenceClock **pClock) = 0;
    
};
    
/* interface IBaseFilter */
/* [unique][uuid][object] */ 

const IID IID_IBaseFilter = {0x56a86895,0x0ad4,0x11ce,{0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70}};
MIDL_INTERFACE("56a86895-0ad4-11ce-b03a-0020af0ba770")
IBaseFilter : public IMediaFilter
{
public:
    virtual HRESULT STDMETHODCALLTYPE EnumPins( 
        /* [out] */ IEnumPins **ppEnum) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE FindPin( 
        /* [string][in] */ LPCWSTR Id,
        /* [out] */ IPin **ppPin) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE QueryFilterInfo( 
        /* [out] */ FILTER_INFO *pInfo) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE JoinFilterGraph( 
        /* [in] */ IFilterGraph *pGraph,
        /* [string][in] */ LPCWSTR pName) = 0;
    
    virtual HRESULT STDMETHODCALLTYPE QueryVendorInfo( 
        /* [string][out] */ LPWSTR *pVendorInfo) = 0;
    
};


const IID IID_ICreateDevEnum = {0x29840822,0x5B84,0x11D0,{0xBD,0x3B,0x00,0xA0,0xC9,0x11,0xCE,0x86}};    
MIDL_INTERFACE("29840822-5B84-11D0-BD3B-00A0C911CE86")
ICreateDevEnum : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE CreateClassEnumerator( 
        /* [in] */ REFCLSID clsidDeviceClass,
        /* [out] */ IEnumMoniker **ppEnumMoniker,
        /* [in] */ DWORD dwFlags) = 0;
    
};

//typedef 
//enum _PinDirection
//    {	PINDIR_INPUT	= 0,
//	PINDIR_OUTPUT	= PINDIR_INPUT + 1
//    } 	PIN_DIRECTION;
//
//
//
//typedef struct _PinInfo
//    {
//    IBaseFilter *pFilter;
//    PIN_DIRECTION dir;
//    WCHAR achName[ 128 ];
//    } 	PIN_INFO;
//
//
//EXTERN_C const IID IID_IPin;
//MIDL_INTERFACE("56a86891-0ad4-11ce-b03a-0020af0ba770")
//IPin : public IUnknown
//{
//public:
//    virtual HRESULT STDMETHODCALLTYPE Connect( 
//        /* [in] */ IPin *pReceivePin,
//        /* [in] */ const AM_MEDIA_TYPE *pmt) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE ReceiveConnection( 
//        /* [in] */ IPin *pConnector,
//        /* [in] */ const AM_MEDIA_TYPE *pmt) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE ConnectedTo( 
//        /* [out] */ IPin **pPin) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE ConnectionMediaType( 
//        /* [out] */ AM_MEDIA_TYPE *pmt) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE QueryPinInfo( 
//        /* [out] */ PIN_INFO *pInfo) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE QueryDirection( 
//        /* [out] */ PIN_DIRECTION *pPinDir) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE QueryId( 
//        /* [out] */ LPWSTR *Id) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE QueryAccept( 
//        /* [in] */ const AM_MEDIA_TYPE *pmt) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE EnumMediaTypes( 
//        /* [out] */ IEnumMediaTypes **ppEnum) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE QueryInternalConnections( 
//        /* [out] */ IPin **apPin,
//        /* [out][in] */ ULONG *nPin) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE EndOfStream( void) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE BeginFlush( void) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE EndFlush( void) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE NewSegment( 
//        /* [in] */ REFERENCE_TIME tStart,
//        /* [in] */ REFERENCE_TIME tStop,
//        /* [in] */ double dRate) = 0;
//    
//};
//
//
//EXTERN_C const IID IID_IEnumPins;   
//MIDL_INTERFACE("56a86892-0ad4-11ce-b03a-0020af0ba770")
//IEnumPins : public IUnknown
//{
//public:
//    virtual HRESULT STDMETHODCALLTYPE Next( 
//        /* [in] */ ULONG cPins,
//        /* [size_is][out] */ IPin **ppPins,
//        /* [out] */ ULONG *pcFetched) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE Skip( 
//        /* [in] */ ULONG cPins) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE Clone( 
//        /* [out] */ IEnumPins **ppEnum) = 0;
//    
//};
//
////EXTERN_C IID IID_IAMAudioInputMixer;    
//MIDL_INTERFACE("54C39221-8380-11d0-B3F0-00AA003761C5")
//IAMAudioInputMixer : public IUnknown
//{
//public:
//    virtual HRESULT STDMETHODCALLTYPE put_Enable( 
//        /* [in] */ BOOL fEnable) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_Enable( 
//        /* [out] */ BOOL *pfEnable) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE put_Mono( 
//        /* [in] */ BOOL fMono) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_Mono( 
//        /* [out] */ BOOL *pfMono) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE put_MixLevel( 
//        /* [in] */ double Level) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_MixLevel( 
//        /* [out] */ double *pLevel) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE put_Pan( 
//        /* [in] */ double Pan) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_Pan( 
//        /* [out] */ double *pPan) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE put_Loudness( 
//        /* [in] */ BOOL fLoudness) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_Loudness( 
//        /* [out] */ BOOL *pfLoudness) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE put_Treble( 
//        /* [in] */ double Treble) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_Treble( 
//        /* [out] */ double *pTreble) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_TrebleRange( 
//        /* [out] */ double *pRange) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE put_Bass( 
//        /* [in] */ double Bass) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_Bass( 
//        /* [out] */ double *pBass) = 0;
//    
//    virtual HRESULT STDMETHODCALLTYPE get_BassRange( 
//        /* [out] */ double *pRange) = 0;
//    
//};


static const GUID CLSID_SystemDeviceEnum = {0x62BE5D10,0x60EB,0x11d0,{0xBD,0x3B,0x00,0xA0,0xC9,0x11,0xCE,0x86}};
static const GUID CLSID_VideoCompressorCategory = {0x33d9a760, 0x90c8, 0x11d0, {0xbd, 0x43, 0x0, 0xa0, 0xc9, 0x11, 0xce, 0x86}};
//860BB310-5D01-11d0-BD3B-00A0C911CE86
static const GUID CLSID_VideoInputDeviceCategory = {0x860BB310, 0x5D01, 0x11d0, {0xbd, 0x3B, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86}};
//33D9A762-90C8-11d0-BD43-00A0C911CE86 
static const GUID CLSID_AudioInputDeviceCategory = {0x33D9A762, 0x90C8, 0x11d0, {0xbd, 0x43, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86}};

//static const IID IID_IAMAudioInputMixer = {0x54C39221,0x8380,0x11d0,{0xB3,0xF0,0x00,0xAA,0x00,0x37,0x61,0xC5}};


class CMepg4Check
{
public:
	BOOL IsInstallMepg4Encoder()
	{
		IBaseFilter * pBaseFilter = NULL;
		BOOL bRet = FALSE;
		bRet = GetMSMPEG4VideoEncoder(&pBaseFilter);
		if(pBaseFilter )
		{
			pBaseFilter->Release();
		}
		return bRet;
	}

	BOOL IsInstallVideoCamara()
	{
		IBaseFilter * pBaseFilter = NULL;
		BOOL bRet = FALSE;
		bRet = FindCaptureDevice(&pBaseFilter);
		if(pBaseFilter )
		{
			pBaseFilter->Release();
		}
		return bRet;
	}

	BOOL IsInstallAudio()
	{
		IBaseFilter * pBaseFilter = NULL;
		BOOL bRet = FALSE;
		bRet = FindAudioCaptureDevice(&pBaseFilter);
		if(pBaseFilter )
		{
			pBaseFilter->Release();
		}
		return bRet;	
	}

//	BOOL IsInstallAudioMic()
//	{
//		IBaseFilter * pBaseFilter = NULL;
//		BOOL bRet = FALSE;
//		bRet = FindAudioCaptureDevice(&pBaseFilter);
//		if(bRet)
//		{
//			bRet = CheckMic(pBaseFilter);
//		}
//
//		if(pBaseFilter)
//		{
//			pBaseFilter->Release();
//		}
//		return bRet;	
// 	}

protected:
	BOOL GetMSMPEG4VideoEncoder(IBaseFilter ** ppVideoEncoder)
	{	
		if (!ppVideoEncoder)
			return FALSE;

		*ppVideoEncoder = NULL;

		HRESULT hr = S_OK;
		// create an enumerator object
		CComPtr< ICreateDevEnum > pCreateDevEnum;
		hr = CoCreateInstance(
							CLSID_SystemDeviceEnum, 
							NULL, 
							CLSCTX_INPROC_SERVER,
							IID_ICreateDevEnum, 
							(void**) &pCreateDevEnum);

		if (FAILED(hr))
		{
			return FALSE;
		}

		// tell the enumerator to enumerate Video Compressors
		CComPtr< IEnumMoniker > pEm;
		hr = pCreateDevEnum->CreateClassEnumerator(
							CLSID_VideoCompressorCategory,
							&pEm,  
							0);

		if (FAILED(hr))
		{
			return FALSE;
		}

		// start enumerating at the beginning
		pEm->Reset();

		// Look for all Video Compressors and add them to the combo box.	
		// Note that we do NOT alphabetize the compressors in the list,
		// because we expect them to be in the same order when the user selects
		// an item.  At that point, we will enumerate through the video compressors
		// again in the same order and select the requested item.
		BOOL bContinue = TRUE;
		while(bContinue)
		{
			// Ask for the next VideoCompressor Moniker.
			// A Moniker represents an object, but is not the object itself.
			// You must get the object using the moniker's BindToObject
			// or you can get a "PropertyBag" by calling BindToStorage
			//
			ULONG cFetched = 0;
			CComPtr< IMoniker > pMoniker;

			hr = pEm->Next(1, &pMoniker, &cFetched);
			if(!pMoniker)
			{
				return FALSE;
			}
        
			// convert the Moniker to a PropertyBag, an object you can use to
			// ask the object's Name
			CComPtr< IPropertyBag > pBag;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**) &pBag);
			if (SUCCEEDED(hr))
			{
				// each video compressor has a name, so ask for it
				VARIANT var;
				var.vt = VT_BSTR;
				hr = pBag->Read(L"FriendlyName",&var, NULL);
				if (hr == NOERROR && var.bstrVal)
				{
					USES_CONVERSION;
					if (wcsstr(var.bstrVal, L"Microsoft MPEG-4")&&wcsstr(var.bstrVal, L"V2"))
					{
						// This is the one
						hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)ppVideoEncoder);
						if (SUCCEEDED(hr))
						{
							bContinue = FALSE;
						}
					}

					SysFreeString(var.bstrVal);
				}
			}
		}

		
		return (*ppVideoEncoder!=NULL);
	}

	BOOL FindCaptureDevice(IBaseFilter ** ppSrcFilter)
	{
		HRESULT hr;
		IBaseFilter * pSrc = NULL;
		CComPtr <IMoniker> pMoniker =NULL;
		ULONG cFetched;

		if (!ppSrcFilter)
			return FALSE;
		*ppSrcFilter = NULL;
   
		// Create the system device enumerator
		CComPtr <ICreateDevEnum> pDevEnum =NULL;

		hr = CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
							   IID_ICreateDevEnum, (void **) &pDevEnum);
		if (FAILED(hr))
		{
			return FALSE;
		}

		// Create an enumerator for the video capture devices
		CComPtr <IEnumMoniker> pClassEnum = NULL;
		hr = pDevEnum->CreateClassEnumerator (CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
		if (FAILED(hr))
		{
			return FALSE;
		}

		// If there are no enumerators for the requested type, then 
		// CreateClassEnumerator will succeed, but pClassEnum will be NULL.
		if (pClassEnum == NULL)
		{
			return FALSE;
		}

		// Use the first video capture device on the device list.
		// Note that if the Next() call succeeds but there are no monikers,
		// it will return S_FALSE (which is not a failure).  Therefore, we
		// check that the return code is S_OK instead of using SUCCEEDED() macro.
		if (S_OK == (pClassEnum->Next (1, &pMoniker, &cFetched)))
		{
			// Bind Moniker to a filter object
			hr = pMoniker->BindToObject(0,0,IID_IBaseFilter, (void**)&pSrc);
			if (FAILED(hr))
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}

		// Copy the found filter pointer to the output parameter.
		// Do NOT Release() the reference, since it will still be used
		// by the calling function.
		*ppSrcFilter = pSrc;

		return TRUE;
	}

	BOOL FindAudioCaptureDevice(IBaseFilter ** ppSrcFilter)
	{
		HRESULT hr;
		IBaseFilter * pSrc = NULL;
		CComPtr <IMoniker> pMoniker =NULL;
		ULONG cFetched;

		if (!ppSrcFilter)
			return FALSE;
		*ppSrcFilter = NULL;
   
		// Create the system device enumerator
		CComPtr <ICreateDevEnum> pDevEnum =NULL;

		hr = CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
							   IID_ICreateDevEnum, (void **) &pDevEnum);
		if (FAILED(hr))
		{
			return FALSE;
		}

		// Create an enumerator for the audio capture devices
		CComPtr <IEnumMoniker> pClassEnum = NULL;
		hr = pDevEnum->CreateClassEnumerator (CLSID_AudioInputDeviceCategory, &pClassEnum, 0);
		if (FAILED(hr))
		{
			return FALSE;
		}

		// If there are no enumerators for the requested type, then 
		// CreateClassEnumerator will succeed, but pClassEnum will be NULL.
		if (pClassEnum == NULL)
		{
			return FALSE;
		}

		// Use the first audio capture device on the device list.
		// Note that if the Next() call succeeds but there are no monikers,
		// it will return S_FALSE (which is not a failure).  Therefore, we
		// check that the return code is S_OK instead of using SUCCEEDED() macro.
		if (S_OK == (pClassEnum->Next (1, &pMoniker, &cFetched)))
		{
			// Bind Moniker to a filter object
			hr = pMoniker->BindToObject(0,0,IID_IBaseFilter, (void**)&pSrc);
			if (FAILED(hr))
			{
				return FALSE;
			}

			CComPtr< IPropertyBag > pBag;
			if (pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**) &pBag)==S_OK)
			{
				// each video compressor has a name, so ask for it
				VARIANT var;
				var.vt = VT_BSTR;
				
				USES_CONVERSION;
				
				hr = pBag->Read(L"FriendlyName",&var, NULL);
				SysFreeString(var.bstrVal);
			}

		}
		else
		{
			return FALSE;
		}

		// Copy the found filter pointer to the output parameter.
		// Do NOT Release() the reference, since it will still be used
		// by the calling function.
		*ppSrcFilter = pSrc;

		return TRUE;
	}

//	BOOL CheckMic(IBaseFilter *pFilter)
//	{
//		HRESULT hr;
//		BOOL bRet= FALSE;
//		IEnumPins  *pEnum = NULL;
//		IPin *pPin = NULL;
//
//		// Verify filter interface
//		if (!pFilter)
//		{
//			return bRet;
//		}
//
//		// Get pin enumerator
//		hr = pFilter->EnumPins(&pEnum);
//		if (FAILED(hr))
//		{
//			return bRet;
//		}
//
//		pEnum->Reset();
//
//		// Enumerate all pins on this filter
//		while((hr = pEnum->Next(1, &pPin, 0)) == S_OK)
//		{
//			PIN_DIRECTION PinDirThis;
//			hr = pPin->QueryDirection(&PinDirThis);
//			if (FAILED(hr))
//			{
//				pPin->Release();
//				continue;
//			}
//
//			// Does the pin's direction match the requested direction?
//			if (PINDIR_INPUT == PinDirThis)
//			{
//				PIN_INFO pininfo={0};
//
//				// Direction matches, so add pin name to listbox
//				hr = pPin->QueryPinInfo(&pininfo);
//				
//				IAMAudioInputMixer *pPinMixer;
//				hr = pPin->QueryInterface(IID_IAMAudioInputMixer, (void **)&pPinMixer);
//
//				if(FAILED(hr))
//				{
//					return ;
//				}
//				BOOL b;
//				pPinMixer->get_Enable(&b);
//
//				double fLevel;
//				pPinMixer->get_MixLevel(&fLevel);
//
//				if (b&&wcsicmp(pininfo.achName, L"Mono Mix")!=0&&wcsicmp(pininfo.achName, L"Stereo Mix")!=0)
//				{
//					bRet = TRUE;
//				}
//
//				pPinMixer->Release();
//				// The pininfo structure contains a reference to an IBaseFilter,
//				// so you must release its reference to prevent resource a leak.
//				pininfo.pFilter->Release();
//			}
//			pPin->Release();
//		}
//
//		pEnum->Release();
//		return bRet;
//	}

};

__declspec(selectany)  CMepg4Check g_mpeg4Check;
#endif