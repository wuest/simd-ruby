require 'helper'

class TestLongArray < IntBaseTests
  def setup
    super
    @start_v    = SIMD::LongArray.new(@start)
    @mult_v     = SIMD::LongArray.new(@mult)
  end

  build_tests(SIMD::LongArray)
end
