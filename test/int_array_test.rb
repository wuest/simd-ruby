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
end
