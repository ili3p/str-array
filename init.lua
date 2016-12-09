local strarray = {}

local _lib = require 'libstrarray'

for k,v in pairs(_lib) do
    strarray[k] = v
end

return strarray
