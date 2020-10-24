function build_release () {
    cmake -H. -B_build/Release -DCMAKE_BUILD_TYPE=Release && cmake --build _build/Release -- -j8
}

function build_debug () {
    cmake -H. -B_build/Debug -DCMAKE_BUILD_TYPE=Debug && cmake --build _build/Debug -- -j8
}
