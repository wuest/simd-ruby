require 'rake/extensiontask'
require 'rake/testtask'

task default: :recompile

spec = Gem::Specification.load('simd.gemspec')
Rake::ExtensionTask.new('simd', spec)

task :recompile do |t|
  [:clean, :compile, :test].each { |task| Rake::Task[task].invoke }
end

Rake::TestTask.new(:test) do |t|
	t.libs.unshift File.expand_path('../test', __FILE__)
  t.test_files = Dir.glob('test/**/*_test.rb')
	t.ruby_opts << '-I./lib'
end
