require 'rake/extensiontask'
require 'rake/testtask'

task default: :conditional_recompile

spec = Gem::Specification.load('simd.gemspec')
Rake::ExtensionTask.new('simd', spec)

task :conditional_recompile do |t|
  Rake::Task[:test].invoke
  [:clean, :compile].each { |task| Rake::Task[task].invoke }
end

Rake::TestTask.new(:test) do |t|
	t.libs.unshift File.expand_path('../test', __FILE__)
  t.test_files = Dir.glob('test/**/test_*.rb')
	t.ruby_opts << '-I./lib'
end
