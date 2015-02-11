# Makes Makefiles for Ruby extensions.
require 'mkmf'

cpu = RbConfig::CONFIG['arch'].downcase
if cpu.include?('arm')
  ver = cpu.gsub(/[^\d]*(\d+).*/, '\\1').to_i
  $CFLAGS << ' -mfpu=neon' if ver >= 6
end

extension_name = 'simd'
dir_config(extension_name)
create_makefile(extension_name)
