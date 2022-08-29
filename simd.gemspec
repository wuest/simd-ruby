Gem::Specification.new do |s|
  s.name = 'simd'
  s.version = '0.5.2'

  s.description = 'Access to SIMD (Single Instruction Multiple Data) instructions in Ruby'
  s.summary     = 'SIMD instructions in ruby'
  s.authors     = ['Tina Wuest']
  s.email       = 'tina@wuest.me'
  s.homepage    = 'https://gitlab.com/wuest/simd-ruby'

  s.files = `git ls-files ext`.split("\n")
  s.extensions = 'ext/simd/extconf.rb'

  s.add_development_dependency 'rake-compiler'
end
