/*******************************************************************************
 * examples/wordcount/word_count_simple.cpp
 *
 * Part of Project c7a.
 *
 *
 * This file has no license. Only Chuck Norris can compile it.
 ******************************************************************************/

#include <random>
#include <thread>
#include <string>

#include "word_count_user_program.cpp"

#include <c7a/api/bootstrap.hpp>
#include <c7a/api/dia.hpp>
#include <c7a/common/cmdline_parser.hpp>

static void local_word_count(size_t workers, size_t elements, size_t port_base) {
    
    std::function<void(c7a::Context&)> start_func = [elements](c7a::Context& ctx) {
        word_count_generated(ctx, elements);
    };

    c7a::ExecuteThreads(workers, port_base, start_func);

}

int main(int argc, char* argv[]) {

    using c7a::Execute;

    const size_t port_base = 8080;

    c7a::common::CmdlineParser clp;

    clp.SetVerboseProcess(false);

    unsigned int workers = 1;
    clp.AddUInt('n', "workers", "N", workers,
                "Create wordcount example with N workers");

    unsigned int elements = 1;
    clp.AddUInt('s', "elements", "S", elements,
                "Create wordcount example with S generated words");

    if (!clp.Process(argc, argv)) {
        return -1;
    }

    local_word_count(workers, elements, port_base);

}

/******************************************************************************/