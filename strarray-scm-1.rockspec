package = "strarray"
version = "scm-1"

source = {
    url = "",
}

description = {
    summary = "",
    detailed = [[
    ]],
    homepage = "",
    license = "MIT"
}

dependencies = {
    "lua >= 5.1"
}

build = {
   type = "command",
   build_command = [[cmake -E make_directory build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$(LUA_BINDIR)/.." -DCMAKE_INSTALL_PREFIX="$(PREFIX)" && $(MAKE)]],
   install_command = "cd build && $(MAKE) install"
}
