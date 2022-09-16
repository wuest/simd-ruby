require 'helper'

class FloatOperationsProps < IntBaseTests
  def force_f32(f)
    [f].pack('f').unpack('f')
  end

  def test_addition
    property do
      xs = (arbitrary Array, Float32)
        .zip(arbitrary Array, Float32)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 4
        a = SIMD::SmallFloatArray.new(xs.map(&:first))
        b = SIMD::SmallFloatArray.new(xs.map(&:last))
        expected = xs.map { |a, b| [a + b].pack('f').unpack('f').first }.to_a
        (a + b).to_a == expected
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Float64)
        .zip(arbitrary Array, Float64)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 2
        a = SIMD::FloatArray.new(xs.map(&:first))
        b = SIMD::FloatArray.new(xs.map(&:last))
        (a + b).to_a == xs.map { |a, b| a + b }
      else
        true
      end
    end
  end

  def test_subtraction
    property do
      xs = (arbitrary Array, Float32)
        .zip(arbitrary Array, Float32)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 4
        a = SIMD::SmallFloatArray.new(xs.map(&:first))
        b = SIMD::SmallFloatArray.new(xs.map(&:last))
        expected = xs.map { |a, b| [a - b].pack('f').unpack('f').first }.to_a
        (a - b).to_a == expected
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Float64)
        .zip(arbitrary Array, Float64)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 2
        a = SIMD::FloatArray.new(xs.map(&:first))
        b = SIMD::FloatArray.new(xs.map(&:last))
        (a - b).to_a == xs.map { |a, b| a - b }
      else
        true
      end
    end
  end

  def test_multiply
    property do
      xs = (arbitrary Array, Float32)
        .zip(arbitrary Array, Float32)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 4
        a = SIMD::SmallFloatArray.new(xs.map(&:first))
        b = SIMD::SmallFloatArray.new(xs.map(&:last))
        expected = xs.map { |a, b| [a * b].pack('f').unpack('f').first }.to_a
        (a * b).to_a == expected
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Float64)
        .zip(arbitrary Array, Float64)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 2
        a = SIMD::FloatArray.new(xs.map(&:first))
        b = SIMD::FloatArray.new(xs.map(&:last))
        (a * b).to_a == xs.map { |a, b| a * b }
      else
        true
      end
    end
  end

  # Single precision not tested due to it being infeasible to easily convert
  # from Ruby's internal double after performing division and achieving the same
  # results as performing division in Float32 domain
  def test_division
    property do
      xs = (arbitrary Array, Float64)
        .zip(arbitrary Array, Float64)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite? || b.zero?
        end

      if xs.length > 2
        a = SIMD::FloatArray.new(xs.map(&:first))
        b = SIMD::FloatArray.new(xs.map(&:last))
        (a / b).to_a == xs.map { |a, b| a / b }
      else
        true
      end
    end
  end

  def test_comparison
    property do
      xs = (arbitrary Array, Float32)
        .zip(arbitrary Array, Float32)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 4
        a = SIMD::SmallFloatArray.new(xs.map(&:first))
        b = SIMD::SmallFloatArray.new(xs.map(&:last))
        (a.gt(b)).to_a == xs.map { |a, b| a > b ? -1 : 0 } &&
          (a > b).to_a == xs.map { |a, b| a > b ? -1 : 0 } &&
          (a < b).to_a == xs.map { |a, b| a < b ? -1 : 0 } &&
          (a.lt(b)).to_a == xs.map { |a, b| a < b ? -1 : 0 }
      else
        true
      end
    end

    property do
      xs = (arbitrary Array, Float64)
        .zip(arbitrary Array, Float64)
        .reject do |a, b|
          a.nil? || b.nil? || a.nan? || a.infinite? || b.nan? || b.infinite?
        end

      if xs.length > 2
        a = SIMD::FloatArray.new(xs.map(&:first))
        b = SIMD::FloatArray.new(xs.map(&:last))
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
