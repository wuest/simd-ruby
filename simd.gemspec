Gem::Specification.new do |s|
  s.name = 'simd'
  s.version = '0.5.2'

  s.description = 'Access to SIMD (Single Instruction Multiple Data) instructions in Ruby'
  s.summary     = 'SIMD instructions in ruby'
  s.authors     = ['Tina Wuest']
  s.email       = 'tina@wuest.me'
  s.homepage    = 'https://github.com/wuest/simd-ruby'
  s.license     = 'MIT'

  s.metadata['homepage_uri'] = s.homepage
  s.metadata['source_code_uri'] = s.homepage
  s.metadata['changelog_uri'] = 'https://github.com/wuest/simd-ruby/blob/main/CHANGELOG.md'

  s.files = `git ls-files ext`.split("\n")
  s.extensions = 'ext/simd/extconf.rb'

  s.add_development_dependency 'rake-compiler', '~> 1.2'
  s.add_development_dependency 'minitest-proptest', '~> 0.0'
end
