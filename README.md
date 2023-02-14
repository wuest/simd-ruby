[![Version](https://img.shields.io/gem/v/simd)][badges:0-gem]
[![Build](https://img.shields.io/github/actions/workflow/status/wuest/simd-ruby/ci.yaml?branch=main)][badges:1-CI]
[![License](https://img.shields.io/github/license/wuest/simd-ruby)][badges:2-license]

# SIMD in Ruby

SIMD is a library which exposes basic SIMD functionality for more efficient
computation in ruby programs.

## Support

Non-EOL MRI releases are tested against prior to release.  Older rubies have
been known to work, but have are not actively tested and may not work.

Testing is performed on AMD64 and ARM64 (see [Testing](#testing))

## Using SIMD
### Creating and Using SIMD Objects

SIMD objects can be created by passing Arrays of compatible objects to their
appropriate constructors (see below, Available Types):

```ruby
# Create a SIMD object for Float arithmetic
simd1 = SIMD::FloatArray.new([1.0, 2.0, 3.0, 4.0])
simd2 = SIMD::FloatArray.new([2.0, 4.0, 6.0, 8.0])
```

SIMD objects can be manipulated and used with each other in a manner similar to
Numeric objects once created, using the `#to_a` method to convert them back to
a ruby Array:

```ruby
# Extract the result of multiplication of both sets
simd3 = simd1 * simd2

# => [2.0, 8.0, 18.0, 32.0]
simd3.to_a
```

### Available Types

Currently the following types are available:

* `FloatArray`: Array of double precision floating point numbers
* `SmallFloatArray`: Array of single-precision floating point numbers
* `IntArray`: Array of short integers
* `LongArray`: Array of long integers

### Comparison

Comparison operators are supported, with the same behavior implemented at the
platform level.  On x86/amd64, the result of a comparison will be -1 if the
comparison succeeds, and 0 otherwise.

**Please note!**  Comparison applied with return the appropriately sized array
of integers: `IntArray` for `SmallFloatArray` comparisons, and `LongArray` for
`FloatArray` comparisons.

### Testing

Tests should cover as much of the codebase as is feasible.  In cases where a
given test case is infeasible to implement, that should be clearly documented.

Prior to release, tests are run on AMD64 and ARM64 platforms against all non-EOL
rubies.  ARM64 tests are performed via QEMU at present.

## Contributions

Whether the contribution concerns code, documentation, bug reports, or something
else entirely, contributions are welcome and appreciated!

If the contribution is relating to a security concern, please see
[SECURITY.md][contributions-0:SECURITY].

For all other contributions, please see
[CONTRIBUTING.md][contributions-1:CONTRIBUTING].  In short:

  * Fork the project.
  * Add tests for any new functionality/to verify that bugs have been fixed.
  * Send a merge request on GitHub.

### Code of Conduct

The SIMD-Ruby project is governed by a [Code of Conduct][code-of-conduct].

## License

Copyright © 2014-2022 Tina Wuest, released under the MIT license.
See [LICENSE][copyright-0:LICENSE] for details.

[badges:0-gem]: https://rubygems.org/gems/simd
[badges:1-CI]: https://github.com/wuest/simd-ruby/actions/workflows/ci.yaml
[badges:2-license]: https://github.com/wuest/simd-ruby/blob/main/LICENSE
[contributions-0:SECURITY]: https://github.com/wuest/simd-ruby/blob/main/SECURITY.md
[contributions-1:CONTRIBUTING]: https://github.com/wuest/simd-ruby/blob/main/CONTRIBUTING.md
[code-of-conduct]: https://github.com/wuest/simd-ruby/blob/main/CODE_OF_CONDUCT.md
[copyright-0:LICENSE]: https://github.com/wuest/simd-ruby/blob/main/CONTRIBUTING.md
