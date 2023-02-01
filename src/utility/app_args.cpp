// MIT License

#include <model/utility/app_args.hpp>

#include <fmt/format.h>
#include <fmt/printf.h>
#include <fmt/ostream.h>

#define LYRA_CONFIG_OPTIONAL_TYPE std::optional

#include <lyra/lyra.hpp>

template <> struct fmt::formatter<lyra::cli> : ostream_formatter {};

// static
nonstd::expected<app_args_t, app_args_t::result> app_args_t::parse(int argc, const char *argv[]) {  // NOLINT(hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
    bool help = false;
    app_args_t args;

    auto cli =
        lyra::help(help) |
        lyra::opt(args.int_a, "int_a")["-ia"]["--int_a"](fmt::format("first integer (default: {})", args.int_a)) |
        lyra::opt(args.int_b, "int_b")["-ib"]["--int_b"]("second` integer").required() |
        lyra::arg(args.welcome_message, "welcome_message")("welcome message to be sent to the client");

    auto const parse_args = cli.parse({argc, argv});
    if ( ! parse_args) {
        fmt::print("Invalid command-line arguments: {}\n", parse_args.message());
        return nonstd::make_unexpected(app_args_t::result::error);
    }

    if (help) {
        fmt::print("{}\n", cli);
        return nonstd::make_unexpected(app_args_t::result::help);
    }

    return args;
}
