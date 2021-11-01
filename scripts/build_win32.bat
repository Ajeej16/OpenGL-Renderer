@echo off

set CommonCompilerFlags=-nologo -EHsc -FC -Zi
set CommonLinkerFlags=-STACK:0x100000,0x100000 -subsystem:windows

set dir=..
set glfw_dll=%dir%\\includes\\glfw\\lib-vc2019\\glfw3.dll

set IncludePaths=-I%dir%\\includes\\glfw\\include -I%dir%\\includes\\glad\\include -I%dir%\\includes\\glad\\src -I%dir%\\includes\\glm -I%dir%\\includes -I%dir%\\includes\\assimp-5.0.1\\include -I%dir%\\includes\\assimp-5.0.1\\build\\include

set LibraryPaths=/LIBPATH:%dir%\\includes\\glfw\\lib-vc2019 /LIBPATH:%dir%\\includes\\assimp-5.0.1\\build\\code\\Debug

set Libraries=glfw3dll.lib opengl32.lib user32.lib assimp-vc142-mtd.lib


if not exist build (mkdir build)
pushd build

copy %glfw_dll%

cl %IncludePaths% %CommonCompilerFlags% %dir%\\src\\test.cpp /link %CommonLinkerFlags% %LibraryPaths% %Libraries%

popd