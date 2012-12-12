/**
 * @file random.cpp
 * Random library implementation.
 */

/**
 * Constructor.
 * @param seed - seed to initialize the RNG
 */
Random::Random(unsigned long seed)
{
    shiftRegister = (seed == 0) ? 1 : seed;
}

/**
 * @return a random integer
 */
int Random::nextInt()
{
    int ret = 0;
    for(int pos = 0; pos < 10; ++pos)
        ret |= ( (int)LFSR() << pos);
    return ret;
}

/**
 * Randomly shuffles a vector with the current seed state.
 * @param array - the vector to shuffle
 */
template <class T>
void Random::shuffle(vector<T> & array)
{
    vector<T> temp(array.size(), T());
    shuffle(array, temp, 0, array.size() - 1);
    temp.clear();
}

/**
 * This function is taken from Bruce Schneier's \emph{Applied Cryptography}
 * @return a random bit
 */
bool Random::LFSR()
{
    if(shiftRegister & 0x00000001)
    {
        shiftRegister = (shiftRegister ^ 0x80000057 >> 1) | 0x80000000;
        return true;
    }
    else
    {
        shiftRegister >>= 1;
        return false;
    }
}

/**
 * Private helper for shuffle.
 * This is basically an implementation of mergesort with random comparisons.
 * @param array - the original array
 * @param temp - the temporary array to hold sorted parts
 * @param left - the leftmost index of the current range
 * @param right - the rightmost index of the current range
 */
template <class T>
void Random::shuffle(vector<T> & array, vector<T> & temp, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;
        shuffle(array, temp, left, mid);
        shuffle(array, temp, mid + 1, right);
        merge(array, temp, left, mid + 1, right);
    }
}

/**
 * Private helper for shuffle.
 * This is basically an implementation of mergesort with random comparisons.
 * @param array - the original array
 * @param temp - the temporary array to hold sorted parts
 * @param left - the leftmost index of the current range
 * @param right - the rightmost index of the current range
 * @param rightEnd - how far to find sorted numbers in the right side
 */
template <class T>
void Random::merge(vector<T> & array, vector<T> & temp, int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tPos = leftPos;
    int n = rightEnd - leftPos + 1;

    while(leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if(LFSR())
            temp[tPos++] = array[leftPos++];
        else
            temp[tPos++] = array[rightPos++];
    }

    while(leftPos <= leftEnd)
        temp[tPos++] = array[leftPos++];

    while(rightPos <= rightEnd)
        temp[tPos++] = array[rightPos++];

    for(int i = 0; i < n; ++i, --rightEnd)
        array[rightEnd] = temp[rightEnd];
}
