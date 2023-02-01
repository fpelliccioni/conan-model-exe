// MIT License

#include <cstdint>
#include <optional>

#include <nonstd/expected.hpp>

#include <string>

struct app_args_t {
    std::uint64_t int_a{100};
    std::uint64_t int_b{200};
    std::optional<std::string> welcome_message;

    enum class result { help, error };
    static nonstd::expected<app_args_t, result> parse(int argc, const char *argv[]);
};
