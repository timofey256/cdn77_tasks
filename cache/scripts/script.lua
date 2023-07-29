local ffi = require("ffi")

local lib = ffi.load("square")

ffi.cdef[[
int square(int num);
]]

local squared = lib.square(5)
print(squared)
