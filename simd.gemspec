# frozen_string_literal: true

Gem::Specification.new do |s|
  s.name = 'simd'
  s.version = '0.6.0'

  s.description = 'Access to SIMD (Single Instruction Multiple Data) instructions in Ruby'
  s.summary     = 'SIMD instructions in ruby'
  s.authors     = ['Tina Wuest']
  s.email       = 'tina@wuest.me'
  s.homepage    = 'https://github.com/wuest/simd-ruby'
  s.license     = 'MIT'

  s.required_ruby_version = '>= 3.0.0'

  s.metadata['homepage_uri'] = s.homepage
  s.metadata['source_code_uri'] = s.homepage
  s.metadata['changelog_uri'] = 'https://github.com/wuest/simd-ruby/blob/main/CHANGELOG.md'
  s.metadata['rubygems_mfa_required'] = 'true'

  s.files = `git ls-files ext`.split("\n")
  s.extensions = 'ext/simd/extconf.rb'
end
