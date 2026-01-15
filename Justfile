

linux-build:
    g++ main.cpp file.cpp -o main

linux ARG: linux-build
      ./main {{ARG}}

windows-build:
    cl main.cpp file.cpp -o main.exe

windows ARG: windows-build
        ./main.exe {{ARG}}
