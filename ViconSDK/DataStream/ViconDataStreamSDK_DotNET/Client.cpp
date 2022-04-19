
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
#include <ViconDataStreamSDK_CPP/DataStreamClient.h>
#include <ViconDataStreamSDK_CPP/DataStreamRetimingClient.h>
#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

namespace ViconDataStreamSDK
{
namespace DotNET
{
  ///@private
  public enum class ServerOrientation
  {
    Unknown,
    YUp,
    ZUp
  };

  ///@private
  public enum class Direction
  {
    Up,
    Down,
    Left,
    Right,
    Forward,
    Backward
  };

  ///@private
  public enum class StreamMode
  {
    ClientPull,
    ClientPullPreFetch,
    ServerPush
  };

  ///@private
  public enum class TimecodeStandard
  {
    None,
    PAL,
    NTSC,
    NTSCDrop,
    Film,
    NTSCFilm,
    ATSC
  };

  ///@private
  public enum class DeviceType
  {
    Unknown,
    ForcePlate,
    EyeTracker
  };

  ///@private
  public enum class Unit
  {
    Unknown,
    Volt,
    Newton,
    NewtonMeter,
    Meter,
    Kilogram,
    Second,
    Ampere,
    Kelvin,
    Mole,
    Candela,
    Radian,
    Steradian,
    MeterSquared,
    MeterCubed,
    MeterPerSecond,
    MeterPerSecondSquared,
    RadianPerSecond,
    RadianPerSecondSquared,
    Hertz,
    Joule,
    Watt,
    Pascal,
    Lumen,
    Lux,
    Coulomb,
    Ohm,
    Farad,
    Weber,
    Tesla,
    Henry,
    Siemens,
    Becquerel,
    Gray,
    Sievert,
    Katal
  };

  ///@private
  public enum class Result
  {
    Unknown,
    NotImplemented,
    Success,
    InvalidHostName,
    InvalidMulticastIP,
    ClientAlreadyConnected,
    ClientConnectionFailed,
    ServerAlreadyTransmittingMulticast,
    ServerNotTransmittingMulticast,
    NotConnected,
    NoFrame,
    InvalidIndex,
    InvalidCameraName,
    InvalidSubjectName,
    InvalidSegmentName,
    InvalidMarkerName,
    InvalidDeviceName,
    InvalidDeviceOutputName,
    InvalidLatencySampleName,
    CoLinearAxes,
    LeftHandedAxes,
    HapticAlreadySet,
    EarlyDataRequested,
    LateDataRequested,
    InvalidOperation,
    NotSupported,
    ConfigurationFailed,
    NotPresent
  };

  ///@private
  public ref class Output_GetVersion
  {
  public:
    unsigned int Major;
    unsigned int Minor;
    unsigned int Point;
    unsigned int Revision;
  };

  ///@private
  public ref class Output_Connect
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_ConnectToMulticast
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_Disconnect
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_IsConnected
  {
  public:
    bool Connected;
  };

  ///@private
  public ref class Output_StartTransmittingMulticast
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_StopTransmittingMulticast
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableSegmentData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableLightweightSegmentData
  {
  public:
    Result Result;
  };
  ///@private
  public ref class Output_EnableMarkerData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableUnlabeledMarkerData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableMarkerRayData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableDeviceData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableCentroidData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableGreyscaleData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableVideoData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_EnableDebugData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableSegmentData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableLightweightSegmentData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableMarkerData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableUnlabeledMarkerData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableMarkerRayData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableDeviceData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableCentroidData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableGreyscaleData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableVideoData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_DisableDebugData
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_IsSegmentDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsLightweightSegmentDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsMarkerDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsUnlabeledMarkerDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsMarkerRayDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsDeviceDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsCentroidDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsGreyscaleDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsVideoDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_IsDebugDataEnabled
  {
  public:
    bool Enabled;
  };

  ///@private
  public ref class Output_SetStreamMode
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_SetApexDeviceFeedback
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_SetAxisMapping
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_GetAxisMapping
  {
  public:
    Direction XAxis;
    Direction YAxis;
    Direction ZAxis;
  };

  ///@private
  public ref class Output_GetServerOrientation
  {
  public:
    Result Result;
    ServerOrientation Orientation;
  };

  ///@private
  public ref class Output_GetFrame
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_GetFrameNumber
  {
  public:
    Result       Result;
    unsigned int FrameNumber;
  };

  ///@private
  public ref class Output_GetTimecode
  {
  public:
    Result           Result;
    unsigned int     Hours;
    unsigned int     Minutes;
    unsigned int     Seconds;
    unsigned int     Frames;
    unsigned int     SubFrame;
    bool             FieldFlag;
    TimecodeStandard Standard;
    unsigned int     SubFramesPerFrame;
    unsigned int     UserBits;
  };

  ///@private
  public ref class Output_GetFrameRate
  {
  public:
    Result       Result;
    double FrameRateHz;
  };

  ///@private
  public ref class Output_GetLatencySampleCount
  {
  public:
    Result       Result;
    unsigned int Count;
  };

  ///@private
  public ref class Output_GetLatencySampleName
  {
  public:
    Result  Result;
    String^ Name;
  };

  ///@private
  public ref class Output_GetLatencySampleValue
  {
  public:
    Result Result;
    double Value;
  };

  ///@private
  public ref class Output_GetLatencyTotal
  {
  public:
    Result Result;
    double Total;
  };

  ///@private
  public ref class Output_GetHardwareFrameNumber
  {
  public:
    Result Result;
    unsigned int HardwareFrameNumber;
  };
  
  ///@private
  public ref class Output_GetFrameRateCount
  {
  public:
    Result       Result;
    unsigned int Count;
  };

  ///@private
  public ref class Output_GetFrameRateName
  {
  public:
    Result  Result;
    String^ Name;
  };

  ///@private
  public ref class Output_GetFrameRateValue
  {
  public:
    Result Result;
    double Value;
  };

  ///@private
  public ref class Output_GetSubjectCount
  {
  public:
    Result       Result;
    unsigned int SubjectCount;
  };

  ///@private
  public ref class Output_GetSubjectName
  {
  public:
    Result     Result;
    String^    SubjectName;
  };

  ///@private
  public ref class Output_GetSubjectRootSegmentName
  {
  public:
    Result     Result;
    String^    SegmentName;
  };

  ///@private
  public ref class Output_GetSegmentCount
  {
  public:
    Result       Result;
    unsigned int SegmentCount;
  };

  ///@private
  public ref class Output_GetSegmentName
  {
  public:
    Result  Result;
    String^ SegmentName;
  };

  ///@private
  public ref class Output_GetSegmentChildCount
  {
  public:
    Result       Result;
    unsigned int SegmentCount;
  };

  ///@private
  public ref class Output_GetSegmentChildName
  {
  public:
    Result  Result;
    String^ SegmentName;
  };

  ///@private
  public ref class Output_GetSegmentParentName
  {
  public:
    Result  Result;
    String^ SegmentName;
  };

  ///@private
  public ref class Output_GetSegmentGlobalTranslation
  {
  public:
    Result           Result;
    array< double >^ Translation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentGlobalRotationHelical
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentGlobalRotationMatrix
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentGlobalRotationQuaternion
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentGlobalRotationEulerXYZ
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentStaticTranslation
  {
  public:
    Result           Result;
    array< double >^ Translation;
  };

  ///@private
  public ref class Output_GetSegmentStaticRotationHelical
  {
  public:
    Result           Result;
    array< double >^ Rotation;
  };

  ///@private
  public ref class Output_GetSegmentStaticRotationMatrix
  {
  public:
    Result           Result;
    array< double >^ Rotation;
  };

  ///@private
  public ref class Output_GetSegmentStaticRotationQuaternion
  {
  public:
    Result           Result;
    array< double >^ Rotation;
  };

  ///@private
  public ref class Output_GetSegmentStaticRotationEulerXYZ
  {
  public:
    Result           Result;
    array< double >^ Rotation;
  };

  ///@private
  public ref class Output_GetSegmentStaticScale
  {
  public:
    Result           Result;
    array< double >^ Scale;
  };
  ///@private
  public ref class Output_GetSegmentLocalTranslation
  {
  public:
    Result           Result;
    array< double >^ Translation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentLocalRotationHelical
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentLocalRotationMatrix
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentLocalRotationQuaternion
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetSegmentLocalRotationEulerXYZ
  {
  public:
    Result           Result;
    array< double >^ Rotation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetObjectQuality
  {
  public:
    Result       Result;
    double       Quality;
  };

  ///@private
  public ref class Output_GetMarkerCount
  {
  public:
    Result       Result;
    unsigned int MarkerCount;
  };

  ///@private
  public ref class Output_GetMarkerName
  {
  public:
    Result  Result;
    String^ MarkerName;
  };

  ///@private
  public ref class Output_GetMarkerParentName
  {
  public:
    Result  Result;
    String^ SegmentName;
  };

  ///@private
  public ref class Output_GetMarkerGlobalTranslation
  {
  public:
    Result           Result;
    array< double >^ Translation;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetMarkerRayContributionCount
  {
  public:
    Result           Result;
    unsigned int     RayContributionsCount;
  };

  ///@private
  public ref class Output_GetMarkerRayContribution
  {
  public:
    Result           Result;
    unsigned int     CameraID;
    unsigned int     CentroidIndex;
  };

  ///@private
  public ref class Output_GetUnlabeledMarkerCount
  {
  public:
    Result       Result;
    unsigned int MarkerCount;
  };

  ///@private
  public ref class Output_GetUnlabeledMarkerGlobalTranslation
  {
  public:
    Result           Result;
    array< double >^ Translation;
    unsigned int     MarkerID;
  };

  ///@private
  public ref class Output_GetLabeledMarkerCount
  {
  public:
    Result       Result;
    unsigned int MarkerCount;
  };

  ///@private
  public ref class Output_GetLabeledMarkerGlobalTranslation
  {
  public:
    Result           Result;
    array< double >^ Translation;
    unsigned int     MarkerID;
  };

  ///@private
  public ref class Output_GetDeviceCount
  {
  public:
    Result       Result;
    unsigned int DeviceCount;
  };

  ///@private
  public ref class Output_GetDeviceName
  {
  public:
    Result     Result;
    String^    DeviceName;
    DeviceType DeviceType;
  };

  ///@private
  public ref class Output_GetDeviceOutputCount
  {
  public:
    Result       Result;
    unsigned int DeviceOutputCount;
  };

  ///@private
  public ref class Output_GetDeviceOutputName
  {
  public:
    Result  Result;
    String^ DeviceOutputName;
    Unit    DeviceOutputUnit;
  };

  ///@private
  public ref class Output_GetDeviceOutputComponentName
  {
  public:
    Result  Result;
    String^ DeviceOutputName;
    String^ DeviceOutputComponentName;
    Unit    DeviceOutputUnit;
  };

  ///@private
  public ref class Output_GetDeviceOutputSubsamples
  {
  public:
    Result       Result;
    unsigned int DeviceOutputSubsamples;
    bool         Occluded;
  };

  ///@private
  public ref class Output_GetDeviceOutputValue
  {
  public:
    Result Result;
    double Value;
    bool   Occluded;
  };

  ///@private
  public ref class Output_GetForcePlateCount
  {
  public:
    Result       Result;
    unsigned int ForcePlateCount;
  };

  ///@private
  public ref class Output_GetGlobalForceVector
  {
  public:
    Result           Result;
    array< double >^ ForceVector;
  };

  ///@private
  public ref class Output_GetGlobalMomentVector
  {
  public:
    Result           Result;
    array< double >^ MomentVector;
  };

  ///@private
  public ref class Output_GetGlobalCentreOfPressure
  {
  public:
    Result           Result;
    array< double >^ CentreOfPressure;
  };

  ///@private
  public ref class Output_GetForcePlateSubsamples
  {
  public:
    Result       Result;
    unsigned int ForcePlateSubsamples;
  };


  ///@private
  public ref class Output_GetEyeTrackerCount
  {
  public:
    Result       Result;
    unsigned int EyeTrackerCount;
  };

  ///@private
  public ref class Output_GetEyeTrackerGlobalPosition
  {
  public:
    Result           Result;
    array< double >^ Position;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetEyeTrackerGlobalGazeVector
  {
  public:
    Result           Result;
    array< double >^ GazeVector;
    bool             Occluded;
  };

  ///@private
  public ref class Output_GetCameraCount
  {
  public:
    Result Result;
    unsigned int CameraCount;
  };

  ///@private
  public ref class Output_GetCameraName
  {
  public:
    Result  Result;
    String^ CameraName;
  };

  ///@private
  public ref class  Output_GetCameraId
  {
  public:
    Result Result;
    unsigned int CameraId;
  };

  ///@private
  public ref class  Output_GetCameraUserId
  {
  public:
    Result Result;
    unsigned int CameraUserId;
  };

  ///@private
  public ref class  Output_GetCameraType
  {
  public:
    Result     Result;
    String^    CameraType;
  };

  ///@private
  public ref class  Output_GetCameraDisplayName
  {
  public:
    Result     Result;
    String^    CameraDisplayName;
  };

  ///@private
  public ref class  Output_GetCameraResolution
  {
  public:
    Result Result;
    unsigned int ResolutionX;
    unsigned int ResolutionY;
  };

  ///@private
  public ref class  Output_GetIsVideoCamera
  {
  public:
    Result Result;
    bool IsVideoCamera;
  };

  ///@private
  public ref class  Output_GetCameraSensorMode
  {
  public:
    Result Result;
    String^ SensorMode;
  };

  ///@private
  public ref class  Output_GetCameraWindowSize
  {
  public:
    Result Result;
    unsigned int WindowStartX;
    unsigned int WindowStartY;
    unsigned int WindowWidth;
    unsigned int WindowHeight;
  };

  ///@private
  public ref class Output_GetCentroidCount
  {
  public:
    Result Result;
    unsigned int CentroidCount;
  };

  ///@private
  public ref class Output_GetCentroidPosition
  {
  public:
    Result Result;
    array< double >^ CentroidPosition;
    double Radius;
    double Accuracy;
  };

  ///@private
  public ref class Output_GetCentroidWeight
  {
  public:
    Result Result;
    double Weight;
  };

  ///@private
  public ref class  Output_GetGreyscaleBlobCount
  {
  public:
    Result Result;
    unsigned int BlobCount;
  };

  ///@private
  public ref class  Output_GetGreyscaleBlobSubsampleInfo
  {
  public:
    Result Result;
    unsigned int TwiceOffsetX;
    unsigned int TwiceOffsetY;
    unsigned int SensorPixelsPerImagePixelX;
    unsigned int SensorPixelsPerImagePixelY;
  };

  ///@private
  public ref class  Output_GetGreyscaleBlob
  {
  public:
    Result Result;
    List< unsigned int >^ BlobLinePositionsX;
    List< unsigned int >^ BlobLinePositionsY;
    List< List< unsigned char >^ >^ BlobLinePixelValues;
  };

  ///@private
  public ref class Output_GetVideoFrame
  {
  public:
    Result Result;

    enum class EFormat { ENoVideo = 0, EMono8, EBayerRG8, EBayerGB8, EBayerGR8, EBayerBG8, ERGB888, EBGR888 };

    unsigned int m_FrameID;
    unsigned short m_Width;
    unsigned short m_Height;
    unsigned int m_Format;
    List< unsigned char >^ m_Data;
  };

  ///@private
  public ref class Output_SetCameraFilter
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_ClearSubjectFilter
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_AddToSubjectFilter
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_UpdateFrame
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_WaitForFrame
  {
  public:
    Result Result;
  };

  ///@private
  public ref class Output_ConfigureWireless
  {
  public:
    Result Result;
    String ^ Error;
  };

  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::Direction::Enum
  ///@private
  ViconDataStreamSDK::CPP::Direction::Enum Adapt(ViconDataStreamSDK::DotNET::Direction i_Direction)
  {
    switch( i_Direction )
    {
    default:
    case ViconDataStreamSDK::DotNET::Direction::Up       : return ViconDataStreamSDK::CPP::Direction::Up;
    case ViconDataStreamSDK::DotNET::Direction::Down     : return ViconDataStreamSDK::CPP::Direction::Down;
    case ViconDataStreamSDK::DotNET::Direction::Left     : return ViconDataStreamSDK::CPP::Direction::Left;
    case ViconDataStreamSDK::DotNET::Direction::Right    : return ViconDataStreamSDK::CPP::Direction::Right;
    case ViconDataStreamSDK::DotNET::Direction::Forward  : return ViconDataStreamSDK::CPP::Direction::Forward;
    case ViconDataStreamSDK::DotNET::Direction::Backward : return ViconDataStreamSDK::CPP::Direction::Backward;
    }
  }

  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::Direction::Enum
  ///@private
  ViconDataStreamSDK::DotNET::Direction Adapt(ViconDataStreamSDK::CPP::Direction::Enum i_Direction)
  {
    switch( i_Direction )
    {
    default:
    case ViconDataStreamSDK::CPP::Direction::Up       : return ViconDataStreamSDK::DotNET::Direction::Up;
    case ViconDataStreamSDK::CPP::Direction::Down     : return ViconDataStreamSDK::DotNET::Direction::Down;
    case ViconDataStreamSDK::CPP::Direction::Left     : return ViconDataStreamSDK::DotNET::Direction::Left;
    case ViconDataStreamSDK::CPP::Direction::Right    : return ViconDataStreamSDK::DotNET::Direction::Right;
    case ViconDataStreamSDK::CPP::Direction::Forward  : return ViconDataStreamSDK::DotNET::Direction::Forward;
    case ViconDataStreamSDK::CPP::Direction::Backward : return ViconDataStreamSDK::DotNET::Direction::Backward;
    }
  }

  ///@private
  ViconDataStreamSDK::DotNET::ServerOrientation Adapt(ViconDataStreamSDK::CPP::ServerOrientation::Enum i_Orientation)
  {
    switch( i_Orientation )
    {
    default:
    case ViconDataStreamSDK::CPP::ServerOrientation::Unknown   : return ViconDataStreamSDK::DotNET::ServerOrientation::Unknown;
    case ViconDataStreamSDK::CPP::ServerOrientation::YUp       : return ViconDataStreamSDK::DotNET::ServerOrientation::YUp;
    case ViconDataStreamSDK::CPP::ServerOrientation::ZUp       : return ViconDataStreamSDK::DotNET::ServerOrientation::ZUp;
    }
  }


  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::StreamMode::Enum
  ///@private
  ViconDataStreamSDK::CPP::StreamMode::Enum Adapt(ViconDataStreamSDK::DotNET::StreamMode i_Mode)
  {
    switch( i_Mode )
    {
    default:
    case ViconDataStreamSDK::DotNET::StreamMode::ClientPull        : return ViconDataStreamSDK::CPP::StreamMode::ClientPull;
    case ViconDataStreamSDK::DotNET::StreamMode::ClientPullPreFetch: return ViconDataStreamSDK::CPP::StreamMode::ClientPullPreFetch;
    case ViconDataStreamSDK::DotNET::StreamMode::ServerPush        : return ViconDataStreamSDK::CPP::StreamMode::ServerPush;
    }
  }

  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::StreamMode::Enum
  ViconDataStreamSDK::DotNET::StreamMode Adapt( ViconDataStreamSDK::CPP::StreamMode::Enum i_Mode )
  {
    switch( i_Mode )
    {
    default:
    case ViconDataStreamSDK::CPP::StreamMode::ClientPull        : return ViconDataStreamSDK::DotNET::StreamMode::ClientPull;
    case ViconDataStreamSDK::CPP::StreamMode::ClientPullPreFetch: return ViconDataStreamSDK::DotNET::StreamMode::ClientPullPreFetch;
    case ViconDataStreamSDK::CPP::StreamMode::ServerPush        : return ViconDataStreamSDK::DotNET::StreamMode::ServerPush;
    }
  }

  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::Result::Enum
  ///@private
  ViconDataStreamSDK::DotNET::Result Adapt(ViconDataStreamSDK::CPP::Result::Enum i_Result)
  {
    switch( i_Result )
    {
    case ViconDataStreamSDK::CPP::Result::Unknown                            : return ViconDataStreamSDK::DotNET::Result::Unknown;
    case ViconDataStreamSDK::CPP::Result::NotImplemented                     : return ViconDataStreamSDK::DotNET::Result::NotImplemented;
    case ViconDataStreamSDK::CPP::Result::Success                            : return ViconDataStreamSDK::DotNET::Result::Success;
    case ViconDataStreamSDK::CPP::Result::InvalidHostName                    : return ViconDataStreamSDK::DotNET::Result::InvalidHostName;
    case ViconDataStreamSDK::CPP::Result::InvalidMulticastIP                 : return ViconDataStreamSDK::DotNET::Result::InvalidMulticastIP;
    case ViconDataStreamSDK::CPP::Result::ClientAlreadyConnected             : return ViconDataStreamSDK::DotNET::Result::ClientAlreadyConnected;
    case ViconDataStreamSDK::CPP::Result::ClientConnectionFailed             : return ViconDataStreamSDK::DotNET::Result::ClientConnectionFailed;
    case ViconDataStreamSDK::CPP::Result::ServerAlreadyTransmittingMulticast : return ViconDataStreamSDK::DotNET::Result::ServerAlreadyTransmittingMulticast;
    case ViconDataStreamSDK::CPP::Result::ServerNotTransmittingMulticast     : return ViconDataStreamSDK::DotNET::Result::ServerNotTransmittingMulticast;
    case ViconDataStreamSDK::CPP::Result::NotConnected                       : return ViconDataStreamSDK::DotNET::Result::NotConnected;
    case ViconDataStreamSDK::CPP::Result::NoFrame                            : return ViconDataStreamSDK::DotNET::Result::NoFrame;
    case ViconDataStreamSDK::CPP::Result::InvalidIndex                       : return ViconDataStreamSDK::DotNET::Result::InvalidIndex;
    case ViconDataStreamSDK::CPP::Result::InvalidCameraName                  : return ViconDataStreamSDK::DotNET::Result::InvalidCameraName;
    case ViconDataStreamSDK::CPP::Result::InvalidSubjectName                 : return ViconDataStreamSDK::DotNET::Result::InvalidSubjectName;
    case ViconDataStreamSDK::CPP::Result::InvalidSegmentName                 : return ViconDataStreamSDK::DotNET::Result::InvalidSegmentName;
    case ViconDataStreamSDK::CPP::Result::InvalidMarkerName                  : return ViconDataStreamSDK::DotNET::Result::InvalidMarkerName;
    case ViconDataStreamSDK::CPP::Result::InvalidDeviceName                  : return ViconDataStreamSDK::DotNET::Result::InvalidDeviceName;
    case ViconDataStreamSDK::CPP::Result::InvalidDeviceOutputName            : return ViconDataStreamSDK::DotNET::Result::InvalidDeviceOutputName;
    case ViconDataStreamSDK::CPP::Result::InvalidLatencySampleName           : return ViconDataStreamSDK::DotNET::Result::InvalidLatencySampleName;
    case ViconDataStreamSDK::CPP::Result::CoLinearAxes                       : return ViconDataStreamSDK::DotNET::Result::CoLinearAxes;
    case ViconDataStreamSDK::CPP::Result::LeftHandedAxes                     : return ViconDataStreamSDK::DotNET::Result::LeftHandedAxes;
    case ViconDataStreamSDK::CPP::Result::HapticAlreadySet                   : return ViconDataStreamSDK::DotNET::Result::HapticAlreadySet;
    case ViconDataStreamSDK::CPP::Result::EarlyDataRequested                 : return ViconDataStreamSDK::DotNET::Result::EarlyDataRequested;
    case ViconDataStreamSDK::CPP::Result::LateDataRequested                  : return ViconDataStreamSDK::DotNET::Result::LateDataRequested;
    case ViconDataStreamSDK::CPP::Result::InvalidOperation                   : return ViconDataStreamSDK::DotNET::Result::InvalidOperation;
    case ViconDataStreamSDK::CPP::Result::NotSupported                       : return ViconDataStreamSDK::DotNET::Result::NotSupported;
    case ViconDataStreamSDK::CPP::Result::ConfigurationFailed                : return ViconDataStreamSDK::DotNET::Result::ConfigurationFailed;
    case ViconDataStreamSDK::CPP::Result::NotPresent                         : return ViconDataStreamSDK::DotNET::Result::NotPresent;
    default: return ViconDataStreamSDK::DotNET::Result::Unknown;
    }
  }

  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::TimecodeStandard::Enum
  ///@private
  ViconDataStreamSDK::DotNET::TimecodeStandard Adapt(ViconDataStreamSDK::CPP::TimecodeStandard::Enum i_TimecodeStandard)
  {
    switch( i_TimecodeStandard )
    {
    case ViconDataStreamSDK::CPP::TimecodeStandard::PAL      : return ViconDataStreamSDK::DotNET::TimecodeStandard::PAL;
    case ViconDataStreamSDK::CPP::TimecodeStandard::NTSC     : return ViconDataStreamSDK::DotNET::TimecodeStandard::NTSC;
    case ViconDataStreamSDK::CPP::TimecodeStandard::NTSCDrop : return ViconDataStreamSDK::DotNET::TimecodeStandard::NTSCDrop;
    case ViconDataStreamSDK::CPP::TimecodeStandard::Film     : return ViconDataStreamSDK::DotNET::TimecodeStandard::Film;
    case ViconDataStreamSDK::CPP::TimecodeStandard::NTSCFilm : return ViconDataStreamSDK::DotNET::TimecodeStandard::NTSCFilm;
    case ViconDataStreamSDK::CPP::TimecodeStandard::ATSC     : return ViconDataStreamSDK::DotNET::TimecodeStandard::ATSC;
    case ViconDataStreamSDK::CPP::TimecodeStandard::None:
    default                                                  : return ViconDataStreamSDK::DotNET::TimecodeStandard::None;
    }
  }

  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::DeviceType::Enum
  ///@private
  ViconDataStreamSDK::DotNET::DeviceType Adapt(ViconDataStreamSDK::CPP::DeviceType::Enum i_DeviceType)
  {
    switch( i_DeviceType )
    {
    case ViconDataStreamSDK::CPP::DeviceType::ForcePlate : return ViconDataStreamSDK::DotNET::DeviceType::ForcePlate;
    case ViconDataStreamSDK::CPP::DeviceType::EyeTracker : return ViconDataStreamSDK::DotNET::DeviceType::EyeTracker;
    case ViconDataStreamSDK::CPP::DeviceType::Unknown    :
    default                                              : return ViconDataStreamSDK::DotNET::DeviceType::Unknown;
    }
  }

  // This function is provided to insulate us from changes to ViconDataStreamSDK::CPP::Unit::Enum
  ///@private
  ViconDataStreamSDK::DotNET::Unit Adapt(ViconDataStreamSDK::CPP::Unit::Enum i_Unit)
  {
    switch( i_Unit )
    {
    case ViconDataStreamSDK::CPP::Unit::Volt                   : return ViconDataStreamSDK::DotNET::Unit::Volt;
    case ViconDataStreamSDK::CPP::Unit::Newton                 : return ViconDataStreamSDK::DotNET::Unit::Newton;
    case ViconDataStreamSDK::CPP::Unit::NewtonMeter            : return ViconDataStreamSDK::DotNET::Unit::NewtonMeter;
    case ViconDataStreamSDK::CPP::Unit::Meter                  : return ViconDataStreamSDK::DotNET::Unit::Meter;
    case ViconDataStreamSDK::CPP::Unit::Kilogram               : return ViconDataStreamSDK::DotNET::Unit::Kilogram;
    case ViconDataStreamSDK::CPP::Unit::Second                 : return ViconDataStreamSDK::DotNET::Unit::Second;
    case ViconDataStreamSDK::CPP::Unit::Ampere                 : return ViconDataStreamSDK::DotNET::Unit::Ampere;
    case ViconDataStreamSDK::CPP::Unit::Kelvin                 : return ViconDataStreamSDK::DotNET::Unit::Kelvin;
    case ViconDataStreamSDK::CPP::Unit::Mole                   : return ViconDataStreamSDK::DotNET::Unit::Mole;
    case ViconDataStreamSDK::CPP::Unit::Candela                : return ViconDataStreamSDK::DotNET::Unit::Candela;
    case ViconDataStreamSDK::CPP::Unit::Radian                 : return ViconDataStreamSDK::DotNET::Unit::Radian;
    case ViconDataStreamSDK::CPP::Unit::Steradian              : return ViconDataStreamSDK::DotNET::Unit::Steradian;
    case ViconDataStreamSDK::CPP::Unit::MeterSquared           : return ViconDataStreamSDK::DotNET::Unit::MeterSquared;
    case ViconDataStreamSDK::CPP::Unit::MeterCubed             : return ViconDataStreamSDK::DotNET::Unit::MeterCubed;
    case ViconDataStreamSDK::CPP::Unit::MeterPerSecond         : return ViconDataStreamSDK::DotNET::Unit::MeterPerSecond;
    case ViconDataStreamSDK::CPP::Unit::MeterPerSecondSquared  : return ViconDataStreamSDK::DotNET::Unit::MeterPerSecondSquared;
    case ViconDataStreamSDK::CPP::Unit::RadianPerSecond        : return ViconDataStreamSDK::DotNET::Unit::RadianPerSecond;
    case ViconDataStreamSDK::CPP::Unit::RadianPerSecondSquared : return ViconDataStreamSDK::DotNET::Unit::RadianPerSecondSquared;
    case ViconDataStreamSDK::CPP::Unit::Hertz                  : return ViconDataStreamSDK::DotNET::Unit::Hertz;
    case ViconDataStreamSDK::CPP::Unit::Joule                  : return ViconDataStreamSDK::DotNET::Unit::Joule;
    case ViconDataStreamSDK::CPP::Unit::Watt                   : return ViconDataStreamSDK::DotNET::Unit::Watt;
    case ViconDataStreamSDK::CPP::Unit::Pascal                 : return ViconDataStreamSDK::DotNET::Unit::Pascal;
    case ViconDataStreamSDK::CPP::Unit::Lumen                  : return ViconDataStreamSDK::DotNET::Unit::Lumen;
    case ViconDataStreamSDK::CPP::Unit::Lux                    : return ViconDataStreamSDK::DotNET::Unit::Lux;
    case ViconDataStreamSDK::CPP::Unit::Coulomb                : return ViconDataStreamSDK::DotNET::Unit::Coulomb;
    case ViconDataStreamSDK::CPP::Unit::Ohm                    : return ViconDataStreamSDK::DotNET::Unit::Ohm;
    case ViconDataStreamSDK::CPP::Unit::Farad                  : return ViconDataStreamSDK::DotNET::Unit::Farad;
    case ViconDataStreamSDK::CPP::Unit::Weber                  : return ViconDataStreamSDK::DotNET::Unit::Weber;
    case ViconDataStreamSDK::CPP::Unit::Tesla                  : return ViconDataStreamSDK::DotNET::Unit::Tesla;
    case ViconDataStreamSDK::CPP::Unit::Henry                  : return ViconDataStreamSDK::DotNET::Unit::Henry;
    case ViconDataStreamSDK::CPP::Unit::Siemens                : return ViconDataStreamSDK::DotNET::Unit::Siemens;
    case ViconDataStreamSDK::CPP::Unit::Becquerel              : return ViconDataStreamSDK::DotNET::Unit::Becquerel;
    case ViconDataStreamSDK::CPP::Unit::Gray                   : return ViconDataStreamSDK::DotNET::Unit::Gray;
    case ViconDataStreamSDK::CPP::Unit::Sievert                : return ViconDataStreamSDK::DotNET::Unit::Sievert;
    case ViconDataStreamSDK::CPP::Unit::Katal                  : return ViconDataStreamSDK::DotNET::Unit::Katal;
    case ViconDataStreamSDK::CPP::Unit::Unknown                :
    default                                                    : return ViconDataStreamSDK::DotNET::Unit::Unknown;
    }
  }

  // Adapt from a std::string to a .NET String
  ///@private
  String^ Adapt(const std::string & i_rString)
  {
    return gcnew System::String( i_rString.c_str() );
  }

  // Basically a no-op to keep the client code readable
  ///@private
  bool Adapt(const bool i_Value)
  {
    return i_Value;
  }

  // Basically a no-op to keep the client code readable
  ///@private
  unsigned char Adapt(const unsigned char i_Value)
  {
    return i_Value;
  }

  // Basically a no-op to keep the client code readable
  ///@private
  unsigned short Adapt(const unsigned short i_Value)
  {
    return i_Value;
  }

  // Basically a no-op to keep the client code readable
  ///@private
  unsigned int Adapt(const unsigned int i_Value)
  {
    return i_Value;
  }

  // Basically a no-op to keep the client code readable
  ///@private
  double Adapt(const double i_Value)
  {
    return i_Value;
  }

  // Adapt from a .NET String to a std::string
  ///@private
  std::string Adapt(String^ i_String)
  {
    const char* chars = ( const char * )( Marshal::StringToHGlobalAnsi( i_String ) ).ToPointer();
    std::string Value( chars );
    Marshal::FreeHGlobal( IntPtr( ( void * ) chars ) );
    return Value;
  }

  // Adapt between a 1d .NET array and a C array
  ///@private
  template< typename T, unsigned int N >
  array< T > ^ Adapt( T (&i_rArray)[N] )
  {
    array< T > ^ outputArray = gcnew array< T >( N );
    for( unsigned int n = 0 ; n < N ; ++n )
    {
      outputArray[ n ] = i_rArray[ n ];
    }

    return outputArray;
  }

  // Adapt between a 2d .NET array and a C array
  ///@private
  template< typename T, unsigned int N, unsigned int M >
  array< T, 2 > ^ Adapt( T (&i_rArray)[N][M] )
  {
    array< T, 2 > ^ outputArray = gcnew array< T, 2 >( N, M );
    for( unsigned int n = 0 ; n < N ; ++n )
    {
      for( unsigned int m = 0 ; m < M ; ++m )
      {
        outputArray[ n, m ] = i_rArray[ n ][ m ];
      }
    }

    return outputArray;
  }

  // Adapt between a .NET list and an STL vector
  ///@private
  template< typename T >
  List< T >^ Adapt( const std::vector< T > & i_rVector )
  {
    List< T >^ NewList = gcnew List< T >();
    for (const T & rVal : i_rVector)
    {
      NewList->Add( Adapt( rVal ) );
    }

    return NewList;
  }

  // Adapt between an STL vector and a .NET list 
  ///@private
  template< typename T >
  std::vector< T > Adapt(List< T >^ i_List)
  {
    std::vector< T > NewVector;
    for each (T Val in i_List )
    {
      NewVector.push_back( Adapt( Val ) );
    }

    return NewVector;
  }

  ///  Vicon DataStream SDK client.
  ///  The core client class for .NET
  public ref class Client
  {
  public:

    /// Construction.
    /// You can create many instances of the Vicon DataStream Client which can connect to multiple Vicon DataStream Servers.
    /// .NET is object oriented, so use the class constructor. 
    /// 
    /// Because objects are lazily garbage collected, your instance may outlive the last reference to it for some time. 
    /// 
    /// If the instance is pre-fetching frame data for you, then it can still use CPU and network bandwidth. 
    /// 
    /// Consider explicitly disconnecting prior to destruction.
    ///
    ///      ViconDataStreamSDK.DotNET.Client pHeapClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///      Output_SomeFunction Output = pHeapClient.SomeFunction(InputParam);

    ///      // Signal to the garbage collector that it can clean up 
    ///      pHeapClient.Disconnect(); 
    ///      pHeapClient = null;
    ///
    Client()
    : m_pClient( new ViconDataStreamSDK::CPP::Client() )
    {
    }

    /// Destruction.
    /// Destruction will Disconnect if required.
    /// 
    /// See Client::Client for an example.
    ~Client()
    {
      delete m_pClient;
      m_pClient = 0;
    }

    /// Get the version of the Vicon DataStream SDK.
    ///   + **Major**
    ///   When this number increases, we break backward compatibility with previous major versions.
    ///   + **Minor**
    ///   When this number increases, we have probably added new functionality to the SDK without breaking 
    ///   backward compatibility with previous versions.
    ///   + **Point**
    ///   When this number increases, we have introduced a bug fix or performance enhancement without breaking 
    ///   backward compatibility with previous versions.
    /// 
    /// The function can be called without the client being connected.
    /// 
    ///      ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///      Output_GetVersion Output = MyClient.GetVersion();
    /// 
    /// \return Output_GetVersion class containing the version information.
    Output_GetVersion^ GetVersion()
    {
      ViconDataStreamSDK::CPP::Output_GetVersion CPPOutput( m_pClient->GetVersion() );

      Output_GetVersion^ Output = gcnew Output_GetVersion();
      Output->Major = Adapt( CPPOutput.Major );
      Output->Minor = Adapt( CPPOutput.Minor );
      Output->Point = Adapt( CPPOutput.Point );
      Output->Revision = Adapt( CPPOutput.Revision );

      return Output;
    }

    /// Establish a dedicated connection to a Vicon DataStream Server.
    /// 
    /// See Also: ConnectToMulticast(), Disconnect(), IsConnected().
    /// 
    /// The function defaults to connecting on port 801. 
    /// You can specify an alternate port number after a colon.
    /// This is for future compatibility: current products serve data on port 801 only.
    /// 
    ///      ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///      Output_Connect Output = MyClient.Connect("localhost:801");
    /// 
    /// \param  HostName The DNS-identifiable name, or IP address of the PC hosting the DataStream server. 
    ///                  For example:
    ///                    + "localhost"
    ///                    + "MyViconPC:801"
    ///                    + "10.0.0.2"
    /// \return An Output_Connect class containing the result of the connect operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + InvalidHostName
    ///           + ClientAlreadyConnected 
    ///           + ClientConnectionFailed
    Output_Connect^ Connect( String^ HostName )
    {
      ViconDataStreamSDK::CPP::Output_Connect CPPOutput( m_pClient->Connect( Adapt( HostName ) ) );

      Output_Connect^ Output = gcnew Output_Connect();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Connect to a Vicon DataStream Server's Multicast stream. 
    /// The stream content is managed by a client who calls StartTransmittingMulticast().
    /// 
    /// See Also: Connect(), Disconnect(), IsConnected(), StartTransmittingMulticast(), StopTransmittingMulticast()
    /// 
    ///      // class Output_ConnectToMulticast
    ///      // {
    ///      //   public Result Result;
    ///      // };
    ///      
    ///      ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();;
    ///      Output_ConnectToMulticast Output = MyClient.ConnectToMulticast("localhost", "224.0.0.0");
    ///
    ///
    /// \param  LocalIP      The DNS-identifiable name, or IP address of the local Ethernet interface 
    ///                      on which you wish to receive multicast data. 
    ///                      Do not specify a port (any port specified will be ignored).
    ///                      For example:
    ///                        + "localhost"
    ///                        + "10.0.0.2"
    /// \param  MulticastIP  The IP Address of the Multicast group on which data will be received. 
    ///                      The address must be in the range 224.0.0.0-239.255.255.255 
    ///                      You may also specify a port by appending it to the end of the IP Address 
    ///                      after a colon, e.g. 224.0.0.0:30001. 
    ///                      If you do not specify a port it will default to 44801.
    /// \return An Output_ConnectToMulticast class containing the result of the connect operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + InvalidHostName
    ///           + InvalidMulticastIP
    ///           + ClientAlreadyConnected 
    ///           + ClientConnectionFailed
    Output_ConnectToMulticast^ ConnectToMulticast( String^ HostName, String ^ MulticastIP )
    {
      ViconDataStreamSDK::CPP::Output_ConnectToMulticast CPPOutput( m_pClient->ConnectToMulticast( Adapt( HostName ), Adapt( MulticastIP ) ) );

      Output_ConnectToMulticast^ Output = gcnew Output_ConnectToMulticast();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disconnect from the Vicon DataStream Server.
    /// 
    /// See Also: Connect(), IsConnected()
    /// 
    ///       ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///       MyClient.Connect("localhost"); 
    ///       Output_Disconnect Output = MyClient.Disconnect();
    /// 
    /// \return An Output_Disconnect class containing the result of the operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + NotConnected
    Output_Disconnect^ Disconnect()
    {
      ViconDataStreamSDK::CPP::Output_Disconnect CPPOutput( m_pClient->Disconnect() );

      Output_Disconnect^ Output = gcnew Output_Disconnect();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Discover whether client is connected to the Vicon DataStream Server.
    /// 
    /// See Also: Connect(), Disconnect()
    /// 
    ///       ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///       Output_IsConnected Output = MyClient.IsConnected();
    ///       // Output.Connected == false 
    ///       MyClient.Connect( "localhost" ); 
    ///       Output_IsConnected Output = MyClient.IsConnected();
    ///       // Output.Connected == true                              
    ///       // (assuming localhost is serving    
    /// 
    /// \return An Output_IsConnected class containing a true value for Connected if you are 
    ///         connected to the stream, otherwise false.
    Output_IsConnected^ IsConnected()
    {
      ViconDataStreamSDK::CPP::Output_IsConnected CPPOutput( m_pClient->IsConnected() );

      Output_IsConnected^ Output = gcnew Output_IsConnected();
      Output->Connected = Adapt( CPPOutput.Connected );

      return Output;
    }

    /// Ask the DataStream Server to start transmitting the data you are receiving directly to a Multicast address as well. 
    /// This allows multiple clients to connect to your stream (via ConnectToMulticast() ) whilst minimizing network 
    /// bandwidth use and frame delivery latency.
    ///
    /// See Also: Connect(), ConnectToMulticast(), Disconnect(), StopTransmittingMulticast()
    /// 
    ///       ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///       MyClient.Connect("localhost"); 
    ///       MyClient.StartTransmittingMulticast("10.0.0.1", "224.0.0.0")    
    /// 
    /// \param  ServerIP      The IP Address of the server Ethernet interface from which the Multicast data will be sent. 
    ///                       Do not specify a port number (any port number specified will be ignored).
    /// \param  MulticastIP   The IP Address of the Multicast group to which Multicast data will be sent. 
    ///                       The address must be in the range 224.0.0.0-239.255.255.255. You may also specify 
    ///                       the port the data will be sent to by appending it to the IP Address after a colon, 
    ///                       e.g. 224.0.0.0:30001. If you do not specify a port it will default to 44801. 
    /// \return An Output_StartTransmittingMulticast class containing the result of the operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + NotConnected
    ///           + InvalidMulticastIP
    ///           + ServerAlreadyTransmittingMulticast
    Output_StartTransmittingMulticast^ StartTransmittingMulticast( String^ ServerIP, String^ MulticastIP )
    {
      ViconDataStreamSDK::CPP::Output_StartTransmittingMulticast CPPOutput( m_pClient->StartTransmittingMulticast( Adapt( ServerIP ), Adapt( MulticastIP ) ) );

      Output_StartTransmittingMulticast^ Output = gcnew Output_StartTransmittingMulticast();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Ask the DataStream Server to stop transmitting the data you are receiving directly to a Multicast address as well. 
    /// You must previously have started a transmission via StartTransmittingMulticast.
    /// 
    /// See Also: Connect(), ConnectToMulticast(), Disconnect(), StartTransmittingMulticast()
    /// 
    ///       ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///       MyClient.Connect("localhost"); 
    ///       MyClient.StartTransmittingMulticast("10.0.0.1", "224.0.0.0"); 
    ///       // Do some stuff 
    ///       MyClient.StopTransmittingMulticast(); 
    /// 
    /// \return An Output_StopTransmittingMulticast class containing the result of the operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + NotConnected
    ///           + ServerNotTransmittingMulticast
    Output_StopTransmittingMulticast^ StopTransmittingMulticast()
    {
      ViconDataStreamSDK::CPP::Output_StopTransmittingMulticast CPPOutput( m_pClient->StopTransmittingMulticast() );

      Output_StopTransmittingMulticast^ Output = gcnew Output_StopTransmittingMulticast();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Set the number of frames that the client should buffer.
    /// The default value is 1, which always supplies the latest frame.
    /// Choose higher values to reduce the risk of missing frames between calls.
    ///
    /// See Also: GetFrame()
    ///
    /// \param  BufferSize  The maximum number of frames to buffer.
    /// \return Nothing
    void SetBufferSize( unsigned int i_BufferSize )
    {
      m_pClient->SetBufferSize( i_BufferSize );
    }

    /// Enable kinematic segment data in the Vicon DataStream. 
    /// Call this function on startup, after connecting to the server, and before trying to read local or global segment data.
    ///
    /// See Also: IsSegmentDataEnabled(), DisableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetSegmentCount(), GetSegmentName(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///        MyClient.Connect("localhost"); 
    ///        Output_EnableSegmentData Output = MyClient.EnableSegmentData()    
    ///
    /// \return An Output_EnableSegmentData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableSegmentData^ EnableSegmentData()
    {
      ViconDataStreamSDK::CPP::Output_EnableSegmentData CPPOutput( m_pClient->EnableSegmentData() );

      Output_EnableSegmentData^ Output = gcnew Output_EnableSegmentData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable kinematic segment data in the Vicon DataStream using the lightweight transport layer. 
    /// Call this function on startup, after connecting to the server, and before trying to read local or global segment data.
    ///
    /// See Also: IsSegmentDataEnabled(), DisableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetSegmentCount(), GetSegmentName(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///        MyClient.Connect("localhost"); 
    ///        Output_EnableLightweightSegmentData Output = MyClient.EnableLightweightSegmentData()    
    ///
    /// \return An Output_EnableLightweightSegmentData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableLightweightSegmentData^ EnableLightweightSegmentData()
    {
      ViconDataStreamSDK::CPP::Output_EnableLightweightSegmentData CPPOutput( m_pClient->EnableLightweightSegmentData() );

      Output_EnableLightweightSegmentData^ Output = gcnew Output_EnableLightweightSegmentData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable labeled reconstructed marker data in the Vicon DataStream. 
    /// Call this function on startup, after connecting to the server, and before trying to read labeled marker data.
    ///
    /// See Also: IsMarkerDataEnabled(), DisableMarkerData(), EnableSegmentData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetMarkerCount(), GetMarkerName(), GetMarkerGlobalTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///       MyClient.Connect( "localhost" );
    ///       Output_EnableMarkerData Output = MyClient.EnableMarkerData();
    ///
    /// \return An Output_EnableMarkerData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableMarkerData^ EnableMarkerData()
    {
      ViconDataStreamSDK::CPP::Output_EnableMarkerData CPPOutput( m_pClient->EnableMarkerData() );

      Output_EnableMarkerData^ Output = gcnew Output_EnableMarkerData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable unlabeled reconstructed marker data in the Vicon DataStream. 
    /// Call this function on startup, after connecting to the server, and before trying to read global unlabeled marker data.
    ///
    /// See Also: IsUnlabeledMarkerDataEnabled(), DisableUnlabeledMarkerData(), EnableSegmentData(), EnableMarkerData(), EnableDeviceData(), GetUnlabeledMarkerCount(), GetUnlabeledMarkerGlobalTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client(); 
    ///       MyClient.Connect( "localhost" );
    ///       Output_EnableUnlabeledMarkerData Output = MyClient.EnableUnlabeledMarkerData();
    ///
    /// \return An Output_UnlabeledMarkerData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableUnlabeledMarkerData^ EnableUnlabeledMarkerData()
    {
      ViconDataStreamSDK::CPP::Output_EnableUnlabeledMarkerData CPPOutput( m_pClient->EnableUnlabeledMarkerData() );

      Output_EnableUnlabeledMarkerData^ Output = gcnew Output_EnableUnlabeledMarkerData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable information about the rays contributing to each labeled marker in the Vicon DataStream. 
    /// Call this function on startup, after connecting to the server, and before trying to read global unlabeled marker data.
    ///
    /// See Also: IsMarkerRayDataEnabled(), DisableMarkerRayData(), EnableSegmentData(), EnableMarkerData(), EnableDeviceData(), GetUnlabeledMarkerCount(), GetUnlabeledMarkerGlobalTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_EnableMarkerRayData Output = MyClient.EnableMarkerRayData();
    ///
    /// \return An Output_EnableMarkerRayData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableMarkerRayData^ EnableMarkerRayData()
    {
      ViconDataStreamSDK::CPP::Output_EnableMarkerRayData CPPOutput( m_pClient->EnableMarkerRayData() );

      Output_EnableMarkerRayData^ Output = gcnew Output_EnableMarkerRayData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable force plate, EMG, and other device data in the Vicon DataStream. 
    /// Call this function on startup, after connecting to the server, and before trying to read device information.
    ///
    /// See Also: IsDeviceDataEnabled(), DisableDeviceData(), EnableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), GetDeviceCount(), GetDeviceName(), GetDeviceOutputCount(), GetDeviceOutputName(),GetDeviceOutputValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_EnableDeviceData Output = MyClient.EnableDeviceData();
    //
    /// \return An Output_EnableDeviceData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableDeviceData^ EnableDeviceData()
    {
      ViconDataStreamSDK::CPP::Output_EnableDeviceData CPPOutput( m_pClient->EnableDeviceData() );

      Output_EnableDeviceData^ Output = gcnew Output_EnableDeviceData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable centroid data in the Vicon DataStream.
    /// Call this function on startup, after connecting to the server, and before trying to read centroid information.
    ///
    /// See Also: IsCentroidDataEnabled(), DisableCentroidData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_EnableCentroidData Output = MyClient.EnableCentroidData ();
    ///
    /// \return An Output_EnableCentroidData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableCentroidData^ EnableCentroidData()
    {
      ViconDataStreamSDK::CPP::Output_EnableCentroidData CPPOutput(m_pClient->EnableCentroidData());

      Output_EnableCentroidData^ Output = gcnew Output_EnableCentroidData();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }
    
    /// Enable Greyscale data in the Vicon DataStream.
    /// Call this function on startup, after connecting to the server, and before trying to read Greyscale information.
    ///
    /// See Also: IsGreyscaleDataEnabled(), DisableGreyscaleData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_EnableGreyscaleData Output = MyClient.EnableGreyscaleData ();
    ///
    /// \return An Output_EnableGreyscaleData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected    
    Output_EnableGreyscaleData^ EnableGreyscaleData()
    {
      ViconDataStreamSDK::CPP::Output_EnableGreyscaleData CPPOutput( m_pClient->EnableGreyscaleData() );

      Output_EnableGreyscaleData^ Output = gcnew Output_EnableGreyscaleData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable Video data in the Vicon DataStream.
    /// Call this function on startup, after connecting to the server, and before trying to read Video information.
    ///
    /// See Also: IsVideoDataEnabled(), DisableVideoData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_EnableVideoData Output = MyClient.EnableVideoData ();
    ///
    /// \return An Output_EnableVideoData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected    
    Output_EnableVideoData^ EnableVideoData()
    {
      ViconDataStreamSDK::CPP::Output_EnableVideoData CPPOutput(m_pClient->EnableVideoData());

      Output_EnableVideoData^ Output = gcnew Output_EnableVideoData();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }    
    
    /// Enable Debug data in the Vicon DataStream.
    /// Call this function on startup, after connecting to the server, and before trying to read Debug information.
    ///
    /// See Also: IsDebugDataEnabled(), DisableDebugData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_EnableDebugData Output = MyClient.EnableDebugData ();
    ///
    /// \return An Output_EnableDebugData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableDebugData^ EnableDebugData()
    {
      ViconDataStreamSDK::CPP::Output_EnableDebugData CPPOutput(m_pClient->EnableDebugData());

      Output_EnableDebugData^ Output = gcnew Output_EnableDebugData();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }    
    

    /// Disable kinematic segment data in the Vicon DataStream.
    ///
    /// See Also: IsSegmentDataEnabled(), EnableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetSegmentCount(), GetSegmentName(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableSegmentData Output = MyClient.DisableSegmentData();
    ///
    /// \return An Output_DisableSegmentData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableSegmentData^ DisableSegmentData()
    {
      ViconDataStreamSDK::CPP::Output_DisableSegmentData CPPOutput( m_pClient->DisableSegmentData() );

      Output_DisableSegmentData^ Output = gcnew Output_DisableSegmentData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disable the lightweight output mode for kinematic segment data in the Vicon DataStream.
    ///
    /// See Also: IsSegmentDataEnabled(), EnableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetSegmentCount(), GetSegmentName(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableLightweightSegmentData Output = MyClient.DisableLightweightSegmentData();
    ///
    /// \return An Output_DisableLightweightSegmentData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableLightweightSegmentData^ DisableLightweightSegmentData()
    {
      ViconDataStreamSDK::CPP::Output_DisableLightweightSegmentData CPPOutput( m_pClient->DisableLightweightSegmentData() );

      Output_DisableLightweightSegmentData^ Output = gcnew Output_DisableLightweightSegmentData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disable labeled reconstructed marker data in the Vicon DataStream.
    ///
    /// See Also: IsMarkerDataEnabled(), EnableMarkerData(), EnableSegmentData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetMarkerCount(), GetMarkerName(), GetMarkerGlobalTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableMarkerData Output = MyClient.DisableMarkerData();
    ///
    /// \return An Output_DisableMarkerData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableMarkerData^ DisableMarkerData()
    {
      ViconDataStreamSDK::CPP::Output_DisableMarkerData CPPOutput( m_pClient->DisableMarkerData() );

      Output_DisableMarkerData^ Output = gcnew Output_DisableMarkerData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disable unlabeled reconstructed marker data in the Vicon DataStream.
    ///
    /// See Also: IsUnlabeledMarkerDataEnabled(), EnableUnlabeledMarkerData(), EnableSegmentData(), EnableMarkerData(), EnableDeviceData(), GetUnlabeledMarkerCount(), GetUnlabeledMarkerGlobalTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableUnlabeledMarkerData Output = MyClient.DisableUnlabeledMarkerData();
    ///
    /// \return An Output_DisableUnlabeledMarkerData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableUnlabeledMarkerData^ DisableUnlabeledMarkerData()
    {
      ViconDataStreamSDK::CPP::Output_DisableUnlabeledMarkerData CPPOutput( m_pClient->DisableUnlabeledMarkerData() );

      Output_DisableUnlabeledMarkerData^ Output = gcnew Output_DisableUnlabeledMarkerData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    ///  Disable unlabeled reconstructed marker data in the Vicon DataStream.
    ///
    ///  See Also: IsMarkerRayDataEnabled(), EnableMarkerRayData(), EnableSegmentData(), EnableMarkerData(), EnableDeviceData(), GetUnlabeledMarkerCount(), GetUnlabeledMarkerGlobalTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableMarkerRayData Output =
    ///        MyClient.DisableMarkerRayData();
    //
    /// \return An Output_DisableMarkerRayData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableMarkerRayData^ DisableMarkerRayData()
    {
      ViconDataStreamSDK::CPP::Output_DisableMarkerRayData CPPOutput( m_pClient->DisableMarkerRayData() );

      Output_DisableMarkerRayData^ Output = gcnew Output_DisableMarkerRayData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disable force plate, EMG, and other device data in the Vicon DataStream.
    ///
    /// See Also: IsDeviceDataEnabled(), EnableDeviceData(), EnableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), GetDeviceCount(), GetDeviceName(), GetDeviceOutputCount(), GetDeviceOutputName(), GetDeviceOutputValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableDeviceData Output = MyClient.DisableDeviceData();
    ///
    /// \return An Output_DisableDeviceData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableDeviceData^ DisableDeviceData()
    {
      ViconDataStreamSDK::CPP::Output_DisableDeviceData CPPOutput( m_pClient->DisableDeviceData() );

      Output_DisableDeviceData^ Output = gcnew Output_DisableDeviceData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disable centroid data in the Vicon DataStream.
    ///
    /// See Also: IsCentroidDataEnabled(), EnableCentroidData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableCentroidData Output = MyClient.DisableCentroidData ();
    ///
    /// \return An Output_DisableCentroidData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableCentroidData^ DisableCentroidData()
    {
      ViconDataStreamSDK::CPP::Output_DisableCentroidData CPPOutput( m_pClient->DisableCentroidData() );

      Output_DisableCentroidData^ Output = gcnew Output_DisableCentroidData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disable Greyscale data in the Vicon DataStream.
    ///
    /// See Also: IsGreyscaleDataEnabled(), EnableGreyscaleData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableGreyscaleData Output = MyClient.DisableGreyscaleData ();
    ///
    /// \return An Output_DisableGreyscaleData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected    
    Output_DisableGreyscaleData^ DisableGreyscaleData()
    {
      ViconDataStreamSDK::CPP::Output_DisableGreyscaleData CPPOutput(m_pClient->DisableGreyscaleData());

      Output_DisableGreyscaleData^ Output = gcnew Output_DisableGreyscaleData();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Disable Video data in the Vicon DataStream.
    ///
    /// See Also: IsVideoDataEnabled(), EnableVideoData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableVideoData Output = MyClient.DisableVideoData ();
    ///
    /// \return An Output_DisableVideoData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableVideoData^ DisableVideoData()
    {
      ViconDataStreamSDK::CPP::Output_DisableVideoData CPPOutput(m_pClient->DisableVideoData());

      Output_DisableVideoData^ Output = gcnew Output_DisableVideoData();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Disable Debug data in the Vicon DataStream.
    ///
    /// See Also: IsDebugDataEnabled(), EnableDebugData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableDebugData Output = MyClient.DisableDebugData ();
    ///
    /// \return An Output_DisableDebugData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableDebugData^ DisableDebugData()
    {
      ViconDataStreamSDK::CPP::Output_DisableDebugData CPPOutput(m_pClient->DisableDebugData());

      Output_DisableDebugData^ Output = gcnew Output_DisableDebugData();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Return whether kinematic segment data is enabled in the Vicon DataStream.
    ///
    /// See Also: EnableSegmentData(), DisableSegmentData(), IsMarkerDataEnabled(), IsUnlabeledMarkerDataEnabled(), IsDeviceDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsSegmentDataEnabled Output = MyClient.IsSegmentDataEnabled();
    ///                                             // Output.Enabled == false
    ///        MyClient.EnableSegmentData();
    ///        Output_IsSegmentDataEnabled Output = MyClient.IsSegmentDataEnabled();
    ///                                             // Output.Enabled == true
    ///
    /// \return An Output_IsSegmentDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsSegmentDataEnabled^ IsSegmentDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsSegmentDataEnabled CPPOutput( m_pClient->IsSegmentDataEnabled() );

      Output_IsSegmentDataEnabled^ Output = gcnew Output_IsSegmentDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }

    /// Return whether the lightweight mode for kinematic segment data is enabled in the Vicon DataStream.
    ///
    /// See Also: EnableSegmentData(), DisableSegmentData(), IsMarkerDataEnabled(), IsUnlabeledMarkerDataEnabled(), IsDeviceDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsLightweightSegmentDataEnabled Output = MyClient.IsLightweightSegmentDataEnabled();
    ///                                             // Output.Enabled == false
    ///        MyClient.EnableLightweightSegmentData();
    ///        Output_IsLightweightSegmentDataEnabled Output = MyClient.IsLightweightSegmentDataEnabled();
    ///                                             // Output.Enabled == true
    ///
    /// \return An Output_IsLightweightSegmentDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsLightweightSegmentDataEnabled^ IsLightweightSegmentDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsLightweightSegmentDataEnabled CPPOutput( m_pClient->IsLightweightSegmentDataEnabled() );

      Output_IsLightweightSegmentDataEnabled^ Output = gcnew Output_IsLightweightSegmentDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }

    /// Return whether labeled reconstructed marker data is enabled in the DataStream.
    ///
    /// See Also: EnableMarkerData(), DisableMarkerData(), IsSegmentDataEnabled(), IsUnlabeledMarkerDataEnabled(), IsDeviceDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new
    ///        ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsMarkerDataEnabled Output = MyClient.IsMarkerDataEnabled();
    ///                                            // Output.Enabled == false
    ///        MyClient.EnableMarkerData();
    ///        Output_IsMarkerDataEnabled Output = MyClient.IsMarkerDataEnabled();
    ///                                            // Output.Enabled == true
    ///
    /// \return An Output_IsMarkerDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsMarkerDataEnabled^ IsMarkerDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsMarkerDataEnabled CPPOutput( m_pClient->IsMarkerDataEnabled() );

      Output_IsMarkerDataEnabled^ Output = gcnew Output_IsMarkerDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }

    /// Return whether unlabeled marker data is enabled in the DataStream.
    ///
    /// See Also: EnableUnlabeledMarkerData(),DisableUnlabeledMarkerData(), IsSegmentDataEnabled(), IsMarkerDataEnabled(), IsDeviceDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsUnlabeledMarkerDataEnabled Output = MyClient.IsMarkerDataEnabled(); // Output.Enabled == false
    ///        MyClient.EnableUnlabeledMarkerData();
    ///        Output_IsUnlabeledMarkerDataEnabled Output = MyClient.IsUnlabeledMarkerDataEnabled(); // Output.Enabled == true
    ///
    /// \return An Output_IsUnlabeledMarkerDataEnabled  class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsUnlabeledMarkerDataEnabled^ IsUnlabeledMarkerDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsUnlabeledMarkerDataEnabled CPPOutput( m_pClient->IsUnlabeledMarkerDataEnabled() );

      Output_IsUnlabeledMarkerDataEnabled^ Output = gcnew Output_IsUnlabeledMarkerDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }

    /// Return whether marker ray data is enabled in the DataStream.
    ///
    /// See Also: EnableMarkerRayData(), DisableMarkerRayData(), IsSegmentDataEnabled(), IsMarkerDataEnabled(), IsDeviceDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new
    ///        ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsMarkerRayDataEnabled Output = MyClient.IsMarkerDataEnabled(); // Output.Enabled == false
    ///        MyClient.EnableMarkerRayData();
    ///        Output_IsMarkerRayDataEnabled Output = MyClient.IsMarkerRayDataEnabled(); // Output.Enabled == true
    ///
    /// \return An Output_IsMarkerRayDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsMarkerRayDataEnabled^ IsMarkerRayDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsMarkerRayDataEnabled CPPOutput( m_pClient->IsMarkerRayDataEnabled() );

      Output_IsMarkerRayDataEnabled^ Output = gcnew Output_IsMarkerRayDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }

    /// Return whether force plate, EMG, and other device data is enabled in the DataStream.
    ///
    /// See Also: EnableDeviceData(), DisableDeviceData(), IsSegmentDataEnabled(), IsMarkerDataEnabled(), IsUnlabeledMarkerDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsDeviceDataEnabled Output = MyClient.IsDeviceDataEnabled();
    ///                                           // Output.Enabled == false
    ///        MyClient.EnableDeviceData();
    ///        Output_IsDeviceDataEnabled Output = MyClient.IsDeviceDataEnabled();
    ///                                            // Output.Enabled == true
    ///
    /// \return An Output_IsDeviceDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsDeviceDataEnabled^ IsDeviceDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsDeviceDataEnabled CPPOutput( m_pClient->IsDeviceDataEnabled() );

      Output_IsDeviceDataEnabled^ Output = gcnew Output_IsDeviceDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }

    /// Return whether Centroid data is enabled in the DataStream.
    ///
    /// See Also: EnableCentroidData(), DisableCentroidData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsCentroidDataEnabled Output = MyClient.IsCentroidDataEnabled ();
    ///                                              // Output.Enabled == false
    ///        MyClient.EnableCentroidData();
    ///        Output_IsCentroidDataEnabled Output = MyClient.IsCentroidDataEnabled ();
    ///                                             // Output.Enabled == true
    ///
    /// \return An Output_IsCentroidDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsCentroidDataEnabled^ IsCentroidDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsCentroidDataEnabled CPPOutput( m_pClient->IsCentroidDataEnabled() );

      Output_IsCentroidDataEnabled^ Output = gcnew Output_IsCentroidDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }

    /// Return whether Greyscale data is enabled in the DataStream.
    ///
    /// See Also: EnableGreyscaleData(), DisableGreyscaleData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsGreyscaleDataEnabled Output = MyClient.IsGreyscaleDataEnabled ();
    ///                                              // Output.Enabled == false
    ///        MyClient.EnableGreyscaleData();
    ///        Output_IsGreyscaleDataEnabled Output = MyClient.IsGreyscaleDataEnabled ();
    ///                                             // Output.Enabled == true
    ///
    /// \return An Output_IsGreyscaleDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsGreyscaleDataEnabled^ IsGreyscaleDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsGreyscaleDataEnabled CPPOutput(m_pClient->IsGreyscaleDataEnabled());

      Output_IsGreyscaleDataEnabled^ Output = gcnew Output_IsGreyscaleDataEnabled();
      Output->Enabled = Adapt(CPPOutput.Enabled);

      return Output;
    }

    /// Return whether Video data is enabled in the DataStream.
    ///
    /// See Also: EnableVideoData(), DisableVideoData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsVideoDataEnabled Output = MyClient.IsVideoDataEnabled ();
    ///                                              // Output.Enabled == false
    ///        MyClient.EnableVideoData();
    ///        Output_IsVideoDataEnabled Output = MyClient.IsVideoDataEnabled ();
    ///                                             // Output.Enabled == true
    ///
    /// \return An Output_IsVideoDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsVideoDataEnabled^ IsVideoDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsVideoDataEnabled CPPOutput(m_pClient->IsVideoDataEnabled());

      Output_IsVideoDataEnabled^ Output = gcnew Output_IsVideoDataEnabled();
      Output->Enabled = Adapt(CPPOutput.Enabled);

      return Output;
    }

    /// Return whether Debug data is enabled in the DataStream.
    ///
    /// See Also: EnableDebugData(), DisableDebugData()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsDebugDataEnabled Output = MyClient.IsDebugDataEnabled ();
    ///                                              // Output.Enabled == false
    ///        MyClient.EnableDebugData();
    ///        Output_IsDebugDataEnabled Output = MyClient.IsDebugDataEnabled ();
    ///                                             // Output.Enabled == true
    ///
    /// \return An Output_IsDebugDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsDebugDataEnabled^ IsDebugDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsDebugDataEnabled CPPOutput(m_pClient->IsDebugDataEnabled());

      Output_IsDebugDataEnabled^ Output = gcnew Output_IsDebugDataEnabled();
      Output->Enabled = Adapt(CPPOutput.Enabled);

      return Output;
    }

    /// There are three modes that the SDK can operate in. Each mode has a different impact on the Client, Server, and network resources used.
    ///
    ///   + **ServerPush**
    ///   In "ServerPush" mode, the Server pushes every new frame of data over the network to the Client. 
    ///   The Server will try not to drop any frames. 
    ///   This results in the lowest latency that can be achieved. 
    ///   If the Client is unable to read data at the rate it is being sent, then it is buffered, firstly in the Client, then on the TCP/IP connection, and then at the Server. 
    ///   When all the buffers are full then frames may be dropped at the Server and the performance of the Server may be affected. 
    ///   The GetFrame() method returns the most recently received frame if available, or blocks the calling thread if the most recently received frame has already been processed.
    ///
    ///   + **ClientPull**
    ///   In "ClientPull" mode, the Client waits for a call to GetFrame(), and then requests the latest frame of data from the Server.
    ///   This increases latency, because a request must be sent over the network to the Server, the Server has to prepare the frame of data for the Client, and then the data must be sent back over the network.
    ///   Network bandwidth is kept to a minimum, because the Server only sends what you need. 
    ///   The buffers are very unlikely to be filled, and Server performance is unlikely to be affected.
    ///   The GetFrame() method blocks the calling thread until the frame has been received.
    ///
    ///   + **ClientPullPreFetch**
    ///   "ClientPullPreFetch" is an enhancement to the "ClientPull" mode.
    ///    A thread in the SDK continuously and preemptively does a "ClientPull" on your behalf, storing the latest requested frame in memory.
    ///    When you next call GetFrame(), the SDK returns the last requested frame that was cached in memory.
    ///    GetFrame() does not need to block the calling thread.
    ///    As with normal "ClientPull", buffers are unlikely to fill up, and Server performance is unlikely to be affected.
    ///    Latency is slightly reduced, but network traffic may increase if you request frames on behalf of the Client which are never used.
    //
    /// The stream defaults to "ClientPull" mode as this is considered the safest option. If performance is a problem, try "ClientPullPreFetch" followed by "ServerPush".
    ///
    /// See Also: GetFrame(), GetLatencyTotal()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.SetStreamMode( ViconDataStreamSDK.DotNET.StreamMode.ServerPush );
    ///        MyClient.SetStreamMode( ViconDataStreamSDK.DotNET.StreamMode.ClientPull );
    ///        MyClient.SetStreamMode( ViconDataStreamSDK.DotNET.StreamMode.ClientPullPreFetch);
    ///
    /// \param StreamMode Stream modes that the SDK can operate in
    ///           + StreamMode.ServerPush
    ///           + StreamMode.ClientPull
    ///           + StreamMode.ClientPullPreFetch
    ///
    /// \return An Output_SetStreamMode class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_SetStreamMode^ SetStreamMode( StreamMode Mode )
    {
      ViconDataStreamSDK::CPP::Output_SetStreamMode CPPOutput( m_pClient->SetStreamMode( Adapt( Mode ) ) );

      Output_SetStreamMode^ Output = gcnew Output_SetStreamMode();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Enable haptic feedback for the selected Apex device.
    ///
    ///        Apex device names may be obtained using GetDeviceCount, GetDeviceName
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame()
    ///        Output_GetDeviceName DeviceName MyClient.GetDeviceName( 0 );
    ///        MyClient.SetApexDeviceFeedback( DeviceName.DeviceName, true );
    ///
    /// \return An Output_SetApexDeviceFeedback class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    ///           + NullClient
    ///           + HapticAlreadySet
    Output_SetApexDeviceFeedback^ SetApexDeviceFeedback( String^ DeviceName, bool bOn )
    {
      ViconDataStreamSDK::CPP::Output_SetApexDeviceFeedback CPPOutput( m_pClient->SetApexDeviceFeedback( Adapt( DeviceName ), Adapt( bOn ) ) );

      Output_SetApexDeviceFeedback^ Output = gcnew Output_SetApexDeviceFeedback();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Remaps the 3D axis.
    /// Vicon Data uses a right-handed coordinate system, with +X forward, +Y left, and +Z up. 
    /// Other systems use different coordinate systems. The SDK can transform its data into any valid right-handed coordinate system by re-mapping each axis. 
    /// Valid directions are "Up", "Down", "Left", "Right", "Forward", and "Backward". Note that "Forward" means moving away from you, and "Backward" is moving towards you. 
    /// Common usages are
    /// Z-up: SetAxisMapping( Forward, Left, Up )
    /// Y-up: SetAxisMapping( Forward, Up, Right )
    ///
    /// See Also: GetAxisMapping()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.SetAxisMapping( ViconDataStreamSDK.DotNET.Direction.Forward,
    ///        ViconDataStreamSDK.DotNET.Direction.Left,
    ///        ViconDataStreamSDK.DotNET.Direction.Up );
    ///
    /// \param XAxis Specify the direction of your X axis relative to yourself as the observer.
    /// \param YAxis Specify the direction of your Y axis relative to yourself as the observer.
    /// \param ZAxis Specify the direction of your Z axis relative to yourself as the observer.
    ///
    /// \return An Output_SetAxisMapping class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + CoLinearAxes
    ///           + LeftHandedAxes
    Output_SetAxisMapping^ SetAxisMapping( Direction i_XAxis, Direction i_YAxis, Direction i_ZAxis )
    {
      ViconDataStreamSDK::CPP::Output_SetAxisMapping CPPOutput( m_pClient->SetAxisMapping( Adapt( i_XAxis ), 
                                                                                           Adapt( i_YAxis ), 
                                                                                           Adapt( i_ZAxis ) ) );
      Output_SetAxisMapping^ Output = gcnew Output_SetAxisMapping();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Get the current Axis mapping.
    ///
    /// See Also: SetAxisMapping()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        Output_GetAxisMapping Output = MyClient.GetAxisMapping();
    ///         // Output.XAxis == ViconDataStreamSDK.DotNET.Direction.Forward
    ///         // Output.YAxis == ViconDataStreamSDK.DotNET.Direction.Left
    ///         // Output.ZAxis == ViconDataStreamSDK.DotNET.Direction.Up
    ///
    /// \return An Output_GetAxisMapping class containing the result of the operation.
    ///         - The Result will be:
    ///           + XAxis, YAxis, ZAxis
    Output_GetAxisMapping^ GetAxisMapping()
    {
      ViconDataStreamSDK::CPP::Output_GetAxisMapping CPPOutput( m_pClient->GetAxisMapping() );

      Output_GetAxisMapping^ Output = gcnew Output_GetAxisMapping();
      Output->XAxis = Adapt( CPPOutput.XAxis );
      Output->YAxis = Adapt( CPPOutput.YAxis );
      Output->ZAxis = Adapt( CPPOutput.ZAxis );

      return Output;
    }

    ///@private
    Output_GetServerOrientation^ GetServerOrientation()
    {
      ViconDataStreamSDK::CPP::Output_GetServerOrientation CPPOutput( m_pClient->GetServerOrientation() );

      Output_GetServerOrientation^ Output = gcnew Output_GetServerOrientation();
      Output->Result = Adapt( CPPOutput.Result );
      Output->Orientation = Adapt( CPPOutput.Orientation );

      return Output;
    }

    /// Request a new frame to be fetched from the Vicon DataStream Server.
    ///
    /// See Also: SetStreamMode()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        Output_GetFrame Output;
    ///        Output = MyClient.GetFrame(); // Output.Result == NotConnected
    ///        MyClient.Connect( "localhost" );
    ///        Output = MyClient.GetFrame(); // Output.Result == Success
    ///
    /// \return An Output_GetFrame class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_GetFrame^ GetFrame()
    {
      ViconDataStreamSDK::CPP::Output_GetFrame CPPOutput( m_pClient->GetFrame() );

      Output_GetFrame^ Output = gcnew Output_GetFrame();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Return the number of the last frame retrieved from the DataStream.
    ///
    /// See Also: GetFrame(), GetTimecode()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_GetFrameNumber Output;
    ///        Output = MyClient.GetFrameNumber(); // Output.Result == NoFrame
    ///                                            // Output.FrameNumber == 0
    ///        MyClient.GetFrame();
    ///        Output = MyClient.GetFrameNumber(); // Output.Result == Success
    ///                                            // Output.FrameNumber >= 1
    ///
    /// \return An Output_GetFrameNumber class containing the result of the operation and the frame number. 
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_GetFrameNumber^ GetFrameNumber()
    {
      ViconDataStreamSDK::CPP::Output_GetFrameNumber CPPOutput( m_pClient->GetFrameNumber() );

      Output_GetFrameNumber^ Output = gcnew Output_GetFrameNumber();
      Output->FrameNumber = Adapt( CPPOutput.FrameNumber );
      Output->Result      = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Return the timecode information for the last frame retrieved from the DataStream. If the stream is valid but timecode is not available, the Output will be Result.Success and the Standard will be None.
    ///
    /// See Also: GetFrame(), GetFrameNumber()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetTimecode Output = MyClient.GetTimecode();
    ///
    ///
    /// \return An Output_GetTimecode class containing the result of the operation and
    ///           + Hours
    ///           + Minutes
    ///           + Seconds
    ///           + Frames
    ///           + SubFrame
    ///           + FieldFlag
    ///           + Standard
    ///           + SubFramesPerFrame
    ///           + UserBits
    ///
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetTimecode^ GetTimecode()
    {
      ViconDataStreamSDK::CPP::Output_GetTimecode CPPOutput( m_pClient->GetTimecode() );
      
      Output_GetTimecode^ Output = gcnew Output_GetTimecode();
      Output->Result            = Adapt( CPPOutput.Result );
      Output->Hours             = Adapt( CPPOutput.Hours );
      Output->Minutes           = Adapt( CPPOutput.Minutes );
      Output->Seconds           = Adapt( CPPOutput.Seconds );
      Output->Frames            = Adapt( CPPOutput.Frames );
      Output->SubFrame          = Adapt( CPPOutput.SubFrame );
      Output->FieldFlag         = Adapt( CPPOutput.FieldFlag );
      Output->Standard          = Adapt( CPPOutput.Standard );
      Output->SubFramesPerFrame = Adapt( CPPOutput.SubFramesPerFrame );
      Output->UserBits          = Adapt( CPPOutput.UserBits );

      return Output;
    }

    /// Return the Vicon camera system frame rate (in Hz) at the time of the last frame retrieved from the DataStream.
    ///
    /// See Also: GetFrame(), GetFrameNumber(), GetTimecode()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetFrameRate Output = MyClient.GetFrameRate ();
    ///
    /// \return An Output_GetFrameRate  class containing the result of the operation and the frame rate in hz.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetFrameRate^ GetFrameRate()
    {
      ViconDataStreamSDK::CPP::Output_GetFrameRate CPPOutput( m_pClient->GetFrameRate() );

      Output_GetFrameRate^ Output = gcnew Output_GetFrameRate();
      Output->FrameRateHz = Adapt( CPPOutput.FrameRateHz );
      Output->Result      = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Return the number of latency measurements that were taken at various stages of the real-time pipeline. This value can be passed into GetLatencySampleName().
    ///
    /// See Also: GetFrame(), GetTimecode(), GetLatencyTotal(), GetLatencySampleName(), GetLatencySampleValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetLatencySampleCount Output = MyClient.GetLatencySampleCount();
    ///
    /// \return An Output_GetLatencySampleCount class containing the result of the operation and the number of samples taken.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetLatencySampleCount^ GetLatencySampleCount()
    {
      ViconDataStreamSDK::CPP::Output_GetLatencySampleCount CPPOutput( m_pClient->GetLatencySampleCount() );

      Output_GetLatencySampleCount^ Output = gcnew Output_GetLatencySampleCount();
      Output->Count  = Adapt( CPPOutput.Count );
      Output->Result = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Return the name of a latency sample. This value can be passed into GetLatencySampleValue().
    ///
    /// See Also: GetFrame(), GetTimecode(), GetLatencyTotal(), GetLatencySampleCount(), GetLatencySampleValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetLatencySampleName Output = MyClient.GetLatencySampleName( 0 );
    ///        // Output.Name == "Data Collected"
    ///
    /// \param LatencySampleIndex The index of the name.
    /// \return An Output_GetLatencySampleName class containing the result of the operation and the name of the latency sample.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetLatencySampleName^ GetLatencySampleName( unsigned int LatencySampleIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetLatencySampleName CPPOutput( m_pClient->GetLatencySampleName( LatencySampleIndex ) );

      Output_GetLatencySampleName^ Output = gcnew Output_GetLatencySampleName();
      Output->Name   = Adapt( CPPOutput.Name );
      Output->Result = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Return the duration of a named latency sample in seconds. This value can be passed into GetLatencySampleValue().
    ///
    /// See Also: GetFrame(), GetTimecode(), GetLatencyTotal(), GetLatencySampleCount(), GetLatencySampleValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetLatencySampleName Output =
    ///        MyClient.GetLatencySampleValue( "Data Collected" );
    ///        // Output.Value == 0.1
    /// 
    /// \param LatencySampleName The name of the latency sample
    /// \return An Output_GetLatencySampleValue class containing the result of the operation and the duration of the latency in seconds.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetLatencySampleValue^ GetLatencySampleValue( String^ LatencySampleName )
    {
      ViconDataStreamSDK::CPP::Output_GetLatencySampleValue CPPOutput( m_pClient->GetLatencySampleValue( Adapt( LatencySampleName ) ) );

      Output_GetLatencySampleValue^ Output = gcnew Output_GetLatencySampleValue();
      Output->Value  = Adapt( CPPOutput.Value );
      Output->Result = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Return the total latency in seconds introduced at various stages of the real-time pipeline. 
    /// If no latency information is available then all latencies will be reported as 0.0.
    ///
    /// See Also: GetFrame(), GetTimecode(), GetLatencySampleCount(), GetLatencySampleName(), GetLatencySampleValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetLatencyTotal Output = MyClient.GetLatencyTotal();
    ///
    /// \return An Output_GetLatencyTotal class containing the result of the operation and the total latency in seconds made from summing the other latencies.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetLatencyTotal^ GetLatencyTotal()
    {
      ViconDataStreamSDK::CPP::Output_GetLatencyTotal CPPOutput( m_pClient->GetLatencyTotal() );

      Output_GetLatencyTotal^ Output = gcnew Output_GetLatencyTotal();
      Output->Total  = Adapt( CPPOutput.Total );
      Output->Result = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Returns the hardware frame number as used by the cameras. This is not reset on synchronization.
    ///
    /// See Also: GetFrameNumber()
    ///
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.GetFrame();
    ///   Output_GetHardwareFrameNumber Output = MyClient.GetHardwareFrameNumber();
    ///
    /// \return An Output_GetHardwareFrameNumber class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_GetHardwareFrameNumber^ GetHardwareFrameNumber()
    {
      ViconDataStreamSDK::CPP::Output_GetHardwareFrameNumber CPPOutput(m_pClient->GetHardwareFrameNumber());

      Output_GetHardwareFrameNumber^ Output = gcnew Output_GetHardwareFrameNumber();
      Output->HardwareFrameNumber = Adapt(CPPOutput.HardwareFrameNumber);
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }
    
    /// Get the number of frame rate types that the server application reports.
    ///
    /// See Also: GetFrameRateName(), GetFrameRateValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetFrameRateCount Output = MyClient.GetFrameRateCount();
    ///
    /// \return An Output_GetFrameRateCount class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_GetFrameRateCount^ GetFrameRateCount()
    {
      ViconDataStreamSDK::CPP::Output_GetFrameRateCount CPPOutput( m_pClient->GetFrameRateCount() );

      Output_GetFrameRateCount^ Output = gcnew Output_GetFrameRateCount();
      Output->Count  = Adapt( CPPOutput.Count );
      Output->Result = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Get the name of a frame rate type at the specified index.
    ///
    /// See Also: GetFrameRateCount(), GetFrameRateValue()
    ///
    ///        A valid index is between 0 and GetFrameRateCount() - 1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetFrameRateCount Output = MyClient.GetFrameRateCount();
    ///        if( Output.Count > 0 )
    ///        {
    ///          Output_GetFrameRateName NameOutput = MyClient.GetFrameRateIndex( 0 );
    ///        }
    ///
    /// \return An Output_GetFrameRateName class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidIndex
    Output_GetFrameRateName^ GetFrameRateName( unsigned int FrameRateIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetFrameRateName CPPOutput( m_pClient->GetFrameRateName( FrameRateIndex ) );

      Output_GetFrameRateName^ Output = gcnew Output_GetFrameRateName();
      Output->Name   = Adapt( CPPOutput.Name );
      Output->Result = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Get the current value of the specified frame rate type.
    ///
    /// See Also: GetFrameRateCount(), GetFrameRateName()
    ///
    ///        A valid name is obtained from GetFrameRateName
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetFrameRateCount Output = MyClient.GetFrameRateCount();
    ///        Output_GetFrameRateName NameOutput = MyClient.GetFrameRateIndex( 0 );
    ///        Output_GetFrameRateValue ValueOutput = MyClient.GetFrameRateValue( NameOutput.Name );
    ///
    /// \return An Output_GetFrameRateValue class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidFrameRateName
    Output_GetFrameRateValue^ GetFrameRateValue( String^ FrameRateName )
    {
      ViconDataStreamSDK::CPP::Output_GetFrameRateValue CPPOutput( m_pClient->GetFrameRateValue( Adapt( FrameRateName ) ) );

      Output_GetFrameRateValue^ Output = gcnew Output_GetFrameRateValue();
      Output->Value  = Adapt( CPPOutput.Value );
      Output->Result = Adapt( CPPOutput.Result );
      
      return Output;
    }

    /// Return the number of subjects in the DataStream. This information can be used in conjunction with GetSubjectName.
    ///
    /// See Also: GetSubjectName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        Output_GetSubjectCount Output;
    ///        Output = MyClient.GetSubjectCount(); // Output.Result == NoFrame
    ///                                             // Ooutput.SubjectCount == 0
    ///        MyClient.GetFrame();
    ///        Output = MyClient.GetSubjectCount(); // Output.Result == Success
    ///                                             // Output.SubjectCount >= 0
    ///
    /// \return An Output_GetSubjectCount class containing the result of the operation and the number of subjects.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetSubjectCount^ GetSubjectCount()
    {
      ViconDataStreamSDK::CPP::Output_GetSubjectCount CPPOutput( m_pClient->GetSubjectCount() );

      Output_GetSubjectCount^ Output = gcnew Output_GetSubjectCount();
      Output->Result       = Adapt( CPPOutput.Result );
      Output->SubjectCount = Adapt( CPPOutput.SubjectCount );
      
      return Output;
    }

    /// Return the name of a subject. This can be passed into segment and marker functions.
    ///
    /// See Also: GetSubjectCount()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSubjectCount OutputGSC;
    ///        OutputGSC = MyClient.GetSubjectCount(); // OutputGSC.Result == Success
    ///                                                // OutputGSC.SubjectCount == 2
    ///        Output_GetSubjectName OutputGSN;
    ///        OutputGSN = MyClient.GetSubjectName(0);// OutputGSN.Result == Success
    ///                                               // OutputGSN.SubjectName == "Al"
    ///        OutputGSN = MyClient.GetSubjectName(1);// OutputGSN.Result == Success
    ///                                               // OutputGSN .SubjectName == "Bob"
    ///        OutputGSN = MyClient.GetSubjectName(2);// OutputGSN.Result == InvalidIndex
    ///                                               // OutputGSN.SubjectName == ""
    ///
    ///
    /// \param Subject Index The index of the subject. A valid Subject Index is between 0 and GetSubjectCount()-1.
    //                                         Matlab: A valid Subject Index is between 1 and GetSubjectCount().
    /// \return An Output_GetSubjectName GetSubjectName class containing the result of the operation and the name of the subject.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetSubjectName^ GetSubjectName( unsigned int SubjectIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetSubjectName CPPOutput( m_pClient->GetSubjectName( SubjectIndex ) );

      Output_GetSubjectName^ Output = gcnew Output_GetSubjectName();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->SubjectName = Adapt( CPPOutput.SubjectName );
      
      return Output;
    }

    /// Return the name of the root segment for a specified subject. This can be passed into segment functions.The root segment is the ancestor of all other segments in the subject.
    ///
    /// See Also: GetSegmentCount(), GetSegmentParentName(), GetSegmentChildCount(), GetSegmentChildName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSubjectRootSegmentName Output;
    ///        Output = MyClient.GetSubjectRootSegmentName( "Bob" );
    ///        // Output.Result == Success
    ///        // Output.SegmentName == "Pelvis"
    ///
    /// \param Subject Name The name of the subject
    /// \return An Output_GetSubjectRootSegmentName class containing the result of the operation and the name of the root segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetSubjectRootSegmentName^ GetSubjectRootSegmentName( String^ SubjectName )
    {
      ViconDataStreamSDK::CPP::Output_GetSubjectRootSegmentName CPPOutput( m_pClient->GetSubjectRootSegmentName( Adapt( SubjectName ) ) );

      Output_GetSubjectRootSegmentName^ Output = gcnew Output_GetSubjectRootSegmentName();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->SegmentName = Adapt( CPPOutput.SegmentName );
      
      return Output;
    }

    /// Return the number of segments for a specified subject in the DataStream. This information can be used in conjunction with GetSegmentName.
    ///
    /// See Also: GetSubjectName(), GetSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.EnableSegmentData();
    ///        MyClient.Connect( "localhost" );
    ///        Output_GetSegmentCount Output;
    ///        Output = MyClient.GetSegmentCount( "Bob" ); // Output.Result == NoFrame
    ///                                                    // Output.SegmentCount == 0
    ///        MyClient.GetFrame();
    ///        Output = MyClient.GetSegmentCount( "Al" ); // Output.Result ==
    ///                                                  // InvalidSubjectName
    ///                                                  // Output.SegmentCount == 0
    ///        Output = MyClient.GetSegmentCount( "Bob" ); // Output.Result == Success
    ///                                                    // Output.SegmentCount >= 0
    ///
    /// \param Subject Name The name of the subject.
    /// \return An Output_GetSegmentCount class containing the result of the operation and the number of segments.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetSegmentCount^ GetSegmentCount( String^ SubjectName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentCount CPPOutput( m_pClient->GetSegmentCount( Adapt( SubjectName ) ) );

      Output_GetSegmentCount^ Output = gcnew Output_GetSegmentCount();
      Output->Result       = Adapt( CPPOutput.Result );
      Output->SegmentCount = Adapt( CPPOutput.SegmentCount );

      return Output;
    }

    /// Return the name of a subject segment specified by index.
    ///
    /// See Also: GetSegmentCount(), GetSegmentChildCount(), GetSegmentChildName(), GetSubjectRootSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentParentName Output;
    ///        // SegmentIndex must be between 0 and GetSegmentCount() - 1
    ///        Output = MyClient.GetSegmentName( "Bob", 0 );
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Index The index of the segment
    /// \return An Output_GetSegmentName  class containing the result of the operation and the name of the parent segment or an empty string if it is the root segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///           + InvalidSubjectName
    Output_GetSegmentName^ GetSegmentName( String^      SubjectName,
                                           unsigned int SegmentIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentName CPPOutput( m_pClient->GetSegmentName( Adapt( SubjectName ), SegmentIndex ) );

      Output_GetSegmentName^ Output = gcnew Output_GetSegmentName();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->SegmentName = Adapt( CPPOutput.SegmentName );
      
      return Output;
    }

    /// Return the name of the parent segment for a specified subject segment. If the specified segment is the root segment of the subject then it will return an empty string.
    ///
    /// See Also: GetSegmentCount(), GetSegmentChildCount(), GetSegmentChildName(), GetSubjectRootSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentParentName Output;
    ///        Output = MyClient.GetSegmentParentName( "Bob", "Pelvis" );
    ///        // Output.Result == Success
    ///        // Output.SegmentName == ""
    ///        // This is the root segment
    ///        Output = MyClient.GetSegmentParentName( "Bob", "LFemur" );
    ///        // Output.Result == Success
    ///        // Output.SegmentName == "Pelvis"
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentParentName  class containing the result of the operation and the name of the parent segment or an empty string if it is the root segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentParentName^ GetSegmentParentName( String^ SubjectName,
                                                       String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentParentName CPPOutput( m_pClient->GetSegmentParentName( Adapt( SubjectName ), Adapt( SegmentName ) ) );

      Output_GetSegmentParentName^ Output = gcnew Output_GetSegmentParentName();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->SegmentName = Adapt( CPPOutput.SegmentName );
      
      return Output;
    }

    /// Return the name of a child segment for a specified subject segment. This can be passed into segment functions.
    ///
    /// See Also: GetSegmentCount()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentChildCount OutputGSCC;
    ///        OutputGSCC = MyClient.GetSegmentChildCount( "Bob", "Pelvis" );
    ///        // OutputGSCC.Result == Success
    ///        // OutputGSCC.SegmentCount == 2
    ///        Output_GetSegmentChildName OutputGSCN;
    ///        OutputGSCN = MyClient.GetSegmentChildName( "Alice", "Pelvis", 0 );
    ///        // OutputGSCN.Result == InvalidSubjectName
    ///        // OutputGSCN.SegmentName == ""
    ///        OutputGSCN = MyClient.GetSegmentChildName( "Bob", "Pelvis", 0 );
    ///        // OutputGSCN.Result == Success
    ///        // OutputGSCN.SegmentName == "LFemur"
    ///        OutputGSCN = MyClient.GetSegmentChildName( "Bob", "Pelvis", 1 );
    ///        // OutputGSCN.Result == Success
    ///        // OutputGSCN.SegmentName == "RFemur"
    ///        OutputGSCN = MyClient.GetSegmentChildName( "Bob", "Pelvis", 2 );
    ///        // OutputGSCN.Result == InvalidIndex
    ///        // OutputGSCN.SegmentName == ""
    ///        // (no third segment)
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \param Segment Index The index of the segment. A valid Segment Index is between 0 and GetSegmentChildCount()-1.
    /// \return An Output_GetSegmentChildCount  class containing the result of the operation and the name of the child segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentChildCount^ GetSegmentChildCount( String^ SubjectName,
                                                       String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentChildCount CPPOutput( m_pClient->GetSegmentChildCount( Adapt( SubjectName ), Adapt( SegmentName ) ) );

      Output_GetSegmentChildCount^ Output = gcnew Output_GetSegmentChildCount();
      Output->Result       = Adapt( CPPOutput.Result );
      Output->SegmentCount = Adapt( CPPOutput.SegmentCount );

      return Output;
    }

    /// Return the name of the child segment for a specified subject segment and index.
    ///
    /// See Also: GetSegmentCount(), GetSegmentChildCount(), GetSegmentChildName(), GetSubjectRootSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentChildName Output;
    ///        // Segment index must be between 0 and GetSegmentChildCount() - 1
    ///        Output = MyClient.GetSegmentChildName( "Bob", "Pelvis", 0 );
    ///
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \param Segment Index The index of the child segment. A valid Segment Index is between 0 and GetSegmentChildCount()-1.
    /// \return An Output_GetSegmentChildName  class containing the result of the operation and the name of the child segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentChildName^ GetSegmentChildName( String^      SubjectName,
                                                     String^      SegmentName,
                                                     unsigned int SegmentIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentChildName CPPOutput( m_pClient->GetSegmentChildName( Adapt( SubjectName ), Adapt( SegmentName ), SegmentIndex ) );

      Output_GetSegmentChildName^ Output = gcnew Output_GetSegmentChildName();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->SegmentName = Adapt( CPPOutput.SegmentName );
      
      return Output;
    }

    /// Return the static pose translation of a subject segment.
    ///
    /// See Also: GetSegmentStaticRotationHelical(), GetSegmentStaticRotationMatrix(), GetSegmentStaticRotationQuaternion(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentStaticTranslation Output =
    ///        MyClient.GetSegmentStaticTranslations( "Alice", "Pelvis" );
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentStaticTranslation class containing the result of the operation and the translation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticTranslation^ GetSegmentStaticTranslation( String^ SubjectName,
                                                                     String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticTranslation CPPOutput( m_pClient->GetSegmentStaticTranslation( 
                                                                              Adapt( SubjectName ), 
                                                                              Adapt( SegmentName ) ) );

      Output_GetSegmentStaticTranslation^ Output = gcnew Output_GetSegmentStaticTranslation();
      Output->Result      = Adapt( CPPOutput.Result );;
      Output->Translation = Adapt( CPPOutput.Translation );

      return Output;
    }

    /// Return the static pose rotation of a subject segment in helical coordinates.
    /// The helical coordinates represent a vector whose length is the amount of rotation in radians, and the direction is the axis about which to rotate.
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationMatrix(), GetSegmentStaticRotationQuaternion(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation, GetSegmentLocalRotationHelical, GetSegmentLocalRotationMatrix, GetSegmentLocalRotationQuaternion, GetSegmentLocalRotationEulerXYZ
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentStaticRotationHelical Output =
    ///        MyClient.GetSegmentStaticRotationHelical( "Alice", "Pelvis" );
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentStaticRotationHelical  class containing the result of the operation and the rotation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationHelical^ GetSegmentStaticRotationHelical( String^ SubjectName,
                                                                             String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationHelical CPPOutput( m_pClient->GetSegmentStaticRotationHelical( 
                                                                                  Adapt( SubjectName ), 
                                                                                  Adapt( SegmentName ) ) );

      Output_GetSegmentStaticRotationHelical^ Output = gcnew Output_GetSegmentStaticRotationHelical();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      
      return Output;
    }

    /// Return the static pose rotation of a subject segment as a 3x3 row-major matrix.
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationHelical(), GetSegmentStaticRotationQuaternion(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentStaticRotationMatrix Output =
    ///        MyClient.GetSegmentStaticRotationMatrix( "Alice", "Pelvis" );
    ///
    /// \param SubjectName The name of the subject
    /// \param SegmentName The name of the segment
    /// \return An Output_GetSegmentStaticRotationMatrix  class containing the result of the operation and the rotation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationMatrix^ GetSegmentStaticRotationMatrix( String^ SubjectName,
                                                                           String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationMatrix CPPOutput( m_pClient->GetSegmentStaticRotationMatrix( 
                                                                                 Adapt( SubjectName ), 
                                                                                 Adapt( SegmentName ) ) );

      Output_GetSegmentStaticRotationMatrix^ Output = gcnew Output_GetSegmentStaticRotationMatrix();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      
      return Output;
    }

    /// Return the static pose rotation of a subject segment in quaternion coordinates.
    /// The quaternion is of the form (x, y, z, w) where w is the real component and x, y and z are the imaginary components. 
    /// N.B. This is different from that used in many other applications, which use (w, x, y, z).
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationHelical(), GetSegmentStaticRotationMatrix(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentStaticRotationQuaternion Output =
    ///        MyClient.GetSegmentStaticRotationQuaternion( "Alice", "Pelvis" );
    ///
    ///
    /// \param SubjectName The name of the subject
    /// \param SegmentName The name of the segment
    /// \return An Output_GetSegmentStaticRotationQuaternion class containing the result of the operation and the rotation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationQuaternion^ GetSegmentStaticRotationQuaternion( String^ SubjectName,
                                                                                   String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationQuaternion CPPOutput( m_pClient->GetSegmentStaticRotationQuaternion( 
                                                                                     Adapt( SubjectName ), 
                                                                                     Adapt( SegmentName ) ) );

      Output_GetSegmentStaticRotationQuaternion^ Output = gcnew Output_GetSegmentStaticRotationQuaternion();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      
      return Output;
    }

    /// Return the static pose rotation of a subject segment in Euler XYZ coordinates.
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationHelical(), GetSegmentStaticRotationMatrix(), 
    /// GetSegmentStaticRotationQuaternion(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), 
    /// GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ().
    /// 
    ///      ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///      MyClient.Connect( "localhost" );
    ///      MyClient.GetFrame();
    ///      Output_GetSegmentStaticRotationEulerXYZ Output =
    ///      MyClient.GetSegmentStaticRotationEulerXYZ( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentStaticRotationEulerXYZ class containing the result of the request
    ///         and the rotation of the segment \f$(x,y,z)\f$. 
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationEulerXYZ^ GetSegmentStaticRotationEulerXYZ( String^ SubjectName,
                                                                               String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationEulerXYZ CPPOutput( m_pClient->GetSegmentStaticRotationEulerXYZ( 
                                                                                   Adapt( SubjectName ), 
                                                                                   Adapt( SegmentName ) ) );

      Output_GetSegmentStaticRotationEulerXYZ^ Output = gcnew Output_GetSegmentStaticRotationEulerXYZ();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      
      return Output;
    }

    Output_GetSegmentStaticScale^ GetSegmentStaticScale(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticScale CPPOutput(m_pClient->GetSegmentStaticScale(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentStaticScale^ Output = gcnew Output_GetSegmentStaticScale();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Scale = Adapt(CPPOutput.Scale);

      return Output;
    }

    /// Return the translation of a subject segment in global coordinates.
    /// The translation is of the form ( x, y, z ) where x, y and z are in millimeters with respect to the global origin.
    ///
    /// See Also: GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentGlobalTranslation Output =
    ///        MyClient.GetSegmentGlobalTranslations( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalTranslation class containing the result of the operation, the translation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///            + Success
    ///            + NotConnected
    ///            + NoFrame
    ///            + InvalidSubjectName
    ///            + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the translation will be [0,0,0].
    Output_GetSegmentGlobalTranslation^ GetSegmentGlobalTranslation( String^ SubjectName,
                                                                     String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalTranslation CPPOutput( m_pClient->GetSegmentGlobalTranslation( 
                                                                              Adapt( SubjectName ), 
                                                                              Adapt( SegmentName ) ) );

      Output_GetSegmentGlobalTranslation^ Output = gcnew Output_GetSegmentGlobalTranslation();
      Output->Result      = Adapt( CPPOutput.Result );;
      Output->Translation = Adapt( CPPOutput.Translation );
      Output->Occluded    = Adapt( CPPOutput.Occluded );;

      return Output;
    }

    /// Return the rotation of a subject segment in global helical coordinates.
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentGlobalRotationHelical Output =
    ///        MyClient.GetSegmentGlobalRotationHelical( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationHelical class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case, the rotation will be [0,0,0].
    Output_GetSegmentGlobalRotationHelical^ GetSegmentGlobalRotationHelical( String^ SubjectName,
                                                                             String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationHelical CPPOutput( m_pClient->GetSegmentGlobalRotationHelical( 
                                                                                  Adapt( SubjectName ), 
                                                                                  Adapt( SegmentName ) ) );

      Output_GetSegmentGlobalRotationHelical^ Output = gcnew Output_GetSegmentGlobalRotationHelical();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the rotation of a subject segment as a 3x3 row-major matrix in global coordinates.
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentGlobalRotationMatrix Output =
    ///        MyClient.GetSegmentGlobalRotationMatrix( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationMatrix  Class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame.
    Output_GetSegmentGlobalRotationMatrix^ GetSegmentGlobalRotationMatrix( String^ SubjectName,
                                                                           String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationMatrix CPPOutput( m_pClient->GetSegmentGlobalRotationMatrix( 
                                                                                 Adapt( SubjectName ), 
                                                                                 Adapt( SegmentName ) ) );

      Output_GetSegmentGlobalRotationMatrix^ Output = gcnew Output_GetSegmentGlobalRotationMatrix();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the rotation of a subject segment in global quaternion coordinates.
    /// The quaternion is of the form (x, y, z, w) where w is the real component and x, y and z are the imaginary components. 
    /// N.B. This is different from that used in many other applications, which use (w, x, y, z).
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentGlobalRotationQuaternion Output =
    ///        MyClient.GetSegmentGlobalRotationQuaternion( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationQuaternion  class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the Rotation will be [1,0,0,0].
    Output_GetSegmentGlobalRotationQuaternion^ GetSegmentGlobalRotationQuaternion( String^ SubjectName,
                                                                                   String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationQuaternion CPPOutput( m_pClient->GetSegmentGlobalRotationQuaternion( 
                                                                                     Adapt( SubjectName ), 
                                                                                     Adapt( SegmentName ) ) );

      Output_GetSegmentGlobalRotationQuaternion^ Output = gcnew Output_GetSegmentGlobalRotationQuaternion();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the rotation of a subject segment in global Euler XYZ coordinates.
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentGlobalRotationEulerXYZ Output =
    ///        MyClient.GetSegmentGlobalRotationEulerXYZ( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationEulerXYZ class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the rotation will be [0,0,0].
    Output_GetSegmentGlobalRotationEulerXYZ^ GetSegmentGlobalRotationEulerXYZ( String^ SubjectName,
                                                                               String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationEulerXYZ CPPOutput( m_pClient->GetSegmentGlobalRotationEulerXYZ( 
                                                                                   Adapt( SubjectName ), 
                                                                                   Adapt( SegmentName ) ) );

      Output_GetSegmentGlobalRotationEulerXYZ^ Output = gcnew Output_GetSegmentGlobalRotationEulerXYZ();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the translation of a subject segment in local coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData();
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentLocalTranslation Output =
    ///        MyClient.GetSegmentLocalTranslations( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalTranslation class containing the result of the operation, the translation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the translation will be [0,0,0].
    Output_GetSegmentLocalTranslation^ GetSegmentLocalTranslation( String^ SubjectName,
                                                                   String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalTranslation CPPOutput( m_pClient->GetSegmentLocalTranslation( 
                                                                             Adapt( SubjectName ), 
                                                                             Adapt( SegmentName ) ) );

      Output_GetSegmentLocalTranslation^ Output = gcnew Output_GetSegmentLocalTranslation();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->Translation = Adapt( CPPOutput.Translation );
      Output->Occluded    = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the rotation of a subject segment in local helical coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentLocalRotationHelical Output =
    ///        MyClient.GetSegmentLocalRotationHelical( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationHelical class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the Rotation will be [0,0,0].
    Output_GetSegmentLocalRotationHelical^ GetSegmentLocalRotationHelical( String^ SubjectName,
                                                                           String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationHelical CPPOutput( m_pClient->GetSegmentLocalRotationHelical( 
                                                                                 Adapt( SubjectName ), 
                                                                                 Adapt( SegmentName ) ) );

      Output_GetSegmentLocalRotationHelical^ Output = gcnew Output_GetSegmentLocalRotationHelical();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the rotation row-major matrix of a subject segment in local coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix() , GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentLocalRotationMatrix Output =
    ///        MyClient.GetSegmentLocalRotationMatrix( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationMatrix class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame.
    Output_GetSegmentLocalRotationMatrix^ GetSegmentLocalRotationMatrix( String^ SubjectName,
                                                                         String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationMatrix CPPOutput( m_pClient->GetSegmentLocalRotationMatrix( 
                                                                                Adapt( SubjectName ), 
                                                                                Adapt( SegmentName ) ) );

      Output_GetSegmentLocalRotationMatrix^ Output = gcnew Output_GetSegmentLocalRotationMatrix();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );

      return Output;
    }

    /// Return the rotation of a subject segment in local quaternion coordinates relative to its parent segment.
    /// The quaternion is of the form (x, y, z, w) where w is the real component and x, y and z are the imaginary components. N.B. This is different from that used in many other applications, which use (w, x, y, z).
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentLocalRotationQuaternion Output =
    ///        MyClient.GetSegmentLocalRotationQuaternion( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationQuaternion class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the rotation will be [1,0,0,0].
    Output_GetSegmentLocalRotationQuaternion^ GetSegmentLocalRotationQuaternion( String^ SubjectName,
                                                                                 String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationQuaternion CPPOutput( m_pClient->GetSegmentLocalRotationQuaternion( 
                                                                                    Adapt( SubjectName ), 
                                                                                    Adapt( SegmentName ) ) );

      Output_GetSegmentLocalRotationQuaternion^ Output = gcnew Output_GetSegmentLocalRotationQuaternion();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );

      return Output;
    }

    /// Return the rotation of a subject segment in local Euler XYZ coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix() , GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetSegmentLocalRotationEulerXYZ Output =
    ///        MyClient.GetSegmentLocalRotationEulerXYZ( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationEulerXYZ class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the rotation will be [0,0,0].
    Output_GetSegmentLocalRotationEulerXYZ^ GetSegmentLocalRotationEulerXYZ( String^ SubjectName,
                                                                             String^ SegmentName )
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationEulerXYZ CPPOutput( m_pClient->GetSegmentLocalRotationEulerXYZ( 
                                                                                  Adapt( SubjectName ), 
                                                                                  Adapt( SegmentName ) ) );

      Output_GetSegmentLocalRotationEulerXYZ^ Output = gcnew Output_GetSegmentLocalRotationEulerXYZ();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Rotation = Adapt( CPPOutput.Rotation );
      Output->Occluded = Adapt( CPPOutput.Occluded );

      return Output;
    }

    /// Return the quality score for a specified Object (Subject). This is only implemented by Tracker.
    ///
    /// See Also: GetSubjectCount(), GetSubjectName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.EnableSegmentData ();
    ///        MyClient.Connect( "localhost" );
    ///        Output_GetMarkerCount Output;
    ///        Output = MyClient.GetObjectQuality( "Object" );
    ///        // Output.Result == NoFrame
    ///        // Output.Quality == 0
    ///        MyClient.GetFrame();
    ///        Output = MyClient.GetObjectQuality( "Camera" );
    ///        // Output.Result == InvalidSubjectName
    ///        // Output.Quality == 0
    ///        // (no "Camera")
    ///        Output = MyClient.GetObjectQuality( "Object" );
    ///        // Output.Result == Success
    ///        // Output.Quality >= 0 && Output.Quality >= 1.0
    ///
    /// \param  ObjectName The name of the subject.
    /// \return An Output_GetObjectQuality class containing the result of the operation and the quality score of the object.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    Output_GetObjectQuality^ GetObjectQuality( String^ ObjectName )
    {
      ViconDataStreamSDK::CPP::Output_GetObjectQuality CPPOutput( m_pClient->GetObjectQuality( Adapt( ObjectName ) ) );

      Output_GetObjectQuality^ Output = gcnew Output_GetObjectQuality();
      Output->Result = Adapt( CPPOutput.Result );
      Output->Quality = Adapt( CPPOutput.Quality );

      return Output;
    }

    /// Return the number of markers for a specified subject in the DataStream. This information can be used in conjunction with GetMarkerName.
    ///
    /// See Also: GetSubjectName(), GetMarkerName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.EnableMarkerData();
    ///        MyClient.Connect( "localhost" );
    ///        Output_GetMarkerCount Output;
    ///        Output = MyClient.GetMarkerCount( "Bob" ); // Output.Result == NoFrame
    ///                                                   // Output.MarkerCount == 0
    ///        MyClient.GetFrame();
    ///        Output = MyClient.GetMarkerCount( "Alice" );
    ///        // Output.Result == InvalidSubjectName
    ///        // Output.MarkerCount == 0
    ///        // (no "Alice")
    ///        Output = MyClient.GetMarkerCount( "Bob" ); // Output.Result == Success
    ///                                                   // Output.MarkerCount >= 0
    ///
    /// \param  SubjectName The name of the subject.
    /// \return An Output_GetMarkerCount class containing the result of the operation, and the number of markers.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    Output_GetMarkerCount^ GetMarkerCount( String^ SubjectName )
    {
      ViconDataStreamSDK::CPP::Output_GetMarkerCount CPPOutput( m_pClient->GetMarkerCount( Adapt( SubjectName ) ) );

      Output_GetMarkerCount^ Output = gcnew Output_GetMarkerCount();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->MarkerCount = Adapt( CPPOutput.MarkerCount );
      
      return Output;
    }

    /// Return the name of a marker for a specified subject. This can be passed into GetMarkerGlobalTranslation.
    ///
    /// See Also: GetMarkerCount(), GetMarkerGlobalTranslation()
    ///
    ///        A valid Marker Index is between 0 and GetMarkerCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableMarkerData();
    ///        MyClient.GetFrame();
    ///        Output_GetMarkerCount OutputGMC;
    ///        OutputGMC = MyClient.GetMarkerCount( "Bob" );
    ///        // OutputGMC.Result == Success
    ///        // OutputGMC.MarkerCount == 2
    ///        Output_GetMarkerName OutputGMN;
    ///        OutputGMN = MyClient.GetMarkerName( "Alice", 0 );
    ///        // OutputGMN.Result == InvalidSubjectName
    ///        // OutputGMN.MarkerName == ""
    ///        // (no "Alice")
    ///        OutputGMN = MyClient.GetMarkerName( "Bob", 0 );
    ///        // OutputGMN.Result == Success
    ///        // OutputGMN.MarkerName == "LASI"
    ///        OutputGMN = MyClient.GetMarkerName( "Bob", 1 );
    ///        // OutputGMN.Result == Success
    ///        // OutputGMN.MarkerName == "RASI"
    ///        OutputGMN = MyClient.GetMarkerName( "Bob", 2 );
    ///        // OutputGMN.Result == InvalidIndex
    ///        // OutputGMN.MarkerName == ""
    ///        // (no third marker)
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  MarkerIndex The index of the marker.
    /// \return An Output_GetMarkerName class containing the result of the operation and the name of the marker.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidIndex
    Output_GetMarkerName^ GetMarkerName( String^      SubjectName,
                                         unsigned int MarkerIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetMarkerName CPPOutput( m_pClient->GetMarkerName( Adapt( SubjectName ), 
                                                                                         Adapt( MarkerIndex ) ) );

      Output_GetMarkerName^ Output = gcnew Output_GetMarkerName();
      Output->Result     = Adapt( CPPOutput.Result );
      Output->MarkerName = Adapt( CPPOutput.MarkerName );
      
      return Output;
    }

    /// Return the name of the segment that is the parent of this marker.
    ///
    /// See Also: GetMarkerCount(), GetMarkerName(), GetMarkerGlobalTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableMarkerData();
    ///        MyClient.GetFrame();
    ///        Output_GetMarkerParentName Output;
    ///        Output = MyClient.GetMarkerParentName( "Bob", "LFHD" );
    ///        // Output.Result == Success
    ///        // Output.SegmentName == "Head"
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  MarkerName The name of the marker.
    /// \return An Output_GetMarkerParentName class containing the result of the operation and the name of the parent segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidMarkerName
    Output_GetMarkerParentName^ GetMarkerParentName( String^ SubjectName,
                                                     String^ MarkerName )
    {
      ViconDataStreamSDK::CPP::Output_GetMarkerParentName CPPOutput( m_pClient->GetMarkerParentName( Adapt( SubjectName ), Adapt( MarkerName ) ) );

      Output_GetMarkerParentName^ Output = gcnew Output_GetMarkerParentName();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->SegmentName = Adapt( CPPOutput.SegmentName );
      
      return Output;
    }

    /// Return the translation of a subject marker in global coordinates.
    /// The Translation is of the form ( x, y, z ) where x, y and z are in millimeters with respect to the global origin.
    ///
    /// See Also: GetMarkerName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableMarkerData();
    ///        MyClient.GetFrame();
    ///        Output_GetMarkerGlobalTranslation Output =
    ///        MyClient.GetMarkerGlobalTranslation( "Alice", "LASI" );
    //
    /// \param  SubjectName The name of the subject.
    /// \param  MarkerName The name of the marker.
    /// \return An Output_GetMarkerGlobalTranslation class containing the result of the operation, the translation of the marker, and whether the marker is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidMarkerName
    ///         - Occluded will be true if the marker was absent at this frame. In this case the Translation will be [0,0,0].
    Output_GetMarkerGlobalTranslation^ GetMarkerGlobalTranslation( String^ SubjectName,
                                                                   String^ MarkerName )
    {
      ViconDataStreamSDK::CPP::Output_GetMarkerGlobalTranslation CPPOutput( m_pClient->GetMarkerGlobalTranslation( 
                                                                             Adapt( SubjectName ), 
                                                                             Adapt( MarkerName ) ) );

      Output_GetMarkerGlobalTranslation^ Output = gcnew Output_GetMarkerGlobalTranslation();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->Translation = Adapt( CPPOutput.Translation );
      Output->Occluded    = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the number of rays that are contributing to a labeled marker in the DataStream. This information can be used in conjunction with GetMarkerRayContribution.
    ///
    /// See Also: GetMarkerRayContribution(), EnableMarkerRayData(), DisableMarkerRayData(), IsMarkerRayDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableMarkerRayData();
    ///        MyClient.GetFrame();
    ///        Output_GetMarkerRayContributionCount Output =
    ///        MyClient.GetMarkerRayContributionCount( "Alice", "LASI" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  MarkerName The name of the marker.
    /// \return An Output_GetMarkerRayContributionCount class containing the result of the operation and the number of rays.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidMarkerName
    Output_GetMarkerRayContributionCount^ GetMarkerRayContributionCount( String^ SubjectName, String^ MarkerName )
    {
      ViconDataStreamSDK::CPP::Output_GetMarkerRayContributionCount CPPOutput( m_pClient->GetMarkerRayContributionCount( Adapt( SubjectName ), Adapt( MarkerName ) ) );
      
      Output_GetMarkerRayContributionCount^ Output = gcnew Output_GetMarkerRayContributionCount();
      Output->Result = Adapt( CPPOutput.Result );
      Output->RayContributionsCount = Adapt( CPPOutput.RayContributionsCount );

      return Output;
    }

    /// Return the camera ID for an indexed ray that is contributing to a labeled marker in the DataStream. This information can be used in conjunction with GetMarkerRayContributionCount.
    ///
    /// See Also: GetMarkerRayContributionCount(), EnableMarkerRayData(), DisableMarkerRayData(), IsMarkerRayDataEnabled()
    ///
    ///        A valid Ray Index is between 0 and GetMarkerRayContributionCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableMarkerRayData();
    ///        MyClient.GetFrame();
    ///        Output_GetMarkerRayContribution Output =
    ///        MyClient.GetMarkerRayContribution( "Alice", "LASI", 0 );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  MarkerName The name of the marker.
    /// \param  MarkerRayContributionIndex The index of the ray required.
    /// \return An Output_GetMarkerRayContribution class containing the result of the operation, the camera ID of the camera producing the ray and the index of the centroid resulting from the ray.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidMarkerName
    Output_GetMarkerRayContribution^ GetMarkerRayContribution( String^ SubjectName, String^ MarkerName, unsigned int MarkerRayContributionIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetMarkerRayContribution CPPOutput( m_pClient->GetMarkerRayContribution( Adapt( SubjectName ), Adapt( MarkerName ), MarkerRayContributionIndex ) );

      Output_GetMarkerRayContribution^ Output = gcnew Output_GetMarkerRayContribution();
      Output->Result = Adapt( CPPOutput.Result );
      Output->CameraID = Adapt( CPPOutput.CameraID );
      Output->CentroidIndex = Adapt( CPPOutput.CentroidIndex );

      return Output;
    }

    /// Return the number of unlabeled markers in the DataStream. This information can be used in conjunction with GetGlobalUnlabeledMarkerTranslation
    ///
    /// See Also: GetGlobalUnlabeledMarkerTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new  ViconDataStreamSDK.DotNET.Client(); 
    ///        MyClient.EnableUnlabeledMarkerData(); 
    ///        MyClient.Connect("localhost"); 
    ///        MyClient.GetFrame();
    ///        Output_GetUnlabeledMarkerCount Output = MyClient.GetUnlabeledMarkerCount(); 
    ///        // Output.Result == Success                                       
    ///        // Output.MarkerCount >= 0    
    ///
    /// \return An Output_GetUnlabeledMarkerCount class containing the result of the operation and the number of markers.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetUnlabeledMarkerCount^ GetUnlabeledMarkerCount()
    {
      ViconDataStreamSDK::CPP::Output_GetUnlabeledMarkerCount CPPOutput( m_pClient->GetUnlabeledMarkerCount() );

      Output_GetUnlabeledMarkerCount^ Output = gcnew Output_GetUnlabeledMarkerCount();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->MarkerCount = Adapt( CPPOutput.MarkerCount );

      return Output;
    }

    /// Return the translation of an unlabeled marker in global coordinates.
    /// The Translation is of the form ( x, y, z ) where x, y and z are in millimeters with respect to the global origin.
    ///
    /// See Also: GetUnlabeledMarkerCount()
    ///
    ///        A valid Marker Index is between 0 and GetUnlabeledMarkerCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableUnlabeledMarkerData();
    ///        MyClient.GetFrame();
    ///        Output_GetUnlabeledMarkerGlobalTranslation Output =
    ///        MyClient.GetUnlabeledMarkerGlobalTranslation( 0 );
    ///
    /// \param MarkerIndex The index of the marker
    /// \return An Output_GetUnlabeledMarkerGlobalTranslation class containing the result of the operation and the translation of the marker.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetUnlabeledMarkerGlobalTranslation^ GetUnlabeledMarkerGlobalTranslation( unsigned int MarkerIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetUnlabeledMarkerGlobalTranslation CPPOutput( m_pClient->GetUnlabeledMarkerGlobalTranslation( MarkerIndex ) );

      Output_GetUnlabeledMarkerGlobalTranslation^ Output = gcnew Output_GetUnlabeledMarkerGlobalTranslation();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->Translation = Adapt( CPPOutput.Translation );
      Output->MarkerID    = Adapt( CPPOutput.MarkerID );
      return Output;
    }

    /// Return the number of labeled markers in the DataStream. This information can be used in conjunction with GetGlobalLabeledMarkerTranslation
    ///
    /// See Also: GetGlobalLabeledMarkerTranslation()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new  ViconDataStreamSDK.DotNET.Client(); 
    ///        MyClient.EnableMarkerData(); 
    ///        MyClient.Connect("localhost"); 
    ///        MyClient.GetFrame();
    ///        Output_GetLabeledMarkerCount Output = MyClient.GetLabeledMarkerCount(); 
    ///        // Output.Result == Success                                       
    ///        // Output.MarkerCount >= 0    
    ///
    /// \return An Output_GetLabeledMarkerCount class containing the result of the operation and the number of markers.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetLabeledMarkerCount^ GetLabeledMarkerCount()
    {
      ViconDataStreamSDK::CPP::Output_GetLabeledMarkerCount CPPOutput(m_pClient->GetLabeledMarkerCount());

      Output_GetLabeledMarkerCount^ Output = gcnew Output_GetLabeledMarkerCount();
      Output->Result = Adapt(CPPOutput.Result);
      Output->MarkerCount = Adapt(CPPOutput.MarkerCount);

      return Output;
    }

    /// Return the translation of an labeled marker in global coordinates.
    /// The Translation is of the form ( x, y, z ) where x, y and z are in millimeters with respect to the global origin.
    ///
    /// See Also: GetLabeledMarkerCount()
    ///
    ///        A valid Marker Index is between 0 and GetLabeledMarkerCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableMarkerData();
    ///        MyClient.GetFrame();
    ///        Output_GetLabeledMarkerGlobalTranslation Output =
    ///        MyClient.GetLabeledMarkerGlobalTranslation( 0 );
    ///
    /// \param MarkerIndex The index of the marker
    /// \return An Output_GetLabeledMarkerGlobalTranslation class containing the result of the operation and the translation of the marker.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetLabeledMarkerGlobalTranslation^ GetLabeledMarkerGlobalTranslation(unsigned int MarkerIndex)
    {
      ViconDataStreamSDK::CPP::Output_GetLabeledMarkerGlobalTranslation CPPOutput(m_pClient->GetLabeledMarkerGlobalTranslation(MarkerIndex));

      Output_GetLabeledMarkerGlobalTranslation^ Output = gcnew Output_GetLabeledMarkerGlobalTranslation();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Translation = Adapt(CPPOutput.Translation);
      Output->MarkerID = Adapt( CPPOutput.MarkerID );
      return Output;
    }

    /// Return the number of force plates, EMGs, and other devices in the DataStream. This information can be used in conjunction with GetDeviceName.
    ///
    /// See Also: GetDeviceName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new  ViconDataStreamSDK.DotNET.Client(); 
    ///        MyClient.EnableDeviceData(); 
    ///        MyClient.Connect("localhost"); 
    ///        MyClient.GetFrame();
    ///        
    ///        Output_GetDeviceCount Output = MyClient.GetDeviceCount();                                         
    // Output.Result == Success                                        
    // Output.DeviceCount >= 0    
    ///
    /// \return An Output_GetDeviceCount class containing the result of the operation and the number of devices.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetDeviceCount^ GetDeviceCount()
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceCount CPPOutput( m_pClient->GetDeviceCount() );

      Output_GetDeviceCount^ Output = gcnew Output_GetDeviceCount();
      Output->Result      = Adapt( CPPOutput.Result );
      Output->DeviceCount = Adapt( CPPOutput.DeviceCount );
      
      return Output;
    }

    /// Return the name and type of a device. This name can be passed into device functions.
    ///
    /// See Also: GetDeviceCount(), GetDeviceOutputCount(), GetDeviceOutputValue()
    ///
    ///        A valid Device Index is between 0 and GetDeviceCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceCount OutputGDC;
    ///        OutputGDC = MyClient.GetDeviceCount( DeviceCount );
    ///        // OutputGDC.Result == Success
    ///        // OutputGDC.DeviceCount == 2
    ///        Output_GetDeviceName OutputGDN;
    ///        OutputGDN = MyClient.GetDeviceName( 0 );
    ///        // OutputGDN.Result == Success
    ///        // OutputGDN.DeviceName == "ZeroWire"
    ///        // OutputGDN.DeviceType == Unknown
    ///        OutputGDN = MyClient.GetDeviceName( 1 );
    ///        // OutputGDN.Result == Success
    ///        // OutputGDN.DeviceName == "AMTI #1"
    ///        // OutputGDN.DeviceType == ForcePlate
    ///        OutputGDN = MyClient.GetDeviceName( 2 );
    ///        // OutputGDN.Result == InvalidIndex
    ///        // OutputGDN.DeviceName == ""
    ///        // OutputGDN.DeviceType == Unknown
    ///
    /// \param DeviceIndex The index of the device.
    /// \return An Output_GetDeviceName class containing the result of the operation, the name of the device, and the device type.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///         The Device Type will be:
    ///           + Unknown
    ///           + ForcePlate
    Output_GetDeviceName^ GetDeviceName( unsigned int DeviceIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceName CPPOutput( m_pClient->GetDeviceName( DeviceIndex ) );

      Output_GetDeviceName^ Output = gcnew Output_GetDeviceName();
      Output->Result     = Adapt( CPPOutput.Result );
      Output->DeviceName = Adapt( CPPOutput.DeviceName );
      Output->DeviceType = Adapt( CPPOutput.DeviceType );
      
      return Output;
    }

    /// Return the number of outputs for a device in the DataStream. This information can be used in conjunction with GetDeviceOutputName.
    ///
    /// See Also: GetDeviceName(), GetDeviceOutputName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputCount Output;
    ///        Output = MyClient.GetDeviceOutputCount( "DataGlove" );
    ///        // Output.Result == InvalidDeviceName
    ///        // Output.DeviceOutputCount == 0
    ///        // (no "DataGlove" device)
    ///        Output = MyClient.GetDeviceOutputCount( "ZeroWire" );
    ///        // Output.Result == Success
    ///        // Output.DeviceOutputCount == 6
    ///
    /// \param DeviceName The device name
    /// \return An Output_GetDeviceOutputCount class containing the result of the operation and the number of device outputs.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    Output_GetDeviceOutputCount^ GetDeviceOutputCount( String^ DeviceName )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputCount CPPOutput( m_pClient->GetDeviceOutputCount( 
                                                                       Adapt( DeviceName ) ) );

      Output_GetDeviceOutputCount^ Output = gcnew Output_GetDeviceOutputCount();
      Output->Result            = Adapt( CPPOutput.Result );
      Output->DeviceOutputCount = Adapt( CPPOutput.DeviceOutputCount );
      
      return Output;
    }

    /// Return the name and SI unit of a device output. This name can be passed into GetDeviceOutputValue.
    ///
    /// See Also: GetDeviceCount(), GetDeviceOutputCount(), GetDeviceOutputValue()
    ///
    ///        A valid Device Output Index is between 0 and GetDeviceOutputCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputName Output =
    ///        MyClient.GetDeviceOutputName( "AMTI", 0 );
    ///        // Output.Result == Success
    ///        // Output.DeviceOutputName == "Fx"
    ///        // Output.DeviceOutputUnit == Newton
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputIndex The index of the device output
    /// \return An Output_GetDeviceOutputName class containing the result of the operation, the name of the device output and the unit of the device output.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///
    ///         - The DeviceOutputName could be:
    ///           + "Fx" - Force X
    ///           + "Fy" - Force Y
    ///           + "Fz" - Force Z
    ///           + "Mx" - Moment X
    ///           + "My" - Moment Y
    ///           + "Mz" - Moment Z
    ///           + "Cx" - Center Of Pressure X
    ///           + "Cy" - Center Of Pressure Y
    ///           + "Cz" - Center Of Pressure Z
    ///           + "Pin1" - Analog Input 1
    ///           + "Pin2" - Analog Input 2
    //
    ///         - The Device Output Unit will be:
    ///           + Unit.Unknown
    ///           + Unit.Volt
    ///           + Unit.Newton
    ///           + Unit.NewtonMeter
    ///           + Unit.Meter
    ///           + Unit.Kilogram
    ///           + Unit.Second
    ///           + Unit.Ampere
    ///           + Unit.Kelvin
    ///           + Unit.Mole
    ///           + Unit.Candela
    ///           + Unit.Radian
    ///           + Unit.Steradian
    ///           + Unit.MeterSquared
    ///           + Unit.MeterCubed
    ///           + Unit.MeterPerSecond
    ///           + Unit.MeterPerSecondSquared
    ///           + Unit.RadianPerSecond
    ///           + Unit.RadianPerSecondSquared
    ///           + Unit.Hertz
    ///           + Unit.Joule
    ///           + Unit.Watt
    ///           + Unit.Pascal
    ///           + Unit.Lumen
    ///           + Unit.Lux
    ///           + Unit.Coulomb
    ///           + Unit.Ohm
    ///           + Unit.Farad
    ///           + Unit.Weber
    ///           + Unit.Tesla
    ///           + Unit.Henry
    ///           + Unit.Siemens
    ///           + Unit.Becquerel
    ///           + Unit.Gray
    ///           + Unit.Sievert
    ///           + Unit.Katal
    Output_GetDeviceOutputName^ GetDeviceOutputName( String^      DeviceName,
      unsigned int DeviceOutputIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputName CPPOutput( m_pClient->GetDeviceOutputName(
        Adapt( DeviceName ),
        Adapt( DeviceOutputIndex ) ) );

      Output_GetDeviceOutputName^ Output = gcnew Output_GetDeviceOutputName();
      Output->Result = Adapt( CPPOutput.Result );
      Output->DeviceOutputName = Adapt( CPPOutput.DeviceOutputName );
      Output->DeviceOutputUnit = Adapt( CPPOutput.DeviceOutputUnit );

      return Output;
    }

    /// Return the name, component name and SI unit of a device output. This name can be passed into GetDeviceOutputValue.
    ///
    /// See Also: GetDeviceCount(), GetDeviceOutputCount(), GetDeviceOutputValue()
    ///
    ///        A valid Device Output Index is between 0 and GetDeviceOutputCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputComponentName Output =
    ///        MyClient.GetDeviceOutputComponentName( "AMTI", 0 );
    ///        // Output.Result == Success
    ///        // Output.DeviceOutputName == "Force"
    ///        // Output.DeviceOutputComponentName == "Fx"
    ///        // Output.DeviceOutputUnit == Newton
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputIndex The index of the device output
    /// \return An Output_GetDeviceOutputComponentName class containing the result of the operation, the name of the device output and the unit of the device output.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///
    ///         - The DeviceOutputName could be:
    ///           + Force
    ///           + Moment
    ///           + CoP
    ///         - The DeviceOutputComponentName could be:
    ///           + "Fx" - Force X
    ///           + "Fy" - Force Y
    ///           + "Fz" - Force Z
    ///           + "Mx" - Moment X
    ///           + "My" - Moment Y
    ///           + "Mz" - Moment Z
    ///           + "Cx" - Center Of Pressure X
    ///           + "Cy" - Center Of Pressure Y
    ///           + "Cz" - Center Of Pressure Z
    ///           + "Pin1" - Analog Input 1
    ///           + "Pin2" - Analog Input 2
    //
    ///         - The Device Output Unit will be:
    ///           + Unit.Unknown
    ///           + Unit.Volt
    ///           + Unit.Newton
    ///           + Unit.NewtonMeter
    ///           + Unit.Meter
    ///           + Unit.Kilogram
    ///           + Unit.Second
    ///           + Unit.Ampere
    ///           + Unit.Kelvin
    ///           + Unit.Mole
    ///           + Unit.Candela
    ///           + Unit.Radian
    ///           + Unit.Steradian
    ///           + Unit.MeterSquared
    ///           + Unit.MeterCubed
    ///           + Unit.MeterPerSecond
    ///           + Unit.MeterPerSecondSquared
    ///           + Unit.RadianPerSecond
    ///           + Unit.RadianPerSecondSquared
    ///           + Unit.Hertz
    ///           + Unit.Joule
    ///           + Unit.Watt
    ///           + Unit.Pascal
    ///           + Unit.Lumen
    ///           + Unit.Lux
    ///           + Unit.Coulomb
    ///           + Unit.Ohm
    ///           + Unit.Farad
    ///           + Unit.Weber
    ///           + Unit.Tesla
    ///           + Unit.Henry
    ///           + Unit.Siemens
    ///           + Unit.Becquerel
    ///           + Unit.Gray
    ///           + Unit.Sievert
    ///           + Unit.Katal
    Output_GetDeviceOutputComponentName^ GetDeviceOutputComponentName( String^      DeviceName,
      unsigned int DeviceOutputIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputComponentName CPPOutput( m_pClient->GetDeviceOutputComponentName(
        Adapt( DeviceName ),
        Adapt( DeviceOutputIndex ) ) );

      Output_GetDeviceOutputComponentName^ Output = gcnew Output_GetDeviceOutputComponentName();
      Output->Result = Adapt( CPPOutput.Result );
      Output->DeviceOutputName = Adapt( CPPOutput.DeviceOutputName );
      Output->DeviceOutputComponentName = Adapt( CPPOutput.DeviceOutputComponentName );
      Output->DeviceOutputUnit = Adapt( CPPOutput.DeviceOutputUnit );

      return Output;
    }

    /// Return the value of a device output. If there are multiple samples for a frame, then the first sample is returned.
    /// The force plate data provided in the individual device channels is in a coordinate system local to the force plate aligned Z upwards, Y towards the front of the force plate. 
    /// This coordinate system is located at the center of the top surface of the force plate. Any plate origin offset has been accounted for in the moment data. These are forces not reactions.
    ///
    /// See Also: GetDeviceCount(), GetDeviceOutputCount(), GetDeviceOutputName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputValue Output =
    ///        MyClient.GetDeviceOutputValue( "AMTI", "Fx" );
    ///        // Output.Result == Success
    ///        // Output.Value == ?
    ///        // Output.Occluded = ?
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputName The name of the device output
    /// \return An Output_GetDeviceOutputValue  class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    ///           + InvalidDeviceOutputName
    Output_GetDeviceOutputValue^ GetDeviceOutputValue( String^  DeviceName,
                                                       String^  DeviceOutputName )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputValue CPPOutput( m_pClient->GetDeviceOutputValue( 
                                                                       Adapt( DeviceName ), 
                                                                       Adapt( DeviceOutputName ) ) );

      Output_GetDeviceOutputValue^ Output = gcnew Output_GetDeviceOutputValue();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Value    = Adapt( CPPOutput.Value );
      Output->Occluded = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the value of a device output. If there are multiple samples for a frame, then the first sample is returned.
    /// The force plate data provided in the individual device channels is in a coordinate system local to the force plate aligned Z upwards, Y towards the front of the force plate. 
    /// This coordinate system is located at the center of the top surface of the force plate. Any plate origin offset has been accounted for in the moment data. These are forces not reactions.
    /// This method takes both the output and component name to allow for duplicate component names across outputs.
    ///
    /// See Also: GetDeviceCount(), GetDeviceOutputCount(), GetDeviceOutputComponentName()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputValue Output =
    ///        MyClient.GetDeviceOutputValue( "AMTI", "Force", "Fx" );
    ///        // Output.Result == Success
    ///        // Output.Value == ?
    ///        // Output.Occluded = ?
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputName The name of the device output
    /// \param DeviceOutputComponentName The name of the device output component
    /// \return An Output_GetDeviceOutputValue  class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    ///           + InvalidDeviceOutputName
    Output_GetDeviceOutputValue^ GetDeviceOutputValue( String^  DeviceName,
      String^  DeviceOutputName, String^ DeviceOutputComponentName )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputValue CPPOutput( m_pClient->GetDeviceOutputValue(
        Adapt( DeviceName ),
        Adapt( DeviceOutputName ),
        Adapt( DeviceOutputComponentName ) ) );

      Output_GetDeviceOutputValue^ Output = gcnew Output_GetDeviceOutputValue();
      Output->Result = Adapt( CPPOutput.Result );
      Output->Value = Adapt( CPPOutput.Value );
      Output->Occluded = Adapt( CPPOutput.Occluded );

      return Output;
    }
    
    /// Return the number of samples available for the specified device at the current frame. If an analog device is sampling at 1000 Hz and the system is running at 100 Hz then this function will return 10.
    /// The samples can be accessed by supplying the subsample index to GetDeviceOutputValue. See below.
    ///
    /// See Also:GetDeviceOutputCount(), GetDeviceOutputValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputSubsamples Output =
    ///        MyClient.GetDeviceOutputSubsamples( "AMTI", "Fx" );
    ///        // Output.Result == Success
    ///        // Output.DeviceOutputSubsamples == ?
    ///        // Output.Occluded = ?
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputName The name of the device output
    /// \return An Output_GetDeviceOutputSubsamples class containing the result of the operation, the number of subsamples for this device output, and whether the device is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    ///           + InvalidDeviceOutputName
    ///         - Occluded will be true if the value was absent at this frame. In this case the value will be 0.
    Output_GetDeviceOutputSubsamples^ GetDeviceOutputSubsamples( String^  DeviceName,
                                                                 String^  DeviceOutputName )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputSubsamples CPPOutput( m_pClient->GetDeviceOutputSubsamples( 
                                                                             Adapt( DeviceName ), 
                                                                             Adapt( DeviceOutputName ) ) );

      Output_GetDeviceOutputSubsamples^ Output = gcnew Output_GetDeviceOutputSubsamples();

      Output->Result                 = Adapt( CPPOutput.Result );
      Output->DeviceOutputSubsamples = Adapt( CPPOutput.DeviceOutputSubsamples );
      Output->Occluded               = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the number of samples available for the specified device at the current frame. If an analog device is sampling at 1000 Hz and the system is running at 100 Hz then this function will return 10.
    /// The samples can be accessed by supplying the subsample index to GetDeviceOutputValue. See below.
    /// This method takes both the output and component name to allow for duplicate component names across outputs.
    ///
    /// See Also:GetDeviceOutputCount(), GetDeviceOutputValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient =
    ///        new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputSubsamples Output =
    ///        MyClient.GetDeviceOutputSubsamples( "AMTI", "Force", "Fx" );
    ///        // Output.Result == Success
    ///        // Output.DeviceOutputSubsamples == ?
    ///        // Output.Occluded = ?
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputName The name of the device output
    /// \param DeviceOutputComponentName The name of the device output component
    /// \return An Output_GetDeviceOutputSubsamples class containing the result of the operation, the number of subsamples for this device output, and whether the device is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    ///           + InvalidDeviceOutputName
    ///         - Occluded will be true if the value was absent at this frame. In this case the value will be 0.
    Output_GetDeviceOutputSubsamples^ GetDeviceOutputSubsamples( String^  DeviceName,
      String^  DeviceOutputName, String^ DeviceOutputComponentName )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputSubsamples CPPOutput( m_pClient->GetDeviceOutputSubsamples(
        Adapt( DeviceName ),
        Adapt( DeviceOutputName ),
        Adapt( DeviceOutputComponentName ) ) );

      Output_GetDeviceOutputSubsamples^ Output = gcnew Output_GetDeviceOutputSubsamples();

      Output->Result = Adapt( CPPOutput.Result );
      Output->DeviceOutputSubsamples = Adapt( CPPOutput.DeviceOutputSubsamples );
      Output->Occluded = Adapt( CPPOutput.Occluded );

      return Output;
    }

    /// Return the value of a device output. This override allows access to the individual subsamples for the current frame of data.
    /// See GetDeviceOutputValue for information about the meaning of the force plate channels.
    ///
    /// See Also: GetDeviceOutputSubsamples(), GetDeviceOutputValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputValue Output =
    ///        MyClient.GetDeviceOutputValue( "AMTI", "Fx", 6 );
    ///        // Output.Result == Success
    ///        // Output.Value == ?
    ///        // Output.Occluded = ?
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputName The name of the device output
    /// \param Subsample The subsamples to access
    /// \return An Output_GetDeviceOutputValue class containing the result of the operation, the value of the device output, and whether the device is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    ///           + InvalidDeviceIndex
    ///           + InvalidDeviceOutputName
    Output_GetDeviceOutputValue^ GetDeviceOutputValue( String^      DeviceName,
                                                       String^      DeviceOutputName,
                                                       unsigned int Subsample )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputValue CPPOutput( m_pClient->GetDeviceOutputValue( 
                                                                        Adapt( DeviceName ), 
                                                                        Adapt( DeviceOutputName ),
                                                                        Subsample ) );

      Output_GetDeviceOutputValue^ Output = gcnew Output_GetDeviceOutputValue();
      Output->Result   = Adapt( CPPOutput.Result );
      Output->Value    = Adapt( CPPOutput.Value );
      Output->Occluded = Adapt( CPPOutput.Occluded );
      
      return Output;
    }

    /// Return the value of a device output. This override allows access to the individual subsamples for the current frame of data.
    /// See GetDeviceOutputValue for information about the meaning of the force plate channels.
    /// This method takes both the output and component name to allow for duplicate component names across outputs.
    ///
    /// See Also: GetDeviceOutputSubsamples(), GetDeviceOutputValue()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData();
    ///        MyClient.GetFrame();
    ///        Output_GetDeviceOutputValue Output =
    ///        MyClient.GetDeviceOutputValue( "AMTI", "Force", "Fx", 6 );
    ///        // Output.Result == Success
    ///        // Output.Value == ?
    ///        // Output.Occluded = ?
    ///
    /// \param DeviceName The device name
    /// \param DeviceOutputName The name of the device output
    /// \param DeviceOutputComponentName The name of the device output component
    /// \param Subsample The subsamples to access
    /// \return An Output_GetDeviceOutputValue class containing the result of the operation, the value of the device output, and whether the device is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidDeviceName
    ///           + InvalidDeviceIndex
    ///           + InvalidDeviceOutputName
    Output_GetDeviceOutputValue^ GetDeviceOutputValue( String^      DeviceName,
      String^      DeviceOutputName,
      String^      DeviceOutputComponentName,
      unsigned int Subsample )
    {
      ViconDataStreamSDK::CPP::Output_GetDeviceOutputValue CPPOutput( m_pClient->GetDeviceOutputValue(
        Adapt( DeviceName ),
        Adapt( DeviceOutputName ),
        Adapt( DeviceOutputComponentName ),
        Subsample ) );

      Output_GetDeviceOutputValue^ Output = gcnew Output_GetDeviceOutputValue();
      Output->Result = Adapt( CPPOutput.Result );
      Output->Value = Adapt( CPPOutput.Value );
      Output->Occluded = Adapt( CPPOutput.Occluded );

      return Output;
    }

    /// Return the number of force plates available in the DataStream.
    ///
    /// See Also: GetGlobalForceVector(), GetGlobalMomentVector(), GetGlobalCentreOfPressure()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.EnableDeviceData();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetForcePlateCount Output = MyClient.GetForcePlateCount();
    ///        // Output.Result == Success
    ///        // Output.ForcePlateCount >= 0
    ///
    /// \return An Output_GetForcePlateCount class containing the result of the operation and the number of force plates.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetForcePlateCount^ GetForcePlateCount()
    {
      ViconDataStreamSDK::CPP::Output_GetForcePlateCount FPOutput( m_pClient->GetForcePlateCount() );

      Output_GetForcePlateCount^ Output = gcnew Output_GetForcePlateCount();
      Output->Result            = Adapt( FPOutput.Result );
      Output->ForcePlateCount   = Adapt( FPOutput.ForcePlateCount );
      
      return Output;
    }

    /// Return the force vector for the force plate in global coordinates.
    /// The vector is in Newtons and is with respect to the global coordinate system regardless of the orientation of the force plate. The vector represents the force exerted upon the force plate, not the reaction force.
    /// If multiple subsamples are available this function returns the first subsample. See the alternate version of this function to access all of the analog data.
    ///
    /// See Also: GetGlobalMomentVector(), GetGlobalCentreOfPressure()
    ///
    ///        A valid ForcePlateIndex is between 0 and GetForcePlateCount() - 1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableUnlabeledMarkerData();
    ///        MyClient.GetFrame();
    ///        Output_GetGlobalForceVector Output = MyClient.GetGlobalForceVector( 0 );
    ///
    /// \param ForcePlateIndex The index of the force plate
    /// \return An Output_GetGlobalForceVector class containing the result of the operation and the force on the force plate
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetGlobalForceVector^ GetGlobalForceVector( unsigned int ForcePlateIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetGlobalForceVector FPOutput( m_pClient->GetGlobalForceVector( ForcePlateIndex ) );

      Output_GetGlobalForceVector^ Output = gcnew Output_GetGlobalForceVector();
      Output->Result      = Adapt( FPOutput.Result );
      Output->ForceVector = Adapt( FPOutput.ForceVector );
      
      return Output;
    }

    /// Return the moment vector for the force plate in global coordinates.
    /// The vector is in Newton-meters and is with respect to the global coordinate system regardless of the orientation of the force plate.
    /// The vector represents the moment exerted upon the force plate, not the reaction moment. Any force plate origin offset is accounted for in the moments so they are acting about the exact center of the top surface of the force plate.
    /// If multiple subsamples are available this function returns the first subsample. See the alternate version of this function to access all of the analog data.
    ///
    /// See Also: GetGlobalForceVector(), GetGlobalCentreOfPressure()
    ///
    /// A valid ForcePlateIndex is between 0 and GetForcePlateCount() - 1
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData ();
    ///        MyClient.GetFrame();
    ///        Output_ GetGlobalMomentVector Output = MyClient.GetGlobalMomentVector( 0 );
    ///
    /// \param ForcePlateIndex The index of the force plate
    /// \return An Output_GetGlobalMomentVector  class containing the result of the operation and the moment exerted on the force plate
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetGlobalMomentVector^ GetGlobalMomentVector( unsigned int ForcePlateIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetGlobalMomentVector FPOutput( m_pClient->GetGlobalMomentVector( ForcePlateIndex ) );

      Output_GetGlobalMomentVector^ Output = gcnew Output_GetGlobalMomentVector();
      Output->Result      = Adapt( FPOutput.Result );
      Output->MomentVector = Adapt( FPOutput.MomentVector );
      
      return Output;
    }

    /// Return the center of pressure for the force plate in global coordinates.
    /// The position is in millimeters and is with respect to the global coordinate system.
    /// If multiple subsamples are available this function returns the first subsample. See the alternate version of this function to access all of the analog data.
    ///
    /// See Also: GetGlobalForceVector(), GetGlobalMomentVector()
    ///
    /// A valid ForcePlateIndex is between 0 and GetForcePlateCount() - 1
    /// 
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData ();
    ///        MyClient.GetFrame();
    ///        Output_GetGlobalCentreOfPressure Output = MyClient.GetGlobalCentreOfPressure( 0 );
    ///
    /// \param ForcePlateIndex The index of the force plate
    /// \return An Output_GetGlobalCentreOfPressure class containing the result of the operation and the center of pressure.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetGlobalCentreOfPressure^ GetGlobalCentreOfPressure( unsigned int ForcePlateIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetGlobalCentreOfPressure FPOutput( m_pClient->GetGlobalCentreOfPressure( ForcePlateIndex ) );

      Output_GetGlobalCentreOfPressure^ Output = gcnew Output_GetGlobalCentreOfPressure();
      Output->Result      = Adapt( FPOutput.Result );
      Output->CentreOfPressure = Adapt( FPOutput.CentreOfPressure );
      
      return Output;
    }

    /// Return the number of subsamples available for a specified plate in the current frame.
    /// Additional versions of GetGlobalForceVector, GetGlobalMomentVector, and GetGlobalCentreOfPressure take the subsample index to allow access to all the force plate data.
    ///
    /// See Also: GetGlobalForceVector(), GetGlobalMomentVector(), GetGlobalCentreOfPressure()
    ///
    ///        A valid ForcePlateIndex is between 0 and GetForcePlateCount()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.EnableDeviceData();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetForcePlateSubsamples Output = MyClient.GetForcePlateSubsamples ( 0 );
    ///        // Output.Result == Success
    ///        // Output.ForcePlateSubsamples >= 0
    ///
    /// \param ForcePlateIndex The index of the force plate
    /// \return An Output_GetForcePlateSubsamples class containing the result of the operation and the number of subsamples.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetForcePlateSubsamples^ GetForcePlateSubsamples( unsigned int ForcePlateIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetForcePlateSubsamples FPOutput( m_pClient->GetForcePlateSubsamples( ForcePlateIndex ) );

      Output_GetForcePlateSubsamples^ Output = gcnew Output_GetForcePlateSubsamples();
      Output->Result = Adapt( FPOutput.Result );
      Output->ForcePlateSubsamples = Adapt( FPOutput.ForcePlateSubsamples );
      
      return Output;
    }

    /// Return the force vector for the plate in global coordinates. This version takes a subsample index that allows access to all of the force information.
    /// The vector is in Newtons and is with respect to the global coordinate system regardless of the orientation of the plate. The vector represents the force exerted upon the plate, not the reaction force.
    ///
    /// See Also: GetGlobalMomentVector(), GetGlobalCentreOfPressure()
    ///
    ///        A valid ForcePlateIndex is between 0 and GetForcePlateCount()-1
    ///        A valid Subsample is between 0 and GetForcePlateSubsamples()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableUnlabeledMarkerData();
    ///        MyClient.GetFrame();
    ///        uint Index = 0;
    ///        uint Samples = MyClient.GetForcePlateSubsamples(ForcePlateIndex).ForcePlateSubsamples;
    ///        for (uint Sample = 0; Sample < Samples; ++ Sample)
    ///        {
    ///          Output_GetGlobalForceVector Output = MyClient.GetGlobalForceVector( Index, Sample );
    ///        }
    ///
    /// \param ForcePlateIndex The index of the force plate
    /// \param Subsample The subsample to access
    /// \return An Output_GetGlobalForceVector class containing the result of the operation and the force on the plate.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetGlobalForceVector^ GetGlobalForceVector( unsigned int ForcePlateIndex, unsigned int Subsample )
    {
      ViconDataStreamSDK::CPP::Output_GetGlobalForceVector FPOutput( m_pClient->GetGlobalForceVector( ForcePlateIndex, Subsample ) );

      Output_GetGlobalForceVector^ Output = gcnew Output_GetGlobalForceVector();
      Output->Result      = Adapt( FPOutput.Result );
      Output->ForceVector = Adapt( FPOutput.ForceVector );
      
      return Output;
    }

    /// Return the moment vector for the plate in global coordinates. This version takes a subsample index that allows access to all of the force information.
    /// The vector is in Newton-meters and is with respect to the global coordinate system regardless of the orientation of the plate.
    /// The vector represents the moment exerted upon the plate, not the reaction moment. Any force plate origin offset is accounted for in the moments so they are acting about the exact center of the top surface of the plate.
    ///
    /// See Also: GetGlobalForceVector(), GetGlobalCentreOfPressure()
    ///
    ///        A valid ForcePlateIndex is between 0 and GetForcePlateCount() - 1
    ///        A valid Subsample is between 0 and GetForcePlateSubsamples()-1
    ///        DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData ();
    ///        MyClient.GetFrame();
    ///        uint Index = 0;
    ///        uint Samples = MyClient.GetForcePlateSubsamples(ForcePlateIndex).ForcePlateSubsamples;
    ///        for (uint Sample = 0; Sample < Samples; ++ Sample)
    ///        {
    ///          Output_GetGlobalMomentVector Output = MyClient.GetGlobalMomentVector( Index, Sample );
    ///        }
    ///
    /// \param ForcePlateIndex The index of the force plate
    /// \param Subsample The subsample to access
    /// \return An Output_GetGlobalMomentVector class containing the result of the operation and the moment exerted on the plate.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetGlobalMomentVector^ GetGlobalMomentVector( unsigned int ForcePlateIndex, unsigned int Subsample )
    {
      ViconDataStreamSDK::CPP::Output_GetGlobalMomentVector FPOutput( m_pClient->GetGlobalMomentVector( ForcePlateIndex, Subsample ) );

      Output_GetGlobalMomentVector^ Output = gcnew Output_GetGlobalMomentVector();
      Output->Result      = Adapt( FPOutput.Result );
      Output->MomentVector = Adapt( FPOutput.MomentVector );
      
      return Output;
    }

    /// Return the center of pressure for the plate in global coordinates. This version takes a subsample index that allows access to all of the force information.
    /// The position is in millimeters and is with respect to the global coordinate system.
    ///
    /// See Also: GetGlobalForceVector(), GetGlobalMomentVector()
    ///
    ///        A valid ForcePlateIndex is between 0 and GetForcePlateCount()-1
    ///        A valid Subsample is between 0 and GetForcePlateSubsamples()-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableDeviceData ();
    ///        MyClient.GetFrame();
    ///        uint Index = 0;
    ///        uint Samples = MyClient.GetForcePlateSubsamples(ForcePlateIndex).ForcePlateSubsamples;
    ///        for (uint Sample = 0; Sample < Samples; ++ Sample)
    ///        {
    ///          Output_GetGlobalCentreOfPressure Output = MyClient.GetGlobalCentreOfPressure (Index,Sample);
    ///        }
    ///
    /// \param ForcePlateIndex The index of the force plate
    /// \param Subsample The subsample to access
    /// \return An Output_GetGlobalCentreOfPressure class containing the result of the operation the center of pressure
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetGlobalCentreOfPressure^ GetGlobalCentreOfPressure( unsigned int ForcePlateIndex, unsigned int Subsample )
    {
      ViconDataStreamSDK::CPP::Output_GetGlobalCentreOfPressure FPOutput( m_pClient->GetGlobalCentreOfPressure( ForcePlateIndex, Subsample ) );

      Output_GetGlobalCentreOfPressure^ Output = gcnew Output_GetGlobalCentreOfPressure();
      Output->Result      = Adapt( FPOutput.Result );
      Output->CentreOfPressure = Adapt( FPOutput.CentreOfPressure );
      
      return Output;
    }

    /// Return the number of eye trackers available in the DataStream.
    ///
    /// See Also: GetEyeTrackerGlobalGazeVector(), GetEyeTrackerGlobalGazeVector()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.EnableDeviceData();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.GetFrame();
    ///        Output_GetEyeTrackerCount Output = MyClient.GetEyeTrackerCount();
    ///        // Output.Result == Success
    ///        // Output.EyeTrackerCount >= 0
    ///
    /// \return An Output_GetEyeTrackerCount class containing the result of the operation and the number of eye trackers.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetEyeTrackerCount^ GetEyeTrackerCount()
    {
      ViconDataStreamSDK::CPP::Output_GetEyeTrackerCount EyeTrackerOutput( m_pClient->GetEyeTrackerCount() );

      Output_GetEyeTrackerCount^ Output = gcnew Output_GetEyeTrackerCount();
      Output->Result            = Adapt( EyeTrackerOutput.Result );
      Output->EyeTrackerCount   = Adapt( EyeTrackerOutput.EyeTrackerCount );
      
      return Output;
    }

    /// Return the location of the eye. The position is in millimeters with respect to the global origin. The segment and device data need to be enabled to get the position.
    ///
    /// See Also: GetEyeTrackerCount(), GetEyeTrackerGlobalGazeVector()
    ///
    ///        A valid EyeTrackerIndex is between 0 and GetEyeTrackerCount() - 1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData ();
    ///        MyClient.EnableDeviceData ();
    ///        MyClient.GetFrame();
    ///        Output_GetEyeTrackerGlobalPosition Output = MyClient.GetEyeTrackerGlobalPosition ( 0 );
    ///
    /// \param EyeTrackerIndex The index of the eye tracker
    /// \return An Output_GetEyeTrackerGlobalPosition class containing the result of the operation, the eye position and whether the eyetracker is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///         - Occluded will be true if the segment that has the eye tracker attached is not visible. If true the position will be (0,0,0).
    Output_GetEyeTrackerGlobalPosition^ GetEyeTrackerGlobalPosition( unsigned int EyeTrackerIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetEyeTrackerGlobalPosition EyeTrackerOutput( m_pClient->GetEyeTrackerGlobalPosition( EyeTrackerIndex ) );

      Output_GetEyeTrackerGlobalPosition^ Output = gcnew Output_GetEyeTrackerGlobalPosition();
      Output->Result      = Adapt( EyeTrackerOutput.Result );
      Output->Position    = Adapt( EyeTrackerOutput.Position );
      Output->Occluded    = Adapt( EyeTrackerOutput.Occluded );
      
      return Output;
    }

    /// Return the gaze direction as a unit vector in global coordinates.
    /// The gaze vector will be marked as occluded if the segment that has the eye tracker attached is not visible, the eye tracker is not calibrated or the pupil is not found.
    /// The segment and device data need to be enabled to get the gaze vector.
    ///
    /// See Also: GetEyeTrackerCount(), GetEyeTrackerGlobalPosition()
    ///
    ///        A valid EyeTrackerIndex is between 0 and GetEyeTrackerCount() - 1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableSegmentData ();
    ///        MyClient.EnableDeviceData ();
    ///        MyClient.GetFrame();
    ///        Output_GetEyeTrackerGlobalPosition Output = MyClient.GetEyeTrackerGlobalPosition ( 0 );
    ///
    /// \param EyeTrackerIndex The index of the eye tracker
    /// \return An Output_GetEyeTrackerGlobalGazeVector class containing the result of the operation, the gaze direction vector, and whether the eye tracker is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///         - Occluded will be true if the gaze vector could not be calculated. If true, the position will be (0,0,0).
    Output_GetEyeTrackerGlobalGazeVector^ GetEyeTrackerGlobalGazeVector( unsigned int EyeTrackerIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetEyeTrackerGlobalGazeVector EyeTrackerOutput( m_pClient->GetEyeTrackerGlobalGazeVector( EyeTrackerIndex ) );

      Output_GetEyeTrackerGlobalGazeVector^ Output = gcnew Output_GetEyeTrackerGlobalGazeVector();
      Output->Result      = Adapt( EyeTrackerOutput.Result );
      Output->GazeVector  = Adapt( EyeTrackerOutput.GazeVector );
      Output->Occluded    = Adapt( EyeTrackerOutput.Occluded );
      
      return Output;
    }

    /// Return the number of cameras available in the DataStream.
    ///
    /// See Also: GetCameraName(), GetCentroidCount(), GetCentroidPosition()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableCentroidData ();
    ///        MyClient.GetFrame();
    ///        Output_GetCameraCount Output = MyClient.GetCameraCount();
    ///        // Output.Result == Success
    ///        // Output.CameraCount >= 0
    ///
    /// \return An Output_GetCameraCount class containing the result of the operation and the number of cameras.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetCameraCount^ GetCameraCount()
    {
      ViconDataStreamSDK::CPP::Output_GetCameraCount CPPOutput( m_pClient->GetCameraCount() );

      Output_GetCameraCount^ Output = gcnew Output_GetCameraCount();
      Output->Result           = Adapt( CPPOutput.Result );
      Output->CameraCount = Adapt( CPPOutput.CameraCount );
      
      return Output;
    }

    /// Return the name of a camera. This name can be passed into centroid functions.
    ///
    /// See Also: GetCameraCount(), GetCentroidCount(), GetCentroidPosition()
    ///
    ///        A valid CameraIndex is between 0 and GetCameraCount() - 1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableCentroidData ();
    ///        MyClient.GetFrame();
    ///        Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///        // OutputGCC.Result == Success
    ///        // OutputGCC.CameraCount == 1
    ///        Output_GetCameraName OutputGCN;
    ///        OutputGCN = MyClient.GetCameraName( 0 )
    ///
    /// \param CameraIndex The index of the camera
    /// \return An Output_GetCameraName class containing the result of the operation and the name of the camera.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetCameraName^ GetCameraName( unsigned int CameraIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetCameraName CPPOutput( m_pClient->GetCameraName( CameraIndex ) );

      Output_GetCameraName^ Output = gcnew Output_GetCameraName();
      Output->Result     = Adapt( CPPOutput.Result );
      Output->CameraName = Adapt( CPPOutput.CameraName );
      
      return Output;
    }

    /// Returns the internal ID of the camera with the specified name.
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( OutputGCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///     Output_GetCameraName OutputGCN;
    ///     OutputGCN = MyClient.GetCameraName( 0 );
    ///     if( OutputGCN.Result == Success )
    ///     {
    ///       Output_GetCameraId Output_GCI = MyClient.GetCameraId( OutputGCN.CameraName );
    ///     }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetCameraId^ GetCameraId(String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetCameraId CPPOutput(m_pClient->GetCameraId(Adapt( CameraName ) ));

      Output_GetCameraId^ Output = gcnew Output_GetCameraId();
      Output->Result = Adapt(CPPOutput.Result);
      Output->CameraId = Adapt(CPPOutput.CameraId);

      return Output;
    }

    /// Returns the user-assigned ID of the camera with the specified name.
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( OutputGCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///      Output_GetCameraName OutputGCN;
    ///      OutputGCN = MyClient.GetCameraName( 0 );
    ///      if( OutputGCN.Result == Success )
    ///      {
    ///        Output_GetCameraUserId Output_GCI = MyClient.GetCameraUserId( OutputGCN.CameraName );
    ///      }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetCameraUserId^ GetCameraUserId(String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetCameraUserId CPPOutput(m_pClient->GetCameraUserId(Adapt( CameraName ) ));

      Output_GetCameraUserId^ Output = gcnew Output_GetCameraUserId();
      Output->Result = Adapt(CPPOutput.Result);
      Output->CameraUserId = Adapt(CPPOutput.CameraUserId);

      return Output;
    }

    /// Returns the type of the camera with the specified name. 
    /// The type returned is an internal type string.
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( OutputGCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///     Output_GetCameraName OutputGCN;
    ///     OutputGCN = MyClient.GetCameraName( 0 );
    ///     if( OutputGCN.Result == Success )
    ///     {
    ///       Output_GetCameraType Output_GCT = MyClient.GetCameraType( OutputGCN.CameraName );
    ///     }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetCameraType^ GetCameraType( String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetCameraType CPPOutput(m_pClient->GetCameraType(Adapt( CameraName ) ));

      Output_GetCameraType^ Output = gcnew Output_GetCameraType();
      Output->Result = Adapt(CPPOutput.Result);
      Output->CameraType = Adapt(CPPOutput.CameraType);

      return Output;
    }

    /// Returns the name of of the camera type as a string suitable for display to a user.
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( Output_GCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///     Output_GetCameraName OutputGCN;
    ///     OutputGCN = MyClient.GetCameraName( 0 );
    ///     if( OutputGCN.Result == Success )
    ///     {
    ///       Output_GetCameraDisplayName Output_GCD = MyClient.GetCameraDisplayName( OutputGCN.CameraName );
    ///     }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetCameraDisplayName^ GetCameraDisplayName( String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetCameraDisplayName CPPOutput(m_pClient->GetCameraDisplayName(Adapt( CameraName ) ));

      Output_GetCameraDisplayName^ Output = gcnew Output_GetCameraDisplayName();
      Output->Result = Adapt(CPPOutput.Result);
      Output->CameraDisplayName = Adapt(CPPOutput.CameraDisplayName);

      return Output;
    }

    /// Returns the sensor resolution of the camera with the specified name.
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( OutputGCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///     Output_GetCameraName OutputGCN;
    ///     OutputGCN = MyClient.GetCameraName( 0 );
    ///     if( OutputGCN.Result == Success )
    ///     {
    ///       Output_GetCameraResolution Output_GCR = MyClient.GetCameraResolution( OutputGCN.CameraName );
    ///     }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetCameraResolution^ GetCameraResolution( String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetCameraResolution CPPOutput(m_pClient->GetCameraResolution(Adapt( CameraName ) ));

      Output_GetCameraResolution^ Output = gcnew Output_GetCameraResolution();
      Output->Result = Adapt(CPPOutput.Result);
      Output->ResolutionX = Adapt(CPPOutput.ResolutionX);
      Output->ResolutionY = Adapt(CPPOutput.ResolutionY);

      return Output;
    }

    /// Returns whether the camera with the specified name is a video camera.
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( OutputGCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///     Output_GetCameraName OutputGCN;
    ///     OutputGCN = MyClient.GetCameraName( 0 );
    ///     if( OutputGCN.Result == Success )
    ///     {
    ///       Output_GetIsVideoCamera Output_GCV = MyClient.GetIsVideoCamera( OutputGCN.CameraName );
    ///     }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetIsVideoCamera^ GetIsVideoCamera( String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetIsVideoCamera CPPOutput(m_pClient->GetIsVideoCamera(Adapt( CameraName )));

      Output_GetIsVideoCamera^ Output = gcnew Output_GetIsVideoCamera();
      Output->Result = Adapt(CPPOutput.Result);
      Output->IsVideoCamera = Adapt(CPPOutput.IsVideoCamera);

      return Output;
    }
    
    /// Returns the sensor mode of the camera
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( OutputGCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///     Output_GetCameraName OutputGCN;
    ///     OutputGCN = MyClient.GetCameraName( 0 );
    ///     if( OutputGCN.Result == Success )
    ///     {
    ///       Output_GetCameraSensorMode Output = MyClient.GetCameraSensorMode( OutputGCN.CameraName );
    ///     }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetCameraSensorMode^ GetCameraSensorMode(String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetCameraSensorMode CPPOutput(m_pClient->GetCameraSensorMode(Adapt(CameraName)));

      Output_GetCameraSensorMode^ Output = gcnew Output_GetCameraSensorMode();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SensorMode = Adapt(CPPOutput.SensorMode);

      return Output;
    }

    /// Returns the camera sensor window size for the specified camera
    ///
    /// See Also: GetCameraName()
    ///

    ///   A valid CameraName may be obtained from GetCameraName()
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableCentroidData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///   if( OutputGCC.Result == Success && OutputGCC.CameraCount > 0 )
    ///   {
    ///     Output_GetCameraName OutputGCN;
    ///     OutputGCN = MyClient.GetCameraName( 0 );
    ///     if( OutputGCN.Result == Success )
    ///     {
    ///       Output_GetCameraWindowSize Output = MyClient.GetCameraWindowSize( OutputGCN.CameraName );
    ///     }
    ///   }

    ///
    /// \return An Output_ class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetCameraWindowSize^ GetCameraWindowSize(String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetCameraWindowSize CPPOutput(m_pClient->GetCameraWindowSize(Adapt(CameraName)));

      Output_GetCameraWindowSize^ Output = gcnew Output_GetCameraWindowSize();
      Output->Result = Adapt(CPPOutput.Result);
      Output->WindowStartX = Adapt(CPPOutput.WindowStartX);
      Output->WindowStartY = Adapt(CPPOutput.WindowStartY);
      Output->WindowWidth = Adapt(CPPOutput.WindowWidth);
      Output->WindowHeight = Adapt(CPPOutput.WindowHeight);

      return Output;
    }

    /// Return the number of centroids reported by a named camera. The centroid data needs to be enabled to get the number of centroids.
    ///
    /// See Also: GetCameraCount(), GetCameraName(), GetCentroidPosition()
    ///
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableCentroidData ();
    ///        MyClient.GetFrame();
    ///        Output_GetCameraCount OutputGCC = MyClient.GetCameraCount();
    ///        for( unsigned int CameraIndex = 0; CameraIndex < OutputGCC.CameraCount; ++CameraIndex )
    ///        {
    ///          OutputGCN = MyClient.GetCameraName( CameraIndex );
    ///          OutputGCeC = MyClient.GetCentroidCount( OutputGCN.CameraName )
    ///          // OutputGCeC.Result == Success
    ///          // OutputGCeC.CentroidCount >= 0
    ///        }
    ///
    /// \param CameraName The name of the camera.
    /// \return An Output_GetCentroidCount class containing the result of the operation and the number of centroids.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidCameraName
    Output_GetCentroidCount^ GetCentroidCount( String^ CameraName )
    {
      ViconDataStreamSDK::CPP::Output_GetCentroidCount CPPOutput( m_pClient->GetCentroidCount( Adapt( CameraName ) ) );

      Output_GetCentroidCount^ Output = gcnew Output_GetCentroidCount();
      Output->Result        = Adapt( CPPOutput.Result );
      Output->CentroidCount = Adapt( CPPOutput.CentroidCount );
      
      return Output;
    }

    /// Return the position and radius of the centroid in camera coordinates. The centroid data needs to be enabled to get the centroid position and radius.
    ///
    /// See Also: GetCameraCount(), GetCameraName(), GetCentroidCount()
    ///
    ///        A valid CameraName is obtained from GetCameraName( CameraIndex )
    ///        A valid CentroidIndex is between 0 and GetCentroidCount( CameraName )-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableCentroidData ();
    ///        MyClient.GetFrame();
    ///        Output_GetCameraName OutputGCN = MyClient.GetCameraName( 0 );
    ///        Output_GetCentroidPosition Output = MyClient.GetCentroidPosition( OutputGCN.CameraName, 0 );
    ///
    /// \param CameraName The name of the camera.
    /// \param CentroidIndex The index of the centroid.
    /// \return An Output_GetCentroidPosition class containing the result of the operation, the position of the centroid and the radius of the centroid.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidCameraName
    ///           + InvalidIndex
    Output_GetCentroidPosition^ GetCentroidPosition( String^ CameraName, unsigned int CentroidIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetCentroidPosition CPPOutput( m_pClient->GetCentroidPosition( Adapt( CameraName ), CentroidIndex ) );

      Output_GetCentroidPosition^ Output = gcnew Output_GetCentroidPosition();
      Output->Result           = Adapt( CPPOutput.Result );
      Output->CentroidPosition = Adapt( CPPOutput.CentroidPosition );
      Output->Radius           = Adapt( CPPOutput.Radius );
//      Output->Accuracy         = Adapt( CPPOutput.Accuracy );
      
      return Output;
    }

    /// Return the weight of the centroid. The centroid data needs to be enabled to get the centroid weight. Only supported by Tracker - weights will be 1.0 for all centroids if Low Jitter mode is not enabled.
    ///
    /// See Also: GetCameraCount(), GetCameraName(), GetCentroidCount()
    ///
    ///        A valid CameraName is obtained from GetCameraName( CameraIndex )
    ///        A valid CentroidIndex is between 0 and GetCentroidCount( CameraName )-1
    ///        ViconDataStreamSDK.DotNET.Client MyClient = new ViconDataStreamSDK.DotNET.Client();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.EnableCentroidData ();
    ///        MyClient.GetFrame();
    ///        Output_GetCameraName OutputGCN = MyClient.GetCameraName( 0 );
    ///        Output_GetCentroidWeight Output = MyClient.GetCentroidWeight( OutputGCN.CameraName, 0 );
    ///
    /// \param CameraName The name of the camera.
    /// \param CentroidIndex The index of the centroid.
    /// \return An Output_GetCentroidWeight class containing the result of the operation and the weight of the centroid.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidCameraName
    ///           + InvalidIndex
    Output_GetCentroidWeight^ GetCentroidWeight( String^ CameraName, unsigned int CentroidIndex )
    {
      ViconDataStreamSDK::CPP::Output_GetCentroidWeight CPPOutput( m_pClient->GetCentroidWeight( Adapt( CameraName ), CentroidIndex ) );

      Output_GetCentroidWeight^ Output = gcnew Output_GetCentroidWeight();
      Output->Result = Adapt( CPPOutput.Result );
      Output->Weight= Adapt( CPPOutput.Weight );

      return Output;
    }

    /// Obtain the number of greyscale blobs that are available for the specified camera.
    ///
    /// See Also: GetGreyscaleBlob(), EnableGreyscaleData()
    ///
    ///   A valid camera name may be obtained from GetCameraName( CameraIndex )
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableGreyscaleData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraName CameraName = MyClient.GetCameraName( 0 );
    ///   Output_GetGreyscaleBlobCount Output = MyClient.GetGreyscaleBlobCount( CameraName.CameraName );
    ///     
    /// \return An Output_GetGreyscaleBlobCount class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetGreyscaleBlobCount^ GetGreyscaleBlobCount( String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetGreyscaleBlobCount CPPOutput(m_pClient->GetGreyscaleBlobCount(Adapt(CameraName)));

      Output_GetGreyscaleBlobCount^ Output = gcnew Output_GetGreyscaleBlobCount();
      Output->Result = Adapt(CPPOutput.Result);
      Output->BlobCount = Adapt(CPPOutput.BlobCount);

      return Output;
    }

    /// Obtain the greyscale subsampling info for the selected camera.
    ///
    /// See Also: GetGreyscaleBlob(), EnableGreyscaleData()
    ///
    ///   A valid camera name may be obtained from GetCameraName( CameraIndex )
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableGreyscaleData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraName CameraName = MyClient.GetCameraName( 0 );
    ///   Output_GetGreyscaleBlobSubsampleInfo Output = MyClient.GetGreyscaleSubsampleInfo( CameraName.CameraName );
    ///     
    /// \return An Output_GetGreyscaleBlobSubsampleInfo class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetGreyscaleBlobSubsampleInfo^ GetGreyscaleBlobSubsampleInfo(String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetGreyscaleBlobSubsampleInfo CPPOutput(m_pClient->GetGreyscaleBlobSubsampleInfo(Adapt(CameraName)));

      Output_GetGreyscaleBlobSubsampleInfo^ Output = gcnew Output_GetGreyscaleBlobSubsampleInfo();
      Output->Result = Adapt(CPPOutput.Result);
      Output->TwiceOffsetX = Adapt(CPPOutput.TwiceOffsetX);
      Output->TwiceOffsetY = Adapt(CPPOutput.TwiceOffsetY);
      Output->SensorPixelsPerImagePixelX = Adapt(CPPOutput.SensorPixelsPerImagePixelX);
      Output->SensorPixelsPerImagePixelY = Adapt(CPPOutput.SensorPixelsPerImagePixelY);

      return Output;
    }

    /// Obtains greyscale blob data for the specified camera and blob index.
    ///
    /// See Also: GetGreyscaleBlobCount(), EnableGreyscaleData()
    ///
    ///   A valid camera name may be obtained from GetCameraName( CameraIndex )
    ///   A valid blob index is between 0 and GetGreyscaleBlobCount() - 1
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableGreyscaleData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraName CameraName = MyClient.GetCameraName( 0 );
    ///   Output_GetGreyscaleBlob GreyscaleData = MyClient.GetGreyscaleBlob( CameraName.CameraName, 0 );
    ///
    /// \return An Output_GetGreyscaleBlob class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    ///           + InvalidIndex
    Output_GetGreyscaleBlob^ GetGreyscaleBlob(String^ CameraName, const unsigned int BlobIndex)
    {
      ViconDataStreamSDK::CPP::Output_GetGreyscaleBlob CPPOutput(m_pClient->GetGreyscaleBlob(Adapt(CameraName), BlobIndex));

      Output_GetGreyscaleBlob^ Output = gcnew Output_GetGreyscaleBlob();
      Output->Result = Adapt(CPPOutput.Result);
      Output->BlobLinePositionsX = Adapt(CPPOutput.BlobLinePositionsX);
      Output->BlobLinePositionsY = Adapt(CPPOutput.BlobLinePositionsY);
      Output->BlobLinePixelValues = gcnew List< List< unsigned char >^ >();
      for (auto Vector : CPPOutput.BlobLinePixelValues )
      {
        Output->BlobLinePixelValues->Add( Adapt( Vector ) );
      }
      return Output;
    }

    /// Obtains video data for the specified camera.
    /// Note that this .NET implementation involves a copy of the frame data into the output
    /// List, so may be slower than the C++ implementation which uses a direct shared pointer.
    ///
    /// See Also: -
    ///
    ///   A valid camera name may be obtained from GetCameraName( CameraIndex )
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.EnableVideoData ();
    ///   MyClient.GetFrame();
    ///   Output_GetCameraName CameraName = MyClient.GetCameraName( 0 );
    ///   Output_GetVideoFrame VideoData = MyClient.GetVideoFrame( CameraName.CameraName );
    ///
    /// \return An Output_GetVideoFrame class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + InvalidCameraName
    Output_GetVideoFrame^ GetVideoFrame(String^ CameraName)
    {
      ViconDataStreamSDK::CPP::Output_GetVideoFrame CPPOutput(m_pClient->GetVideoFrame(Adapt(CameraName) ));

      Output_GetVideoFrame^ Output = gcnew Output_GetVideoFrame();
      Output->Result = Adapt(CPPOutput.Result);
      Output->m_FrameID = Adapt(CPPOutput.m_FrameID);
      Output->m_Height = Adapt(CPPOutput.m_Height);
      Output->m_Width = Adapt(CPPOutput.m_Width);
      Output->m_Format = Adapt(CPPOutput.m_Format);

      std::shared_ptr< std::vector< unsigned char > > pData = CPPOutput.m_Data;

      if (pData)
      {
        // Copy the data from the shared pointer
        std::vector< unsigned char > Data = *pData;
        Output->m_Data = Adapt(Data);
      }

      return Output;
    }

    /// Add a filter to allow centroid, blob or video data being transmitted only for the specified cameras.
    ///
    /// See Also: GetGreyscaleBlobCount(), GetGreyscaleBlob(), GetCentroidCount(), GetCentroidPosition(), GetCentroidWeight()
    /// 
    ///   A valid camera name may be obtained from GetCameraName( CameraIndex )
    ///   A valid camera id may be obtained from GetCameraId( CameraName )
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.Connect( "localhost" );
    ///   MyClient.GetFrame();
    ///   Output_GetCameraName CameraName = MyClient.GetCameraName( 0 );
    ///   Output_GetCameraId CameraId = MyClient.GetCameraName( CameraName.CameraName );
    ///   List< unsigned int >^ ReceiveCentroids = gcnew List< unsigned int >();
    ///   ReceiveCentroids.Add( CameraId.CameraId );
    ///   List< unsigned int >^ ReceiveBlobs = gcnew List< unsigned int >();
    ///   ReceiveBlobs.Add( CameraId.CameraId );
    ///   List< unsigned int >^ ReceiveVideo = gcnew List< unsigned int >();
    ///   ReceiveVideo.Add( CameraId.CameraId );
    ///   Output_SetCameraFilter FilterResults = MyClient.SetCameraFilter( ReceiveCentroids, ReceiveBlobs, ReceiveVideo );
    ///
    ///
    /// \return An Output_SetCameraFilter class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    Output_SetCameraFilter^ SetCameraFilter(List< unsigned int > ^ CameraIdsForCentroids,
      List< unsigned int >^ CameraIdsForBlobs,
      List< unsigned int >^ CameraIdsForVideo)
    {
      ViconDataStreamSDK::CPP::Output_SetCameraFilter CPPOutput(m_pClient->SetCameraFilter(Adapt(CameraIdsForCentroids), Adapt(CameraIdsForBlobs), Adapt(CameraIdsForVideo)));

      Output_SetCameraFilter^ Output = gcnew Output_SetCameraFilter();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }
    
    Output_ClearSubjectFilter^ ClearSubjectFilter()
    {
      ViconDataStreamSDK::CPP::Output_ClearSubjectFilter CPPOutput(m_pClient->ClearSubjectFilter());

      Output_ClearSubjectFilter^ Output = gcnew Output_ClearSubjectFilter();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    Output_AddToSubjectFilter^ AddToSubjectFilter( String^ SubjectName )
    {
      ViconDataStreamSDK::CPP::Output_AddToSubjectFilter CPPOutput(m_pClient->AddToSubjectFilter( Adapt(SubjectName) ));

      Output_AddToSubjectFilter^ Output = gcnew Output_AddToSubjectFilter();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Request that the wireless adapters will be optimally configured for streaming data.
    ///
    /// On Windows this will disable background scan and enable streaming.
    /// The call does not need the client to be connected.
    ///
    ///   ViconDataStreamSDK.DotNET.Client MyClient;
    ///   MyClient.ConfigureWireless();
    ///
    /// \return An Output_ConfigureWireless class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success if the adapters are configured or there are no adapters to do
    ///           + NotSupported if the OS does not support this function
    ///           + WirelessConfigurationFailed if the request failed
    ///         - The Error will provide additional information in the failure case
    Output_ConfigureWireless^ ConfigureWireless()
    {
      ViconDataStreamSDK::CPP::Output_ConfigureWireless CPPOutput( m_pClient->ConfigureWireless() );

      Output_ConfigureWireless ^ Output = gcnew Output_ConfigureWireless();
      Output->Result = Adapt( CPPOutput.Result );
      Output->Error = Adapt( CPPOutput.Error );

      return Output;
    }

  private:

    ViconDataStreamSDK::CPP::Client * m_pClient;
  };

  ///  \class RetimingClient 
  ///  \brief The re-timing client class for DotNET.
  ///  Vicon DataStream SDK Re-Timing Client
  ///  ===========================
  ///  Intended uses
  ///  -------------
  ///  The Vicon DataStream re-timing client provides calls to obtain subject data from the 
  ///  DataStream with minimal latency and temporal jitter. 
  ///  When UpdateFrame() is called, the client uses re-timed data that has been linearly interpolated 
  ///  from an internal buffer to predict the position of each segment to the current time. 
  ///
  ///  The system and network latencies are used when determining the amount of prediction required.
  ///  If additional prediction is required, for example for use in a VR system where an additional latency 
  ///  is present due to rendering and display latency; this may be requested in the call to UpdateFrame().
  ///
  ///  The user will either call UpdateFrame(), which will update the current frame state to 
  ///  the time of calling and return immediately. This is intended for use in systems where you require
  ///  subject data positions at times driven by an external clock.
  ///
  ///  If you do not have an external clock, and require behavior similar to that of the standard DataStream 
  ///  client running in ServerPush streaming mode, than the system may be configured to provide frame data
  ///  at a consistent frame rate by providing a frame rate to the Connect() call. The user will then call 
  ///  WaitForFrame(), which will block in a similar method to Client::GetFrame(), but using retimed data
  ///  in order to keep the frame period very consistent.
  /// 
  ///  Examples of use
  ///  --------------
  /// 
  ///  If you are using the client in a situation where you need to obtain the position of subjects in  
  /// 
  ///       ViconDataStreamSDK::CPP::RetimingClient _MyClient;
  ///       _MyClient.Connect( "localhost" );
  ///       
  ///       // example render method. Real code would probably cache the subject and segment names and bind them to a model, so 
  ///       // this code would iterate over the model and update the joint positions.
  ///       void render() 
  ///       {
  ///         _MyClient.UpdateFrame();
  ///
  ///          Output_GetSubjectCount SubjectCount = _MyClient.GetSubjectCount();
  ///          if (SubjectCount.Result == Result::Success)
  ///          {
  ///            for (unsigned int SubjectIndex = 0; SubjectIndex < SubjectCount.SubjectCount; ++SubjectIndex)
  ///            {
  ///              Output_GetSubjectName SubjectName = _MyClient.GetSubjectName(SubjectIndex);
  ///              if (SubjectName.Result == Result::Success)
  ///              {
  ///                Output_GetSegmentCount SegmentCount = _MyClient.GetSegmentCount(SubjectName.SubjectName);
  ///                if (SegmentCount.Result == Result::Success)
  ///                {
  ///                  for (unsigned int SegmentIndex = 0; SegmentIndex < SegmentCount.SegmentCount; ++SegmentIndex)
  ///                  {
  ///                    Output_GetSegmentName SegmentName = _MyClient.GetSegmentName(SubjectName.SubjectName, SegmentIndex);
  ///                    if (SegmentName.Result == Result::Success)
  ///                    {
  ///                      Output_GetSegmentGlobalRotationQuaternion SegmentRotation = _MyClient.GetSegmentGlobalRotationQuaternion(SubjectName.SubjectName, SegmentName.SegmentName);
  ///                      if (SegmentRotation.Result == Result::Success && !SegmentRotation.Occluded)
  ///                      {
  ///                        // use the segment rotation
  ///                      }
  ///                    }
  ///                  }
  ///                }
  ///              }
  ///            }
  ///          }
  /// 
  ///
  /// If using the client where there is no render call and you require your own timing.
  /// 
  ///       ViconDataStreamSDK::CPP::RetimingClient _MyClient;
  ///       // Request a retimed update frame rate of 90Hz.
  ///       _MyClient.Connect( "localhost", 90 );
  ///       while( _MyClient.IsConnected() )
  ///       {
  ///         Output_WaitForFrame WaitOutput = _MyClient.WaitForFrame();
  ///         if( WaitOutput.Result == Result::Success )
  ///         {
  ///           // iterate over subjects and segments and obtain the joint positions and rotations as above.
  ///         }
  ///       }
  ///        
  ///  For a more detailed example, see the ViconDataStreamSDK_CPPRetimingTest example. The SimpleViewer application
  ///  also provides an example of re-timing client use in a practical context.
  public ref class RetimingClient {
  public:

    /// Construction.
    /// Instances of the Vicon Data Stream RetimingClient create a DataStreamClient internally that manages the connection 
    /// to the data stream.
    /// 
    /// The RetimingClient will set the underlying client up to receive the required data from the stream and to set the 
    /// correct data delivery mode, so it is not necessary to set this up manually.
    ///
    /// .NET is object oriented, so use the class constructor. 
    /// 
    /// Because objects are lazily garbage collected, your instance may outlive the last reference to it for some time. 
    /// 
    /// If the instance is pre-fetching frame data for you, then it can still use CPU and network bandwidth. 
    /// 
    /// Consider explicitly disconnecting prior to destruction.
    ///
    ///      ViconDataStreamSDK.DotNET.RetimingClient pHeapClient = new ViconDataStreamSDK.DotNET.RetimingClient(); 
    ///      Output_SomeFunction Output = pHeapClient.SomeFunction(InputParam);

    ///      // Signal to the garbage collector that it can clean up 
    ///      pHeapClient.Disconnect(); 
    ///      pHeapClient = null;
    ///
    RetimingClient()
      : m_pClient(new ViconDataStreamSDK::CPP::RetimingClient())
    {
    }

    /// Destruction.
    /// Destruction will Disconnect if required.
    /// 
    /// See RetimingClient::RetimingClient for an example.
    ~RetimingClient()
    {
      delete m_pClient;
      m_pClient = 0;
    }

    /// Get the version of the Vicon DataStream SDK.
    ///   + **Major**
    ///   When this number increases, we break backward compatibility with previous major versions.
    ///   + **Minor**
    ///   When this number increases, we have probably added new functionality to the SDK without breaking 
    ///   backward compatibility with previous versions.
    ///   + **Point**
    ///   When this number increases, we have introduced a bug fix or performance enhancement without breaking 
    ///   backward compatibility with previous versions.
    /// 
    /// The function can be called without the client being connected.
    /// 
    ///      ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///      Output_GetVersion Output = MyClient.GetVersion();
    /// 
    /// \return Output_GetVersion class containing the version information.
    Output_GetVersion^ GetVersion()
    {
      ViconDataStreamSDK::CPP::Output_GetVersion CPPOutput(m_pClient->GetVersion());

      Output_GetVersion^ Output = gcnew Output_GetVersion();
      Output->Major = Adapt(CPPOutput.Major);
      Output->Minor = Adapt(CPPOutput.Minor);
      Output->Point = Adapt(CPPOutput.Point);

      return Output;
    }

    /// Establish a dedicated connection to a Vicon DataStream Server.
    /// 
    /// See Also: Disconnect(), IsConnected().
    /// 
    /// The function defaults to connecting on port 801. 
    /// You can specify an alternate port number after a colon.
    /// This is for future compatibility: current products serve data on port 801 only.
    /// 
    ///      ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///      Output_Connect Output = MyClient.Connect( "localhost" );
    /// 
    /// \param  HostName The DNS-identifiable name, or IP address of the PC hosting the DataStream server. 
    ///                  For example:
    ///                    + "localhost"
    ///                    + "MyViconPC:801"
    ///                    + "10.0.0.2"
    /// 
    /// \param FrameRate An optional parameter - if specified, the re-timing client's internal frame output
    ///        clock will be active.
    /// 
    /// \return An Output_Connect class containing the result of the connect operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + InvalidHostName
    ///           + ClientAlreadyConnected 
    ///           + ClientConnectionFailed
    Output_Connect^ Connect(String^ HostName)
    {
      ViconDataStreamSDK::CPP::Output_Connect CPPOutput(m_pClient->Connect(Adapt(HostName), 0.0 ));

      Output_Connect^ Output = gcnew Output_Connect();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Establish a dedicated connection to a Vicon DataStream Server.
    /// 
    /// See Also: Disconnect(), IsConnected().
    /// 
    /// The function defaults to connecting on port 801. 
    /// You can specify an alternate port number after a colon.
    /// This is for future compatibility: current products serve data on port 801 only.
    /// 
    ///      ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///      Output_Connect Output = MyClient.Connect( "localhost" );
    /// 
    /// \param  HostName The DNS-identifiable name, or IP address of the PC hosting the DataStream server. 
    ///                  For example:
    ///                    + "localhost"
    ///                    + "MyViconPC:801"
    ///                    + "10.0.0.2"
    /// 
    /// \param FrameRate An optional parameter - if specified, the re-timing client's internal frame output
    ///        clock will be active.
    /// 
    /// \return An Output_Connect class containing the result of the connect operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + InvalidHostName
    ///           + ClientAlreadyConnected 
    ///           + ClientConnectionFailed
    Output_Connect^ Connect(String^ HostName, double FrameRate )
    {
      ViconDataStreamSDK::CPP::Output_Connect CPPOutput(m_pClient->Connect(Adapt(HostName), FrameRate));

      Output_Connect^ Output = gcnew Output_Connect();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Disconnect from the Vicon DataStream Server.
    /// 
    /// See Also: Connect(), IsConnected()
    /// 
    ///      ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///       MyClient.Connect( "localhost" );
    ///       Output_Disconnect Output = MyClient.Disconnect();
    /// 
    /// \return An Output_Disconnect class containing the result of the operation.
    ///         - The Result will be: 
    ///           + Success
    ///           + NotConnected
    Output_Disconnect^ Disconnect()
    {
      ViconDataStreamSDK::CPP::Output_Disconnect CPPOutput(m_pClient->Disconnect());

      Output_Disconnect^ Output = gcnew Output_Disconnect();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Discover whether client is connected to the Vicon DataStream Server.
    /// 
    /// See Also: Connect(), Disconnect()
    /// 
    ///      ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///       Output_IsConnected Output = MyClient.IsConnected()
    ///       // Output.Connected == false
    ///       MyClient.Connect( "localhost" );
    ///       Output_IsConnected Output = MyClient.IsConnected()
    ///       // Output.Connected == true
    ///       // (assuming localhost is serving)
    /// 
    /// \return An Output_IsConnected class containing a true value for Connected if you are 
    ///         connected to the stream, otherwise false.
    Output_IsConnected^ IsConnected()
    {
      ViconDataStreamSDK::CPP::Output_IsConnected CPPOutput(m_pClient->IsConnected());

      Output_IsConnected^ Output = gcnew Output_IsConnected();
      Output->Connected = Adapt(CPPOutput.Connected);

      return Output;
    }

    /// Enable kinematic segment data in the Vicon DataStream using the lightweight transport layer. 
    /// Call this function on startup, after connecting to the server, and before trying to read local or global segment data.
    ///
    /// See Also: IsSegmentDataEnabled(), DisableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetSegmentCount(), GetSegmentName(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient(); 
    ///        MyClient.Connect("localhost"); 
    ///        Output_EnableLightweightSegmentData Output = MyClient.EnableLightweightSegmentData()    
    ///
    /// \return An Output_EnableLightweightSegmentData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_EnableLightweightSegmentData^ EnableLightweightSegmentData()
    {
      ViconDataStreamSDK::CPP::Output_EnableLightweightSegmentData CPPOutput( m_pClient->EnableLightweightSegmentData() );

      Output_EnableLightweightSegmentData^ Output = gcnew Output_EnableLightweightSegmentData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }

    /// Disable the lightweight output mode for kinematic segment data in the Vicon DataStream.
    ///
    /// See Also: IsSegmentDataEnabled(), EnableSegmentData(), EnableMarkerData(), EnableUnlabeledMarkerData(), EnableDeviceData(), GetSegmentCount(), GetSegmentName(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        Output_DisableLightweightSegmentData Output = MyClient.DisableLightweightSegmentData();
    ///
    /// \return An Output_DisableLightweightSegmentData class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_DisableLightweightSegmentData^ DisableLightweightSegmentData()
    {
      ViconDataStreamSDK::CPP::Output_DisableLightweightSegmentData CPPOutput( m_pClient->DisableLightweightSegmentData() );

      Output_DisableLightweightSegmentData^ Output = gcnew Output_DisableLightweightSegmentData();
      Output->Result = Adapt( CPPOutput.Result );

      return Output;
    }
    
    /// Return whether the lightweight mode for kinematic segment data is enabled in the Vicon DataStream.
    ///
    /// See Also: EnableSegmentData(), DisableSegmentData(), IsMarkerDataEnabled(), IsUnlabeledMarkerDataEnabled(), IsDeviceDataEnabled()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        Output_IsLightweightSegmentDataEnabled Output = MyClient.IsLightweightSegmentDataEnabled();
    ///                                             // Output.Enabled == false
    ///        MyClient.EnableLightweightSegmentData();
    ///        Output_IsLightweightSegmentDataEnabled Output = MyClient.IsLightweightSegmentDataEnabled();
    ///                                             // Output.Enabled == true
    ///
    /// \return An Output_IsLightweightSegmentDataEnabled class containing the result of the operation.
    ///         - The Result will be:
    ///           + Whether the data is enabled
    Output_IsLightweightSegmentDataEnabled^ IsLightweightSegmentDataEnabled()
    {
      ViconDataStreamSDK::CPP::Output_IsLightweightSegmentDataEnabled CPPOutput( m_pClient->IsLightweightSegmentDataEnabled() );

      Output_IsLightweightSegmentDataEnabled^ Output = gcnew Output_IsLightweightSegmentDataEnabled();
      Output->Enabled = Adapt( CPPOutput.Enabled );

      return Output;
    }
    
    /// Remaps the 3D axis.
    /// Vicon Data uses a right-handed coordinate system, with +X forward, +Y left, and +Z up. 
    /// Other systems use different coordinate systems. The SDK can transform its data into any valid right-handed coordinate system by re-mapping each axis. 
    /// Valid directions are "Up", "Down", "Left", "Right", "Forward", and "Backward". Note that "Forward" means moving away from you, and "Backward" is moving towards you. 
    /// Common usages are
    /// Z-up: SetAxisMapping( Forward, Left, Up )
    /// Y-up: SetAxisMapping( Forward, Up, Right )
    ///
    /// See Also: GetAxisMapping()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.SetAxisMapping( ViconDataStreamSDK.DotNET.Direction.Forward,
    ///        ViconDataStreamSDK.DotNET.Direction.Left,
    ///        ViconDataStreamSDK.DotNET.Direction.Up );
    ///
    /// \param XAxis Specify the direction of your X axis relative to yourself as the observer.
    /// \param YAxis Specify the direction of your Y axis relative to yourself as the observer.
    /// \param ZAxis Specify the direction of your Z axis relative to yourself as the observer.
    ///
    /// \return An Output_SetAxisMapping class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + CoLinearAxes
    ///           + LeftHandedAxes
    Output_SetAxisMapping^ SetAxisMapping(Direction i_XAxis, Direction i_YAxis, Direction i_ZAxis)
    {
      ViconDataStreamSDK::CPP::Output_SetAxisMapping CPPOutput(m_pClient->SetAxisMapping(Adapt(i_XAxis),
        Adapt(i_YAxis),
        Adapt(i_ZAxis)));
      Output_SetAxisMapping^ Output = gcnew Output_SetAxisMapping();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    /// Get the current Axis mapping.
    ///
    /// See Also: SetAxisMapping()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        Output_GetAxisMapping Output = MyClient.GetAxisMapping();
    ///         // Output.XAxis == ViconDataStreamSDK.DotNET.Direction.Forward
    ///         // Output.YAxis == ViconDataStreamSDK.DotNET.Direction.Left
    ///         // Output.ZAxis == ViconDataStreamSDK.DotNET.Direction.Up
    ///
    /// \return An Output_GetAxisMapping class containing the result of the operation.
    ///         - The Result will be:
    ///           + XAxis, YAxis, ZAxis
    Output_GetAxisMapping^ GetAxisMapping()
    {
      ViconDataStreamSDK::CPP::Output_GetAxisMapping CPPOutput(m_pClient->GetAxisMapping());

      Output_GetAxisMapping^ Output = gcnew Output_GetAxisMapping();
      Output->XAxis = Adapt(CPPOutput.XAxis);
      Output->YAxis = Adapt(CPPOutput.YAxis);
      Output->ZAxis = Adapt(CPPOutput.ZAxis);

      return Output;
    }

    /// Update the current frame state to represent the position of all active subjects at the 
    /// current time.
    /// 
    /// The position of each segment is estimated by predicting forwards from the most recent 
    /// frames received from the DataStream, taking into account the latency reported by the 
    /// system to determine the amount of prediction required.
    ///
    /// The results of calls which return details about the current frame state such as GetSubjectCount() 
    /// and GetSegmentGlobalRotationQuaternion() will all return the stream contents and position at the
    /// time that this call was made. 
    /// 
    /// If no call to UpdateFrame() is made, calls querying the stream state will return NoFrame
    /// 
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        Output_UpdateFrame Output;
    ///        Output = MyClient.UpdateFrame(); // Output.Result == NotConnected
    ///        MyClient.Connect( "localhost" );
    ///        Output = MyClient.UpdateFrame(); // Output.Result == Success
    ///
    /// \return An Output_UpdateFrame class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_UpdateFrame^ UpdateFrame()
    {
      Output_UpdateFrame^ Output = gcnew Output_UpdateFrame();
      Output->Result = Adapt(m_pClient->UpdateFrame(0.0).Result);
      return Output;
    }

    /// Update the current frame state to represent the position of all active subjects at the 
    /// current time, specifying an additional prediction offset
    /// 
    /// The position of each segment is estimated by predicting forwards from the most recent 
    /// frames received from the DataStream, taking into account the latency reported by the 
    /// system to determine the amount of prediction required.
    ///
    /// The results of calls which return details about the current frame state such as GetSubjectCount() 
    /// and GetSegmentGlobalRotationQuaternion() will all return the stream contents and position at the
    /// time that this call was made. 
    /// 
    /// If no call to UpdateFrame() is made, calls querying the stream state will return NoFrame
    /// 
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        Output_UpdateFrame Output;
    ///        Output = MyClient.UpdateFrame( 10 ); // Output.Result == NotConnected
    ///        MyClient.Connect( "localhost" );
    ///        Output = MyClient.UpdateFrame( 10 ); // Output.Result == Success
    ///  
    /// \param Offset An additional offset that will be applied to the time at which which the predicted
    ///               position is calculated. This may be used to compensate for additional delays that 
    ///               are in the users system, such as render delay
    ///
    /// \return An Output_UpdateFrame class containing the result of the operation.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    Output_UpdateFrame^ UpdateFrame(double Offset )
    {
      Output_UpdateFrame^ Output = gcnew Output_UpdateFrame();
      Output->Result = Adapt(m_pClient->UpdateFrame(Offset).Result);
      return Output;
    }

    Output_WaitForFrame^ WaitForFrame()
    {
      Output_WaitForFrame^ Output = gcnew Output_WaitForFrame();
      Output->Result = Adapt(m_pClient->WaitForFrame().Result);
      return Output;
    }

    /// Return the number of subjects in the DataStream. This information can be used in conjunction with GetSubjectName.
    ///
    /// See Also: GetSubjectName()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        Output_GetSubjectCount Output;
    ///        Output = MyClient.GetSubjectCount(); // Output.Result == NoFrame
    ///                                            // Ooutput.SubjectCount == 0
    ///        MyClient.UpdateFrame();
    ///        Output = MyClient.GetSubjectCount(); // Output.Result == Success
    ///                                            // Output.SubjectCount >= 0
    ///        
    ///
    /// \return An Output_GetSubjectCount class containing the result of the operation and the number of subjects.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    Output_GetSubjectCount^ GetSubjectCount()
    {
      ViconDataStreamSDK::CPP::Output_GetSubjectCount CPPOutput(m_pClient->GetSubjectCount());

      Output_GetSubjectCount^ Output = gcnew Output_GetSubjectCount();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SubjectCount = Adapt(CPPOutput.SubjectCount);

      return Output;
    }

    /// Return the name of a subject. This can be passed into segment and marker functions.
    ///
    /// See Also: GetSubjectCount()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSubjectCount OutputGSC;
    ///        OutputGSC = MyClient.GetSubjectCount(); // OutputGSC.Result == Success
    ///                                                // OutputGSC.SubjectCount == 2
    ///        Output_GetSubjectName OutputGSN;
    ///        OutputGSN = MyClient.GetSubjectName(0);// OutputGSN.Result == Success
    ///                                               // OutputGSN.SubjectName == "Al"
    ///        OutputGSN = MyClient.GetSubjectName(1);// OutputGSN.Result == Success
    ///                                               // OutputGSN .SubjectName == "Bob"
    ///        OutputGSN = MyClient.GetSubjectName(2);// OutputGSN.Result == InvalidIndex
    ///                                               // OutputGSN.SubjectName == ""
    ///
    ///
    /// \param Subject Index The index of the subject. A valid Subject Index is between 0 and GetSubjectCount()-1.
    ///                                         
    /// \return An Output_GetSubjectName GetSubjectName class containing the result of the operation and the name of the subject.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetSubjectName^ GetSubjectName(unsigned int SubjectIndex)
    {
      ViconDataStreamSDK::CPP::Output_GetSubjectName CPPOutput(m_pClient->GetSubjectName(SubjectIndex));

      Output_GetSubjectName^ Output = gcnew Output_GetSubjectName();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SubjectName = Adapt(CPPOutput.SubjectName);

      return Output;
    }

    /// Return the name of the root segment for a specified subject. This can be passed into segment functions.The root segment is the ancestor of all other segments in the subject.
    ///
    /// See Also: GetSegmentCount(), GetSegmentParentName(), GetSegmentChildCount(), GetSegmentChildName()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSubjectRootSegmentName Output;
    ///        Output = MyClient.GetSubjectRootSegmentName( "Bob" );
    ///        // Output.Result == Success
    ///        // Output.SegmentName == "Pelvis"
    ///        
    ///
    /// \param Subject Name The name of the subject
    /// \return An Output_GetSubjectRootSegmentName class containing the result of the operation and the name of the root segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetSubjectRootSegmentName^ GetSubjectRootSegmentName(String^ SubjectName)
    {
      ViconDataStreamSDK::CPP::Output_GetSubjectRootSegmentName CPPOutput(m_pClient->GetSubjectRootSegmentName(Adapt(SubjectName)));

      Output_GetSubjectRootSegmentName^ Output = gcnew Output_GetSubjectRootSegmentName();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SegmentName = Adapt(CPPOutput.SegmentName);

      return Output;
    }

    /// Return the number of segments for a specified subject in the DataStream. This information can be used in conjunction with GetSegmentName.
    ///
    /// See Also: GetSubjectName(), GetSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        Output_GetSegmentCount Output;
    ///        Output = MyClient.GetSegmentCount( "Bob" ); // Output.Result == NoFrame
    ///                                                    // Output.SegmentCount == 0
    ///        MyClient.UpdateFrame();
    ///        Output = MyClient.GetSegmentCount( "Al" ); // Output.Result ==
    ///                                                   // InvalidSubjectName
    ///        // Output.SegmentCount == 0
    ///        Output = MyClient.GetSegmentCount( "Bob" );// Output.Result == Success
    ///                                                   // Output.SegmentCount >= 0
    ///        
    ///
    /// \param Subject Name The name of the subject.
    /// \return An Output_GetSegmentCount class containing the result of the operation and the number of segments.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    Output_GetSegmentCount^ GetSegmentCount(String^ SubjectName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentCount CPPOutput(m_pClient->GetSegmentCount(Adapt(SubjectName)));

      Output_GetSegmentCount^ Output = gcnew Output_GetSegmentCount();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SegmentCount = Adapt(CPPOutput.SegmentCount);

      return Output;
    }

    /// Return the name of a subject segment specified by index.
    ///
    /// See Also: GetSegmentCount(), GetSegmentChildCount(), GetSegmentChildName(), GetSubjectRootSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentName Output;
    ///        // SegmentIndex must be between 0 and GetSegmentCount() - 1
    ///        Output = MyClient.GetSegmentName( "Bob", 0 );
    ///        
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Index The index of the segment
    /// \return An Output_GetSegmentName  class containing the result of the operation and the name of the parent segment or an empty string if it is the root segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///           + InvalidSubjectName
    Output_GetSegmentName^ GetSegmentName(String^      SubjectName,
      unsigned int SegmentIndex)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentName CPPOutput(m_pClient->GetSegmentName(Adapt(SubjectName), SegmentIndex));

      Output_GetSegmentName^ Output = gcnew Output_GetSegmentName();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SegmentName = Adapt(CPPOutput.SegmentName);

      return Output;
    }

    /// Return the name of the parent segment for a specified subject segment. If the specified segment is the root segment of the subject then it will return an empty string.
    ///
    /// See Also: GetSegmentCount(), GetSegmentChildCount(), GetSegmentChildName(), GetSubjectRootSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentParentName Output;
    ///        Output = MyClient.GetSegmentParentName( "Bob", "Pelvis" );
    ///        // Output.Result == Success
    ///        // Output.SegmentName == ""
    ///        // This is the root segment
    ///        Output = MyClient.GetSegmentParentName( "Bob", "LFemur" );
    ///        // Output.Result == Success
    ///        // Output.SegmentName == "Pelvis"
    ///        
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentParentName  class containing the result of the operation and the name of the parent segment or an empty string if it is the root segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentParentName^ GetSegmentParentName(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentParentName CPPOutput(m_pClient->GetSegmentParentName(Adapt(SubjectName), Adapt(SegmentName)));

      Output_GetSegmentParentName^ Output = gcnew Output_GetSegmentParentName();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SegmentName = Adapt(CPPOutput.SegmentName);

      return Output;
    }

    /// Return the name of a child segment for a specified subject segment. This can be passed into segment functions.
    ///
    /// See Also: GetSegmentCount()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentChildCount OutputGSCC;
    ///        OutputGSCC = MyClient.GetSegmentChildCount( "Bob", "Pelvis" );
    ///        // OutputGSCC.Result == Success
    ///        // OutputGSCC.SegmentCount == 2
    ///        Output_GetSegmentChildName OutputGSCN;
    ///        OutputGSCN = MyClient.GetSegmentName( "Alice", 0 );
    ///        // OutputGSN.Result == InvalidSubjectName
    ///        // OutputGSN.SegmentName == ""
    ///        OutputGSCN = MyClient.GetSegmentName( "Bob", "Pelvis", 0 );
    ///        // OutputGSCN.Result == Success
    ///        // OutputGSCN.SegmentName == "LFemur"
    ///        OutputGSCN = MyClient.GetSegmentName( "Bob", "Pelvis", 1 );
    ///        // OutputGSCN.Result == Success
    ///        // OutputGSCN.SegmentName == "RFemur"
    ///        OutputGSCN = MyClient.GetSegmentName( "Bob", "Pelvis", 2 );
    ///        // OutputGSCN.Result == InvalidIndex
    ///        // OutputGSCN.SegmentName == ""
    ///        // (no third segment)
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \param Segment Index The index of the segment. A valid Segment Index is between 0 and GetSegmentChildCount()-1.
    /// \return An Output_GetSegmentChildCount  class containing the result of the operation and the name of the child segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentChildCount^ GetSegmentChildCount(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentChildCount CPPOutput(m_pClient->GetSegmentChildCount(Adapt(SubjectName), Adapt(SegmentName)));

      Output_GetSegmentChildCount^ Output = gcnew Output_GetSegmentChildCount();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SegmentCount = Adapt(CPPOutput.SegmentCount);

      return Output;
    }

    /// Return the name of the child segment for a specified subject segment and index.
    ///
    /// See Also: GetSegmentCount(), GetSegmentChildCount(), GetSegmentChildName(), GetSubjectRootSegmentName()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentChildName Output;
    ///        // Segment index must be between 0 and GetSegmentChildCount() - 1
    ///        Output = MyClient.GetSegmentChildName( "Bob", "Pelvis", 0 );
    ///        
    ///
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \param Segment Index The index of the child segment. A valid Segment Index is between 0 and GetSegmentChildCount()-1.
    /// \return An Output_GetSegmentChildName  class containing the result of the operation and the name of the child segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidIndex
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentChildName^ GetSegmentChildName(String^      SubjectName,
      String^      SegmentName,
      unsigned int SegmentIndex)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentChildName CPPOutput(m_pClient->GetSegmentChildName(Adapt(SubjectName), Adapt(SegmentName), SegmentIndex));

      Output_GetSegmentChildName^ Output = gcnew Output_GetSegmentChildName();
      Output->Result = Adapt(CPPOutput.Result);
      Output->SegmentName = Adapt(CPPOutput.SegmentName);

      return Output;
    }

    /// Return the static pose translation of a subject segment.
    ///
    /// See Also: GetSegmentStaticRotationHelical(), GetSegmentStaticRotationMatrix(), GetSegmentStaticRotationQuaternion(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentStaticTranslation Output =
    ///        MyClient.GetSegmentStaticTranslation( "Alice", "Pelvis" );
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentStaticTranslation class containing the result of the operation and the translation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticTranslation^ GetSegmentStaticTranslation(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticTranslation CPPOutput(m_pClient->GetSegmentStaticTranslation(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentStaticTranslation^ Output = gcnew Output_GetSegmentStaticTranslation();
      Output->Result = Adapt(CPPOutput.Result);;
      Output->Translation = Adapt(CPPOutput.Translation);

      return Output;
    }

    /// Return the static pose rotation of a subject segment in helical coordinates.
    /// The helical coordinates represent a vector whose length is the amount of rotation in radians, and the direction is the axis about which to rotate.
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationMatrix(), GetSegmentStaticRotationQuaternion(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation, GetSegmentLocalRotationHelical, GetSegmentLocalRotationMatrix, GetSegmentLocalRotationQuaternion, GetSegmentLocalRotationEulerXYZ
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentStaticRotationHelical Output =
    ///        MyClient.GetSegmentStaticRotationHelical( "Alice", "Pelvis" );
    ///        
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentStaticRotationHelical  class containing the result of the operation and the rotation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationHelical^ GetSegmentStaticRotationHelical(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationHelical CPPOutput(m_pClient->GetSegmentStaticRotationHelical(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentStaticRotationHelical^ Output = gcnew Output_GetSegmentStaticRotationHelical();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);

      return Output;
    }

    /// Return the static pose rotation of a subject segment as a 3x3 row-major matrix.
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationHelical(), GetSegmentStaticRotationQuaternion(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentStaticRotationMatrix Output =
    ///        MyClient.GetSegmentStaticRotationMatrix( "Alice", "Pelvis" );
    ///        
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentStaticRotationMatrix  class containing the result of the operation and the rotation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationMatrix^ GetSegmentStaticRotationMatrix(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationMatrix CPPOutput(m_pClient->GetSegmentStaticRotationMatrix(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentStaticRotationMatrix^ Output = gcnew Output_GetSegmentStaticRotationMatrix();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);

      return Output;
    }

    /// Return the static pose rotation of a subject segment in quaternion coordinates.
    /// The quaternion is of the form (x, y, z, w) where w is the real component and x, y and z are the imaginary components. 
    /// N.B. This is different from that used in many other applications, which use (w, x, y, z).
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationHelical(), GetSegmentStaticRotationMatrix(), GetSegmentStaticRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentStaticRotationQuaternion Output =
    ///        MyClient.GetSegmentStaticRotationQuaternion( "Alice", "Pelvis" );
    ///        
    ///
    ///
    /// \param Subject Name The name of the subject
    /// \param Segment Name The name of the segment
    /// \return An Output_GetSegmentStaticRotationQuaternion class containing the result of the operation and the rotation of the segment.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationQuaternion^ GetSegmentStaticRotationQuaternion(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationQuaternion CPPOutput(m_pClient->GetSegmentStaticRotationQuaternion(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentStaticRotationQuaternion^ Output = gcnew Output_GetSegmentStaticRotationQuaternion();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);

      return Output;
    }

    /// Return the static pose rotation of a subject segment in Euler XYZ coordinates.
    ///
    /// See Also: GetSegmentStaticTranslation(), GetSegmentStaticRotationHelical(), GetSegmentStaticRotationMatrix(), 
    /// GetSegmentStaticRotationQuaternion(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), 
    /// GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ().
    /// 
    ///      ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///      MyClient.Connect( "localhost" );
    ///      MyClient.UpdateFrame();
    ///      Output_GetSegmentStaticRotationEulerXYZ Output;
    ///      Output = MyClient.GetSegmentStaticRotationEulerXYZ( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentStaticRotationEulerXYZ class containing the result of the request
    ///         and the rotation of the segment \f$(x,y,z)\f$. 
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    Output_GetSegmentStaticRotationEulerXYZ^ GetSegmentStaticRotationEulerXYZ(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticRotationEulerXYZ CPPOutput(m_pClient->GetSegmentStaticRotationEulerXYZ(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentStaticRotationEulerXYZ^ Output = gcnew Output_GetSegmentStaticRotationEulerXYZ();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);

      return Output;
    }

    Output_GetSegmentStaticScale^ GetSegmentStaticScale(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentStaticScale CPPOutput(m_pClient->GetSegmentStaticScale(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentStaticScale^ Output = gcnew Output_GetSegmentStaticScale();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Scale = Adapt(CPPOutput.Scale);

      return Output;
    }
    /// Return the translation of a subject segment in global coordinates.
    /// The translation is of the form ( x, y, z ) where x, y and z are in millimeters with respect to the global origin.
    ///
    /// See Also: GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentGlobalTranslation Output =
    ///        MyClient.GetSegmentGlobalTranslation( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalTranslation class containing the result of the operation, the translation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///            + Success
    ///            + NotConnected
    ///            + NoFrame
    ///            + InvalidSubjectName
    ///            + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the translation will be [0,0,0].
    Output_GetSegmentGlobalTranslation^ GetSegmentGlobalTranslation(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalTranslation CPPOutput(m_pClient->GetSegmentGlobalTranslation(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentGlobalTranslation^ Output = gcnew Output_GetSegmentGlobalTranslation();
      Output->Result = Adapt(CPPOutput.Result);;
      Output->Translation = Adapt(CPPOutput.Translation);
      Output->Occluded = Adapt(CPPOutput.Occluded);;

      return Output;
    }

    /// Return the rotation of a subject segment in global helical coordinates.
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentGlobalRotationHelical Output =
    ///        MyClient.GetSegmentGlobalRotationHelical( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationHelical class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case, the rotation will be [0,0,0].
    Output_GetSegmentGlobalRotationHelical^ GetSegmentGlobalRotationHelical(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationHelical CPPOutput(m_pClient->GetSegmentGlobalRotationHelical(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentGlobalRotationHelical^ Output = gcnew Output_GetSegmentGlobalRotationHelical();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the rotation of a subject segment as a 3x3 row-major matrix in global coordinates.
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentGlobalRotationMatrix Output =
    ///        MyClient.GetSegmentGlobalRotationMatrix( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationMatrix  Class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame.
    Output_GetSegmentGlobalRotationMatrix^ GetSegmentGlobalRotationMatrix(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationMatrix CPPOutput(m_pClient->GetSegmentGlobalRotationMatrix(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentGlobalRotationMatrix^ Output = gcnew Output_GetSegmentGlobalRotationMatrix();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the rotation of a subject segment in global quaternion coordinates.
    /// The quaternion is of the form (x, y, z, w) where w is the real component and x, y and z are the imaginary components. 
    /// N.B. This is different from that used in many other applications, which use (w, x, y, z).
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationEulerXYZ(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentGlobalRotationQuaternion Output =
    ///        MyClient.GetSegmentGlobalRotationQuaternion( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationQuaternion  class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the Rotation will be [1,0,0,0].
    Output_GetSegmentGlobalRotationQuaternion^ GetSegmentGlobalRotationQuaternion(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationQuaternion CPPOutput(m_pClient->GetSegmentGlobalRotationQuaternion(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentGlobalRotationQuaternion^ Output = gcnew Output_GetSegmentGlobalRotationQuaternion();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the rotation of a subject segment in global Euler XYZ coordinates.
    ///
    /// See Also: GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentGlobalRotationEulerXYZ Output =
    ///        MyClient.GetSegmentGlobalRotationEulerXYZ( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentGlobalRotationEulerXYZ class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the rotation will be [0,0,0].
    Output_GetSegmentGlobalRotationEulerXYZ^ GetSegmentGlobalRotationEulerXYZ(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationEulerXYZ CPPOutput(m_pClient->GetSegmentGlobalRotationEulerXYZ(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentGlobalRotationEulerXYZ^ Output = gcnew Output_GetSegmentGlobalRotationEulerXYZ();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the translation of a subject segment in local coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentLocalTranslation Output =
    ///        MyClient.GetSegmentLocalTranslation( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalTranslation class containing the result of the operation, the translation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the translation will be [0,0,0].
    Output_GetSegmentLocalTranslation^ GetSegmentLocalTranslation(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalTranslation CPPOutput(m_pClient->GetSegmentLocalTranslation(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentLocalTranslation^ Output = gcnew Output_GetSegmentLocalTranslation();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Translation = Adapt(CPPOutput.Translation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the rotation of a subject segment in local helical coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentLocalRotationHelical Output =
    ///        MyClient.GetSegmentLocalRotationHelical( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationHelical class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the Rotation will be [0,0,0].
    Output_GetSegmentLocalRotationHelical^ GetSegmentLocalRotationHelical(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationHelical CPPOutput(m_pClient->GetSegmentLocalRotationHelical(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentLocalRotationHelical^ Output = gcnew Output_GetSegmentLocalRotationHelical();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the rotation row-major matrix of a subject segment in local coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationQuaternion(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix() , GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentLocalRotationMatrix Output =
    ///        MyClient.GetSegmentLocalRotationMatrix( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationMatrix class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame.
    Output_GetSegmentLocalRotationMatrix^ GetSegmentLocalRotationMatrix(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationMatrix CPPOutput(m_pClient->GetSegmentLocalRotationMatrix(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentLocalRotationMatrix^ Output = gcnew Output_GetSegmentLocalRotationMatrix();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the rotation of a subject segment in local quaternion coordinates relative to its parent segment.
    /// The quaternion is of the form (x, y, z, w) where w is the real component and x, y and z are the imaginary components. N.B. This is different from that used in many other applications, which use (w, x, y, z).
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationEulerXYZ(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix(), GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentLocalRotationQuaternion Output =
    ///         MyClient.GetSegmentLocalRotationQuaternion( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationQuaternion class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the rotation will be [1,0,0,0].
    Output_GetSegmentLocalRotationQuaternion^ GetSegmentLocalRotationQuaternion(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationQuaternion CPPOutput(m_pClient->GetSegmentLocalRotationQuaternion(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentLocalRotationQuaternion^ Output = gcnew Output_GetSegmentLocalRotationQuaternion();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    /// Return the rotation of a subject segment in local Euler XYZ coordinates relative to its parent segment.
    ///
    /// See Also: GetSegmentLocalTranslation(), GetSegmentLocalRotationHelical(), GetSegmentLocalRotationMatrix(), GetSegmentLocalRotationQuaternion(), GetSegmentGlobalTranslation(), GetSegmentGlobalRotationHelical(), GetSegmentGlobalRotationMatrix() , GetSegmentGlobalRotationQuaternion(), GetSegmentGlobalRotationEulerXYZ()
    ///
    ///
    ///        ViconDataStreamSDK.DotNET.RetimingClient MyClient = new ViconDataStreamSDK.DotNET.RetimingClient();
    ///        MyClient.Connect( "localhost" );
    ///        MyClient.UpdateFrame();
    ///        Output_GetSegmentLocalRotationEulerXYZ Output =
    ///         MyClient.GetSegmentLocalRotationEulerXYZ( "Alice", "Pelvis" );
    ///
    /// \param  SubjectName The name of the subject.
    /// \param  SegmentName The name of the segment.
    /// \return An Output_GetSegmentLocalRotationEulerXYZ class containing the result of the operation, the rotation of the segment, and whether the segment is occluded.
    ///         - The Result will be:
    ///           + Success
    ///           + NotConnected
    ///           + NoFrame
    ///           + InvalidSubjectName
    ///           + InvalidSegmentName
    ///         - Occluded will be True if the segment was absent at this frame. In this case the rotation will be [0,0,0].
    Output_GetSegmentLocalRotationEulerXYZ^ GetSegmentLocalRotationEulerXYZ(String^ SubjectName,
      String^ SegmentName)
    {
      ViconDataStreamSDK::CPP::Output_GetSegmentLocalRotationEulerXYZ CPPOutput(m_pClient->GetSegmentLocalRotationEulerXYZ(
        Adapt(SubjectName),
        Adapt(SegmentName)));

      Output_GetSegmentLocalRotationEulerXYZ^ Output = gcnew Output_GetSegmentLocalRotationEulerXYZ();
      Output->Result = Adapt(CPPOutput.Result);
      Output->Rotation = Adapt(CPPOutput.Rotation);
      Output->Occluded = Adapt(CPPOutput.Occluded);

      return Output;
    }

    Output_ClearSubjectFilter^ ClearSubjectFilter()
    {
      ViconDataStreamSDK::CPP::Output_ClearSubjectFilter CPPOutput(m_pClient->ClearSubjectFilter());

      Output_ClearSubjectFilter^ Output = gcnew Output_ClearSubjectFilter();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }

    Output_AddToSubjectFilter^ AddToSubjectFilter( String^ SubjectName )
    {
      ViconDataStreamSDK::CPP::Output_AddToSubjectFilter CPPOutput(m_pClient->AddToSubjectFilter( Adapt(SubjectName) ));

      Output_AddToSubjectFilter^ Output = gcnew Output_AddToSubjectFilter();
      Output->Result = Adapt(CPPOutput.Result);

      return Output;
    }


    /// Sets a fixed amount of latency in the output stream; this may be used to avoid the need to predict data forwards 
    /// 
    /// \param i_OutputLatency The amount of latency that is acceptable in the output. The latency of output values should
    ///        always be this value
    void SetOutputLatency(double i_OutputLatency)
    {
      m_pClient->SetOutputLatency(i_OutputLatency);
    }

    /// Returns the fixed latency set by the user. By default this is zero
    ///
    /// \return The fixed latency in milliseconds
    double OutputLatency()
    {
      return m_pClient->OutputLatency();
    }

    /// Sets the maximum amount by which the interpolation engine will predict later than the latest received frame. If required to predict by more than this amount,
    /// the result LateDataRequested will be returned.
    /// 
    /// \param i_MaxPrediction The maximum amount of prediction required in milliseconds
    void SetMaximumPrediction(double i_MaxPrediction)
    {
      m_pClient->SetMaximumPrediction(i_MaxPrediction);
    }

    /// Returns the maximum prediction value currently in use
    /// 
    /// \return The maximum prediction allowed in milliseconds
    double MaximumPrediction()
    {
      return m_pClient->MaximumPrediction();
    }

  private:

    ViconDataStreamSDK::CPP::RetimingClient * m_pClient;
  };
} // End of namespace DotNET
} // End of namespace ViconDataStreamSDK
