#!/usr/bin/env ruby
$:.unshift(File.expand_path('../lib'))
require 'simd'
require 'benchmark'

include SIMD

iter = 500

a1 = (1..50_000).to_a * 25
a2 = (2..100_000).select(&:even?) * 25
a3 = [70_000, 80_000, 90_000, 100_000]
a4 = [90_000, 100_000]
s1 = FloatArray.new(a1)
s2 = FloatArray.new(a2)
s3 = FloatArray.new(a3)
s4 = FloatArray.new(a4)

puts "Same size array"
Benchmark.bm do |b|
  b.report('SIMD') { iter.times { s1 * s2 } }
  b.report('SISD') do
    iter.times do
      x = Array.new
      a1.each_with_index { |e,i| x << e * a2[i] }
    end
  end
end

puts
puts "4-wide operand"
Benchmark.bm do |b|
  b.report('SIMD') { iter.times { s1 * s3 } }
  b.report('SISD') do
    iter.times do
      x = Array.new
      a1.each_with_index { |e,i| x << e * a3[i % 4] }
    end
  end
end

puts
puts "2-wide operand"
Benchmark.bm do |b|
  b.report('SIMD') { iter.times { s1 * s4 } }
  b.report('SISD') do
    iter.times do
      x = Array.new
      a1.each_with_index { |e,i| x << e * a4[i % 2] }
    end
  end
end
