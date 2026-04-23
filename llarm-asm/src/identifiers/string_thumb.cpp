#include "string_thumb.hpp"
#include "../interpreter/interpreter.hpp"
#include "../id/instruction_id.hpp"
#include "src/interpreter/mnemonic_thumb.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>
#include <nonstd/string_view.hpp>

using namespace internal;
using enum token_enum;

thumb_id ident::string_thumb::thumb(const std::string& code) {
    const std::string& assembly = llarm::util::to_upper(code);
    const sv mnemonic = interpreter::fetch_instruction(assembly);

    return mnemonic_thumb::fetch_thumb_id(code, mnemonic);
}