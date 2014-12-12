require 'helper'

class TestFloatArray < FloatBaseTests
  def setup
    super
    @start_v  = SIMD::FloatArray.new(@start)
    @mult_v   = SIMD::FloatArray.new(@mult)
  end

  build_float_tests(SIMD::FloatArray)

  def test_cannot_create_arrays_shorter_than_two
    assert_raises(ArgumentError) { SIMD::FloatArray.new([]) }
    assert_raises(ArgumentError) { SIMD::FloatArray.new([1]) }
  end
end
