
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
#include "DataStreamClient.h"
#include "DataStreamRetimingClient.h"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <fstream>
#include <chrono>

#ifdef WIN32
#include <conio.h>   // For _kbhit()
#include <cstdio>   // For getchar()
#include <windows.h> // For Sleep()
#else
#include <unistd.h> // For sleep()
#endif // WIN32

#define CSV_OUTPUT( FILE, OUTPUT ) if( FILE.good() ) FILE << OUTPUT

using namespace ViconDataStreamSDK::CPP;

#ifdef WIN32
bool Hit()
{
  bool hit = false;
  while( _kbhit() )
  {
    getchar();
    hit = true;
  }
  return hit;
}
#endif

namespace
{
  std::string Adapt(const bool i_Value)
  {
    return i_Value ? "True" : "False";
  }

  void PrintSubjects( const ViconDataStreamSDK::CPP::RetimingClient & i_rRetimer, std::ostream & o_rStream )
  {
    // Count the number of subjects
    unsigned int SubjectCount = i_rRetimer.GetSubjectCount().SubjectCount;
    o_rStream << "Subjects (" << SubjectCount << "):" << std::endl;
    for (unsigned int SubjectIndex = 0; SubjectIndex < SubjectCount; ++SubjectIndex)
    {
      o_rStream << "  Subject #" << SubjectIndex << std::endl;

      // Get the subject name
      std::string SubjectName = i_rRetimer.GetSubjectName(SubjectIndex).SubjectName;
      o_rStream << "    Name: " << SubjectName << std::endl;

      // Get the root segment
      std::string RootSegment = i_rRetimer.GetSubjectRootSegmentName(SubjectName).SegmentName;
      o_rStream << "    Root Segment: " << RootSegment << std::endl;

      // Count the number of segments
      unsigned int SegmentCount = i_rRetimer.GetSegmentCount(SubjectName).SegmentCount;
      o_rStream << "    Segments (" << SegmentCount << "):" << std::endl;
      for (unsigned int SegmentIndex = 0; SegmentIndex < SegmentCount; ++SegmentIndex)
      {
        o_rStream << "      Segment #" << SegmentIndex << std::endl;

        // Get the segment name
        std::string SegmentName = i_rRetimer.GetSegmentName(SubjectName, SegmentIndex).SegmentName;
        o_rStream << "        Name: " << SegmentName << std::endl;

        // Get the segment parent
        std::string SegmentParentName = i_rRetimer.GetSegmentParentName(SubjectName, SegmentName).SegmentName;
        o_rStream << "        Parent: " << SegmentParentName << std::endl;

        // Get the segment's children
        unsigned int ChildCount = i_rRetimer.GetSegmentChildCount(SubjectName, SegmentName).SegmentCount;
        o_rStream << "     Children (" << ChildCount << "):" << std::endl;
        for (unsigned int ChildIndex = 0; ChildIndex < ChildCount; ++ChildIndex)
        {
          std::string ChildName = i_rRetimer.GetSegmentChildName(SubjectName, SegmentName, ChildIndex).SegmentName;
          o_rStream << "       " << ChildName << std::endl;
        }

        // Get the static segment translation
        Output_GetSegmentStaticTranslation _Output_GetSegmentStaticTranslation =
          i_rRetimer.GetSegmentStaticTranslation(SubjectName, SegmentName);
        o_rStream << "        Static Translation: (" << _Output_GetSegmentStaticTranslation.Translation[0] << ", "
          << _Output_GetSegmentStaticTranslation.Translation[1] << ", "
          << _Output_GetSegmentStaticTranslation.Translation[2] << ")" << std::endl;

        // Get the static segment rotation in helical co-ordinates
        Output_GetSegmentStaticRotationHelical _Output_GetSegmentStaticRotationHelical =
          i_rRetimer.GetSegmentStaticRotationHelical(SubjectName, SegmentName);
        o_rStream << "        Static Rotation Helical: (" << _Output_GetSegmentStaticRotationHelical.Rotation[0] << ", "
          << _Output_GetSegmentStaticRotationHelical.Rotation[1] << ", "
          << _Output_GetSegmentStaticRotationHelical.Rotation[2] << ")" << std::endl;

        // Get the static segment rotation as a matrix
        Output_GetSegmentStaticRotationMatrix _Output_GetSegmentStaticRotationMatrix =
          i_rRetimer.GetSegmentStaticRotationMatrix(SubjectName, SegmentName);
        o_rStream << "        Static Rotation Matrix: (" << _Output_GetSegmentStaticRotationMatrix.Rotation[0] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[1] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[2] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[3] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[4] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[5] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[6] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[7] << ", "
          << _Output_GetSegmentStaticRotationMatrix.Rotation[8] << ")" << std::endl;

        // Get the static segment rotation in quaternion co-ordinates
        Output_GetSegmentStaticRotationQuaternion _Output_GetSegmentStaticRotationQuaternion =
          i_rRetimer.GetSegmentStaticRotationQuaternion(SubjectName, SegmentName);
        o_rStream << "        Static Rotation Quaternion: (" << _Output_GetSegmentStaticRotationQuaternion.Rotation[0] << ", "
          << _Output_GetSegmentStaticRotationQuaternion.Rotation[1] << ", "
          << _Output_GetSegmentStaticRotationQuaternion.Rotation[2] << ", "
          << _Output_GetSegmentStaticRotationQuaternion.Rotation[3] << ")" << std::endl;

        // Get the static segment rotation in EulerXYZ co-ordinates
        Output_GetSegmentStaticRotationEulerXYZ _Output_GetSegmentStaticRotationEulerXYZ =
          i_rRetimer.GetSegmentStaticRotationEulerXYZ(SubjectName, SegmentName);
        o_rStream << "        Static Rotation EulerXYZ: (" << _Output_GetSegmentStaticRotationEulerXYZ.Rotation[0] << ", "
          << _Output_GetSegmentStaticRotationEulerXYZ.Rotation[1] << ", "
          << _Output_GetSegmentStaticRotationEulerXYZ.Rotation[2] << ")" << std::endl;

        // Get the global segment translation
        Output_GetSegmentGlobalTranslation _Output_GetSegmentGlobalTranslation =
          i_rRetimer.GetSegmentGlobalTranslation(SubjectName, SegmentName);
        o_rStream << "        Global Translation: (" << _Output_GetSegmentGlobalTranslation.Translation[0] << ", "
          << _Output_GetSegmentGlobalTranslation.Translation[1] << ", "
          << _Output_GetSegmentGlobalTranslation.Translation[2] << ") "
          << Adapt(_Output_GetSegmentGlobalTranslation.Occluded) << std::endl;

        // Get the global segment rotation in helical co-ordinates
        Output_GetSegmentGlobalRotationHelical _Output_GetSegmentGlobalRotationHelical =
          i_rRetimer.GetSegmentGlobalRotationHelical(SubjectName, SegmentName);
        o_rStream << "        Global Rotation Helical: (" << _Output_GetSegmentGlobalRotationHelical.Rotation[0] << ", "
          << _Output_GetSegmentGlobalRotationHelical.Rotation[1] << ", "
          << _Output_GetSegmentGlobalRotationHelical.Rotation[2] << ") "
          << Adapt(_Output_GetSegmentGlobalRotationHelical.Occluded) << std::endl;

        // Get the global segment rotation as a matrix
        Output_GetSegmentGlobalRotationMatrix _Output_GetSegmentGlobalRotationMatrix =
          i_rRetimer.GetSegmentGlobalRotationMatrix(SubjectName, SegmentName);
        o_rStream << "        Global Rotation Matrix: (" << _Output_GetSegmentGlobalRotationMatrix.Rotation[0] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[1] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[2] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[3] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[4] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[5] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[6] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[7] << ", "
          << _Output_GetSegmentGlobalRotationMatrix.Rotation[8] << ") "
          << Adapt(_Output_GetSegmentGlobalRotationMatrix.Occluded) << std::endl;

        // Get the global segment rotation in quaternion co-ordinates
        Output_GetSegmentGlobalRotationQuaternion _Output_GetSegmentGlobalRotationQuaternion =
          i_rRetimer.GetSegmentGlobalRotationQuaternion(SubjectName, SegmentName);
        o_rStream << "        Global Rotation Quaternion: (" << _Output_GetSegmentGlobalRotationQuaternion.Rotation[0] << ", "
          << _Output_GetSegmentGlobalRotationQuaternion.Rotation[1] << ", "
          << _Output_GetSegmentGlobalRotationQuaternion.Rotation[2] << ", "
          << _Output_GetSegmentGlobalRotationQuaternion.Rotation[3] << ") "
          << Adapt(_Output_GetSegmentGlobalRotationQuaternion.Occluded) << std::endl;

        // Get the global segment rotation in EulerXYZ co-ordinates
        Output_GetSegmentGlobalRotationEulerXYZ _Output_GetSegmentGlobalRotationEulerXYZ =
          i_rRetimer.GetSegmentGlobalRotationEulerXYZ(SubjectName, SegmentName);
        o_rStream << "        Global Rotation EulerXYZ: (" << _Output_GetSegmentGlobalRotationEulerXYZ.Rotation[0] << ", "
          << _Output_GetSegmentGlobalRotationEulerXYZ.Rotation[1] << ", "
          << _Output_GetSegmentGlobalRotationEulerXYZ.Rotation[2] << ") "
          << Adapt(_Output_GetSegmentGlobalRotationEulerXYZ.Occluded) << std::endl;

        // Get the local segment translation
        Output_GetSegmentLocalTranslation _Output_GetSegmentLocalTranslation =
          i_rRetimer.GetSegmentLocalTranslation(SubjectName, SegmentName);
        o_rStream << "        Local Translation: (" << _Output_GetSegmentLocalTranslation.Translation[0] << ", "
          << _Output_GetSegmentLocalTranslation.Translation[1] << ", "
          << _Output_GetSegmentLocalTranslation.Translation[2] << ") "
          << Adapt(_Output_GetSegmentLocalTranslation.Occluded) << std::endl;

        // Get the local segment rotation in helical co-ordinates
        Output_GetSegmentLocalRotationHelical _Output_GetSegmentLocalRotationHelical =
          i_rRetimer.GetSegmentLocalRotationHelical(SubjectName, SegmentName);
        o_rStream << "        Local Rotation Helical: (" << _Output_GetSegmentLocalRotationHelical.Rotation[0] << ", "
          << _Output_GetSegmentLocalRotationHelical.Rotation[1] << ", "
          << _Output_GetSegmentLocalRotationHelical.Rotation[2] << ") "
          << Adapt(_Output_GetSegmentLocalRotationHelical.Occluded) << std::endl;

        // Get the local segment rotation as a matrix
        Output_GetSegmentLocalRotationMatrix _Output_GetSegmentLocalRotationMatrix =
          i_rRetimer.GetSegmentLocalRotationMatrix(SubjectName, SegmentName);
        o_rStream << "        Local Rotation Matrix: (" << _Output_GetSegmentLocalRotationMatrix.Rotation[0] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[1] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[2] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[3] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[4] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[5] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[6] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[7] << ", "
          << _Output_GetSegmentLocalRotationMatrix.Rotation[8] << ") "
          << Adapt(_Output_GetSegmentLocalRotationMatrix.Occluded) << std::endl;

        // Get the local segment rotation in quaternion co-ordinates
        Output_GetSegmentLocalRotationQuaternion _Output_GetSegmentLocalRotationQuaternion =
          i_rRetimer.GetSegmentLocalRotationQuaternion(SubjectName, SegmentName);
        o_rStream << "        Local Rotation Quaternion: (" << _Output_GetSegmentLocalRotationQuaternion.Rotation[0] << ", "
          << _Output_GetSegmentLocalRotationQuaternion.Rotation[1] << ", "
          << _Output_GetSegmentLocalRotationQuaternion.Rotation[2] << ", "
          << _Output_GetSegmentLocalRotationQuaternion.Rotation[3] << ") "
          << Adapt(_Output_GetSegmentLocalRotationQuaternion.Occluded) << std::endl;

        // Get the local segment rotation in EulerXYZ co-ordinates
        Output_GetSegmentLocalRotationEulerXYZ _Output_GetSegmentLocalRotationEulerXYZ =
          i_rRetimer.GetSegmentLocalRotationEulerXYZ(SubjectName, SegmentName);
        o_rStream << "        Local Rotation EulerXYZ: (" << _Output_GetSegmentLocalRotationEulerXYZ.Rotation[0] << ", "
          << _Output_GetSegmentLocalRotationEulerXYZ.Rotation[1] << ", "
          << _Output_GetSegmentLocalRotationEulerXYZ.Rotation[2] << ") "
          << Adapt(_Output_GetSegmentLocalRotationEulerXYZ.Occluded) << std::endl;
      }
    }
  }
}

int main( int argc, char* argv[] )
{
  std::cout << "DSSDK C++ API Retiming Test" << std::endl;

  // Program options

  bool bOutput = true;
  bool bLightweight = false;
  std::vector< std::string > FilteredSubjects;
  bool bSubjectFilterApplied = false;

  std::string HostName = "localhost:801";
  if( argc > 1 )
  {
    HostName = argv[1];
  }

  double FrameRate = -1;
  unsigned int NumRestarts = 1;
  double Duration = 0;
  std::string OutputFile;
  std::string DebugLog;
  std::string RedirectOutput;

  for( int a = 2; a < argc; ++a )
  {
    std::string arg = argv[a];
    if( arg == "--help" )
    {
      std::cout << argv[0] << " <HostName>: allowed options include:\n --framerate <frame rate> --output <csv_filename> --restarts <nrestarts> --duration <duration in ms> --no-output" << std::endl;
      return 0;
    }
    else if( arg == "--framerate" )
    {
      if( a < argc )
      {
        FrameRate = boost::lexical_cast<double>( argv[++a] );
      }
    }
    else if( arg == "--restarts" )
    {
      if( a < argc )
      {
        try
        {
          NumRestarts = boost::lexical_cast<unsigned int>( argv[++a] ) + 1;
        }
        catch( boost::bad_lexical_cast & e )
        {
          std::cerr << e.what() << std::endl;
        }
      }
    }
    else if( arg == "--duration" )
    {
      if( a < argc )
      {
        try
        {
          Duration = boost::lexical_cast<double>( argv[++a] );
        }
        catch( boost::bad_lexical_cast & e )
        {
          std::cerr << e.what() << std::endl;
        }
      }
    }
    else if (arg == "--output-file")
    {
      OutputFile = argv[++a];
    }
    else if( arg == "--debug-log" )
    {
      DebugLog = argv[++a];
    }
    else if( arg == "--no-output" )
    {
      bOutput = false;
    }
    else if ( arg == "--lightweight" )
    {
      bLightweight = true;
    }
    else if( arg == "--redirect-output" )
    {
      RedirectOutput = argv[++a];
    }
    else if( arg == "--subjects" )
    {
      ++a;
      //assuming no subject name starts with "--"
      while( a < argc )
      {
        if (strncmp( argv[a], "--", 2 ) == 0)
        { 
          --a;
          break;
        }
        FilteredSubjects.push_back( argv[ a ] );
        ++a;
      }
    }
  }


  std::string LogFile = "";

  ViconDataStreamSDK::CPP::RetimingClient Retimer;

  if ( bLightweight )
  {
    Retimer.EnableLightweightSegmentData();
  }
  
  if (!OutputFile.empty())
  {
    if (Retimer.SetOutputFile(OutputFile))
    {
      std::cout << "Writing retimer data to " << OutputFile << std::endl;
    }
    else
    {
      std::cout << "Unable to open " << OutputFile << std::endl;
    }
  }

  if( !DebugLog.empty() )
  {
    if( Retimer.SetDebugLogFile( DebugLog ) )
    {
      std::cout << "Writing retimer debug log to " << DebugLog << std::endl;
    }
    else
    {
      std::cout << "Unable to open " << DebugLog << std::endl;
    }
  }

  std::ostream* pOutput;
  if( !RedirectOutput.empty() )
  {
    pOutput = new std::ofstream(RedirectOutput);
  }
  else
  {
    pOutput = &std::cout;
  }

  for (unsigned int RunNumber = 0; RunNumber < NumRestarts; ++RunNumber)
  {
    if (NumRestarts > 1)
    {
      std::cout << "Run number " << RunNumber << " with duration " << Duration << std::endl;
    }

    if (Retimer.Connect(HostName, FrameRate ).Result != Result::Success)
    {
      std::cout << "Could not connect to " << HostName << std::endl;
      return false;
    }

    const auto StartTime = std::chrono::high_resolution_clock::now();
    bool bStop = false;

    
    // The retimer may sometimes take a few frames to start producing data as it 
    // needs to fill a buffer before it can produce output.
    // We will use this flag to inhibit output during this spool up phase.
    bool bDataReceived = false;

#ifdef WIN32
    while( !bStop && !Hit() )
#else
    while( !bStop )
#endif  
    {


      if( Duration != 0 )
      {
        double TimeElapsed = static_cast< double >( std::chrono::duration_cast<std::chrono::milliseconds>(
                                  ( std::chrono::high_resolution_clock::now() - StartTime ) ).count() );
        bStop = TimeElapsed > Duration;
      }

      // We are running on a loop timer - use this method if you do not have an existing timer in your project
      if( FrameRate > 0 )
      {
        // Wait for a frame. This method blocks until the next frame period has elapsed.
        auto WaitResult = Retimer.WaitForFrame();
        bDataReceived = bDataReceived || ( WaitResult.Result == Result::Success );
      }
      else
      {
        auto UpdateResult = Retimer.UpdateFrame();
        bDataReceived = bDataReceived || (UpdateResult.Result == Result::Success);

        // Impose our own simple frame rate throttle, so that we do not overload the process
#ifdef WIN32
        Sleep( 10 );
#else
        sleep( 1 );
#endif      
      }

      // We have to call this after the call to get frame, otherwise we don't have any subject info
      // to map the name to ids
      if( !bSubjectFilterApplied )
      {
        for( const auto& rSubject : FilteredSubjects )
        {
          Output_AddToSubjectFilter SubjectFilterResult = Retimer.AddToSubjectFilter(rSubject);
          bSubjectFilterApplied = bSubjectFilterApplied || SubjectFilterResult.Result == Result::Success;
        }
      }
      if (bDataReceived && bOutput)
      {
        PrintSubjects(Retimer, *pOutput );
      }
    }

    Retimer.Disconnect();
  }
}

