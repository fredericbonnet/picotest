from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy
import os


class PicoTestConan(ConanFile):
    name = "picotest"
    version = "1.4.3"
    description = ("PicoTest is a single-file unit testing framework for C "
                   "programs that follows the xUnit principles")
    license = "BSD-3-Clause"
    author = "Frédéric Bonnet <fredericbonnet@free.fr>"
    url = "https://github.com/fredericbonnet/picotest"
    homepage = "https://fredericbonnet.github.io/picotest"
    topics = ("c", "testing", "unit-testing", "xunit")

    # Package is header-only
    package_type = "header-library"
    no_copy_source = False

    # No settings needed for header-only
    settings = "os", "compiler", "build_type", "arch"

    # Sources are not needed for the conan package
    exports_sources = "include/*", "*.cmake", "LICENSE"
    
    def layout(self):
        cmake_layout(self)

    def package_info(self):
        # Header-only library
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        
        # Include directories
        self.cpp_info.includedirs = ["include"]
        
        # CMake integration
        self.cpp_info.set_property("cmake_module_file_name", "PicoTest")
        self.cpp_info.set_property("cmake_file_name", "PicoTest")
        self.cpp_info.set_property("cmake_target_name", "PicoTest::PicoTest")
        self.cpp_info.set_property("cmake_build_modules", ["cmake/PicoTest.cmake"])
        
        # CMake build directories
        self.cpp_info.builddirs = ["cmake"]

    def package(self):
        # Copy license
        copy(self, "LICENSE", src=self.source_folder, 
             dst=os.path.join(self.package_folder, "licenses"))
        
        # Copy headers
        copy(self, "*.h", src=os.path.join(self.source_folder, "include"), 
             dst=os.path.join(self.package_folder, "include"))
        
        # Copy CMake files
        cmake_dir = os.path.join(self.package_folder, "cmake")
        copy(self, "PicoTest.cmake", src=self.source_folder, dst=cmake_dir)
        copy(self, "PicoTestAddTests.cmake", src=self.source_folder, 
             dst=cmake_dir)
        copy(self, "PicoTestConfig.cmake", src=self.source_folder, 
             dst=cmake_dir)

    def package_id(self):
        # Header-only package - no dependency on settings
        self.info.clear() 
        