#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>

int main() {
    std::unordered_set<std::string> methods = {"GET","POST","PUT","DELETE","HEAD","OPTIONS","PATCH"};
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            std::cout << "INVALID\n";
            continue;
        }
        if (line.back() == '\r')
        line.pop_back();

        size_t space1 = line.find(' ');
        size_t space2 = line.find(' ', space1 + 1);

        if (space1 == std::string::npos || 
            space2 == std::string::npos || 
            line.find(' ', space2 + 1) != std::string::npos) {
            
            std::cout << "INVALID\n";
            continue;
        }

        if (space1 == 0 || space2 == space1 + 1 || space2 == line.size() - 1) {
            std::cout << "INVALID\n";
            continue;
        }

        std::vector<std::string> parts;
        parts.push_back(line.substr(0, space1));                         
        parts.push_back(line.substr(space1 + 1, space2 - space1 - 1));   
        parts.push_back(line.substr(space2 + 1));                       

        if (parts.size() != 3) {
            std::cout << "INVALID\n";
            continue;
        }

        const std::string& m = parts[0];
        const std::string& p = parts[1];
        const std::string& v = parts[2];

        if (!methods.count(m)) {
            std::cout << "INVALID\n";
            continue;
        }

        if (p.empty() || p[0] != '/') {
            std::cout << "INVALID\n";
            continue;
        }

        bool valid_version =
            v.size() == 8 &&
            v.compare(0, 5, "HTTP/") == 0 &&
            std::isdigit((unsigned char)v[5]) &&
            v[6] == '.' &&
            std::isdigit((unsigned char)v[7]);

        if (!valid_version) {
            std::cout << "INVALID\n";
            continue;
        }

        std::cout << "METHOD=" << m << " PATH=" << p << " VERSION=" << v << "\n";
    }

    return 0;
}