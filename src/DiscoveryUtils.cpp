#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "DiscoveryUtils.hpp"
#include "ImportOpenCL.hpp"

void DiscoverPlatformsAndDevices() {
    std::cout << "Attempting to query OpenCL Platforms\n";
    cl_platform_id platformIDs[4];
    cl_uint num_platforms = 0;
    auto err = clGetPlatformIDs(4, &platformIDs[0], &num_platforms);
    if (err == CL_SUCCESS) {
        std::cout << "Succesfully manually queried and found " << num_platforms << " platforms\n";
    } else {
        std::cout << "Failed to fetch platforms with error code " << err << std::endl;
    }

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    if (platforms.empty()) {
        std::cout << "No OpenCL platforms found!" << std::endl;
    }

    std::cout << "Found " << platforms.size() << " OpenCL Platform";
    std::cout << ((platforms.size() > 1) ? "s." : ".") << std::endl;

    for (auto & platform : platforms) {
        std::cout << "--------------------" << std::endl;
        auto name = platform.getInfo<CL_PLATFORM_NAME>();
        std::cout << "Name: " << name << std::endl;
        auto vendor = platform.getInfo<CL_PLATFORM_VENDOR>();
        std::cout << "Vendor: " << vendor << std::endl;
        auto version = platform.getInfo<CL_PLATFORM_VERSION>();
        std::cout << "Version: " << version << std::endl;
        auto profile = platform.getInfo<CL_PLATFORM_PROFILE>();
        std::cout << "Supported profile: " << profile << std::endl;

        auto extensions = platform.getInfo<CL_PLATFORM_EXTENSIONS>();

        if (extensions.empty() || extensions == " ")
            std::cout << "No extensions found." << std::endl;
        else {
            std::cout << "Supported extensions: " << std::endl;
            std::stringstream ss(extensions);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> extensionsList(begin, end);
            for (auto & anExtension : extensionsList) {
                std::cout << "\t" << anExtension << "\n";
            }
        }
        // Get the devices supported under this platform.
        std::vector<cl::Device> cpuDevices;
        std::vector<cl::Device> gpuDevices;
        std::vector<cl::Device> acceleratorDevices;

        int deviceCount = 1;

        try {
            std::cout << "Platform has these device(s):" << std::endl;
            platform.getDevices(CL_DEVICE_TYPE_GPU, &gpuDevices);

            for (auto & aDevice : gpuDevices) {
                std::cout << "\t" << deviceCount << ". ";
                std::cout << aDevice.getInfo<CL_DEVICE_NAME>() << std::endl;
                deviceCount++;
            }
        } catch (...) {
        }

        try {
            platform.getDevices(CL_DEVICE_TYPE_CPU, &cpuDevices);
            for (auto & aDevice : cpuDevices) {
                std::cout << "\t" << deviceCount << ". ";
                std::cout << aDevice.getInfo<CL_DEVICE_NAME>() << std::endl;
                deviceCount++;
            }

        } catch (...) {
        }

        try {
            platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &acceleratorDevices);
            for (auto & aDevice : acceleratorDevices) {
                std::cout << "\t" << deviceCount << ". ";
                std::cout << aDevice.getInfo<CL_DEVICE_NAME>() << std::endl;
                deviceCount++;
            }

        } catch (...) {
        }
    }
    std::cout << "--------------------" << std::endl;
}
