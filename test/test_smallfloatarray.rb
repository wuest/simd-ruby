require 'helper'

class TestSmallFloatArray < BaseTests
  def setup
    super
    @start_v    = SIMD::SmallFloatArray.new(@start)
    @mult_v     = SIMD::SmallFloatArray.new(@mult)
  end

  build_tests(SIMD::SmallFloatArray)

  def test_creation_and_extraction
    expected = (1..8).to_a
    vector = SIMD::FloatArray.new(expected)

    assert_equal(8, vector.length)
    assert_equal(expected, vector.to_a)
  end

  def test_cannot_create_arrays_shorter_than_four
    assert_raises(ArgumentError) { SIMD::SmallFloatArray.new([]) }
    assert_raises(ArgumentError) { SIMD::SmallFloatArray.new([1]) }
    assert_raises(ArgumentError) { SIMD::SmallFloatArray.new([1,2]) }
    assert_raises(ArgumentError) { SIMD::SmallFloatArray.new([1,2,3]) }
  end
end
