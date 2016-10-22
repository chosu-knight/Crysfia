# ifndef __TextTypes__
# define __TextTypes__

# include <array>
# include <string>
# include <vector>
# include <map>

namespace User
{
    enum class Tag
    {
        Novel = 1001,
        Name = 1002,
        Human = 1003,
    };
    constexpr uint32_t lineSize = 3U;
    using NovelData = std::array<std::string, lineSize>;
    using RawScriptPartsData = std::vector<std::string>;

    struct TagWithNovelStringAndRawScriptPartsData
    {
        enum class Tag
        {
            NIL,
            NOV,
            VAR,
            FUN,
        };
        Tag tag;
        std::string novel;
        RawScriptPartsData script;
    };
    using VariableScriptData = std::map<std::string, std::string>;
    using ArgumentList = std::vector<std::string>;

    struct FunctionInfo
    {
        std::string name;
        ArgumentList argumentList;
    };
    using FunctionScriptData = std::map<std::string, FunctionInfo>;
    struct FunctionScriptChip
    {
        std::string variable;
        FunctionInfo functionInfo;
    };
}

# endif // __TextTypes__
