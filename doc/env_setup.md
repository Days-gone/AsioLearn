# Env
Using boost and other libs, so we need a package manager to install them.
We will choose vcpkg as our package manager.

# Vcpkg
Vcpkg is a C++ package manager for Windows, Linux and MacOS. It simplifies the process of managing libraries for your projects. Now let's install the vcpkg.
```bash
git clone git@github.com:microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg install boost
./vcpkg integrate install
```
then we need to integrate the lib with our project.
According to the official doc, the newest version of vcpkg has a new feature that can integrate the lib with the project automatically. But I found that it doesn't work for me. So I choose to use the older way.
whichi is prompted by the vcpkg cli info.
```bash
# change the [] to your vcpkg root
cmake build -DCMAKE_TOOLCHAIN_FILE= "[vcpkg root]/scripts/buildsystems/vcpkg.cmake"
# the total command is like this
cmake -DCMAKE_TOOLCHAIN_FILE=/home/xym/code_folder/cpp_code/vcpkg/scripts/buildsystems/vcpkg.cmake -B build
```

# Integrate with the Vscode
we don't wanna input such long command everytime we wanna build, to solve this problem,
in your VScode settings.json, add the following code:
```json
"cmake.configureSettings": {

    "CMAKE_TOOLCHAIN_FILE": "/home/xym/code_folder/cpp_code/vcpkg/scripts/buildsystems/vcpkg.cmake"
}
```
then you can use the vscode cmake extension to build your project, without having to input the long command. However the official doc recommend a newer way to solve this problem, which is to use vcpkg.json and CMakePresets.json. I haven't tried it yet, but I will try it later.
There is a another way to integrate the vcpkg with the project.
By creating a directory called .vscode and adding a settings.json file in your project root directory. Adding the following code to the settings.json file.
```json
{
    // change the following path to your vcpkg.cmake path
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "/vcpkg/scripts/buildsystems/vcpkg.cmake"
    }
}
```
Then you can use the vscode cmake extension to build your project, without having to input the long command.
# TODO
try the new way to integrate the vcpkg with the project.
