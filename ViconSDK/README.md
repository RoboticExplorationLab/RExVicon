# Building the Vicon DataStream SDK
This package relies on the Vicon DataStream SDK, which can be obtained for free 
[here](https://www.vicon.com/software/datastream-sdk/?section=downloads). 

To use this package, the header files and compiled binaries must be extracted onto 
your computer. Using the link above, extract the headers and binaries into this 
folder. It's recommended to keep them contained within the top-level `Mac64` or `Linux64`
folder in which they're shipped. After extraction, the directory structure should look like
the following, with minor differences between Linux and MacOS operating systems. Note that
Windows and other operating systems are not currently supported by this library.

### Linux
```
RExVicon/
  ...
  ViconSDK/
    Linux64/
      DataStreamClient.h
      ...
      libViconDataStreamSDK_CPP.so
      ...
    ...
  ...
```

### MacOS
```
RExVicon/
  ...
  ViconSDK/
    Mac64/
      DataStreamClient.h
      ...
      libViconDataStreamSDK_CPP.dylib
      ...
    ...
  ...
```

