require 'helper'

class TestSmallFloatArray < FloatBaseTests
  def setup
    super
    @start_v    = SIMD::SmallFloatArray.new(@start)
    @mult_v     = SIMD::SmallFloatArray.new(@mult)
  end

  build_float_tests(SIMD::SmallFloatArray)

  def test_cannot_create_arrays_shorter_than_four
    assert_raises(ArgumentError) { SIMD::SmallFloatArray.new([1,2]) }
    assert_raises(ArgumentError) { SIMD::SmallFloatArray.new([1,2,3]) }
  end
end
