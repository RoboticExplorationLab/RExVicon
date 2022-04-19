
//////////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2017 Vicon Motion Systems Ltd
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////
#include <ViconDataStreamSDKCore/CoreClient.h>
#include <ViconCGStreamClientSDK/ICGClient.h>
#include <memory>
#include <functional>
#include <iostream>

#include "ViconDataStreamSDK_MATLAB.h"
namespace ph = std::placeholders;
// N.B. header is NOT included as will clash with extern "C"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

// below is a macro that checks for null strings and 
// converts these into zero-length strings
#define CHECK_STRING(c) 0 == c ? "" : c

namespace
{
  unsigned int NextInstanceID = 1;
  std::map< unsigned int, std::shared_ptr< ViconDataStreamSDK::Core::VClient > > Clients;

  void Clear( bool & i_rValue )
  {
    i_rValue = false;
  }

  void Clear( unsigned int & i_rValue )
  {
    i_rValue = 0;
  }

  void Clear( double & i_rValue )
  {
    i_rValue = 0.0;
  }

  void Clear( std::string & i_rValue )
  {
    i_rValue.clear();
  }

  template< typename T, unsigned int N >
  void Clear( T i_rValue[] )
  {
    for( unsigned int i = 0 ; i < N ; ++i )
    {
      Clear( i_rValue[ i ] );
    }
  }

  template< typename T, unsigned int N >
  void Copy( T o_rDest[], const T (& i_rSource)[N] )
  {
    for( unsigned int i = 0 ; i < N ; ++i )
    {
      o_rDest[ i ] = i_rSource[ i ];
    }
  }

  bool IsValidInstance( unsigned int i_InstanceID )
  {
    std::map< unsigned int, std::shared_ptr< ViconDataStreamSDK::Core::VClient > >::const_iterator It = Clients.find( i_InstanceID );
    return It != Clients.end();
  }
}

// Dll entry point

BOOL APIENTRY DllMain( HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
  switch(ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH: 
    {        
      break;
    }
  case DLL_THREAD_ATTACH: 
    {
      break;
    }
  case DLL_THREAD_DETACH: 
    {
      break;
    }
  case DLL_PROCESS_DETACH: 
    {      
      break;
    }
  }
  return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif


// Create an instance of a Client
extern "C"  __declspec(dllexport)
unsigned int ConstructInstance_v2()
{
  unsigned int MyInstanceID = NextInstanceID++;

  Clients[ MyInstanceID ] = std::shared_ptr< ViconDataStreamSDK::Core::VClient >( new ViconDataStreamSDK::Core::VClient() );
  return MyInstanceID;
}


// Destroy an instance of a Client
extern "C"  __declspec(dllexport)
void DestroyInstance_v2( unsigned int i_InstanceID )
{
  std::map< unsigned int, std::shared_ptr< ViconDataStreamSDK::Core::VClient > >::iterator It = Clients.find( i_InstanceID );
  if( It != Clients.end() )
  {
    Clients.erase( It );
  }
}

// Get the version of the Vicon Data Stream SDK
extern "C"  __declspec(dllexport)
void GetVersion_v2( unsigned int i_InstanceID, unsigned int *o_pMajor, unsigned int *o_pMinor, unsigned int *o_pPoint, unsigned int * o_pRevision )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    Clients[ i_InstanceID ]->GetVersion( *o_pMajor, *o_pMinor, *o_pPoint, *o_pRevision );
  }
  else
  {
    Clear( *o_pMajor );
    Clear( *o_pMinor );
    Clear( *o_pPoint );
  }
}

extern "C"  __declspec(dllexport) 
void Connect_v2( unsigned int i_InstanceID, const char* i_pHostname, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->Connect( 
      std::shared_ptr< ViconCGStreamClientSDK::ICGClient >( 
      ViconCGStreamClientSDK::ICGClient::CreateCGClient(), 
      std::bind( &ViconCGStreamClientSDK::ICGClient::Destroy, ph::_1 )), 
     CHECK_STRING( i_pHostname ) );
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void ConnectToMulticast_v2( unsigned int i_InstanceID, const char* i_pHostname, const char * i_pMulticastIP, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->ConnectToMulticast( 
      std::shared_ptr< ViconCGStreamClientSDK::ICGClient >( 
      ViconCGStreamClientSDK::ICGClient::CreateCGClient(), 
      std::bind( &ViconCGStreamClientSDK::ICGClient::Destroy, ph::_1 )), 
     CHECK_STRING( i_pHostname ),
     CHECK_STRING( i_pMulticastIP ) );
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void Disconnect_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->Disconnect();
  }
  else
  {
    Clear( *o_pResult );
  }
}


extern "C"  __declspec(dllexport) 
bool IsConnected_v2( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[ i_InstanceID ]->IsConnected();
  }
  else
  {
    return false;
  }
}

extern "C"  __declspec(dllexport) 
void StartTransmittingMulticast_v2( unsigned int   i_InstanceID,
                                    const char   * i_pServerIP,
                                    const char   * i_pMulticastIP,
                                    unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->StartTransmittingMulticast( CHECK_STRING( i_pServerIP ),
                                                                     CHECK_STRING( i_pMulticastIP ) );
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void StopTransmittingMulticast_v2( unsigned int   i_InstanceID,
                                   unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->StopTransmittingMulticast();
  }
  else
  {
    Clear( *o_pResult );
  }
}


extern "C"  __declspec(dllexport) 
void EnableSegmentData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->EnableSegmentData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void EnableLightweightSegmentData( unsigned int  i_InstanceID, unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->EnableLightweightSegmentData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void EnableMarkerData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->EnableMarkerData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void EnableUnlabeledMarkerData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->EnableUnlabeledMarkerData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec( dllexport )
void EnableMarkerRayData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[i_InstanceID]->EnableMarkerRayData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec( dllexport )
void EnableDeviceData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->EnableDeviceData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void EnableCentroidData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->EnableCentroidData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void DisableSegmentData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->DisableSegmentData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void DisableLightweightSegmentData( unsigned int i_InstanceID, unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->DisableLightweightSegmentData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void DisableMarkerData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->DisableMarkerData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void DisableUnlabeledMarkerData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->DisableUnlabeledMarkerData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec( dllexport )
void DisableMarkerRayData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[i_InstanceID]->DisableMarkerRayData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec( dllexport )
void DisableDeviceData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->DisableDeviceData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void DisableCentroidData_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->DisableCentroidData();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
bool IsSegmentDataEnabled_v2( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[ i_InstanceID ]->IsSegmentDataEnabled();
  }
  else
  {
    return false;
  }
}

extern "C"  __declspec(dllexport) 
bool IsLightweightSegmentDataEnabled( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[ i_InstanceID ]->IsLightweightSegmentDataEnabled();
  }
  else
  {
    return false;
  }

}

extern "C"  __declspec(dllexport) 
bool IsMarkerDataEnabled_v2( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[ i_InstanceID ]->IsMarkerDataEnabled();
  }
  else
  {
    return false;
  }
}

extern "C"  __declspec(dllexport) 
bool IsUnlabeledMarkerDataEnabled_v2( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[ i_InstanceID ]->IsUnlabeledMarkerDataEnabled();
  }
  else
  {
    return false;
  }
}

extern "C"  __declspec( dllexport )
bool IsMarkerRayDataEnabled_v2( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[i_InstanceID]->IsMarkerRayDataEnabled();
  }
  else
  {
    return false;
  }
}

extern "C"  __declspec( dllexport )
bool IsDeviceDataEnabled_v2( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[ i_InstanceID ]->IsDeviceDataEnabled();
  }
  else
  {
    return false;
  }
}

extern "C"  __declspec(dllexport) 
bool IsCentroidDataEnabled_v2( unsigned int i_InstanceID )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    return Clients[ i_InstanceID ]->IsCentroidDataEnabled();
  }
  else
  {
    return false;
  }
}

extern "C"  __declspec(dllexport) 

void SetBufferSize( unsigned int i_InstanceID,  unsigned int i_BufferSize )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    Clients[ i_InstanceID ]->SetBufferSize( i_BufferSize );
  }
}

extern "C"  __declspec(dllexport) 

void SetStreamMode_v2( unsigned int i_InstanceID, unsigned int i_Mode, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->SetStreamMode( static_cast< ViconDataStreamSDK::Core::StreamMode::Enum >( i_Mode ) );
  }
  else
  {
    Clear( *o_pResult );
  }
}

void SetApexDeviceFeedback_v2( unsigned int i_InstanceID, const char * i_pDeviceName, bool i_bOn, unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->SetApexDeviceFeedback( i_pDeviceName, i_bOn );
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void SetAxisMapping_v2( unsigned int i_InstanceID, unsigned int i_XAxis, unsigned int i_YAxis, unsigned int i_ZAxis, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->SetAxisMapping( static_cast< ViconDataStreamSDK::Core::Direction::Enum >( i_XAxis ),
                                                         static_cast< ViconDataStreamSDK::Core::Direction::Enum >( i_YAxis ),
                                                         static_cast< ViconDataStreamSDK::Core::Direction::Enum >( i_ZAxis ) );
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetAxisMapping_v2( unsigned int i_InstanceID, unsigned int *o_pXAxis, unsigned int *o_pYAxis, unsigned int *o_pZAxis )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    ViconDataStreamSDK::Core::Direction::Enum XAxis;
    ViconDataStreamSDK::Core::Direction::Enum YAxis;
    ViconDataStreamSDK::Core::Direction::Enum ZAxis;

    Clients[ i_InstanceID ]->GetAxisMapping( XAxis, YAxis, ZAxis );

    *o_pXAxis = static_cast< unsigned int >( XAxis );
    *o_pYAxis = static_cast< unsigned int >( YAxis );
    *o_pZAxis = static_cast< unsigned int >( ZAxis );
  }
  else
  {
    Clear( *o_pXAxis );
    Clear( *o_pYAxis );
    Clear( *o_pZAxis );
  }
}

extern "C"  __declspec(dllexport) 
void GetServerOrientation_v2( unsigned int i_InstanceID, unsigned int *o_pResult, unsigned int *o_pOrientation )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    ViconDataStreamSDK::Core::Result::Enum Result;
    ViconDataStreamSDK::Core::ServerOrientation::Enum Orientation;

    Result = Clients[ i_InstanceID ]->GetServerOrientation( Orientation );

    *o_pResult = static_cast< unsigned int >( Result );
    *o_pOrientation = static_cast< unsigned int >( Orientation );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pOrientation );
  }
}

extern "C"  __declspec(dllexport) 
void GetFrame_v2( unsigned int i_InstanceID, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetFrame();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetFrameNumber_v2( unsigned int i_InstanceID, unsigned int *o_pFrameNumber, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetFrameNumber( *o_pFrameNumber );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pFrameNumber );
  }
}

extern "C"  __declspec(dllexport) 
void GetTimecode_v2( unsigned int i_InstanceID, 
                     unsigned int *o_pHours, 
                     unsigned int *o_pMinutes, 
                     unsigned int *o_pSeconds, 
                     unsigned int *o_pFrames, 
                     unsigned int *o_pSubFrame, 
                     unsigned int *o_pFieldFlag,
                     unsigned int *o_ppStandard, 
                     unsigned int *o_pSubFramesPerFrame, 
                     unsigned int *o_pUserBits, 
                     unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    ViconDataStreamSDK::Core::TimecodeStandard::Enum Standard;
    bool                                             bFieldFlag;

    *o_pResult = Clients[ i_InstanceID ]->GetTimecode( *o_pHours,
                                                      *o_pMinutes,
                                                      *o_pSeconds,
                                                      *o_pFrames,
                                                      *o_pSubFrame,
                                                      bFieldFlag,
                                                      Standard,
                                                      *o_pSubFramesPerFrame,
                                                      *o_pUserBits );
    *o_pFieldFlag = static_cast< unsigned int >( bFieldFlag );
    *o_ppStandard = static_cast< unsigned int >( Standard );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pHours );
    Clear( *o_pMinutes );
    Clear( *o_pSeconds );
    Clear( *o_pFrames );
    Clear( *o_pSubFrame );
    Clear( *o_pFieldFlag );
    Clear( *o_ppStandard );
    Clear( *o_pSubFramesPerFrame );
    Clear( *o_pUserBits );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetFrameRate( unsigned int i_InstanceID, double * o_pFrameRate, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetFrameRate( *o_pFrameRate );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pFrameRate );
  }
}

extern "C"  __declspec(dllexport) 
void GetLatencySampleCount_v2( unsigned int   i_InstanceID, 
                               unsigned int *o_pCount, 
                               unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetLatencySampleCount( *o_pCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pCount );
  }
}

extern "C"  __declspec(dllexport) 
const char * GetLatencySampleName_v2( unsigned int   i_InstanceID, 
                                      unsigned int   i_OneBasedLatencySampleIndex, 
                                      unsigned int *o_pResult )
{
  static std::string SampleName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetLatencySampleName( i_OneBasedLatencySampleIndex - 1, SampleName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( SampleName );
  }

  return SampleName.c_str();
}

extern "C"  __declspec(dllexport) 
void GetLatencySampleValue_v2( unsigned int   i_InstanceID, 
                               const char   * i_pLatencySampleName,
                               double       *o_pLatency,
                               unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetLatencySampleValue( i_pLatencySampleName, *o_pLatency );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pLatency );
  }
}

extern "C"  __declspec(dllexport) 
void GetLatencyTotal_v2( unsigned int   i_InstanceID, 
                         double       *o_pLatency,
                         unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetLatencyTotal( *o_pLatency );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pLatency );
  }
}

extern "C"  __declspec(dllexport) 
void GetFrameRateCount( unsigned int   i_InstanceID, 
                        unsigned int *o_pCount, 
                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetFrameRateCount( *o_pCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pCount );
  }
}

extern "C"  __declspec(dllexport) 
const char * GetFrameRateName( unsigned int   i_InstanceID, 
                               unsigned int   i_OneBasedFrameRateIndex, 
                               unsigned int *o_pResult )
{
  static std::string SampleName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetFrameRateName( i_OneBasedFrameRateIndex - 1, SampleName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( SampleName );
  }

  return SampleName.c_str();
}

extern "C"  __declspec(dllexport) 
void GetFrameRateValue( unsigned int   i_InstanceID, 
                        const char   * i_pFrameRateName,
                        double       *o_pLatency,
                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetFrameRateValue( i_pFrameRateName, *o_pLatency );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pLatency );
  }
}

extern "C"  __declspec(dllexport) 
void GetSubjectCount_v2( unsigned int i_InstanceID, unsigned int *o_pSubjectCount, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSubjectCount( *o_pSubjectCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pSubjectCount );
  }
}

extern "C"  __declspec(dllexport) 
const char* GetSubjectName_v2( unsigned int i_InstanceID, unsigned int i_OneBasedSubjectIndex, unsigned int *o_pResult )
{
  static std::string SubjectName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSubjectName( i_OneBasedSubjectIndex - 1, SubjectName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( SubjectName );
  }

  return SubjectName.c_str();
}

extern "C"  __declspec(dllexport) 
const char* GetSubjectRootSegmentName_v2( unsigned int i_InstanceID, const char * i_pSubjectName, unsigned int *o_pResult )
{
  static std::string SegmentName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSubjectRootSegmentName( i_pSubjectName, SegmentName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( SegmentName );
  }

  return SegmentName.c_str();
}

extern "C"  __declspec(dllexport) 
void GetSegmentCount_v2( unsigned int i_InstanceID, const char * i_pSubjectName, unsigned int *o_pSegmentCount, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSegmentCount( i_pSubjectName, *o_pSegmentCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pSegmentCount );
  }
}

extern "C"  __declspec(dllexport) 
const char* GetSegmentName_v2( unsigned int i_InstanceID, const char * i_pSubjectName, unsigned int i_OneBasedSegmentIndex, unsigned int *o_pResult )
{
  static std::string SegmentName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSegmentName( i_pSubjectName, i_OneBasedSegmentIndex - 1, SegmentName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( SegmentName );
  }

  return SegmentName.c_str();
}

extern "C"  __declspec(dllexport) 
const char* GetSegmentParentName_v2( unsigned int i_InstanceID, const char * i_pSubjectName, const char * i_pSegmentName, unsigned int *o_pResult )
{
  static std::string SegmentName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSegmentParentName( i_pSubjectName, i_pSegmentName, SegmentName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( SegmentName );
  }

  return SegmentName.c_str();
}

extern "C"  __declspec(dllexport) 
void GetSegmentChildCount_v2( unsigned int i_InstanceID, const char * i_pSubjectName, const char * i_pSegmentName, unsigned int *o_pSegmentCount, unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSegmentChildCount( i_pSubjectName, i_pSegmentName, *o_pSegmentCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pSegmentCount );
  }
}

extern "C"  __declspec(dllexport) 
const char* GetSegmentChildName_v2( unsigned int i_InstanceID, const char * i_pSubjectName, const char * i_pSegmentName, unsigned int i_OneBasedSegmentIndex, unsigned int *o_pResult )
{
  static std::string SegmentName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetSegmentChildName( i_pSubjectName, i_pSegmentName, i_OneBasedSegmentIndex - 1, SegmentName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( SegmentName );
  }

  return SegmentName.c_str();
}

extern "C"  __declspec(dllexport) 
void GetSegmentStaticTranslation_v2( unsigned int   i_InstanceID, 
                                     const char   * i_pSubjectName, 
                                     const char   * i_pSegmentName, 
                                     double         o_pTranslation[ 3 ],
                                     unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentStaticTranslation( i_pSubjectName, 
                                                                      i_pSegmentName,
                                                                      _Translation );
    Copy( o_pTranslation, _Translation );
  }
  else
  {
    Clear< double, 3 >( o_pTranslation );
    Clear( *o_pResult );
  }
}


extern "C"  __declspec(dllexport) 
void GetSegmentStaticRotationHelical_v2( unsigned int   i_InstanceID, 
                                         const char   * i_pSubjectName, 
                                         const char   * i_pSegmentName, 
                                         double         o_pRotation[ 3 ],
                                         unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 3 ];

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentStaticRotationHelical( i_pSubjectName, 
                                                                          i_pSegmentName,
                                                                          _Rotation );
    Copy( o_pRotation, _Rotation );
  }
  else
  {
    Clear< double, 3 >( o_pRotation );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentStaticRotationMatrix_v2( unsigned int   i_InstanceID, 
                                        const char   * i_pSubjectName, 
                                        const char   * i_pSegmentName, 
                                        double         o_pRotation[ 9 ],
                                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 9 ];

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentStaticRotationMatrix( i_pSubjectName, 
                                                                         i_pSegmentName,
                                                                         _Rotation );
    Copy( o_pRotation, _Rotation );
  }
  else
  {
    Clear< double, 9 >( o_pRotation );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentStaticRotationQuaternion_v2( unsigned int   i_InstanceID, 
                                            const char   * i_pSubjectName, 
                                            const char   * i_pSegmentName, 
                                            double         o_pRotation[ 4 ],
                                            unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 4 ];

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentStaticRotationQuaternion( i_pSubjectName, 
                                                                             i_pSegmentName,
                                                                             _Rotation );
    Copy( o_pRotation, _Rotation );
  }
  else
  {
    Clear< double, 4 >( o_pRotation );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentStaticRotationEulerXYZ_v2( unsigned int   i_InstanceID, 
                                          const char   * i_pSubjectName, 
                                          const char   * i_pSegmentName, 
                                          double         o_pRotation[ 3 ],
                                          unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 3 ];

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentStaticRotationEulerXYZ( i_pSubjectName, 
                                                                           i_pSegmentName,
                                                                           _Rotation );
    Copy( o_pRotation, _Rotation );
  }
  else
  {
    Clear< double, 3 >( o_pRotation );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentGlobalTranslation_v2( unsigned int   i_InstanceID, 
                                     const char   * i_pSubjectName, 
                                     const char   * i_pSegmentName, 
                                     double         o_pTranslation[ 3 ], 
                                     unsigned int *o_pOccluded,
                                     unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentGlobalTranslation( i_pSubjectName, 
                                                                      i_pSegmentName,
                                                                      _Translation,
                                                                      _Occluded );
    Copy( o_pTranslation, _Translation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 3 >( o_pTranslation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}


extern "C"  __declspec(dllexport) 
void GetSegmentGlobalRotationHelical_v2( unsigned int   i_InstanceID, 
                                         const char   * i_pSubjectName, 
                                         const char   * i_pSegmentName, 
                                         double         o_pRotation[ 3 ], 
                                         unsigned int *o_pOccluded,
                                         unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 3 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentGlobalRotationHelical( i_pSubjectName, 
                                                                          i_pSegmentName,
                                                                          _Rotation,
                                                                          _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 3 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentGlobalRotationMatrix_v2( unsigned int   i_InstanceID, 
                                        const char   * i_pSubjectName, 
                                        const char   * i_pSegmentName, 
                                        double         o_pRotation[ 9 ], 
                                        unsigned int *o_pOccluded,
                                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 9 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentGlobalRotationMatrix( i_pSubjectName, 
                                                                         i_pSegmentName,
                                                                         _Rotation,
                                                                         _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 9 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentGlobalRotationQuaternion_v2( unsigned int   i_InstanceID, 
                                            const char   * i_pSubjectName, 
                                            const char   * i_pSegmentName, 
                                            double         o_pRotation[ 4 ], 
                                            unsigned int *o_pOccluded,
                                            unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 4 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentGlobalRotationQuaternion( i_pSubjectName, 
                                                                             i_pSegmentName,
                                                                             _Rotation,
                                                                             _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 4 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentGlobalRotationEulerXYZ_v2( unsigned int   i_InstanceID, 
                                          const char   * i_pSubjectName, 
                                          const char   * i_pSegmentName, 
                                          double         o_pRotation[ 3 ], 
                                          unsigned int *o_pOccluded,
                                          unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 3 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentGlobalRotationEulerXYZ( i_pSubjectName, 
                                                                           i_pSegmentName,
                                                                           _Rotation,
                                                                           _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 3 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentLocalTranslation_v2( unsigned int   i_InstanceID, 
                                    const char   * i_pSubjectName, 
                                    const char   * i_pSegmentName, 
                                    double         o_pTranslation[ 3 ], 
                                    unsigned int *o_pOccluded,
                                    unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentLocalTranslation( i_pSubjectName, 
                                                                     i_pSegmentName,
                                                                     _Translation,
                                                                     _Occluded );
    Copy( o_pTranslation, _Translation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 3 >( o_pTranslation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}


extern "C"  __declspec(dllexport) 
void GetSegmentLocalRotationHelical_v2( unsigned int   i_InstanceID, 
                                        const char   * i_pSubjectName, 
                                        const char   * i_pSegmentName, 
                                        double         o_pRotation[ 3 ], 
                                        unsigned int *o_pOccluded,
                                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 3 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentLocalRotationHelical( i_pSubjectName, 
                                                                         i_pSegmentName,
                                                                         _Rotation,
                                                                         _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 3 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentLocalRotationMatrix_v2( unsigned int   i_InstanceID, 
                                       const char   * i_pSubjectName, 
                                       const char   * i_pSegmentName, 
                                       double         o_pRotation[ 9 ], 
                                       unsigned int *o_pOccluded,
                                       unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 9 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentLocalRotationMatrix( i_pSubjectName, 
                                                                        i_pSegmentName,
                                                                        _Rotation,
                                                                        _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 9 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentLocalRotationQuaternion_v2( unsigned int   i_InstanceID, 
                                           const char   * i_pSubjectName, 
                                           const char   * i_pSegmentName, 
                                           double         o_pRotation[ 4 ], 
                                           unsigned int *o_pOccluded,
                                           unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 4 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentLocalRotationQuaternion( i_pSubjectName, 
                                                                            i_pSegmentName,
                                                                            _Rotation,
                                                                            _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 4 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec(dllexport) 
void GetSegmentLocalRotationEulerXYZ_v2( unsigned int   i_InstanceID, 
                                         const char   * i_pSubjectName, 
                                         const char   * i_pSegmentName, 
                                         double         o_pRotation[ 3 ], 
                                         unsigned int *o_pOccluded,
                                         unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Rotation[ 3 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetSegmentLocalRotationEulerXYZ( i_pSubjectName, 
                                                                          i_pSegmentName,
                                                                          _Rotation,
                                                                          _Occluded );
    Copy( o_pRotation, _Rotation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 3 >( o_pRotation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}


extern "C"  __declspec( dllexport )
void GetObjectQuality_v2( unsigned int   i_InstanceID,
const char   * i_pObjectName,
double *o_pQuality,
unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[i_InstanceID]->GetObjectQuality( i_pObjectName, *o_pQuality );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pQuality );
  }
}

extern "C"  __declspec( dllexport )
void GetMarkerCount_v2( unsigned int   i_InstanceID, 
                        const char   * i_pSubjectName, 
                        unsigned int *o_pMarkerCount, 
                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetMarkerCount( i_pSubjectName, *o_pMarkerCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pMarkerCount );
  }
}

extern "C"  __declspec(dllexport) 
const char* GetMarkerName_v2( unsigned int   i_InstanceID, 
                              const char   * i_pSubjectName, 
                              unsigned int   i_OneBasedMarkerIndex, 
                              unsigned int *o_pResult )
{
  static std::string MarkerName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetMarkerName( i_pSubjectName, i_OneBasedMarkerIndex - 1, MarkerName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( MarkerName );
  }

  return MarkerName.c_str();
}

extern "C"  __declspec(dllexport) 
const char* GetMarkerParentName_v2( unsigned int   i_InstanceID, 
                                    const char   * i_pSubjectName, 
                                    const char   * i_pMarkerName, 
                                    unsigned int *o_pResult )
{
  static std::string MarkerParentName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetMarkerParentName( i_pSubjectName, i_pMarkerName, MarkerParentName );
  }
  else
  {
    Clear( *o_pResult );
    Clear( MarkerParentName );
  }

  return MarkerParentName.c_str();
}

extern "C"  __declspec(dllexport) 
void GetMarkerGlobalTranslation_v2( unsigned int   i_InstanceID, 
                                    const char   * i_pSubjectName, 
                                    const char   * i_pMarkerName, 
                                    double         o_pTranslation[ 3 ], 
                                    unsigned int *o_pOccluded,
                                    unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];
    bool   _Occluded;

    *o_pResult = Clients[ i_InstanceID ]->GetMarkerGlobalTranslation( i_pSubjectName, 
                                                                      i_pMarkerName,
                                                                      _Translation,
                                                                      _Occluded );
    Copy( o_pTranslation, _Translation );
    *o_pOccluded = _Occluded;
  }
  else
  {
    Clear< double, 3 >( o_pTranslation );
    Clear( *o_pOccluded );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec( dllexport )
void GetMarkerRayContributionCount_v2( unsigned int   i_InstanceID,
                                    const char   * i_pSubjectName,
                                    const char   * i_pMarkerName,
                                    unsigned int * o_pContributionCount,
                                    unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[i_InstanceID]->GetMarkerRayAssignmentCount( i_pSubjectName,
      i_pMarkerName,
      *o_pContributionCount );
  }
  else
  {
    Clear( *o_pContributionCount );
    Clear( *o_pResult );
  }
}

extern "C"  __declspec( dllexport )
void GetMarkerRayContribution_v2( unsigned int   i_InstanceID,
                               const char   * i_pSubjectName,
                               const char   * i_pMarkerName,
                               unsigned int   i_OneBasedMarkerRayContributionIndex,
                               unsigned int * o_pCameraID,
                               unsigned int * o_pCentroidIndex,
                               unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[i_InstanceID]->GetMarkerRayAssignment( i_pSubjectName,
      i_pMarkerName,
      i_OneBasedMarkerRayContributionIndex - 1,
      *o_pCameraID,
      *o_pCentroidIndex);
  }
  else
  {
    Clear( *o_pCameraID );
    Clear( *o_pResult );
  }
}


extern "C"  __declspec(dllexport) 
void GetUnlabeledMarkerCount_v2( unsigned int   i_InstanceID, 
                                 unsigned int *o_pMarkerCount, 
                                 unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetUnlabeledMarkerCount( *o_pMarkerCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pMarkerCount );
  }
}

extern "C"  __declspec(dllexport) 
void GetUnlabeledMarkerGlobalTranslation_v2( unsigned int   i_InstanceID, 
                                             unsigned int   i_OneBasedMarkerIndex, 
                                             double         o_pTranslation[ 3 ], 
                                             unsigned int * o_pMarkerID,
                                             unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];
    *o_pResult = Clients[ i_InstanceID ]->GetUnlabeledMarkerGlobalTranslation( i_OneBasedMarkerIndex - 1, _Translation, *o_pMarkerID );
    Copy( o_pTranslation, _Translation );
  }
  else
  {
    Clear( *o_pResult );
    Clear< double, 3 >( o_pTranslation );
  }
}

extern "C"  __declspec(dllexport)
void GetLabeledMarkerCount_v2(unsigned int   i_InstanceID,
  unsigned int *o_pMarkerCount,
  unsigned int *o_pResult)
{
  if (IsValidInstance(i_InstanceID))
  {
    *o_pResult = Clients[i_InstanceID]->GetLabeledMarkerCount(*o_pMarkerCount);
  }
  else
  {
    Clear(*o_pResult);
    Clear(*o_pMarkerCount);
  }
}

extern "C"  __declspec(dllexport)
void GetLabeledMarkerGlobalTranslation_v2(unsigned int   i_InstanceID,
  unsigned int   i_OneBasedMarkerIndex,
  double         o_pTranslation[3],
  unsigned int * o_pMarkerID,
  unsigned int *o_pResult)
{
  if (IsValidInstance(i_InstanceID))
  {
    double _Translation[3];
    *o_pResult = Clients[i_InstanceID]->GetLabeledMarkerGlobalTranslation(i_OneBasedMarkerIndex - 1, _Translation, *o_pMarkerID );
    Copy(o_pTranslation, _Translation);
  }
  else
  {
    Clear(*o_pResult);
    Clear< double, 3 >(o_pTranslation);
  }
}

extern "C"  __declspec(dllexport)
void GetDeviceCount_v2( unsigned int   i_InstanceID, 
                        unsigned int *o_pDeviceCount, 
                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetDeviceCount( *o_pDeviceCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pDeviceCount );
  }
}

extern "C"  __declspec(dllexport) 
const char* GetDeviceName_v2( unsigned int   i_InstanceID, 
                              unsigned int   i_OneBasedDeviceIndex, 
                              unsigned int *o_pDeviceType,
                              unsigned int *o_pResult )
{
  static std::string DeviceName;

  if( IsValidInstance( i_InstanceID ) )
  {
    ViconDataStreamSDK::Core::DeviceType::Enum _DeviceType;
    *o_pResult = Clients[ i_InstanceID ]->GetDeviceName( i_OneBasedDeviceIndex - 1, DeviceName, _DeviceType );
    *o_pDeviceType = static_cast< unsigned int >( _DeviceType );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pDeviceType );
  }

  return DeviceName.c_str();
}

extern "C"  __declspec(dllexport) 
void GetDeviceOutputCount_v2( unsigned int   i_InstanceID, 
                              const char   * i_pDeviceName,
                              unsigned int *o_pDeviceOutputCount, 
                              unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetDeviceOutputCount( i_pDeviceName, *o_pDeviceOutputCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pDeviceOutputCount );
  }
}

extern "C"  __declspec(dllexport) 
const char* GetDeviceOutputName_v2( unsigned int   i_InstanceID, 
                                    const char   * i_pDeviceName,
                                    unsigned int   i_OneBasedDeviceOutputIndex, 
                                    unsigned int *o_pDeviceOutputUnit,
                                    unsigned int *o_pResult )
{
  static std::string DeviceOutputName;

  if( IsValidInstance( i_InstanceID ) )
  {
    ViconDataStreamSDK::Core::Unit::Enum _Unit;
    *o_pResult = Clients[ i_InstanceID ]->GetDeviceOutputName( i_pDeviceName, i_OneBasedDeviceOutputIndex - 1, DeviceOutputName, _Unit );
    *o_pDeviceOutputUnit = static_cast< unsigned int >( _Unit );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pDeviceOutputUnit );
  }

  return DeviceOutputName.c_str();
}

extern "C"  __declspec( dllexport )
const char* GetDeviceComponentOutputName_v2( unsigned int   i_InstanceID,
  const char   * i_pDeviceName,
  unsigned int   i_OneBasedDeviceOutputIndex,
  unsigned int *o_pDeviceOutputUnit,
  unsigned int *o_pResult )
{
  static std::string DeviceOutputName;
  static std::string DeviceComponentName;

  if ( IsValidInstance( i_InstanceID ) )
  {
    ViconDataStreamSDK::Core::Unit::Enum _Unit;
    *o_pResult = Clients[i_InstanceID]->GetDeviceOutputNameComponent( i_pDeviceName, i_OneBasedDeviceOutputIndex - 1, DeviceOutputName, DeviceComponentName, _Unit );
    *o_pDeviceOutputUnit = static_cast< unsigned int >( _Unit );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pDeviceOutputUnit );
  }

  return DeviceOutputName.c_str();
}

extern "C"  __declspec( dllexport )
const char* GetDeviceComponentName_v2( unsigned int   i_InstanceID,
  const char   * i_pDeviceName,
  unsigned int   i_OneBasedDeviceOutputIndex,
  unsigned int *o_pDeviceOutputUnit,
  unsigned int *o_pResult )
{
  static std::string DeviceOutputName;
  static std::string DeviceComponentName;

  if ( IsValidInstance( i_InstanceID ) )
  {
    ViconDataStreamSDK::Core::Unit::Enum _Unit;
    *o_pResult = Clients[i_InstanceID]->GetDeviceOutputNameComponent( i_pDeviceName, i_OneBasedDeviceOutputIndex - 1, DeviceOutputName, DeviceComponentName, _Unit );
    *o_pDeviceOutputUnit = static_cast< unsigned int >( _Unit );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pDeviceOutputUnit );
  }

  return DeviceComponentName.c_str();
}

extern "C"  __declspec(dllexport)
void GetDeviceOutputSubsamples_v2( unsigned int   i_InstanceID, 
                                   const char   * i_pDeviceName, 
                                   const char   * i_pDeviceOutputName, 
                                   unsigned int * o_pSubsamples, 
                                   unsigned int * o_pOccluded,
                                   unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    bool _Occluded;
    *o_pResult = Clients[ i_InstanceID ]->GetDeviceOutputSubsamples( i_pDeviceName, i_pDeviceOutputName, *o_pSubsamples, _Occluded );
    *o_pOccluded = static_cast< bool >( _Occluded );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pSubsamples );
    Clear( *o_pOccluded );
  }
}

extern "C"  __declspec( dllexport )
void GetDeviceOutputComponentSubsamples_v2( unsigned int   i_InstanceID,
  const char   * i_pDeviceName,
  const char   * i_pDeviceOutputName,
  const char   * i_pDeviceOutputComponentName,
  unsigned int * o_pSubsamples,
  unsigned int * o_pOccluded,
  unsigned int * o_pResult )
{
  if ( IsValidInstance( i_InstanceID ) )
  {
    bool _Occluded;
    *o_pResult = Clients[i_InstanceID]->GetDeviceOutputSubsamples( i_pDeviceName, i_pDeviceOutputName, i_pDeviceOutputComponentName, *o_pSubsamples, _Occluded );
    *o_pOccluded = static_cast< bool >( _Occluded );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pSubsamples );
    Clear( *o_pOccluded );
  }
}

extern "C"  __declspec(dllexport) 
void GetDeviceOutputValue_v2( unsigned int   i_InstanceID, 
                              const char   * i_pDeviceName, 
                              const char   * i_pDeviceOutputName, 
                              double       *o_pValue, 
                              unsigned int *o_pOccluded,
                              unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    bool _Occluded;
    *o_pResult = Clients[ i_InstanceID ]->GetDeviceOutputValue( i_pDeviceName, i_pDeviceOutputName, *o_pValue, _Occluded );
    *o_pOccluded = static_cast< bool >( _Occluded );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pValue );
    Clear( *o_pOccluded );
  }
}

extern "C"  __declspec( dllexport )
void GetDeviceOutputComponentValue_v2( unsigned int   i_InstanceID,
                                       const char   * i_pDeviceName,
                                       const char   * i_pDeviceOutputName,
                                       const char   * i_pDeviceOutputComponentName,
                                       double       *o_pValue,
                                       unsigned int *o_pOccluded,
                                       unsigned int *o_pResult )
{
  if ( IsValidInstance( i_InstanceID ) )
  {
    bool _Occluded;
    *o_pResult = Clients[i_InstanceID]->GetDeviceOutputValue( i_pDeviceName, i_pDeviceOutputName, i_pDeviceOutputComponentName, *o_pValue, _Occluded );
    *o_pOccluded = static_cast< bool >( _Occluded );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pValue );
    Clear( *o_pOccluded );
  }
}

extern "C"  __declspec(dllexport) 
void GetDeviceOutputSubsample_v2( unsigned int   i_InstanceID, 
                                  const char   * i_pDeviceName, 
                                  const char   * i_pDeviceOutputName, 
                                  unsigned int   i_pOneBasedSubsampleIndex,
                                  double       * o_pValue, 
                                  unsigned int * o_pOccluded,
                                  unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    bool _Occluded;
    *o_pResult = Clients[ i_InstanceID ]->GetDeviceOutputValue( i_pDeviceName, i_pDeviceOutputName, i_pOneBasedSubsampleIndex - 1, *o_pValue, _Occluded );
    *o_pOccluded = static_cast< bool >( _Occluded );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pValue );
    Clear( *o_pOccluded );
  }
}

extern "C"  __declspec( dllexport )
void GetDeviceOutputComponentSubsample_v2( unsigned int   i_InstanceID,
                                           const char   * i_pDeviceName,
                                           const char   * i_pDeviceOutputName,
                                           const char   * i_pDeviceOutputComponentName,
                                           unsigned int   i_pOneBasedSubsampleIndex,
                                           double       * o_pValue,
                                           unsigned int * o_pOccluded,
                                           unsigned int * o_pResult )
{
  if ( IsValidInstance( i_InstanceID ) )
  {
    bool _Occluded;
    *o_pResult = Clients[i_InstanceID]->GetDeviceOutputValue( i_pDeviceName, i_pDeviceOutputName, i_pDeviceOutputComponentName, i_pOneBasedSubsampleIndex - 1, *o_pValue, _Occluded );
    *o_pOccluded = static_cast< bool >( _Occluded );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pValue );
    Clear( *o_pOccluded );
  }
}
extern "C"  __declspec(dllexport) 
void GetForcePlateCount_v2( unsigned int   i_InstanceID, 
                            unsigned int *o_pDeviceCount, 
                            unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetForcePlateCount( *o_pDeviceCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pDeviceCount );
  }
}

extern "C"  __declspec(dllexport) 
void GetGlobalForceVector_v2( unsigned int   i_InstanceID, 
                              unsigned int   i_OneBasedMarkerIndex, 
                              double         o_pTranslation[ 3 ], 
                              unsigned int * o_pResult )
{
  GetGlobalForceVectorSubsample_v2( i_InstanceID, i_OneBasedMarkerIndex, 0, o_pTranslation, o_pResult );
}

extern "C"  __declspec(dllexport) 
void GetGlobalMomentVector_v2( unsigned int   i_InstanceID, 
                               unsigned int   i_OneBasedMarkerIndex, 
                               double         o_pTranslation[ 3 ], 
                               unsigned int * o_pResult )
{
  GetGlobalMomentVectorSubsample_v2( i_InstanceID, i_OneBasedMarkerIndex, 0, o_pTranslation, o_pResult );
}

extern "C"  __declspec(dllexport) 
void GetGlobalCentreOfPressure_v2( unsigned int   i_InstanceID, 
                                   unsigned int   i_OneBasedMarkerIndex, 
                                   double         o_pTranslation[ 3 ], 
                                   unsigned int * o_pResult )
{
  GetGlobalCentreOfPressureSubsample_v2( i_InstanceID, i_OneBasedMarkerIndex, 0, o_pTranslation, o_pResult );
}

extern "C"  __declspec(dllexport) 
void GetForcePlateSubsamples_v2( unsigned int   i_InstanceID, 
                                 unsigned int   i_OneBasedForcePlateIndex, 
                                 unsigned int * o_pForcePlateSubsamples, 
                                 unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    unsigned int PlateID;
    *o_pResult = Clients[ i_InstanceID ]->GetForcePlateID( i_OneBasedForcePlateIndex - 1, PlateID );
    if( ViconDataStreamSDK::Core::Result::Success == *o_pResult )
    {
      *o_pResult = Clients[ i_InstanceID ]->GetForcePlateSubsamples( PlateID, *o_pForcePlateSubsamples );
    }
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pForcePlateSubsamples );
  }
}

extern "C"  __declspec(dllexport) 
void GetGlobalForceVectorSubsample_v2( unsigned int   i_InstanceID, 
                                       unsigned int   i_OneBasedForcePlateIndex, 
                                       unsigned int   i_OneBasedForcePlateSubsample, 
                                       double         o_pTranslation[ 3 ], 
                                       unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];
    unsigned int PlateID;
    *o_pResult = Clients[ i_InstanceID ]->GetForcePlateID( i_OneBasedForcePlateIndex - 1, PlateID );
    if( ViconDataStreamSDK::Core::Result::Success == *o_pResult )
    {
      *o_pResult = Clients[ i_InstanceID ]->GetGlobalForceVectorAtSample( PlateID, i_OneBasedForcePlateSubsample - 1, _Translation );
      Copy( o_pTranslation, _Translation );
    }
    else
    {
      Clear< double, 3 >( o_pTranslation );
    }
  }
  else
  {
    Clear( *o_pResult );
    Clear< double, 3 >( o_pTranslation );
  }
}

extern "C"  __declspec(dllexport) 
void GetGlobalMomentVectorSubsample_v2( unsigned int   i_InstanceID, 
                                        unsigned int   i_OneBasedForcePlateIndex, 
                                        unsigned int   i_OneBasedForcePlateSubsample, 
                                        double         o_pTranslation[ 3 ], 
                                        unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];
    unsigned int PlateID;
    *o_pResult = Clients[ i_InstanceID ]->GetForcePlateID( i_OneBasedForcePlateIndex - 1, PlateID );
    if( ViconDataStreamSDK::Core::Result::Success == *o_pResult )
    {
      *o_pResult = Clients[ i_InstanceID ]->GetGlobalMomentVectorAtSample( PlateID, i_OneBasedForcePlateSubsample - 1, _Translation );
      Copy( o_pTranslation, _Translation );
    }
    else
    {
      Clear< double, 3 >( o_pTranslation );
    }
  }
  else
  {
    Clear( *o_pResult );
    Clear< double, 3 >( o_pTranslation );
  }
}

extern "C"  __declspec(dllexport) 
void GetGlobalCentreOfPressureSubsample_v2( unsigned int   i_InstanceID, 
                                            unsigned int   i_OneBasedForcePlateIndex, 
                                            unsigned int   i_OneBasedForcePlateSubsample, 
                                            double         o_pTranslation[ 3 ], 
                                            unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Translation[ 3 ];
    unsigned int PlateID;
    *o_pResult = Clients[ i_InstanceID ]->GetForcePlateID( i_OneBasedForcePlateIndex - 1, PlateID );
    if( ViconDataStreamSDK::Core::Result::Success == *o_pResult )
    {
      *o_pResult = Clients[ i_InstanceID ]->GetGlobalCentreOfPressureAtSample( PlateID, i_OneBasedForcePlateSubsample - 1, _Translation );
      Copy( o_pTranslation, _Translation );
    }
    else
    {
      Clear< double, 3 >( o_pTranslation );
    }
  }
  else
  {
    Clear( *o_pResult );
    Clear< double, 3 >( o_pTranslation );
  }
}

extern "C"  __declspec(dllexport) 
void GetEyeTrackerCount_v2( unsigned int  i_InstanceID, 
                            unsigned int *o_pEyeTrackerCount, 
                            unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetEyeTrackerCount( *o_pEyeTrackerCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pEyeTrackerCount );
  }
}

extern "C"  __declspec(dllexport) 
void GetEyeTrackerGlobalPosition_v2( unsigned int   i_InstanceID, 
                                     unsigned int   i_OneBasedEyeTrackerIndex, 
                                     double         o_pPosition[ 3 ], 
                                     unsigned int * o_pOccluded,
                                     unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Position[ 3 ];
    unsigned int _EyeTrackerID;
    bool _Occluded;
    *o_pResult = Clients[ i_InstanceID ]->GetEyeTrackerID( i_OneBasedEyeTrackerIndex - 1, _EyeTrackerID );
    if( ViconDataStreamSDK::Core::Result::Success == *o_pResult )
    {
      *o_pResult = Clients[ i_InstanceID ]->GetEyeTrackerGlobalPosition( _EyeTrackerID, _Position, _Occluded );
      Copy( o_pPosition, _Position );
      *o_pOccluded = static_cast< bool >( _Occluded );
      return;
    }
  }

  Clear( *o_pResult );
  Clear< double, 3 >( o_pPosition );
  Clear( *o_pOccluded );
}

extern "C"  __declspec(dllexport) 
void GetEyeTrackerGlobalGazeVector_v2( unsigned int   i_InstanceID, 
                                       unsigned int   i_OneBasedEyeTrackerIndex, 
                                       double         o_pGazeVector[ 3 ], 
                                       unsigned int * o_pOccluded,
                                       unsigned int * o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _GazeVector[ 3 ];
    unsigned int _EyeTrackerID;
    bool _Occluded;
    *o_pResult = Clients[ i_InstanceID ]->GetEyeTrackerID( i_OneBasedEyeTrackerIndex - 1, _EyeTrackerID );
    if( ViconDataStreamSDK::Core::Result::Success == *o_pResult )
    {
      *o_pResult = Clients[ i_InstanceID ]->GetEyeTrackerGlobalGazeVector( _EyeTrackerID, _GazeVector, _Occluded );
      Copy( o_pGazeVector, _GazeVector );
      *o_pOccluded = static_cast< bool >( _Occluded );
      return;
    }
  }

  Clear( *o_pResult );
  Clear< double, 3 >( o_pGazeVector );
  Clear( *o_pOccluded );
}

extern "C"  __declspec(dllexport)
void GetCameraCount_v2( unsigned int  i_InstanceID, 
                        unsigned int *o_pCameraCount, 
                        unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetCameraCount( *o_pCameraCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pCameraCount );
  }
}

extern "C"  __declspec(dllexport) 
const char* GetCameraName_v2( unsigned int  i_InstanceID, 
                              unsigned int  i_OneBasedCameraIndex, 
                              unsigned int *o_pResult )
{
  static std::string CameraName;

  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetCameraName( i_OneBasedCameraIndex - 1, CameraName );
  }
  else
  {
    Clear( *o_pResult );
  }

  return CameraName.c_str();
}

extern "C"  __declspec(dllexport)
void GetCameraId_v2(unsigned int  i_InstanceID,
  const char   * i_pCameraName,
  unsigned int *o_pId,
  unsigned int *o_pResult)
{
  if (IsValidInstance(i_InstanceID))
  {
    *o_pResult = Clients[i_InstanceID]->GetCameraID(i_pCameraName, *o_pId );
  }
  else
  {
    Clear(*o_pId);
    Clear(*o_pResult);
  }
}

extern "C"  __declspec(dllexport)
void GetCameraUserId_v2(unsigned int  i_InstanceID,
  const char   * i_pCameraName,
  unsigned int * o_pUserId,
  unsigned int *o_pResult)
{
  if (IsValidInstance(i_InstanceID))
  {
    *o_pResult = Clients[i_InstanceID]->GetCameraUserID(i_pCameraName, *o_pUserId);
  }
  else
  {
    Clear(*o_pUserId);
    Clear(*o_pResult);
  }
}

extern "C"  __declspec(dllexport)
const char* GetCameraType_v2(unsigned int  i_InstanceID,
  const char   * i_pCameraName,
  unsigned int *o_pResult)
{
  static std::string CameraType;
  
  if (IsValidInstance(i_InstanceID))
  {
    *o_pResult = Clients[i_InstanceID]->GetCameraType(i_pCameraName, CameraType);
  }
  else
  {
    Clear(*o_pResult);
  }

  return CameraType.c_str();
}

extern "C"  __declspec(dllexport)
const char* GetCameraDisplayName_v2(unsigned int  i_InstanceID,
  const char   * i_pCameraName,
  unsigned int *o_pResult)
{
  static std::string CameraDisplayName;

  if (IsValidInstance(i_InstanceID))
  {
    *o_pResult = Clients[i_InstanceID]->GetCameraType(i_pCameraName, CameraDisplayName);
  }
  else
  {
    Clear(*o_pResult);
  }

  return CameraDisplayName.c_str();
}

extern "C"  __declspec(dllexport)
void GetCameraResolution_v2(unsigned int  i_InstanceID,
  const char   * i_pCameraName,
  unsigned int * o_pResolutionX,
  unsigned int * o_pResolutionY,
  unsigned int *o_pResult)
{
  if (IsValidInstance(i_InstanceID))
  {
    *o_pResult = Clients[i_InstanceID]->GetCameraResolution(i_pCameraName, *o_pResolutionX, *o_pResolutionY);
  }
  else
  {
    Clear(*o_pResult);
    Clear(*o_pResolutionX);
    Clear(*o_pResolutionY);
  }
}

extern "C"  __declspec(dllexport)
void GetIsVideoCamera_v2(unsigned int  i_InstanceID,
  const char   * i_pCameraName,
  unsigned int * o_pIsVideoCamera,
  unsigned int *o_pResult)
{
  if (IsValidInstance(i_InstanceID))
  {
    bool _IsVideoCamera;
    *o_pResult = Clients[i_InstanceID]->GetIsVideoCamera(i_pCameraName, _IsVideoCamera);
    *o_pIsVideoCamera = static_cast< unsigned int >(_IsVideoCamera);
  }
  else
  {
    Clear(*o_pResult);
    Clear(*o_pIsVideoCamera);
  }
}

extern "C"  __declspec(dllexport)
void GetCentroidCount_v2( unsigned int  i_InstanceID, 
                          const char*   i_pCameraName,
                          unsigned int *o_pCentroidCount, 
                          unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[ i_InstanceID ]->GetCentroidCount( i_pCameraName, *o_pCentroidCount );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pCentroidCount );
  }
}

extern "C"  __declspec(dllexport)
void GetCentroidPosition_v2( unsigned int  i_InstanceID, 
                             const char*   i_pCameraName,
                             unsigned int  i_OneBasedCentroidIndex,
                             double        o_pPosition[ 2 ],
                             double       *o_pRadius,
//                             double       *o_pAccuracy,
                             unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    double _Position[ 2 ];
    *o_pResult = Clients[ i_InstanceID ]->GetCentroidPosition( i_pCameraName, i_OneBasedCentroidIndex-1, _Position, *o_pRadius /*, *o_pAccuracy */ );
    Copy( o_pPosition, _Position );
  }
  else
  {
    Clear( *o_pResult );
    Clear< double, 2 >( o_pPosition );
    Clear( *o_pRadius );
//    Clear( *o_pAccuracy );
  }
}

extern "C"  __declspec( dllexport )
void GetCentroidWeight_v2( unsigned int  i_InstanceID,
const char*   i_pCameraName,
unsigned int  i_OneBasedCentroidIndex,
double       *o_pWeight,
unsigned int *o_pResult )
{
  if( IsValidInstance( i_InstanceID ) )
  {
    *o_pResult = Clients[i_InstanceID]->GetCentroidWeight( i_pCameraName, i_OneBasedCentroidIndex - 1, *o_pWeight );
  }
  else
  {
    Clear( *o_pResult );
    Clear( *o_pWeight );
  }
}

extern "C" __declspec( dllexport )
void ClearSubjectFilter( unsigned int  i_InstanceID,
                         unsigned int * o_pResult )
{
  if (IsValidInstance( i_InstanceID ))
  {
    *o_pResult = Clients[i_InstanceID]->ClearSubjectFilter();
  }
  else
  {
    Clear( *o_pResult );
  }
}

extern "C" __declspec(dllexport)
void AddToSubjectFilter( unsigned int  i_InstanceID,
                         const char * i_pSubjectName,
                         unsigned int * o_pResult )
{
  if (IsValidInstance( i_InstanceID ))
  {
    *o_pResult = Clients[i_InstanceID]->AddToSubjectFilter( i_pSubjectName );
  }
  else
  {
    Clear( *o_pResult );
  }
}
