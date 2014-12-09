# Makes Makefiles for Ruby extensions.
require 'mkmf'

extension_name = 'simd'
dir_config(extension_name)
create_makefile(extension_name)
