# Benchmark protocol

Use a disposable copy of the same world for each configuration. Record the game, Java, Fabric Loader, and mod versions, along with the CPU, GPU, driver, graphics backend, resolution, render distance, simulation distance, and FPS cap. Keep these fixed within a comparison. Record whether shaders and renderer extensions are active.

## Workloads

| Workload | Setup | Record |
| --- | --- | --- |
| Stationary | Load a populated scene and hold position and camera angle. | Frame times and GPU utilization |
| New terrain | Restore the starting snapshot and follow the same route into ungenerated chunks at the same speed. | Frame times, tick times, and completed chunks per second |
| Mod-heavy scene | Restore a snapshot with a representative active build and repeat the same interaction sequence. | Frame times, tick times, and memory use |

Warm up the client for 60 seconds in a preloaded area before each run. Capture for 120 seconds and use at least five runs per configuration. Alternate between control and candidate runs. Keep the launcher settings and background workload consistent. If a route completes before 120 seconds, choose a longer route and rerun both configurations.

Analyze each frame capture individually with Framebench. Report per-run sample count, p50, p95, and p99 in milliseconds, plus the median and range of each metric across runs. Record any interrupted runs and why they were excluded. Report tick time in milliseconds, generated chunks per second, memory in MiB, and GPU utilization as a percentage if those metrics are available.

Use an instrumented Java-only run to measure capture overhead and as the control for the native module. Compare the original 26.2 pack and the upgraded 26.3 pack separately to show the effect of upgrading the game and mods.
