# dimval

[![CI](https://github.com/aurimasniekis/cpp-dimval/actions/workflows/ci.yml/badge.svg)](https://github.com/aurimasniekis/cpp-dimval/actions/workflows/ci.yml)
[![Docs](https://github.com/aurimasniekis/cpp-dimval/actions/workflows/docs.yml/badge.svg)](https://aurimasniekis.github.io/cpp-dimval/)

A header-only C++23 library for *dimensional values* — numbers paired with
units (`Meter`, `Hertz`, `Decibel`, …) and optional semantic measures
(`Distance`, `CenterFrequency`, `Snr`, …) at the type level. Conversions,
formatting, parsing, ranges, hashing, and optional JSON serialization come in
the box; mixing incompatible quantities is a compile error.

## Why use this library?

`dimval` is most useful when you have a lot of numeric quantities flowing
through a system and you want the compiler to catch accidents like adding
meters to kilograms or decoding a kilogram into a `MeterValue` from JSON.

- **Good for** scientific, RF/SDR, GNSS, mechanics, networking, and
  configuration-heavy code where numbers carry physical or semantic meaning.
- **Good for** formatting/parsing "42.5 m" round-trips, including JSON.
- **Avoids** silent unit coercion: `MeterValue + KilogramValue` does not
  compile.
- **Useful when** you need a polymorphic handle (`IUnitValue*`) for
  heterogeneous containers but still want compile-time arithmetic.
- **Not ideal for** full dimensional algebra (e.g. `kg·m/s²` automatically
  becoming `Newton`). Use [mp-units](https://github.com/mpusz/mp-units) for
  that. `dimval` keeps each unit a flat tag.
- **Not ideal for** hard real-time code that cannot tolerate a tiny vtable
  per polymorphic value or `std::format` allocations during rendering.

## Quick example

```cpp
#include <dimval/dimval.hpp>

#include <iostream>

int main() {
    namespace dv = dimval;

    dv::MeterValue   height = 1.78;          // implicit from numeric
    dv::CelsiusValue room   = 21.5;

    std::cout << height << "\n";                       // 1.78 m
    std::cout << dv::convert<dv::Foot>(height) << "\n";   // ~5.84 ft
    std::cout << dv::convert<dv::Kelvin>(room) << "\n";   // 294.65 K

    if (auto parsed = dv::MeterValue::parse("42.5 m")) {
        std::cout << *parsed << "\n";                  // 42.5 m
    } else {
        std::cout << "parse failed: " << parsed.error().message << "\n";
    }
}
```

What this shows:

- `MeterValue` is the alias for `UnitValue<Meter>`. The macro that defines a
  unit also publishes `<Tag>Value`, `<Tag>ValueShared`, `<Tag>ValueUnique`,
  and `<Tag>RangeValue`.
- The implicit constructor from `double` only triggers between the numeric
  type and a *specific* tagged type — `MeterValue x = 1.5` compiles, but
  `MeterValue x = some_kg_value` does not.
- `dv::convert<To>(value)` is a free function that handles linear and
  affine (`Celsius` ↔ `Kelvin`) conversions and is a `static_assert` error
  if the kinds disagree.
- Parsing returns `std::expected<UnitValue, ParseError>` — no exceptions.

## Installation

`dimval` is a header-only INTERFACE target with optional integrations. Pick
one of the supported integrations.

### CMake — FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(dimval
    URL      https://github.com/aurimasniekis/cpp-dimval/archive/refs/tags/v0.2.0.tar.gz
    URL_HASH SHA256=<sha256-of-v0.2.0-tarball>
)
FetchContent_MakeAvailable(dimval)

add_executable(example main.cpp)
target_link_libraries(example PRIVATE dimval::dimval)
```

The `Dependencies.cmake` file always fetches `cpp-commons` (0.1.3) — the
source of the `comms::Icon` / `comms::Color` types used by every descriptor —
and fetches `nlohmann/json` (3.12.0) and `cpp-parcel` (0.2.0) as needed, via
`FetchContent_Declare(... FIND_PACKAGE_ARGS ...)`, so an already-installed copy
is preferred over a new download.

### CMake — `find_package` after `cmake --install`

```cmake
find_package(dimval 0.2 REQUIRED)
target_link_libraries(my_app PRIVATE dimval::dimval)
```

Install rules are auto-disabled if any dependency was fetched (`commons`,
`nlohmann_json`, `parcel`); install those via system packages or `find_package`
to keep `DIMVAL_INSTALL=ON`. `commons` is always required, so it must be
installed for the install rules to stay enabled.

### Meson

```meson
dimval_dep = dependency('dimval', version: '>=0.2.0',
    fallback: ['dimval', 'dimval_dep'])
```

Meson options mirror the CMake ones: `-Djson=true|false`,
`-Dparcel=true|false`, `-Dtests=true|false`, `-Dexamples=true|false`.
A `pkg-config` file is generated on install.

### Header-only drop-in

Copy `include/dimval` into your include path. The core requires the C++23
standard library and `cpp-commons` (for `comms::Icon` / `comms::Color`); the
JSON and parcel headers are guarded by `__has_include` checks and stay inert if
the dependency is missing. Note that `dimval/version.hpp` is generated from
`version.hpp.in` by the build system — a pure copy-in must run the
`configure_file`/`configure_file()` step (or hand-write the four
`DIMVAL_VERSION_*` macros) before including `<dimval/dimval.hpp>`.

## Requirements

- **C++ standard**: C++23 — `<format>`, `<expected>`, ranges, and the
  CRTP-style metadata layout all rely on C++23 library features. CMake
  enforces this with `target_compile_features(dimval INTERFACE cxx_std_23)`.
- **CMake** ≥ 3.25 (or **Meson** ≥ 1.3.0).
- **Required dependency**:
  - [`cpp-commons`](https://github.com/aurimasniekis/cpp-commons) ≥ 0.1.3 —
    provides `comms::Icon` / `comms::Color`, used by every unit/measure
    descriptor. Fetched unconditionally.
- **Optional dependencies**:
  - [`nlohmann/json`](https://github.com/nlohmann/json) ≥ 3.12 — enables
    `<dimval/json_nlohmann.hpp>` (controlled by `DIMVAL_WITH_NLOHMANN_JSON`).
  - [`cpp-parcel`](https://github.com/aurimasniekis/cpp-parcel) ≥ 0.2.0 —
    enables `<dimval/parcel.hpp>` (controlled by `DIMVAL_WITH_PARCEL`;
    auto-disabled if JSON is OFF, since parcel depends on it).

## Core concepts

### Tag types

Every unit and measure is its own struct with `static constexpr` metadata,
declared via two macros. The struct derives from `UnitBase<Self>` /
`MeasureBase<Self, BaseUnit>`, which synthesises the runtime descriptor.

```cpp
DIMVAL_DEFINE_UNIT(Frame,                  // Tag (struct name)
                   "frame",                // id
                   "frm",                  // symbol
                   "frm",                  // short_name
                   "frame",                // long_name
                   "frame_count",          // kind (compatibility group)
                   1.0,                    // factor
                   ::comms::Icons::mdi::movie_roll,  // icon (comms::Icon catalog constant)
                   ::comms::Colors::mui::blue[400])  // color (comms::Color, MUI shade)
```

The `Icon` argument is a `comms::Icon`: use a catalog constant like
`comms::Icons::mdi::movie_roll` (from `<commons/icons.hpp>`) or, for a set with
no catalog (`ph:`, `tabler:`, …), the validated `comms::Icon::from("set:name")`.
The `Color` argument is a `comms::Color`, e.g. a Material UI shade
`comms::Colors::mui::blue[400]` or any `comms::Color` you construct.

The macro defines `dimval::Frame`, the aliases `dimval::FrameValue`,
`dimval::FrameValueShared`, `dimval::FrameValueUnique`,
`dimval::FrameRangeValue`, and registers a `UnitDescriptor` at static-init
time. The struct lives in `namespace dimval` regardless of where the macro
is invoked.

### `UnitValue<U, T = double>`

A `T` value tagged with a unit type at compile time. Operators are
restricted to same-tag arithmetic plus scalar `*` / `/`.

```cpp
dimval::MeterValue a = 1.5;            // implicit from numeric — preferred
dimval::MeterValue b{1.5};             // brace-init also works
auto                c = dimval::unit_value<dimval::Meter>(1.5);  // factory (rarely needed)
dimval::UnitValue<dimval::Meter> d{1.5};                          // explicit long form

// Heap-owned aliases generated by the macro:
dimval::MeterValueShared s = dimval::MeterValue::of(2.0);
dimval::MeterValueUnique u = dimval::MeterValue::unique(2.0);

a += b;          // 3.0 m
a *= 2.0;        // 6.0 m
auto ratio = a / b;        // double, 4.0  — same-unit division strips the tag
auto neg   = -a;           // -6.0 m
bool lt    = a < b;        // <=> ordering between same-unit values
```

The `<Tag>Value` aliases are the intended day-to-day form;
`unit_value<>` / `UnitValue<>` are listed for completeness but rarely
appear in user code.

`UnitValue<U, T>` derives from `IUnitValue` (a vtable adds 8 bytes per
instance). The full per-instance state is a single `T v;` member plus the
vtable pointer. Arithmetic is `constexpr`.

### `MeasureValue<M, T = double>`

A `MeasureValue` carries both a unit *and* a semantic refinement.
`Distance`, `Length`, `Width`, `Height`, `Depth` all use `Meter`, but each
is its own measure tag.

```cpp
dimval::DistanceValue d = 1500.0;                          // preferred alias form
auto raw = d.as_unit_value();                              // -> dimval::MeterValue
auto d2  = dimval::from_unit_value<dimval::Distance>(      // wrap a MeterValue back
    dimval::MeterValue{7.0});

// Cross-measure arithmetic is a compile error even if both wrap Meter.
// auto bad = d + dimval::LengthValue{1.0};                // ill-formed
```

### Ranges

`UnitRangeValue<U, T>` and `MeasureRangeValue<M, T>` are closed/open
intervals. Four named factories cover the common cases; `make` validates
the bounds and returns `std::expected<…, RangeError>`.

```cpp
using mr = dimval::MeterRangeValue;  // = UnitRangeValue<Meter>

auto closed     = mr::closed(0.0, 10.0);  // [0, 10] — bounds construct from numerics
auto open       = mr::open(0.0, 10.0);    // (0, 10)
auto left_open  = mr::left_open(0.0, 10.0);   // (0, 10]
auto right_open = mr::right_open(0.0, 10.0);  // [0, 10)

closed.contains(dimval::MeterValue{5.0});   // true
closed.contains(dimval::MeterValue{10.0});  // true (inclusive)
open.contains(dimval::MeterValue{10.0});    // false (exclusive)
closed.contains(open);                       // bool — range-in-range
closed.overlaps(other);                      // bool
auto inter = closed.intersect(other);        // std::optional<mr>

// Validating untrusted bounds:
auto r = mr::make(dimval::MeterValue{10.0}, dimval::MeterValue{0.0});
if (!r) {
    // r.error().code == RangeErrorCode::MaxLessThanMin
}
```

### Registries

`UnitRegistry::global()` and `MeasureRegistry::global()` are thread-safe
singletons. Built-in tags auto-register at static-init via the
`DIMVAL_DEFINE_*` macros. You can also register descriptors at runtime —
useful when units come from configuration files.

```cpp
auto& reg = dimval::UnitRegistry::global();
reg.register_unit({
    .id        = "furlong",
    .symbol    = "fur",
    .short_name= "fur",
    .long_name = "furlong",
    .kind      = "length",
    .factor    = 201.168,
});

if (auto* d = reg.find("fur")) {
    std::cout << d->long_name << "\n";    // "furlong"
}
for (const auto& d : reg.by_kind("length")) {
    std::cout << d.id << "\n";
}
bool ok = reg.compatible("m", "h");        // false — different kinds
```

Lookups acquire a shared lock; registrations acquire a unique lock. The
descriptor's `std::string_view` fields are non-owning — for runtime
registration, the caller must keep the underlying strings alive.

### Polymorphic handles

`IUnitValue` and `IMeasureValue` are pure-virtual interfaces with a small
fixed surface (`descriptor()`, `numeric_as_double()`, `to_string()`,
`to_formatted_string()`, `clone()`). They let you mix tags in one
container.

```cpp
std::vector<dimval::IUnitValueUnique> readings;
readings.push_back(dimval::MeterValue::unique(1.0));
readings.push_back(dimval::KilogramValue::unique(80.0));
readings.push_back(dimval::HertzValue::unique(2.4e9));

for (const auto& r : readings) {
    std::cout << r->descriptor().kind << ": " << r->to_string() << "\n";
}
```

## Common usage patterns

### Conversion across units of the same kind

```cpp
namespace dv = dimval;

dv::KilometerPerHourValue km_h = 36.0;
auto m_s = dv::convert<dv::MeterPerSecond>(km_h);   // -> MeterPerSecondValue, 10.0
auto kn  = dv::convert<dv::Knot>(m_s);              // -> KnotValue, ~19.4

// Affine: Celsius/Fahrenheit/Kelvin — handled correctly.
dv::CelsiusValue c0 = 0.0;
auto k0 = dv::convert<dv::Kelvin>(c0);              // -> KelvinValue{273.15}

// static_assert blocks unrelated kinds:
// auto bad = dv::convert<dv::Kilogram>(km_h);      // ill-formed
```

`convert<To>(From)` reduces `From` to a canonical value
(`canonical = factor * v + offset`) and unfolds it back into `To`. It is
`constexpr` and `noexcept`; an identity convert returns the value
unchanged.

### Formatting with `std::format` and streams

The format spec is `[style][.precision]` where `style` ∈
`{default, short, full, json}`.

| Spec        | `MeterValue{42.5}` output     |
|-------------|-------------------------------|
| `{}`        | `42.5 m`                      |
| `{:short}`  | `42.5m`                       |
| `{:full}`   | `42.5 meter`                  |
| `{:json}`   | `{"unit":"m","value":42.5}`   |
| `{:.2}`     | `42.50 m`                     |
| `{:full.3}` | `42.500 meter`                |

Notes:

- `MeasureValue` adds the measure name in `:full` (`"42.5 Distance (meter)"`)
  and `:json` (`{"measure":"distance","unit":"m","value":42.5}`).
- Ranges render with `[...]` / `(...)` brackets matching their inclusion,
  e.g. `(0 m, 10 m]` for `left_open`. The `:json` style emits a `min`,
  `max`, `min_inclusive`, `max_inclusive` payload.
- `operator<<` for every value type and descriptor is in
  `<dimval/ostream.hpp>` (already pulled in by the umbrella) and forwards
  to `std::format("{}", v)`.
- A bogus spec (e.g. `"{:full.x}"`) throws `std::format_error`.

### Parsing strings

```cpp
namespace dv = dimval;

// Compile-time-typed — the `Value::parse` member is the preferred form:
auto a = dv::MeterValue::parse("42.5 m");                  // std::expected<MeterValue, ParseError>
auto b = dv::DistanceValue::parse("100 m");                // measure
auto c = dv::UnitValue<dv::Meter, int>::parse("42 m");     // non-default numeric type
auto d = dv::parse_unit_value<dv::Meter>("42.5 m");        // free-function equivalent

// Runtime-typed (descriptor lookup via the registry):
auto e = dv::parse_dynamic_unit_value("125 dBm");
// e->desc->kind  == "log_power"
// e->value       == 125
```

The grammar is `<number><whitespace?><tail>`, where the number accepts
sign, decimal point, and `e`/`E` exponents. Leading/trailing whitespace is
trimmed. The tail must equal one of the unit's `id`, `symbol`, or
`short_name` (or be empty for a purely dimensionless value).

Failure cases (each maps to a `ParseErrorCode`):

```cpp
dv::MeterValue::parse("   ");                  // Empty
dv::MeterValue::parse("abc m");                // InvalidNumber
dv::MeterValue::parse("1.5 kg");               // UnitMismatch
dv::MeterValue::parse("42 m foo");             // UnitMismatch (trailing garbage tail)
dv::parse_dynamic_unit_value("3.14 zorgs");    // UnknownUnit
dv::parse_dynamic_unit_value("3.14");          // dimensionless, success
dv::UnitValue<dv::Meter, int>::parse("42.5 m");  // InvalidNumber (int rejects '.')
```

### Hashing, ordering, and containers

```cpp
std::unordered_set<dimval::MeterValue> seen;
std::unordered_map<dimval::DistanceValue, std::string> labels;
std::map<dimval::MeterValue, int> sorted;            // ordered by <=>
std::vector<dimval::MeterValue> v{3.0, 1.0, 2.0};
std::ranges::sort(v);
```

`std::hash` specializations are defined in `<dimval/hash.hpp>` (in the
umbrella). The hash mixes the tag's `id` with `std::hash<T>{}(value)`, so
two `MeterValue{1.5}` produce the same hash, and a `MeterValue{1.5}` does
*not* collide with a `KilogramValue{1.5}` of equal numeric value.

### Math helpers (opt-in)

`<dimval/math.hpp>` is **not** in the umbrella; pull it in explicitly. It
adds tag-preserving `abs`, `min`, `max`, `clamp`, and `midpoint(range)`.

```cpp
#include <dimval/math.hpp>

auto a = dimval::abs(dimval::MeterValue{-3.0});                       // 3 m
auto m = dimval::midpoint(dimval::MeterRangeValue::closed(2.0, 8.0)); // 5 m
```

Without these helpers the natural reach is `value.v`, which strips the
tag — that's the escape hatch you usually want to avoid.

### nlohmann/json integration

```cpp
#include <dimval/dimval.hpp>

#include <nlohmann/json.hpp>

dimval::DistanceValue distance = 7.0;
nlohmann::json j = distance;
// j == {"m":"distance","u":"m","v":7.0}

auto v = j.get<dimval::DistanceValue>();
```

Wire format (compact field names — different from the `{:json}` format
spec output, which uses the long names `"unit"` / `"value"`):

```text
UnitValue           {"u":"m","v":42.5}
MeasureValue        {"m":"distance","u":"m","v":42.5}
UnitRangeValue      {"u":"m","min":0,"max":10,"mi":true,"xi":true}
MeasureRangeValue   {"m":"distance","u":"m","min":0,"max":10,"mi":true,"xi":true}
```

Field legend: `u` = unit id, `m` = measure id, `v` = numeric value,
`mi` = min_inclusive, `xi` = max_inclusive (default `true`/`true`).

`from_json` validates the `u` / `m` fields against the destination tag's
descriptor; a mismatch raises `nlohmann::json::other_error`. Range
validation errors (e.g. inverted bounds) are also reported via
`nlohmann::json::other_error`.

### cpp-parcel integration

`<dimval/parcel.hpp>` wraps each value type in a parcel `Cell` so it can
ship through a parcel registry. Wire format:

```text
UnitValueCell           {"k":"uv",  "v":{"u":"m","v":42.5}}
MeasureValueCell        {"k":"mv",  "v":{"m":"distance","u":"m","v":42.5}}
UnitRangeValueCell      {"k":"urv", "v":{...}}
MeasureRangeValueCell   {"k":"mrv", "v":{...}}
```

```cpp
dimval::UnitValueCell<dimval::Meter> cell = dimval::MeterValue{42.5};
parcel::json_t j = cell.to_json();      // {"k":"uv","v":{"u":"m","v":42.5}}

parcel::ParcelRegistry reg;
auto decoded = dimval::UnitValueCell<dimval::Meter>::from_json(j, reg);
```

Caveat (documented in the header): all `UnitValueCell<U,T>` instantiations
share `kind_id = "uv"`, so a single `parcel::ParcelRegistry` cannot route
between multiple unit-tag variants — the last registered wins. Decoding at
sites that already know the C++ type works because the inner JSON adapter
validates the `u`/`m` field anyway.

## Error handling

| Mechanism                           | Used by                                                                                                                    |
|-------------------------------------|----------------------------------------------------------------------------------------------------------------------------|
| `std::expected<T, ParseError>`      | `parse_unit_value`, `parse_measure_value`, `parse_dynamic_unit_value`, `UnitValue::parse`, `MeasureValue::parse`           |
| `std::expected<T, RangeError>`      | `UnitRangeValue::make`, `MeasureRangeValue::make`                                                                          |
| `std::optional<T>`                  | `UnitRangeValue::intersect`, `MeasureRangeValue::intersect`                                                                |
| `static_assert`                     | `convert<To>(From)` when `From` and `To` have different `kind`                                                             |
| Compile error (overload resolution) | Same-tag `+`/`-` and `MeasureValue<A> + MeasureValue<B>` mixing                                                            |
| Exceptions                          | `std::format_error` (bad spec); `nlohmann::json::other_error` (JSON tag mismatch / invalid range); parcel adapter rethrows |

`ParseError` carries `code`, a copy of the input, the byte offset where
parsing failed, and a human-readable message. `RangeError` carries the
code (`MaxLessThanMin`, `EmptyOpenRange`) and a message.

```cpp
if (auto v = dimval::MeterValue::parse("3.14 km"); !v) {
    // v.error().code    == ParseErrorCode::UnitMismatch
    // v.error().input   == "3.14 km"
    // v.error().pos     == 4   (byte offset where the unit starts)
    // v.error().message == "expected 'm', got 'km'"
}
```

## Edge cases and pitfalls

- **Affine conversion direction**. `Celsius` and `Fahrenheit` carry an
  `offset`; canonical storage is `Kelvin`. Round-trips like
  `Celsius(0) → Kelvin(273.15) → Celsius(0)` work. Never reach for
  `value.v` to "do your own" temperature conversion — you'll skip the
  offset.
- **`{:json}` format spec ≠ nlohmann adapter shape**. Format-string output
  uses long field names (`"unit"`, `"value"`); the `nlohmann::json`
  adapter uses short names (`"u"`, `"v"`). Pick one and stick with it on
  the wire.
- **Integer value type is strict**. `UnitValue<Meter, int>::parse("42.5 m")`
  fails with `InvalidNumber` — `from_chars` stops at the `.` and reports
  trailing bytes; the parser does not silently truncate. `parse("42 m")`
  succeeds.
- **Trailing tokens are an error**, not a warning.
  `MeterValue::parse("42 m foo")` returns `UnitMismatch` because the whole
  tail (`m foo`) does not match `id`/`symbol`/`short_name`.
- **Empty input vs empty tail**. `"   "` is `Empty`. `"3.14"` is valid for
  `parse_dynamic_unit_value` (resolves to `dimensionless` via the
  registry); the same input through `MeterValue::parse` is a
  `UnitMismatch` because `Meter` requires a non-empty symbol.
- **Range single-point with exclusive bound**. `make(5.0, 5.0,
  open()/left_open()/right_open())` returns `EmptyOpenRange`.
  `make(5.0, 5.0)` (closed default) is allowed and contains exactly `5.0`.
- **Range factories `closed`/`open`/etc. are unchecked**. They construct
  even with inverted bounds. Use `make(...)` when bounds come from
  untrusted sources.
- **Same-unit division returns a scalar**, *not* a `UnitValue<...,double>`.
  `MeterValue{10} / MeterValue{2}` is `double{5.0}`. Multiplication by a
  scalar keeps the tag.
- **No compound dimensional algebra**. `Meter / Second` does not become
  `meters per second`. The catalog includes `MeterPerSecond` as its own
  unit (kind `"velocity"`); model new compound units the same way.
- **Polymorphic copies need `clone()`**. `IUnitValue` is non-copyable
  through the interface. Use `v->clone()` (returns a fresh
  `unique_ptr<IUnitValue>`).
- **`std::string_view` fields in descriptors don't own**. Built-in
  descriptors point to string literals (safe forever). For runtime
  `register_unit({...})`, keep the strings alive at least as long as the
  descriptor is reachable.
- **`<dimval/math.hpp>` is opt-in**. The umbrella does not include it.
  Without that header, `dimval::abs(value)` is unresolved.
- **Format precision applies to numbers, not symbols**. `{:.2}` formats
  `value` with two decimals; the symbol/long_name is unchanged.
- **Stable lifetime of the registry**. The global registries are Meyers
  singletons — fine for static-init use because every macro call only
  touches its own descriptor, but do not store references that outlive
  `main()`.
- **Parcel kind ids collide across tag instantiations**. See the parcel
  section above; this is a documented limitation rather than a bug.

## API overview

| API                                                                               | Purpose                                                       | Notes                                                                                                                      |
|-----------------------------------------------------------------------------------|---------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------|
| `UnitValue<U, T>`                                                                 | Tagged numeric value                                          | Implicit ctor from `T`; `+`,`-`,scalar `*`/`/`,same-tag `/` returns `T`                                                    |
| `MeasureValue<M, T>`                                                              | Unit value + measure tag                                      | `as_unit_value()`, `from_unit_value<M>()` bridge to/from `UnitValue`                                                       |
| `UnitRangeValue<U, T>` / `MeasureRangeValue<M, T>`                                | Closed/open intervals                                         | Factories `closed/open/left_open/right_open` (unchecked); `make` returns `expected`                                        |
| `unit_value<U>(T)` / `measure_value<M>(T)`                                        | Free factories                                                | `noexcept`, `constexpr`                                                                                                    |
| `convert<To>(value)`                                                              | Same-kind unit conversion                                     | `static_assert` blocks unrelated kinds; affine-aware                                                                       |
| `parse_unit_value<U,T>` / `parse_measure_value<M,T>` / `parse_dynamic_unit_value` | String parsing                                                | `std::expected`; integer `T` rejects fractional input                                                                      |
| `IUnitValue` / `IMeasureValue`                                                    | Polymorphic handle                                            | `descriptor()`, `numeric_as_double()`, `to_string()`, `clone()`                                                            |
| `UnitDescriptor` / `MeasureDescriptor`                                            | Runtime metadata                                              | Aggregate; `string_view` fields non-owning                                                                                 |
| `UnitRegistry::global()` / `MeasureRegistry::global()`                            | Thread-safe descriptor lookup                                 | `find`, `by_kind`, `list`, `compatible`, `register_unit`, `register_unit<Tag>()`                                           |
| `DIMVAL_DEFINE_UNIT(Tag, ...)`                                                    | Define and auto-register a unit tag                           | Generates aliases `<Tag>Value`, `<Tag>ValueShared/Unique`, `<Tag>RangeValue`                                               |
| `DIMVAL_DEFINE_MEASURE(Tag, BaseUnit, ...)`                                       | Define and auto-register a measure tag                        | Same alias pattern; `BaseUnit::id` becomes `base_unit_id`                                                                  |
| `<dimval/math.hpp>`                                                               | `abs`, `min`, `max`, `clamp`, `midpoint` (tag-preserving)     | Not in umbrella; include explicitly                                                                                        |
| `<dimval/ostream.hpp>`                                                            | `operator<<` for every value type and descriptor              | In umbrella; delegates to `std::format`                                                                                    |
| `<dimval/json_nlohmann.hpp>`                                                      | nlohmann/json `to_json` / `from_json`                         | Auto-enabled if `nlohmann/json.hpp` is on the include path                                                                 |
| `<dimval/parcel.hpp>`                                                             | cpp-parcel `Cell` wrappers                                    | Auto-enabled if `parcel/parcel.h` is on the include path; depends on JSON                                                  |
| `dimval::version` / `version_major/minor/patch`                                   | Library version (string_view + ints) in `<dimval/dimval.hpp>` | Backed by `DIMVAL_VERSION_*` macros in the generated `<dimval/version.hpp>`                                                |

### Built-in catalog

The built-ins ship **103 units across 57 kinds** and **115 measures**.
Rather than freezing a list here that drifts out of date with every new
release, run `examples/list_catalog.cpp` to print the current registry
contents:

```bash
make examples            # builds and runs every example
./build/examples/dimval_list_catalog
```

Or, in your own code:

```cpp
#include <dimval/dimval.hpp>

#include <iostream>

int main() {
    for (const auto& u : dimval::UnitRegistry::global().list()) {
        std::cout << u.kind << '\t' << u.id << '\t' << u.symbol << '\n';
    }
    for (const auto& m : dimval::MeasureRegistry::global().list()) {
        std::cout << m.id << '\t' << m.base_unit_id << '\t' << m.name << '\n';
    }
}
```

A snapshot of what the registry currently contains, listed by C++ tag
(use `<Tag>Value`, `<Tag>RangeValue`, `convert<Tag>(...)`, etc.):

**Units, grouped by `kind`**

| `kind`                        | Tags                                                                                              |
|-------------------------------|---------------------------------------------------------------------------------------------------|
| `length`                      | `Meter`, `Foot`, `Inch`, `Mile`, `NauticalMile`, `Wavelength`                                     |
| `mass`                        | `Kilogram`, `Pound`, `Tonne`                                                                      |
| `time`                        | `Second`, `Minute`, `Hour`, `Day`                                                                 |
| `temperature`                 | `Kelvin`, `Celsius`, `Fahrenheit`                                                                 |
| `current`                     | `Ampere`, `CoulombPerSecond`                                                                      |
| `amount_of_substance`         | `Mole`                                                                                            |
| `luminous_intensity`          | `Candela`                                                                                         |
| `frequency`                   | `Hertz`                                                                                           |
| `angle`                       | `Radian`, `Degree`, `Arcminute`, `Arcsecond`, `PhaseDegree`, `PhaseRadian`                        |
| `solid_angle`                 | `Steradian`                                                                                       |
| `force`                       | `Newton`                                                                                          |
| `pressure`                    | `Pascal`, `Bar`, `Atmosphere`, `PoundsPerSquareInch`                                              |
| `energy`                      | `Joule`, `WattHour`, `KilowattHour`                                                               |
| `power`                       | `Watt`                                                                                            |
| `apparent_power`              | `VoltAmpere`                                                                                      |
| `reactive_power`              | `Var`                                                                                             |
| `voltage`                     | `Volt`, `JoulePerCoulomb`                                                                         |
| `charge`                      | `Coulomb`, `AmpereHour`                                                                           |
| `resistance`                  | `Ohm`, `VoltPerAmpere`                                                                            |
| `conductance`                 | `Siemens`, `AmperePerVolt`                                                                        |
| `capacitance`                 | `Farad`, `CoulombPerVolt`                                                                         |
| `inductance`                  | `Henry`, `WeberPerAmpere`                                                                         |
| `magnetic_flux`               | `Weber`, `VoltSecond`                                                                             |
| `magnetic_flux_density`       | `Tesla`, `Gauss`                                                                                  |
| `electric_field_strength`     | `VoltPerMeter`                                                                                    |
| `magnetic_field_strength`     | `AmperePerMeter`                                                                                  |
| `permittivity`                | `FaradPerMeter`                                                                                   |
| `permeability`                | `HenryPerMeter`                                                                                   |
| `resistivity`                 | `OhmMeter`                                                                                        |
| `conductivity`                | `SiemensPerMeter`                                                                                 |
| `sheet_resistance`            | `OhmSquare`                                                                                       |
| `ionizing_radiation_exposure` | `CoulombPerKilogram`                                                                              |
| `luminous_flux`               | `Lumen`                                                                                           |
| `illuminance`                 | `Lux`                                                                                             |
| `radioactivity`               | `Becquerel`                                                                                       |
| `absorbed_dose`               | `Gray`                                                                                            |
| `dose_equivalent`             | `Sievert`                                                                                         |
| `catalytic_activity`          | `Katal`                                                                                           |
| `volume`                      | `Litre`, `CubicMeter`, `Gallon`                                                                   |
| `area`                        | `SquareMeter`, `Hectare`                                                                          |
| `density`                     | `KilogramPerCubicMeter`, `GramPerCubicCentimeter`                                                 |
| `velocity`                    | `MeterPerSecond`, `KilometerPerHour`, `Knot`                                                      |
| `acceleration`                | `MeterPerSecondSquared`, `StandardGravity`                                                        |
| `rotational_frequency`        | `RotationPerMinute`                                                                               |
| `clock_drift`                 | `SecondsPerDay`                                                                                   |
| `data_size`                   | `Bit`, `Byte`                                                                                     |
| `data_rate`                   | `BitPerSecond`, `BytePerSecond`                                                                   |
| `count`                       | `Count`                                                                                           |
| `dimensionless`               | `Dimensionless`                                                                                   |
| `ratio`                       | `Ratio`, `Percent`, `PartsPerMillion`, `PartsPerBillion`                                          |
| `log_ratio`                   | `Decibel`, `Neper`                                                                                |
| `log_power`                   | `DecibelMilliwatt`, `DecibelWatt`                                                                 |
| `log_voltage`                 | `DecibelMicrovolt`, `DecibelMillivolt`                                                            |
| `noise_density_db`            | `DecibelPerHertz`                                                                                 |
| `voltage_noise_density`       | `VoltPerRootHertz`                                                                                |
| `current_noise_density`       | `AmperePerRootHertz`                                                                              |
| `power_spectral_density`      | `WattPerHertz`                                                                                    |

**Measures, grouped by base unit tag**

| Base unit Tag           | Measure tags                                                                                                                                                 |
|-------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `Meter`                 | `Length`, `Width`, `Height`, `Depth`, `Distance`, `Altitude`, `GeoidSeparation`, `PositionAccuracy`, `HorizontalAccuracy`, `VerticalAccuracy`, `Pseudorange` |
| `Kilogram`              | `Mass`, `Weight`                                                                                                                                             |
| `Second`                | `Duration`, `ElapsedTime`, `Time`, `Latency`, `Jitter`, `OffsetTime`, `TimeAccuracy`, `PropagationDelay`                                                     |
| `Byte`                  | `Size`, `Capacity`                                                                                                                                           |
| `BytePerSecond`         | `Throughput`, `ByteRate`                                                                                                                                     |
| `BitPerSecond`          | `BitRate`                                                                                                                                                    |
| `Hertz`                 | `Frequency`, `CenterFrequency`, `SampleRate`, `SymbolRate`, `Bandwidth`, `IntermediateFrequency`, `FrameRate`, `FrequencyErrorHz`                            |
| `Celsius`               | `Temperature`                                                                                                                                                |
| `Kelvin`                | `TemperatureKelvin`                                                                                                                                          |
| `Ratio`                 | `Percentage`, `RatioMeasure`                                                                                                                                 |
| `Count`                 | `CountMeasure`                                                                                                                                               |
| `Radian`                | `Angle`                                                                                                                                                      |
| `Degree`                | `Latitude`, `Longitude`, `Heading`, `Azimuth`, `Elevation`, `CourseOverGround`, `PolarizationAngle`                                                          |
| `MeterPerSecond`        | `Speed`, `GroundSpeed`, `VerticalSpeed`                                                                                                                      |
| `MeterPerSecondSquared` | `Acceleration`                                                                                                                                               |
| `SquareMeter`           | `Area`                                                                                                                                                       |
| `KilogramPerCubicMeter` | `Density`                                                                                                                                                    |
| `Litre`                 | `Volume`                                                                                                                                                     |
| `Pascal`                | `Pressure`                                                                                                                                                   |
| `Newton`                | `Force`                                                                                                                                                      |
| `Volt`                  | `Voltage`                                                                                                                                                    |
| `Ampere`                | `Current`                                                                                                                                                    |
| `Ohm`                   | `Resistance`                                                                                                                                                 |
| `Siemens`               | `Conductance`                                                                                                                                                |
| `Farad`                 | `Capacitance`                                                                                                                                                |
| `Henry`                 | `Inductance`                                                                                                                                                 |
| `Watt`                  | `Power`, `RfPower`                                                                                                                                           |
| `Joule`                 | `Energy`                                                                                                                                                     |
| `Coulomb`               | `Charge`                                                                                                                                                     |
| `VoltPerMeter`          | `ElectricFieldStrength`                                                                                                                                      |
| `AmperePerMeter`        | `MagneticFieldStrength`                                                                                                                                      |
| `Weber`                 | `MagneticFlux`                                                                                                                                               |
| `Tesla`                 | `MagneticFluxDensity`                                                                                                                                        |
| `OhmMeter`              | `Resistivity`                                                                                                                                                |
| `SiemensPerMeter`       | `Conductivity`                                                                                                                                               |
| `FaradPerMeter`         | `Permittivity`                                                                                                                                               |
| `HenryPerMeter`         | `Permeability`                                                                                                                                               |
| `OhmSquare`             | `SheetResistance`                                                                                                                                            |
| `RotationPerMinute`     | `RotationRate`                                                                                                                                               |
| `SecondsPerDay`         | `ClockDrift`                                                                                                                                                 |
| `Decibel`               | `Gain`, `Loss`, `PathLoss`, `ReturnLoss`, `AntennaGain`, `Snr`, `Cnr`, `CarrierToNoiseDensity`, `EbNo`, `Mer`, `EvmDb`, `IqImbalanceGain`                    |
| `DecibelMilliwatt`      | `RfPowerDbm`                                                                                                                                                 |
| `DecibelWatt`           | `RfPowerDbw`                                                                                                                                                 |
| `DecibelMicrovolt`      | `SignalLevelDbuv`                                                                                                                                            |
| `DecibelMillivolt`      | `SignalLevelDbmv`                                                                                                                                            |
| `Percent`               | `EvmPercent`, `Vswr`, `Ber`, `Fer`, `Per`, `PacketErrorRate`, `DilutionOfPrecision`, `Hdop`, `Vdop`, `Pdop`, `Tdop`                                          |
| `PartsPerMillion`       | `FrequencyErrorPpm`                                                                                                                                          |
| `PartsPerBillion`       | `FrequencyStabilityPpb`                                                                                                                                      |
| `PhaseDegree`           | `Phase`, `IqImbalancePhase`                                                                                                                                  |
| `PhaseRadian`           | `PhaseRadians`, `CarrierPhase`                                                                                                                               |
| `VoltPerRootHertz`      | `NoiseDensityVoltage`                                                                                                                                        |
| `AmperePerRootHertz`    | `NoiseDensityCurrent`                                                                                                                                        |
| `DecibelPerHertz`       | `NoiseDensityDb`                                                                                                                                             |
| `WattPerHertz`          | `PowerSpectralDensity`                                                                                                                                       |
| `Wavelength`            | `WavelengthMeasure`                                                                                                                                          |

If you need binary-prefix data sizes (`KiB`, `MiB`, …) or any unit not
in the list, define your own with `DIMVAL_DEFINE_UNIT` — that's the
supported extension path.

## Examples

The `examples/` directory contains short, standalone programs. They are
all built by `make examples` (or `cmake --build build`).

| Example                           | Demonstrates                                                            |
|-----------------------------------|-------------------------------------------------------------------------|
| `examples/basic_unit.cpp`         | Stack/heap construction, `convert<>`, alt-unit and affine conversions   |
| `examples/basic_measure.cpp`      | `MeasureValue`, `as_unit_value`, polymorphic `IMeasureValue` container  |
| `examples/range.cpp`              | Range factories, `contains`, `overlaps`, `intersect`, error from `make` |
| `examples/formatting.cpp`         | Every `std::format` style/precision combination                         |
| `examples/sorting_hashing.cpp`    | `std::hash` + `<=>` in `unordered_set` and sorted `vector`              |
| `examples/error_handling.cpp`     | The four parse failure shapes plus range validation                     |
| `examples/validation.cpp`         | Member-form `Value::parse`, dynamic registry parse, range guard         |
| `examples/mechanics.cpp`          | Mechanics measures and imperial/metric round-trips                      |
| `examples/custom_unit.cpp`        | `DIMVAL_DEFINE_UNIT` + runtime `register_unit`                          |
| `examples/custom_measure.cpp`     | `DIMVAL_DEFINE_MEASURE` reusing a built-in unit (`Byte`)                |
| `examples/registry_inquiry.cpp`   | Walking the registry, `find`, `by_kind`, `compatible`                   |
| `examples/list_catalog.cpp`       | Dumps every built-in unit (grouped by kind) and every measure           |
| `examples/ostream.cpp`            | `operator<<` on values, ranges, and descriptors                         |
| `examples/json_integration.cpp`   | `to_json`/`from_json` for unit, measure, and range values               |
| `examples/parcel_integration.cpp` | `*ValueCell` wire format and round-trip                                 |

## Building from source

CMake (the canonical path):

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

Meson:

```bash
meson setup build-meson -Dtests=true -Dexamples=true
meson compile -C build-meson
meson test -C build-meson
```

The `Makefile` is a thin wrapper around the CMake invocations the project
uses in CI:

| Target                              | What it does                                                                      |
|-------------------------------------|-----------------------------------------------------------------------------------|
| `make build`                        | Configure + build (`build/`, Debug)                                               |
| `make test`                         | `ctest` in `build/`                                                               |
| `make examples`                     | Build and run every `dimval_*` example, fail on any non-zero exit                 |
| `make sanitize`                     | Configure + build + test in `build-san/` with ASan + UBSan                        |
| `make tidy`                         | Configure + build in `build-tidy/` with `clang-tidy`                              |
| `make release`                      | Release build + tests in `build-release/`                                         |
| `make coverage`                     | Clang source-based coverage; HTML in `build-coverage/coverage-html/`              |
| `make no-json`                      | Build + test with `DIMVAL_WITH_NLOHMANN_JSON=OFF` (parcel auto-disabled)          |
| `make docs`                         | Doxygen output in `build-docs/`                                                   |
| `make format` / `make format-check` | clang-format the project sources                                                  |
| `make ci`                           | The full pre-push gate: format-check + tidy + test + sanitize + release + no-json |

### Build options

| CMake option                | Default   | Effect                                                                  |
|-----------------------------|-----------|-------------------------------------------------------------------------|
| `DIMVAL_BUILD_TESTS`        | top-level | Build the GoogleTest suite (auto-fetches GTest 1.17 if not found)       |
| `DIMVAL_BUILD_EXAMPLES`     | top-level | Build every example target                                              |
| `DIMVAL_BUILD_DOCS`         | OFF       | Configure the Doxygen target                                            |
| `DIMVAL_WITH_NLOHMANN_JSON` | ON        | Link nlohmann/json and define `DIMVAL_WITH_NLOHMANN_JSON=1`             |
| `DIMVAL_WITH_PARCEL`        | ON        | Link cpp-parcel; auto-disabled if JSON is OFF                           |
| `DIMVAL_ENABLE_SANITIZERS`  | OFF       | ASan + UBSan flags (Debug)                                              |
| `DIMVAL_ENABLE_CLANG_TIDY`  | OFF       | Run clang-tidy during the build (uses the `.clang-tidy` in the repo)    |
| `DIMVAL_ENABLE_COVERAGE`    | OFF       | Clang source-based coverage flags                                       |
| `DIMVAL_WARNINGS_AS_ERRORS` | top-level | Promote compiler warnings to errors                                     |
| `DIMVAL_INSTALL`            | top-level | Generate install rules; auto-disabled if a fetched dependency is in use |

`top-level` means "ON when `dimval` is the top project, OFF when it's a
subproject" (`PROJECT_IS_TOP_LEVEL`).

## Performance notes

The library carries no runtime overhead beyond:

- 8 bytes per polymorphic value (the vtable pointer; arithmetic is still
  `constexpr`).
- A `std::shared_mutex` on each registry, shared-locked for lookups.
- `std::format` allocations during `to_string()` / `operator<<`.

Storage is "one canonical unit per kind"; SI-prefix variants (`km`, `MHz`,
`ms`, …) are the formatter's responsibility, not extra stored types — so
you don't pay for unused conversions you'll never call. There are no
benchmarks in the repository; the claims above are about design, not
measurement.

## FAQ

**Do I need to link a library, or is it header-only?**

It's header-only. The CMake target is `INTERFACE`. Linking
`dimval::dimval` only adds include paths (and propagates the
`DIMVAL_WITH_NLOHMANN_JSON=1` / `DIMVAL_WITH_PARCEL=1` definitions when
those integrations are on).

**What happens if input is invalid?**

Parse and range constructors return `std::expected`; the value side is
free of validation exceptions. `convert<>` mismatches are
`static_assert`-compile errors. Mixing tags is an overload-resolution
compile error. `nlohmann::json` mismatches throw
`nlohmann::json::other_error` because that's the JSON adapter's own
contract.

**Can I use this in multiple threads?**

Reading and writing the same `UnitValue` from multiple threads is a data
race like any other plain struct. The *registries* are thread-safe — the
test suite stresses this with concurrent `find` calls.

**Does this own the data or borrow it?**

`UnitValue<U, T>` owns its `T v;` by value. Heap helpers `of()` /
`unique()` give you `shared_ptr` / `unique_ptr` ownership. Descriptor
fields are `string_view` and *do not* own the underlying strings — you
must keep them alive for as long as the descriptor is reachable.

**Which compiler versions work?**

The repo doesn't pin compilers explicitly; any C++23-complete toolchain
(`<format>`, `<expected>`, ranges, deducing `this` is not used) should
build. Run `make ci` to verify locally.

**How do I disable JSON / parcel?**

Configure with `-DDIMVAL_WITH_NLOHMANN_JSON=OFF` and/or
`-DDIMVAL_WITH_PARCEL=OFF`. Setting JSON off auto-disables parcel.
Equivalent Meson options are `-Djson=false -Dparcel=false`.

**How do I debug build errors?**

Compile errors when adding mismatched tags read as overload-resolution
failures (`no operator+ matches…`). Compile errors from `convert<>` come
through the `static_assert` message. Parse and range errors are runtime
and surface through `std::expected`. Format errors throw
`std::format_error` and include the offending spec.

## Contributing

Contributions to the library are welcome! If you encounter any issues or have suggestions for
improvements,
please feel free to submit a pull request or open an issue on the project's repository.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
