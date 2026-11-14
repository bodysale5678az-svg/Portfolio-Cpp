#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <deque>
#include <sstream>
#include <cctype>
#include <climits>

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

    // ---------- 12. Fibonacci (iterative) ----------
    static long long fibIterative(int n) {
        if (n < 0) throw std::invalid_argument("n must be >= 0");
        long long a = 0, b = 1;
        for (int i = 0; i < n; ++i) { long long t = a + b; a = b; b = t; }
        return a;
    }

    // ---------- 13. Count vowels ----------
    static int countVowels(const std::string& s) {
        int count = 0;
        for (char c : s) {
            char l = (char)std::tolower((unsigned char)c);
            if (l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u') ++count;
        }
        return count;
    }

    // ---------- 14. Sum of digits ----------
    static int sumOfDigits(int n) {
        n = std::abs(n);
        int sum = 0;
        while (n > 0) { sum += n % 10; n /= 10; }
        return sum;
    }

    // ---------- 15. Max subarray sum (Kadane) ----------
    static long long maxSubarraySum(const std::vector<int>& nums) {
        if (nums.empty()) throw std::invalid_argument("empty array");
        long long best = nums[0], current = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            current = std::max<long long>(nums[i], current + nums[i]);
            best = std::max(best, current);
        }
        return best;
    }

    // ---------- 16. Move zeros to end ----------
    static void moveZeros(std::vector<int>& nums) {
        size_t write = 0;
        for (size_t read = 0; read < nums.size(); ++read)
            if (nums[read] != 0) std::swap(nums[write++], nums[read]);
    }

    // ---------- 17. Remove duplicates (sorted) ----------
    static size_t removeDuplicates(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        size_t write = 1;
        for (size_t read = 1; read < nums.size(); ++read)
            if (nums[read] != nums[write - 1]) nums[write++] = nums[read];
        nums.resize(write);
        return write;
    }

    // ---------- 18. Is prime ----------
    static bool isPrime(int n) {
        if (n < 2) return false;
        if (n < 4) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; (long long)i * i <= n; i += 2)
            if (n % i == 0) return false;
        return true;
    }

    // ---------- 19. Count words ----------
    static int countWords(const std::string& s) {
        int count = 0;
        bool inWord = false;
        for (char c : s) {
            if (std::isspace((unsigned char)c)) inWord = false;
            else if (!inWord) { inWord = true; ++count; }
        }
        return count;
    }

    // ---------- 20. Capitalize each word ----------
    static std::string capitalizeWords(const std::string& s) {
        std::string out = s;
        bool newWord = true;
        for (char& c : out) {
            if (std::isspace((unsigned char)c)) newWord = true;
            else if (newWord) { c = (char)std::toupper((unsigned char)c); newWord = false; }
        }
        return out;
    }

    // ---------- 21. Power (fast exponentiation) ----------
    static long long power(long long base, int exp) {
        if (exp < 0) throw std::invalid_argument("exp must be >= 0");
        long long result = 1;
        while (exp > 0) {
            if (exp & 1) result *= base;
            base *= base;
            exp >>= 1;
        }
        return result;
    }

    // ---------- 22. Second largest ----------
    static int secondLargest(const std::vector<int>& nums) {
        if (nums.size() < 2) throw std::invalid_argument("need at least 2 elements");
        int first = INT_MIN, second = INT_MIN;
        for (int n : nums) {
            if (n > first) { second = first; first = n; }
            else if (n > second && n != first) second = n;
        }
        return second;
    }

    // ---------- 23. Rotate array left by k ----------
    static void rotateLeft(std::vector<int>& nums, int k) {
        if (nums.empty()) return;
        int n = (int)nums.size();
        k %= n;
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
        std::reverse(nums.begin(), nums.end());
    }

    // ---------- 24. Missing number 0..n ----------
    static int missingNumber(const std::vector<int>& nums) {
        int n = (int)nums.size();
        int expected = n * (n + 1) / 2;
        int actual = 0;
        for (int v : nums) actual += v;
        return expected - actual;
    }

    // ---------- 25. Longest word ----------
    static std::string longestWord(const std::string& s) {
        std::istringstream stream(s);
        std::string word, best;
        while (stream >> word)
            if (word.size() > best.size()) best = word;
        return best;
    }
};

} // namespace ps
