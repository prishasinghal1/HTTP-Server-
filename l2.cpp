#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

static std::string strip(std::string s) {
    size_t i = 0;
    while (i < s.size() && std::isspace((unsigned char)s[i])) i++;
    size_t j = s.size();
    while (j > i && std::isspace((unsigned char)s[j - 1])) j--;
    return s.substr(i, j - i);
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) break;

        auto pos = line.find(':');
        if (pos == std::string::npos) {
            std::cout << "ERR malformed: " << line << "\n";
            continue;
        }

        std::string raw_name = line.substr(0, pos);

        // No whitespace allowed before the colon. Must check this BEFORE
        // stripping raw_name, since strip() would erase the evidence.
        // e.g. "Content-Length : 5" -> malformed, not "content-length".
        if (!raw_name.empty() && std::isspace((unsigned char)raw_name.back())) {
            std::cout << "ERR malformed: " << line << "\n";
            continue;
        }

        std::string name = strip(raw_name);   // strips any leading ws (rare but harmless)
        std::string value = strip(line.substr(pos + 1));

        // Names are case-insensitive; normalize to lowercase for storage/lookup.
        std::transform(name.begin(), name.end(), name.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        std::cout << name << ": " << value << "\n";
    }
    return 0;
}