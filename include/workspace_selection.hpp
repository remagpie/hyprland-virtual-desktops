#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

constexpr int firstWorkspaceForVDesk(int vdeskId, std::size_t monitorCount, int configuredFirstWorkspace = -1) {
    return configuredFirstWorkspace != -1 ? configuredFirstWorkspace : static_cast<int>((vdeskId - 1) * monitorCount + 1);
}

inline std::optional<std::unordered_map<int, int>> parseFirstWorkspaces(std::string_view rawConf) {
    std::unordered_map<int, int> parsed;
    if (rawConf.empty() || rawConf == "unset")
        return parsed;

    std::string conf{rawConf};
    while (true) {
        const auto pos   = conf.find(',');
        const auto rule  = conf.substr(0, pos);
        const auto delim = rule.find(':');
        if (delim == std::string::npos)
            return std::nullopt;

        try {
            const int vdeskId = std::stoi(rule.substr(0, delim));
            parsed[vdeskId]   = std::stoi(rule.substr(delim + 1));
        } catch (const std::exception&) { return std::nullopt; }

        if (pos == std::string::npos)
            return parsed;
        conf.erase(0, pos + 1);
    }
}
