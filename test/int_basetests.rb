require 'helper'

class IntBaseTests < BaseTests
  def setup
    @start    = [250] * 8
    @mult     = [5, 10, 20, 25, 50, 100, 125, 250]
  end

  def self.build_int_tests(klass)
    define_method :test_unaligned_vectors_wont_div_by_zero do
      unaligned1 = [3,4,5,6,7]
      unaligned2 = [1,2,3,4,5]
      unaligned3 = [2] * 5
      expected   = [1] * 5

      vector1 = klass.new(unaligned1)
      vector2 = klass.new(unaligned2)
      vector3 = klass.new(unaligned3)

      intermediary = vector1 - vector2
      assert_equal(unaligned3, intermediary.to_a)

      result = intermediary / vector3
      assert_equal(expected, result.to_a)
    end

    define_method :test_division do
      expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:/).map(&:reduce)
      result   = @start_v / @mult_v

      assert_equal(expected, result.to_a)
    end

    define_method :test_and do
      expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:&).map(&:reduce)
      result   = @start_v & @mult_v

      assert_equal(expected, result.to_a)
    end

    define_method :test_or do
      expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:|).map(&:reduce)
      result   = @start_v | @mult_v

      assert_equal(expected, result.to_a)
    end

    define_method :test_xor do
      expected = @start.map(&:to_i).zip(@mult.map(&:to_i)).each_with_object(:^).map(&:reduce)
      result   = @start_v ^ @mult_v

      assert_equal(expected, result.to_a)
    end

    build_tests(klass)
  end
end
