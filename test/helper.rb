require 'minitest'
require 'minitest/autorun'
require 'simd'

$LOAD_PATH.unshift File.dirname(__FILE__)

class BaseTests < Minitest::Test
  def self.build_tests(klass)
    define_method :test_multiplication do
      expected = @start.zip(@mult).each_with_object(:*).map(&:reduce)
      result   = @start_v * @mult_v

      assert_equal(expected, result.to_a)
    end

    define_method :test_addition do
      expected = @start.zip(@mult).each_with_object(:+).map(&:reduce)
      result   = @start_v + @mult_v

      assert_equal(expected, result.to_a)
    end

    define_method :test_subtraction do
      expected = @start.zip(@mult).each_with_object(:-).map(&:reduce)
      result   = @start_v - @mult_v

      assert_equal(expected, result.to_a)
    end

    define_method :test_comparisons do
      expected_gt   = @start.zip(@mult).map { |x,y| x > y ? -1 : 0 }
      expected_lt   = @start.zip(@mult).map { |x,y| x < y ? -1 : 0 }
      expected_zero = @start.map { |_| 0 }

      # Make sure equality works
      result_gt = @start_v.gt(@start_v)
      result_lt = @start_v.lt(@start_v)
      assert_equal(expected_zero, result_gt.to_a)
      assert_equal(expected_zero, result_lt.to_a)

      # Make sure that < and > work as well
      result_gt = @start_v > @start_v
      result_lt = @start_v < @start_v
      assert_equal(expected_zero, result_gt.to_a)
      assert_equal(expected_zero, result_lt.to_a)

      # Verify comparisons
      result_gt = @start_v > @mult_v
      result_lt = @start_v < @mult_v
      assert_equal(expected_gt, result_gt.to_a)
      assert_equal(expected_lt, result_lt.to_a)

      # Verify that inverse works as expected
      result_gt = @mult_v > @start_v
      result_lt = @mult_v < @start_v
      assert_equal(expected_lt, result_gt.to_a)
      assert_equal(expected_gt, result_lt.to_a)
    end

    define_method :test_cannot_operate_between_even_and_odd_length_vectors do
      veven = klass.new([1,2,3,4])
      vodd  = klass.new([1,2,3,4,5])
      assert_raises(ArgumentError) { veven * vodd }
    end

    define_method :test_creation_and_extraction do
      expected = (1..8).to_a
      vector = klass.new(expected)

      assert_equal(8, vector.length)
      assert_equal(expected, vector.to_a)
    end
  end
end

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

    define_method :test_and do
      zero_out = klass.new([0] * 8)
      expected = [0.0] * 8
      result   = @start_v & zero_out

      assert_equal(expected, result.to_a)
    end

    define_method :test_or do
      double_bit = klass.new([1 << 8] * 8)
      expected = @start.map { |n| n * 2 }
      result   = @start_v | double_bit

      assert_equal(expected, result.to_a)
    end

    define_method :test_xor do
      expected = [0] * 8
      result   = @start_v ^ @start_v

      assert_equal(expected, result.to_a)
    end

    build_tests(klass)
  end
end
