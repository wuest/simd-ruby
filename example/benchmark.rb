#!/usr/bin/env ruby

# frozen_string_literal: true

$LOAD_PATH.unshift(File.expand_path('../lib'))
require 'simd'
require 'benchmark'

include SIMD

def sisd_loop(op, modulo, sisd, x)
  if modulo
    len = sisd.length
    case op
    when :*
      ->(e, i) { x << (e * sisd[i % len]) }
    when :+
      ->(e, i) { x << (e + sisd[i % len]) }
    when :/
      ->(e, i) { x << (e / sisd[i % len]) }
    when :-
      ->(e, i) { x << (e - sisd[i % len]) }
    end
  else
    case op
    when :*
      ->(e, i) { x << (e * sisd[i]) }
    when :+
      ->(e, i) { x << (e + sisd[i]) }
    when :/
      ->(e, i) { x << (e / sisd[i]) }
    when :-
      ->(e, i) { x << (e - sisd[i]) }
    end
  end
end

iter = 500

a1 = (1..50_000).to_a * 25
a2 = (2..100_000).select(&:even?) * 25
a3 = [70_000, 80_000, 90_000, 100_000]
a4 = [90_000, 100_000]
s1 = FloatArray.new(a1)
s2 = FloatArray.new(a2)
s3 = FloatArray.new(a3)
s4 = FloatArray.new(a4)

modes = { 'Same size array' => [a2, [s1, s2]],
          '4-wide operand'  => [a3, [s1, s3]],
          '2-wide operand'  => [a4, [s1, s4]]
        }
ops = { 'Multiplication' => :*,
        'Addition'       => :+,
        'Division'       => :/,
        'Subtraction'    => :-
      }

modes.each do |mode, args|
  puts " *** #{mode} ***"
  sisd   = args.first
  s1, s2 = *args.last
  modulo = sisd.length != a1.length
  ops.each do |name, op|
    puts " *** #{name} ***"

    Benchmark.bm do |b|
      b.report('SIMD') { iter.times { s1.method(op).call(s2) } }
      b.report('Ruby') do
        iter.times do
          a1.each_with_index(&sisd_loop(op, modulo, sisd, []))
        end
      end
    end
  end
  puts
end

puts ' *** Square root calculation *** '
Benchmark.bm do |b|
  b.report('SIMD') { iter.times { s1.sqrt } }
  b.report('SISD') do
    iter.times do
      a1.map(&Math.method(:sqrt))
    end
  end
end
