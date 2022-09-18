require 'helper'

class TestIntArray < IntBaseTests
  def setup
    super
    @start_v    = SIMD::IntArray.new(@start)
    @mult_v     = SIMD::IntArray.new(@mult)
  end

  build_int_tests(SIMD::IntArray)

  def test_cannot_create_arrays_shorter_than_four
    assert_raises(ArgumentError) { SIMD::IntArray.new([1,2]) }
    assert_raises(ArgumentError) { SIMD::IntArray.new([1,2,3]) }
  end

  def test_sqrt_returns_smallfloat_array
    roots    = SIMD::IntArray.new([4, 9, 16, 25]).sqrt.to_a
    expected = [2.0, 3.0, 4.0, 5.0]
    assert roots.zip(expected).all? { |a, b| a.eql?(b) }
  end
end
