// Benchmark: spdlog::info() vs fmt::println() vs std::println() vs std::cout
// for 1M formatted lines. spdlog adds [timestamp][level] prefix on every line,
// so its output is larger — this measures the real cost of structured logging.
//
// Sync vs Async:
//   Synchronous (this file): log call blocks until the sink has accepted the
//   message. Simple, no extra threads, safe on crash — what you want for
//   learning and most library code.
//
//   Asynchronous: log call pushes to a lock-free queue; a background thread
//   drains it to the sink. The calling thread returns immediately — lower
//   latency per call, higher throughput under bursts — but messages in the
//   queue are lost if the process crashes before the thread flushes.
//
// Run comparison (redirect to /dev/null to isolate formatting cost from I/O):
//   hyperfine --warmup 2
//     './ch01_benchmarks_spdlog_bench_23 > /dev/null'
//     './ch01_benchmarks_fmt_bench_23    > /dev/null'
//     './ch01_benchmarks_println_bench_23 > /dev/null'
//     './ch01_benchmarks_cout_bench_23   > /dev/null'
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main() {
    // Drop the timestamp to make output volume comparable to fmt/cout.
    spdlog::set_pattern("[%l] %v");

    for (int i = 0; i < 1'000'000; ++i)
        spdlog::info("row {:6d}  x = {:10.5f}  tag = {}", i, i * 0.333, "node");
}
