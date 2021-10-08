#!/usr/bin/env python3

from waflib.Tools.compiler_cxx import cxx_compiler

import os
import sys
import subprocess

APPNAME = "base64"

cxx_compiler["linux"] = ["clang++"]

def options(opt) :
    opt.load("compiler_cxx")

def configure(cnf) :
    cnf.load("compiler_cxx")

    link_flags = ["-pthread"]
    cxx_flags = ["-std=c++17", "-Wall", "-Wextra", "-O3"]
    
    if sys.platform == "darwin":
        link_flags.append("-L/usr/local/opt/llvm/lib")
        cxx_flags.append("-stdlib=libc++")

    cnf.env.append_value("CXXFLAGS", cxx_flags)        
    cnf.env.append_value("LINKFLAGS",
                         link_flags)
    
def build(bld):

    bld(name = "{!s}-includes".format(APPNAME),
        includes="./include/",
        export_includes="./include/")
    

    bld.recurse("test/test_base64")

    bld.recurse("example")            
    
def test(ctx):
    subprocess.call(["./build/test/test_base64/test_base64"], encoding="utf-8")


def documentation(ctx):

    subprocess.call(["doxygen", "Doxyfile"])
