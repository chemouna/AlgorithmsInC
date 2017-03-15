
/*#ifndef RabinKarp_Included
#define RabinKarp_Included*/

#include <iterator>  // For distance
#include <algorithm> // For equal
#include <vector>
#include <string>
#include <iostream>

/**
 * RabinKarpMatch(ForwardIterator1 textBegin, ForwardIterator1 textEnd,
 *                ForwardIterator2 patternBegin, ForwardIterator2 patternEnd);
 * Usage: if (RabinKarpMatch(t.begin(), t.end(), p.begin(), p.end()) != t.end())
 * ----------------------------------------------------------------------------
 * Given a string encoded by the range [textBegin, textEnd) composed of chars,
 * returns the first instance of the string [patternBegin, patternEnd) (also
 * composed of chars) in that string using the Rabin-Karp algorithm.  If no
 * match is found, this function returns textEnd as a sentinel value.
 */
template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1
RabinKarpMatch(ForwardIterator1 textBegin, ForwardIterator1 textEnd,
               ForwardIterator2 patternBegin, ForwardIterator2 patternEnd) {
    /* The number of possible characters. */
    const size_t kNumChars = 256;

    /* A prime number q such that 256q fits into a 32-bit machine word.  On a 64-
     * bit machine, it may be advantageous to pick a larger prime.
     */
    const size_t kPrime = 16777213;

    /* Check that the number of characters in the text is at least as large as
     * the number of characters in the pattern.  Otherwise there's no possible
     * way that we have a match.
     */
    const size_t patternSize = size_t(std::distance(patternBegin, patternEnd));
    const size_t textSize = size_t(std::distance(textBegin, textEnd));
    if (textSize < patternSize)
        return textEnd;

    /* Scan over the pattern and compute its hash code.  This works by building
     * up the base-n number one digit at a time, while always still working
     * modulo the prime.
     */
    size_t patternHash = 0;
    for (ForwardIterator2 itr = patternBegin; itr != patternEnd; ++itr) {
        /* Update the hash code by scaling up the existing hash code by the number
         * of characters, then adding in the new character.  This is the same logic
         * you would use to update the value of a base-n number by appending a new
         * digit to that number.
         */
        patternHash = (patternHash * kNumChars + (unsigned char) *itr) % kPrime;
    }

    /* Next, compute the hash code for the first |P| characters of the text.  We
     * declare the iterator that we'll use to scan the text outside of the loop,
     * since we'll need to remember where to pick up from.
     */
    ForwardIterator1 itr = textBegin;
    size_t hashCode = 0;

    /* Scan over the first patternSize characters, updating the hash code as in
     * the above case.
     */
    for (size_t i = 0; i < patternSize; ++i, ++itr)
        hashCode = (hashCode * kNumChars + (unsigned char) *itr) % kPrime;

    /* Before we can enter the loop, we'll need to know the value of n^k from the
     * above formula, which we'll need to have on-hand so we can update the hash
     * code.
     */
    size_t highestRadix = 1;
    for (size_t i = 0; i < patternSize; ++i)
        highestRadix = (highestRadix * kNumChars) % kPrime;

    /* Finally, enter the actual loop logic.  Scan across the rest of the text,
     * checking for matches and updating the hash code as appropriate.  In the
     * course of doing so, we'll maintain an iterator tracking the start of the
     * current string we're considering.
     */
    ForwardIterator1 wordStart = textBegin;
    while (true) {
        /* Check if the candidate string has a matching hash code and, if so, do the
         * actual comparison.
         */
        if (hashCode == patternHash && std::equal(patternBegin, patternEnd, wordStart))
            return wordStart;

        /* If we've hit the end of our input, we've failed to find a match and are
         * done.
         */
        if (itr == textEnd)
            return textEnd;

        /* Otherwise, update our hash code.  To do this, we need to do the
         * following:
         *
         * 1. Scale up the existing hash code by a factor of n.
         * 2. Add in the next character.
         * 3. Subtract out n^k times the character that was just evicted.
         *
         * We need to do each step individually, since otherwise we risk an integer
         * overflow, which breaks all of our logic.
         */

        /* Step one: Scale up the hash code. */
        hashCode = (hashCode * kNumChars) % kPrime;

        /* Step two: Add in the next character. */
        hashCode = (hashCode + (unsigned char) *itr) % kPrime;

        /* Step three: Subtract out n^k times the character we just evicted.
         * This step is tricky because we can't subtract out one unsigned value from
         * another.  Instead, we'll use the fact that
         *
         *                            -k == q - k  (mod q)
         *
         * To do the subtraction implicitly.
         */
        const size_t toSubtract = kPrime - ((highestRadix * (unsigned char) *wordStart) % kPrime);
        hashCode = (hashCode + toSubtract) % kPrime;

        /* Advance the word forward a step. */
        ++wordStart;
        ++itr;
    }
}

int main(int argc, char *argv[]) {
    std::string s = "Hello World";
    std::string t = "Wo";
    std::string::iterator it = RabinKarpMatch(s.begin(), s.end(), t.begin(), t.end());
    std::cout << "I: " << it-s.begin();
}

//#endif