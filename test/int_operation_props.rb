# frozen_string_literal: true

require 'helper'

class IntOperationsProps < IntBaseTests
  def test_addition
    property do
      xs = (arbitrary Array, Int16).zip((arbitrary Array, Int16))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 4 }

      a = SIMD::IntArray.new(xs.map(&:first))
      b = SIMD::IntArray.new(xs.map(&:last))

      (a + b).to_a == xs.map { |x, y| x + y }
    end

    property do
      xs = (arbitrary Array, Int32).zip((arbitrary Array, Int32))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 2 }

      a = SIMD::LongArray.new(xs.map(&:first))
      b = SIMD::LongArray.new(xs.map(&:last))

      (a + b).to_a == xs.map { |x, y| x + y }
    end
  end

  def test_subtraction
    property do
      xs = (arbitrary Array, Int16).zip((arbitrary Array, Int16))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 4 }

      a = SIMD::IntArray.new(xs.map(&:first))
      b = SIMD::IntArray.new(xs.map(&:last))

      (a - b).to_a == xs.map { |x, y| x - y }
    end

    property do
      xs = (arbitrary Array, Int32).zip((arbitrary Array, Int32))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 2 }

      a = SIMD::LongArray.new(xs.map(&:first))
      b = SIMD::LongArray.new(xs.map(&:last))

      (a - b).to_a == xs.map { |x, y| x - y }
    end
  end

  def test_multiply
    property do
      xs = (arbitrary Array, Int16).zip((arbitrary Array, Int8))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 4 }

      a = SIMD::IntArray.new(xs.map(&:first))
      b = SIMD::IntArray.new(xs.map(&:last))

      (a * b).to_a == xs.map { |x, y| x * y }
    end

    property do
      xs = (arbitrary Array, Int32).zip((arbitrary Array, Int16))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 2 }

      a = SIMD::LongArray.new(xs.map(&:first))
      b = SIMD::LongArray.new(xs.map(&:last))

      (a * b).to_a == xs.map { |x, y| x * y }
    end
  end

  def test_division
    property do
      xs = (arbitrary Array, Int16).zip((arbitrary Array, Int8))
                                   .reject { |a, b| a.nil? || b.nil? || b.zero? }

      where { xs.length >= 4 }

      a = SIMD::IntArray.new(xs.map(&:first))
      b = SIMD::IntArray.new(xs.map(&:last))

      (a / b).to_a == xs.map { |x, y| (x.to_f / y).to_i }
    end

    property do
      xs = (arbitrary Array, Int32).zip((arbitrary Array, Int16))
                                   .reject { |a, b| a.nil? || b.nil? || b.zero? }

      where { xs.length >= 2 }

      a = SIMD::LongArray.new(xs.map(&:first))
      b = SIMD::LongArray.new(xs.map(&:last))

      (a / b).to_a == xs.map { |x, y| (x.to_f / y).to_i }
    end
  end

  # Short integer sqrt not tested due to it being infeasible to easily convert
  # from Ruby's internal double after calculating the square root to a Float32
  # in order to achieving the same results as performing square root targeting
  # a Float32
  def test_sqare_root
    property do
      xs = (arbitrary Array, Int64).map(&:abs)

      where { xs.length >= 2 }

      a = SIMD::LongArray.new(xs)

      a.sqrt.to_a == xs.map { |x| Math.sqrt(x) }
    end
  end

  def test_bitwise
    property do
      xs = (arbitrary Array, Int32).zip((arbitrary Array, Int32))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 4 }

      a = SIMD::IntArray.new(xs.map(&:first))
      b = SIMD::IntArray.new(xs.map(&:last))

      (a & b).to_a == xs.map { |x, y| (x & y).to_i } &&
        (a | b).to_a == xs.map { |x, y| (x | y).to_i } &&
        (a ^ b).to_a == xs.map { |x, y| (x ^ y).to_i }
    end

    property do
      xs = (arbitrary Array, Int64).zip((arbitrary Array, Int64))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 2 }

      a = SIMD::LongArray.new(xs.map(&:first))
      b = SIMD::LongArray.new(xs.map(&:last))

      (a & b).to_a == xs.map { |x, y| (x & y).to_i } &&
        (a | b).to_a == xs.map { |x, y| (x | y).to_i } &&
        (a ^ b).to_a == xs.map { |x, y| (x ^ y).to_i }
    end
  end

  def test_comparison
    property do
      xs = (arbitrary Array, Int32).zip((arbitrary Array, Int32))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 4 }

      a = SIMD::IntArray.new(xs.map(&:first))
      b = SIMD::IntArray.new(xs.map(&:last))

      a.gt(b).to_a == xs.map { |x, y| x > y ? -1 : 0 } &&
        (a > b).to_a == xs.map { |x, y| x > y ? -1 : 0 } &&
        (a < b).to_a == xs.map { |x, y| x < y ? -1 : 0 } &&
        a.lt(b).to_a == xs.map { |x, y| x < y ? -1 : 0 } &&
        a.lte(b).to_a == xs.map { |x, y| x <= y ? -1 : 0 } &&
        a.gte(b).to_a == xs.map { |x, y| x >= y ? -1 : 0 }
    end

    property do
      xs = (arbitrary Array, Int64).zip((arbitrary Array, Int64))
                                   .reject { |a, b| a.nil? || b.nil? }

      where { xs.length >= 2 }

      a = SIMD::LongArray.new(xs.map(&:first))
      b = SIMD::LongArray.new(xs.map(&:last))

      a.gt(b).to_a == xs.map { |x, y| x > y ? -1 : 0 } &&
        (a > b).to_a == xs.map { |x, y| x > y ? -1 : 0 } &&
        (a < b).to_a == xs.map { |x, y| x < y ? -1 : 0 } &&
        a.lt(b).to_a == xs.map { |x, y| x < y ? -1 : 0 } &&
        a.lte(b).to_a == xs.map { |x, y| x <= y ? -1 : 0 } &&
        a.gte(b).to_a == xs.map { |x, y| x >= y ? -1 : 0 }
    end
  end
end
