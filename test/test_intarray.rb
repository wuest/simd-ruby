require 'helper'

class TestIntArray < BaseTests
  def setup
    super
    @start_v    = SIMD::IntArray.new(@start)
    @mult_v     = SIMD::IntArray.new(@mult)
  end

  build_tests(SIMD::IntArray)

  def test_division
    expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:/).map(&:reduce)
    result   = @start_v / @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_and
    expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:&).map(&:reduce)
    result   = @start_v & @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_or
    expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:|).map(&:reduce)
    result   = @start_v | @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_xor
    expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:^).map(&:reduce)
    result   = @start_v ^ @mult_v

    assert_equal(expected, result.to_a)
  end

  def test_cannot_create_arrays_shorter_than_four
    assert_raises(ArgumentError) { SIMD::IntArray.new([]) }
    assert_raises(ArgumentError) { SIMD::IntArray.new([1]) }
    assert_raises(ArgumentError) { SIMD::IntArray.new([1,2]) }
    assert_raises(ArgumentError) { SIMD::IntArray.new([1,2,3]) }
  end
end
