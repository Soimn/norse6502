@echo off

set "compile_options= /diagnostics:column /Gm- /FC /W4 /wd4116 /wd4100 /wd4201 /wd4101 /wd4204 /wd4996 /Od /Zo /Zf /Z7 /Oi /nologo /GR- /MP"
set "link_options= /INCREMENTAL:NO /opt:ref"

if NOT EXIST .\build mkdir build
pushd .\build

cl %compile_options% %defines% .\..\assembler.c /link %link_options% /dll /out:assembler.dll
D:\odin\odin.exe build ../main.odin -debug -opt:0

popd
