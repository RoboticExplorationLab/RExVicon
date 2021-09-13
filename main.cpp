#include <iostream>

#include "DataStreamClient.h"

namespace ViconSDK = ViconDataStreamSDK::CPP;

int main() {
    ViconSDK::Client client;
    std::cout << "Hello World!" << std::endl;
    return 0;
}
