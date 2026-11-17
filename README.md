# Framebench

Framebench is a C++ frame-time analyzer for performance work on modded Minecraft Java. The current command-line tool summarizes captures on Windows x64. The Fabric 26.3 capture integration is planned.

## Build and test

Use CMake 3.21 or later, a C++20 compiler, and a Visual Studio developer shell on Windows.

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

## Analyze a capture

```powershell
.\build\Release\framebench.exe .\tests\frames.csv
```

The input is a single-column CSV with a `frame_ms` header and one positive, finite duration in milliseconds per row. LF and CRLF line endings are accepted. The tool reports sample count and nearest-rank p50, p95, and p99 frame times.

For comparisons, use the same world copy, route, graphics settings, mod versions, Java runtime, and warm-up period. Record multiple runs per configuration and compare tail frame times along with the median. The included CSV is a test fixture.

See the [benchmark protocol](docs/benchmark-protocol.md) for repeatable workloads and reporting.
