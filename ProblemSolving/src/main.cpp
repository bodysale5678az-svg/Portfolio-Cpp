// ============================================================
//  Problem Solving — algorithm demos with a tiny test runner
//  Author: Mahmoud Saleh
// ============================================================
#include "Algorithms.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace ps;

static int passed = 0;
static int failed = 0;

template <typename T>
static void checkEqual(const std::string& name, const T& actual, const T& expected) {
    bool ok = (actual == expected);
    if (ok) { ++passed; std::cout << "  [PASS] " << name << "\n"; }
    else {
        ++failed;
        std::cout << "  [FAIL] " << name << "\n";
        std::cout << "         expected: " << expected << "\n";
        std::cout << "         actual  : " << actual << "\n";
    }
}

static void checkTrue(const std::string& name, bool actual) {
    checkEqual<bool>(name, actual, true);
}

static void header(const std::string& t) {
    std::cout << "\n--- " << t << " ---\n";
}

int main() {
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║   PROBLEM SOLVING  -  C++17 test suite   ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n";

    header("1. Two Sum");
    {
        auto r = Algorithms::twoSum({ 2, 7, 11, 15 }, 9);
        checkEqual<int>("twoSum([2,7,11,15], 9) -> first index",  r.first,  0);
        checkEqual<int>("twoSum([2,7,11,15], 9) -> second index", r.second, 1);

        auto n = Algorithms::twoSum({ 1, 2, 3 }, 100);
        checkEqual<int>("twoSum no solution -> -1", n.first, -1);
    }

    header("2. Palindrome");
    checkTrue("'racecar'", Algorithms::isPalindrome("racecar"));
    checkTrue("'A man, a plan, a canal: Panama'", Algorithms::isPalindrome("A man, a plan, a canal: Panama"));
    checkEqual<bool>("'hello' is not palindrome", Algorithms::isPalindrome("hello"), false);

    header("3. FizzBuzz");
    {
        auto fb = Algorithms::fizzBuzz(15);
        checkEqual<std::string>("fizzBuzz(15)[2] (n=3)",  fb[2],  "Fizz");
        checkEqual<std::string>("fizzBuzz(15)[4] (n=5)",  fb[4],  "Buzz");
        checkEqual<std::string>("fizzBuzz(15)[14] (n=15)", fb[14], "FizzBuzz");
        checkEqual<size_t>("fizzBuzz(15) size", fb.size(), (size_t)15);
    }

    header("4. Fibonacci");
    checkEqual<long long>("fib(0)",  Algorithms::fibonacci(0),  0);
    checkEqual<long long>("fib(1)",  Algorithms::fibonacci(1),  1);
    checkEqual<long long>("fib(10)", Algorithms::fibonacci(10), 55);
    checkEqual<long long>("fib(50)", Algorithms::fibonacci(50), 12586269025LL);

    header("5. Factorial");
    checkEqual<long long>("5!",  Algorithms::factorial(5),  120);
    checkEqual<long long>("0!",  Algorithms::factorial(0),  1);
    checkEqual<long long>("10!", Algorithms::factorial(10), 3628800);

    header("6. Reverse string");
    checkEqual<std::string>("reverse 'hello'", Algorithms::reverseString("hello"), std::string("olleh"));
    checkEqual<std::string>("reverse 'abc'",   Algorithms::reverseString("abc"),   std::string("cba"));

    header("7. Anagram");
    checkTrue("'listen' / 'silent'",  Algorithms::isAnagram("listen", "silent"));
    checkEqual<bool>("'hello' / 'world'", Algorithms::isAnagram("hello", "world"), false);

    header("8. Binary search");
    checkEqual<int>("search 7 in sorted [1,3,5,7,9]", Algorithms::binarySearch({ 1, 3, 5, 7, 9 }, 7), 3);
    checkEqual<int>("search 1 (first)",               Algorithms::binarySearch({ 1, 3, 5, 7, 9 }, 1), 0);
    checkEqual<int>("search 100 (missing)",           Algorithms::binarySearch({ 1, 3, 5, 7, 9 }, 100), -1);

    header("9. Balanced parentheses");
    checkTrue("'()[]{}'",      Algorithms::balancedParentheses("()[]{}"));
    checkTrue("'{[()()]}'",    Algorithms::balancedParentheses("{[()()]}"));
    checkEqual<bool>("'([)]'", Algorithms::balancedParentheses("([)]"), false);
    checkEqual<bool>("'(('",   Algorithms::balancedParentheses("(("),   false);

    header("10. Longest common prefix");
    checkEqual<std::string>("[flower,flow,flight]",
        Algorithms::longestCommonPrefix({ "flower", "flow", "flight" }), std::string("fl"));
    checkEqual<std::string>("[dog,cat]",
        Algorithms::longestCommonPrefix({ "dog", "cat" }), std::string(""));

    header("11. GCD");
    checkEqual<int>("gcd(48, 18)", Algorithms::gcd(48, 18), 6);
    checkEqual<int>("gcd(17, 5)",  Algorithms::gcd(17, 5),  1);

    header("12. Fibonacci (iterative)");
    checkEqual<long long>("fibIter(0)",  Algorithms::fibIterative(0),  0);
    checkEqual<long long>("fibIter(10)", Algorithms::fibIterative(10), 55);
    checkEqual<long long>("fibIter(30)", Algorithms::fibIterative(30), 832040LL);
    checkEqual<long long>("matches memo fib(20)",
        Algorithms::fibIterative(20), Algorithms::fibonacci(20));

    header("13. Count vowels");
    checkEqual<int>("'hello' -> 2",             Algorithms::countVowels("hello"), 2);
    checkEqual<int>("'EDUCATION' -> 5",         Algorithms::countVowels("EDUCATION"), 5);
    checkEqual<int>("'xyz' -> 0",               Algorithms::countVowels("xyz"), 0);

    header("14. Sum of digits");
    checkEqual<int>("12345",  Algorithms::sumOfDigits(12345),  15);
    checkEqual<int>("999",    Algorithms::sumOfDigits(999),    27);
    checkEqual<int>("-456",   Algorithms::sumOfDigits(-456),   15);

    header("15. Max subarray sum (Kadane)");
    checkEqual<long long>("[-2,1,-3,4,-1,2,1,-5,4] = 6",
        Algorithms::maxSubarraySum({ -2, 1, -3, 4, -1, 2, 1, -5, 4 }), 6);
    checkEqual<long long>("[1,2,3,4] = 10",
        Algorithms::maxSubarraySum({ 1, 2, 3, 4 }), 10);
    checkEqual<long long>("[-5,-2,-9] = -2",
        Algorithms::maxSubarraySum({ -5, -2, -9 }), -2);

    header("16. Move zeros to end");
    {
        std::vector<int> v = { 0, 1, 0, 3, 12 };
        Algorithms::moveZeros(v);
        checkTrue("-> 1,3,12,0,0",
            v == std::vector<int>({ 1, 3, 12, 0, 0 }));
    }

    header("17. Remove duplicates (sorted)");
    {
        std::vector<int> v = { 1, 1, 2, 2, 3, 4, 4 };
        size_t n = Algorithms::removeDuplicates(v);
        checkEqual<size_t>("unique count = 4", n, (size_t)4);
        checkTrue("-> 1,2,3,4", v == std::vector<int>({ 1, 2, 3, 4 }));
    }

    header("18. Is prime");
    checkTrue("2",       Algorithms::isPrime(2));
    checkTrue("97",      Algorithms::isPrime(97));
    checkEqual<bool>("1",   Algorithms::isPrime(1),  false);
    checkEqual<bool>("100", Algorithms::isPrime(100), false);

    header("19. Count words");
    checkEqual<int>("'hello world' -> 2",        Algorithms::countWords("hello world"), 2);
    checkEqual<int>("spaces -> 3",               Algorithms::countWords("  the quick  brown  "), 3);
    checkEqual<int>("empty -> 0",                Algorithms::countWords(""), 0);

    header("20. Capitalize words");
    checkEqual<std::string>("'hello world'",
        Algorithms::capitalizeWords("hello world"), std::string("Hello World"));
    checkEqual<std::string>("'the quick brown'",
        Algorithms::capitalizeWords("the quick brown"), std::string("The Quick Brown"));

    header("21. Power (fast exponentiation)");
    checkEqual<long long>("2^10",  Algorithms::power(2, 10),  1024);
    checkEqual<long long>("3^5",   Algorithms::power(3, 5),   243);
    checkEqual<long long>("5^0",   Algorithms::power(5, 0),   1);

    header("22. Second largest");
    checkEqual<int>("[3,1,4,1,5,9,2,6] -> 6",
        Algorithms::secondLargest({ 3, 1, 4, 1, 5, 9, 2, 6 }), 6);
    checkEqual<int>("[10,20,30] -> 20",
        Algorithms::secondLargest({ 10, 20, 30 }), 20);

    header("23. Rotate left");
    {
        std::vector<int> v = { 1, 2, 3, 4, 5 };
        Algorithms::rotateLeft(v, 2);
        checkTrue("k=2 -> 3,4,5,1,2", v == std::vector<int>({ 3, 4, 5, 1, 2 }));
    }

    header("24. Missing number");
    checkEqual<int>("[3,0,1] -> 2",       Algorithms::missingNumber({ 3, 0, 1 }), 2);
    checkEqual<int>("[0,1,2,4] -> 3",     Algorithms::missingNumber({ 0, 1, 2, 4 }), 3);

    header("25. Longest word");
    checkEqual<std::string>("'the quick brown fox'",
        Algorithms::longestWord("the quick brown fox"), std::string("quick"));
    checkEqual<std::string>("'I love programming'",
        Algorithms::longestWord("I love programming"), std::string("programming"));

    // ---- summary ----
    std::cout << "\n==============================================\n";
    std::cout << "  PASSED: " << passed << "   FAILED: " << failed << "\n";
    std::cout << "==============================================\n\n";

    return failed == 0 ? 0 : 1;
}
