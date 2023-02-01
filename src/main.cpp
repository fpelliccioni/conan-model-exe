/*
*/

#include <model/utility/app_args.hpp>
#include <model/utility/server_logger.hpp>

int main(int argc, const char* argv[]) {
    auto const args = app_args_t::parse(argc, argv);
    if ( ! args.has_value()) return static_cast<int>(args.error());

    if (args->welcome_message.has_value()) {
        fmt::print("Welcome message: {}\n", args->welcome_message.value());
    }

    fmt::print("int_a: {}\n", args->int_a);
    fmt::print("int_b: {}\n", args->int_b);
    fmt::print("int_a + int_b: {}\n", args->int_a + args->int_b);
    fmt::print("int_a * int_b: {}\n", args->int_a * args->int_b);

    return 0;
}
