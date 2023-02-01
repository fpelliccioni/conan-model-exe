from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, CMake, cmake_layout
from conan.tools.build import check_min_cppstd

class ModelExeConan(ConanFile):
    name = "conan-model-exe"
    license = "MIT"
    url = "https://github.com/fpelliccioni/conan-model-exe"
    description = "Model of a C++20 project using CMake, Conan and modern tooling"

    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "include/*"

    def validate(self):
        if self.info.settings.compiler.cppstd:
            check_min_cppstd(self, "20")

    def build_requirements(self):
        self.test_requires("catch2/3.3.0")
        # self.test_requires("doctest/2.4.9")       # Alternative to Catch2
        self.test_requires("nanobench/4.3.9")
        # self.requires("cppfront/cci.20221024")


    def requirements(self):
        self.requires("jfalcou-eve/v2022.09.1")
        self.requires("fmt/9.1.0")
        self.requires("spdlog/1.11.0")
        self.requires("lyra/1.6.1")
        self.requires("expected-lite/0.6.2")

        # self.requires("cthash/???")
        # self.requires("fmtlog/???")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        # tc.variables["CMAKE_VERBOSE_MAKEFILE"] = True
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    # def package(self):
    #     cmake = CMake(self)
    #     cmake.install()

    def package(self):
        self.copy("*.hpp", src=".")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*model_app", dst="bin", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["model"]

    def deploy(self):
        self.copy("model_app", src="bin", dst="bin")
