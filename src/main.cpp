#include <algorithm>
#include <charconv>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool read_line(std::istream& input, std::string& line) {
    if (!std::getline(input, line)) {
        return false;
    }
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    return true;
}

double percentile(const std::vector<double>& sorted, std::size_t percentage) {
    const auto count = sorted.size();
    const auto rank = (count / 100) * percentage
        + ((count % 100) * percentage + 99) / 100;
    return sorted[rank - 1];
}

} // namespace

#ifdef _WIN32
int wmain(int argc, wchar_t* argv[]) {
#else
int main(int argc, char* argv[]) {
#endif
    if (argc != 2) {
        std::cerr << "Usage: framebench <capture.csv>\n";
        return 2;
    }

    const std::filesystem::path capture(argv[1]);
    std::ifstream input(capture);
    if (!input) {
        std::cerr << "Could not open capture: " << capture << '\n';
        return 1;
    }

    std::string line;
    if (!read_line(input, line) || line != "frame_ms") {
        std::cerr << "Expected frame_ms header\n";
        return 1;
    }

    std::vector<double> samples;
    while (read_line(input, line)) {
        double duration = 0;
        const auto end = line.data() + line.size();
        const auto [next, error] = std::from_chars(line.data(), end, duration);
        if (error != std::errc{} || next != end || !std::isfinite(duration) || duration <= 0) {
            std::cerr << "Invalid frame duration on line " << samples.size() + 2 << '\n';
            return 1;
        }
        samples.push_back(duration);
    }

    if (input.bad() || samples.empty()) {
        std::cerr << "Could not read any complete capture data\n";
        return 1;
    }

    std::sort(samples.begin(), samples.end());
    std::cout << std::fixed << std::setprecision(3)
              << "frames=" << samples.size()
              << " p50_ms=" << percentile(samples, 50)
              << " p95_ms=" << percentile(samples, 95)
              << " p99_ms=" << percentile(samples, 99) << '\n';
}
