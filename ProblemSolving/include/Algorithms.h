#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <deque>

namespace ps {

/**
 * A curated collection of classic algorithm problems, each a small
 * self-contained function. Kept together to show range: strings,
 * arrays, recursion, dynamic programming and data structures.
 */
class Algorithms {
public:
    // ---------- 1. Two Sum ----------
    /** Indices of the pair summing to target, or {-1,-1}. O(n). */
    static std::pair<int, int> twoSum(const std::vector<int>& nums, int target) {
        std::unordered_map<int, int> seen;  // value -> index
        for (int i = 0; i < (int)nums.size(); ++i) {
            int need = target - nums[i];
            auto it = seen.find(need);
            if (it != seen.end()) return { it->second, i };
            seen[nums[i]] = i;
        }
        return { -1, -1 };
    }

    // ---------- 2. Palindrome ----------
    /** Ignores case and non-alphanumeric characters. O(n). */
    static bool isPalindrome(const std::string& s) {
        int i = 0, j = (int)s.size() - 1;
        auto alnum = [](char c) { return std::isalnum((unsigned char)c) != 0; };
        auto lower = [](char c) { return (char)std::tolower((unsigned char)c); };

        while (i < j) {
            while (i < j && !alnum(s[i])) ++i;
            while (i < j && !alnum(s[j])) --j;
            if (lower(s[i]) != lower(s[j])) return false;
            ++i; --j;
        }
        return true;
    }

    // ---------- 3. FizzBuzz ----------
    static std::vector<std::string> fizzBuzz(int n) {
        std::vector<std::string> out;
        for (int i = 1; i <= n; ++i) {
            if      (i % 15 == 0) out.push_back("FizzBuzz");
            else if (i % 3  == 0) out.push_back("Fizz");
            else if (i % 5  == 0) out.push_back("Buzz");
            else                  out.push_back(std::to_string(i));
        }
        return out;
    }

    // ---------- 4. Fibonacci (memoised) ----------
    static long long fibonacci(int n) {
        static std::vector<long long> memo = { 0, 1 };
        if (n < 0) throw std::invalid_argument("n must be >= 0");
        while ((int)memo.size() <= n) memo.push_back(memo[memo.size() - 1] + memo[memo.size() - 2]);
        return memo[n];
    }

    // ---------- 5. Factorial ----------
    static long long factorial(int n) {
        if (n < 0) throw std::invalid_argument("n must be >= 0");
        long long r = 1;
        for (int i = 2; i <= n; ++i) r *= i;
        return r;
    }

    // ---------- 6. Reverse string ----------
    static std::string reverseString(const std::string& s) {
        std::string r(s.rbegin(), s.rend());
        return r;
    }

    // ---------- 7. Anagram ----------
    static bool isAnagram(const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return false;
        int count[26] = { 0 };
        for (char c : a) if (std::isalpha((unsigned char)c)) count[std::tolower((unsigned char)c) - 'a']++;
        for (char c : b) if (std::isalpha((unsigned char)c)) count[std::tolower((unsigned char)c) - 'a']--;
        for (int v : count) if (v != 0) return false;
        return true;
    }

    // ---------- 8. Binary search ----------
    /** Requires a sorted vector. Returns index or -1. O(log n). */
    static int binarySearch(const std::vector<int>& sorted, int target) {
        int lo = 0, hi = (int)sorted.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (sorted[mid] == target) return mid;
            if (sorted[mid] < target)  lo = mid + 1;
            else                       hi = mid - 1;
        }
        return -1;
    }

    // ---------- 9. Balanced parentheses ----------
    static bool balancedParentheses(const std::string& s) {
        std::deque<char> stack;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') stack.push_back(c);
            else if (c == ')' || c == ']' || c == '}') {
                if (stack.empty()) return false;
                char top = stack.back();
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) return false;
                stack.pop_back();
            }
        }
        return stack.empty();
    }

    // ---------- 10. Longest common prefix ----------
    static std::string longestCommonPrefix(const std::vector<std::string>& words) {
        if (words.empty()) return "";
        std::string prefix = words[0];
        for (size_t i = 1; i < words.size(); ++i) {
            size_t j = 0;
            while (j < prefix.size() && j < words[i].size() && prefix[j] == words[i][j]) ++j;
            prefix = prefix.substr(0, j);
            if (prefix.empty()) break;
        }
        return prefix;
    }

    // ---------- 11. GCD (Euclid) ----------
    static int gcd(int a, int b) {
        a = std::abs(a); b = std::abs(b);
        while (b != 0) { int t = b; b = a % b; a = t; }
        return a;
    }
};

} // namespace ps
