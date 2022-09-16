require 'helper'

class IntOperationsProps < IntBaseTests
  def test_addition
    property do
      xs = (arbitrary Array, Int16).zip(arbitrary Array, Int16)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 4
        a = SIMD::IntArray.new(xs.map(&:first))
        b = SIMD::IntArray.new(xs.map(&:last))
        (a + b).to_a == xs.map { |a, b| a + b }
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Int32).zip(arbitrary Array, Int32)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 2
        a = SIMD::LongArray.new(xs.map(&:first))
        b = SIMD::LongArray.new(xs.map(&:last))
        (a + b).to_a == xs.map { |a, b| a + b }
      else
        true
      end
    end
  end

  def test_subtraction
    property do
      xs = (arbitrary Array, Int16).zip(arbitrary Array, Int16)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 4
        a = SIMD::IntArray.new(xs.map(&:first))
        b = SIMD::IntArray.new(xs.map(&:last))
        (a - b).to_a == xs.map { |a, b| a - b }
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Int32).zip(arbitrary Array, Int32)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 2
        a = SIMD::LongArray.new(xs.map(&:first))
        b = SIMD::LongArray.new(xs.map(&:last))
        (a - b).to_a == xs.map { |a, b| a - b }
      else
        true
      end
    end
  end

  def test_multiply
    property do
      xs = (arbitrary Array, Int16).zip(arbitrary Array, Int8)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 4
        a = SIMD::IntArray.new(xs.map(&:first))
        b = SIMD::IntArray.new(xs.map(&:last))
        (a * b).to_a == xs.map { |a, b| a * b }
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Int32).zip(arbitrary Array, Int16)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 2
        a = SIMD::LongArray.new(xs.map(&:first))
        b = SIMD::LongArray.new(xs.map(&:last))
        (a * b).to_a == xs.map { |a, b| a * b }
      else
        true
      end
    end
  end

  def test_division
    property do
      xs = (arbitrary Array, Int16).zip(arbitrary Array, Int8)
                                   .reject { |a, b| a.nil? || b.nil? || b.zero? }

      if xs.length > 4
        a = SIMD::IntArray.new(xs.map(&:first))
        b = SIMD::IntArray.new(xs.map(&:last))
        (a / b).to_a == xs.map { |a, b| (a.to_f / b).to_i }
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Int32).zip(arbitrary Array, Int16)
                                   .reject { |a, b| a.nil? || b.nil? || b.zero? }

      if xs.length > 2
        a = SIMD::LongArray.new(xs.map(&:first))
        b = SIMD::LongArray.new(xs.map(&:last))
        (a / b).to_a == xs.map { |a, b| (a.to_f / b).to_i }
      else
        true
      end
    end
  end

  def test_bitwise
    property do
      xs = (arbitrary Array, Int32).zip(arbitrary Array, Int32)
                                    .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 4
        a = SIMD::IntArray.new(xs.map(&:first))
        b = SIMD::IntArray.new(xs.map(&:last))
        (a & b).to_a == xs.map { |a, b| (a & b).to_i } &&
          (a | b).to_a == xs.map { |a, b| (a | b).to_i } &&
          (a ^ b).to_a == xs.map { |a, b| (a ^ b).to_i }
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Int64).zip(arbitrary Array, Int64)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 2
        a = SIMD::LongArray.new(xs.map(&:first))
        b = SIMD::LongArray.new(xs.map(&:last))
        (a & b).to_a == xs.map { |a, b| (a & b).to_i } &&
          (a | b).to_a == xs.map { |a, b| (a | b).to_i } &&
          (a ^ b).to_a == xs.map { |a, b| (a ^ b).to_i }
      else
        true
      end
    end
  end

  def test_comparison
    property do
      xs = (arbitrary Array, Int32).zip(arbitrary Array, Int32)
                                    .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 4
        a = SIMD::IntArray.new(xs.map(&:first))
        b = SIMD::IntArray.new(xs.map(&:last))
        (a.gt(b)).to_a == xs.map { |a, b| a > b ? -1 : 0 } &&
          (a > b).to_a == xs.map { |a, b| a > b ? -1 : 0 } &&
          (a < b).to_a == xs.map { |a, b| a < b ? -1 : 0 } &&
          (a.lt(b)).to_a == xs.map { |a, b| a < b ? -1 : 0 }
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Int64).zip(arbitrary Array, Int64)
                                   .reject { |a, b| a.nil? || b.nil? }

      if xs.length > 2
        a = SIMD::LongArray.new(xs.map(&:first))
        b = SIMD::LongArray.new(xs.map(&:last))
        (a.gt(b)).to_a == xs.map { |a, b| a > b ? -1 : 0 } &&
          (a > b).to_a == xs.map { |a, b| a > b ? -1 : 0 } &&
          (a < b).to_a == xs.map { |a, b| a < b ? -1 : 0 } &&
          (a.lt(b)).to_a == xs.map { |a, b| a < b ? -1 : 0 }
      else
        true
      end
    end
  end
end
