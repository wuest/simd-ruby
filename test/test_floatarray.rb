require 'helper'

class TestFloatArray < Test::Unit::TestCase
  def setup
    @start    = [10.0] * 8
    @mult     = (1..8).to_a
    @start_v  = SIMD::FloatArray.new(@start)
    @mult_v   = SIMD::FloatArray.new(@mult)
  end

  def test_multiplication
    expected = @start.zip(@mult).each_with_object(:*).map(&:reduce)
    result   = @start_v * @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_division
    expected = @start.zip(@mult).each_with_object(:/).map(&:reduce)
    result   = @start_v / @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_addition
    expected = @start.zip(@mult).each_with_object(:+).map(&:reduce)
    result   = @start_v + @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_subtraction
    expected = @start.zip(@mult).each_with_object(:-).map(&:reduce)
    result   = @start_v - @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_unaligned_vectors_wont_div_by_zero
    unaligned1 = [3,4,5,6,7]
    unaligned2 = [1,2,3,4,5]
    unaligned3 = [2.0] * 5
    expected   = [1.0] * 5

    vector1 = SIMD::FloatArray.new(unaligned1)
    vector2 = SIMD::FloatArray.new(unaligned2)
    vector3 = SIMD::FloatArray.new(unaligned3)

    intermediary = vector1 - vector2
    assert_equal(unaligned3, intermediary.to_a)

    result = intermediary / vector3
    assert_equal(expected, result.to_a)
  end

  def test_creation_and_extraction
    expected = (1..8).to_a
    vector = SIMD::FloatArray.new(expected)

    assert_equal(8, vector.length)
    assert_equal(expected, vector.to_a)
  end
end
