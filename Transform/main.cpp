#include <iostream>
#include <vector>

/* Basic implementation for generic transform function
 * with variadic templates.
 * Note, that function signature is different from
 * std::transform, since parameter pack needs to be final
 * in the list of passed arguments.
 * Validity tested on Microsoft Visual C++ Compiler 15.0*/

template <class InIter> void Increment(InIter& arg1)
{
    ++arg1;
}

template <class InIterFirst, class... InIter> void Increment(InIterFirst& arg1, InIter&... rest)
{
    ++arg1;
    Increment(rest...);
}

template <class Lambda, class OutputIter, class InIterBase, class... InIter>
void GenericTransform(Lambda&& operation, OutputIter&& output, InIterBase&& iter_begin,
                      const InIterBase& iter_end, InIter&&... args)
{
    for (; iter_begin != iter_end; Increment(iter_begin, output, args...))
        *output = operation(*iter_begin, *args...);
}

/* tests*/

void TestVector() {
    std::vector<size_t> digits{1, 2, 3, 4};
    std::vector<size_t> digits_to_sum{2, 3, 4, 5};
    std::vector<size_t> result(4);
    GenericTransform([](size_t i, size_t j) { return i + j; }, result.begin(), digits.cbegin(),
                     digits.cend(), digits_to_sum.cbegin());
    if (result == std::vector<size_t>{3,5,7,9}) {
        std::cout << "TestVector:\tOK" << std::endl;
        return;
    }
    throw std::runtime_error("Error in TestVector: expected and actual vectors are not equal");
}

void TestBarePointers() {
    size_t digits[4] = {1, 2, 3, 4};
    size_t digits_to_sum[4] = {2, 3, 4, 5};
    size_t result[4];
    size_t reference[4] = {3, 5, 7, 9};
    GenericTransform([](size_t i, size_t j) { return i + j; }, &result[0], &digits[0],
                     &digits[0] + 4, &digits_to_sum[0]);
    for (size_t i = 0; i < 4; ++i)
        if (result[i] != reference[i])
            throw std::runtime_error(
                "Error in TestBarePointers: expected and actual vectors are not equal");

    std::cout << "TestBarePointers:\tOK" << std::endl;
    return;
}

int main()
{
    TestVector();
    TestBarePointers();
    return 0;
}
