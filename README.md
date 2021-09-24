# RExVicon
A simple interface to the Vicon SDK to relay data over ZMQ or a serial port.
Also includes Arduino code to relay the data over radio with LoRa Feather M0.

## Setup on Jetson
Follow these steps to install on an Nvidia Jetson (tested on the Jetson Nano).

1. Install dependencies
    ```
    sudo apt-get install autoconf libboost-dev libboost-all-dev
    ```
2. Download [ViconSDK](https://www.vicon.com/software/datastream-sdk/?section=downloads)
3. Extract the source files from the Vicon archive (located inside the Linux 64 archive, and placed inside another archive called `ViconDataStreamSDKSourceLinux64-source.7z`) into the `RExVicon/ViconSDK` directory
4. Open a terminal in the root of the extracted source code (there should be a `gcc.mk` file and `Vicon/` directory)
5. Run the `RExVicon/ViconSDK/change_to_arm.sh` from the source code directory. This modifies the makefiles to work on the Jetson.
6. Build the code in release mode
    ```
    make CONFIG=Release
    ```
7. Copy the files in the `RExVicon/ViconSDK/` directory by running `RExVicon/ViconSDK/copy_build_output.sh`. It takes a single argument that expects the location of the `ViconSDK/` directory.
8. Change directory to another place in your filesystem, outside this repo
9. Clone the libserialport library:
    ```
    git clone git://sigrok.org/libserialport
    ```
10. Install the libserialport library, building from source:
    ```
    cd libserialport
    ./autogen
    ./configure
    make
    sudo make install

## Building and Running
To build the library, follow these steps from the root folder of the repo.

```
mkdir build
cd build
cmake ..
cmake --build .
```

To run the main executable, call `RExVicon/build/src/rexvicon`. This file takes as 
arguments:

- `-sp` / `--serial-port`: The name of the serial port to print to (default `/dev/ttyACM0`).
- `-b` / `--baud_rate`: Baud rate of the serial port (default `57600`).
- `-a` / `--ipaddres`: IP address on which to publish the ZMQ data (default `192.168.3.134`).
- `-p` / `--port`: Port on which which to publish the ZMQ data (default `5555`).
- `-t` / `--subject`: Name of the Vicon object to publish (default `rex1`).
- `-w` / `--wait`: Wait indefinitely to connect to the vicon, recommended if running on startup (default `false`).

## Running the script on startup
If running the script on a Linux machine (tested on a Jetson Nano), and you want the
Vicon publisher to start automatically, follow these instructions:
1. Create a limited user
    sudo addgroup --system vicon
    sudo adduser --system --no-create-home --disabled-login --disabled-password --ingroup vicon vicon
2. Copy the `vicon.service` file to `/lib/systemd/system/`
    sudo cp vicon.service /lib/systemd/system
3. Reload and start the service daemon
    sudo systemctl daemon-reload
    sudo systemctl start vicon
4. Enable the service to run on startup
    sudo systemctl enable vicon
