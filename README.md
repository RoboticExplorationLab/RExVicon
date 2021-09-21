# RExVicon
A simple interface to the Vicon SDK to relay data over ZMQ or serial


## Dependencies


### Install on RPi3
Download ViconSDK
clone libserialport
```
sudo apt-get install autoconf
git clone git://sigrok.org/libserialport
cd libserialport
./autogen
./configu
```

### Building the ViconSDK from source
When building on ARM chips, the ViconSDK build system needs to be modified since it isn't supported out of the box. We've provided some scripts to make the changes for you. Follow these steps:
1. Extract the Vicon source folder inside of the `ViconSDK` folder. This should contain a makefile, `gcc.mk` and a `Vicon/` directory with all of the source code.
2. In a terminal move to the root of the extracted directory. You should have a `gcc.mk` and `makefile` in the directory.
3. Run the `change_to_arm.sh` file from your directory. This will modify all of the make files in the build.
4. Install the boost libraries on your system
    sudo apt-get install libboost-dev libboost-all-dev
5. Build the code in release mode
    make CONFIG=Release
6. Copy the files into the `ViconSDK/` directory using `ViconSDK/copy_build_output.sh`. This file needs to be called from the root directory of the ViconSDK source code:
   ../../copy_build_output.sh ../..
