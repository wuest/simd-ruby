require 'helper'

class TestLongArray < IntBaseTests
  def setup
    super
    @start_v    = SIMD::LongArray.new(@start)
    @mult_v     = SIMD::LongArray.new(@mult)
  end

  build_tests(SIMD::LongArray)

  def test_sqrt_returns_smallfloat_array
    roots    = SIMD::IntArray.new([4, 9, 16, 25]).sqrt.to_a
    expected = [2.0, 3.0, 4.0, 5.0]
    assert roots.zip(expected).all? { |a, b| a.eql?(b) }
  end
end
