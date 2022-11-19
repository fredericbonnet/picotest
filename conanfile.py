from conans import ConanFile, CMake
import platform

class PicotestConan(ConanFile):
    name = "picotest"
    version = "1.4.2"
    license = "BSD-3-Clause"
    author = "Frédéric Bonnet <fredericbonnet@free.fr>"
    url = "https://github.com/fredericbonnet/picotest.git"
    description = "PicoTest is a single-file unit testing framework for C programs that follows the xUnit principles"
    topics = ("testing", "testing-framework", "unit-test", "header-only")

    exports_sources = "include/*", "tests/*", "!tests/*/*", "*.cmake"
    no_copy_source = True

    def build(self): # build & run tests
        cmake = CMake(self)
        cmake.configure(source_folder="tests")
        cmake.build()
        target_test = "RUN_TESTS" if platform.system() == "Windows" else "test"
        cmake.test(target=target_test)

    def package(self):
        self.copy("include/*")

    def package_id(self):
        self.info.clear()
