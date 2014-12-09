#!/usr/bin/env ruby
$:.unshift(File.expand_path('../lib'))
require 'simd'
require 'benchmark'

include SIMD

iter = 500

a1 = (1..50_000).to_a * 25
a2 = (2..100_000).select(&:even?) * 25
s1 = FloatArray.new(a1)
s2 = FloatArray.new(a2)

Benchmark.bm do |b|
  b.report('SIMD') { iter.times { s1 * s2 } }
  b.report('SISD') do
    iter.times do
      a3 = Array.new
      a1.each_with_index { |e,i| a3 << e * a2[i] }
    end
  end
end
