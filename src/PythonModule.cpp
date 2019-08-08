#include "DiscoveryUtils.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;
PYBIND11_MODULE(TestModule, m) {
    m.def("query_platforms_and_devices", &DiscoverPlatformsAndDevices);
}
