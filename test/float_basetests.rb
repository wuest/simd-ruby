require 'helper'

class FloatBaseTests < BaseTests
  def setup
    @start    = [250.0] * 8
    @mult     = [5.0, 10.0, 20.0, 25.0, 50.0, 100.0, 125.0, 250.0]
  end

  def self.build_float_tests(klass)
    define_method :test_unaligned_vectors_wont_div_by_zero do
      unaligned1 = [3,4,5,6,7]
      unaligned2 = [1,2,3,4,5]
      unaligned3 = [2.0] * 5
      expected   = [1] * 5

      vector1 = klass.new(unaligned1)
      vector2 = klass.new(unaligned2)
      vector3 = klass.new(unaligned3)

      intermediary = vector1 - vector2
      assert_equal(unaligned3, intermediary.to_a)

      result = intermediary / vector3
      assert_equal(expected, result.to_a)
    end

    build_tests(klass)
  end
end
