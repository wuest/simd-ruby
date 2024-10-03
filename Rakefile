# frozen_string_literal: true

require 'rake/extensiontask'
require 'rake/testtask'

task default: :recompile

spec = Gem::Specification.load('simd.gemspec')
Rake::ExtensionTask.new('simd', spec)

task :recompile do
  [:clean, :compile, :test, :prop].each { |task| Rake::Task[task].invoke }
end

Rake::TestTask.new(:test) do |t|
  t.libs.unshift File.expand_path('test', __dir__)
  t.libs.unshift File.expand_path('lib', __dir__)
  t.test_files = Dir.glob('test/**/*_test.rb')
end

Rake::TestTask.new(:prop) do |t|
  t.libs.unshift File.expand_path('test', __dir__)
  t.libs.unshift File.expand_path('lib', __dir__)
  t.test_files = Dir.glob('test/**/*_props.rb')
end

task :coverage do
  test_files = Dir.glob('test/**/*_test.rb')
  test_files.each do |file|
    Rake::TestTask.new("cov_#{file}") do |tt|
      tt.libs.unshift File.expand_path('test', __dir__)
      tt.libs.unshift File.expand_path('lib', __dir__)
      tt.ruby_opts << '-rprofhooks'
      tt.test_files = [file]
    end
    Rake::Task["cov_#{file}"].invoke
  end
end
