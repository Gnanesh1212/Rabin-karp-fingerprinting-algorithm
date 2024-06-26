# d is the number of characters in the input alphabet
d = 256

# pat -> pattern
# txt -> text
# q -> A prime number


def search(pat, txt, q):
    M = len(pat)
    N = len(txt)
    h = 1

    # The value of h would be "pow(d, M-1)%q"
    for _ in range(M - 1):
        h = (h * d) % q

    # Calculate the hash value of pattern and first window
    # of text
    p = sum(ord(pat[i]) * (d ** (M - i - 1)) for i in range(M)) % q
    t = sum(ord(txt[i]) * (d ** (M - i - 1)) for i in range(M)) % q

    # Slide the pattern over text one by one
    for i in range(N - M + 1):
        # Check the hash values of current window of text and
        # pattern if the hash values match then only check
        # for characters one by one
        if p == t:
            # Check for characters one by one
            if txt[i:i+M] == pat:
                print("Pattern found at index " + str(i))

        # Calculate hash value for next window of text: Remove
        # leading digit, add trailing digit
        if i < N - M:
            t = (d * (t - ord(txt[i]) * h) + ord(txt[i + M])) % q

            # We might get negative values of t, converting it to
            # positive
            if t < 0:
                t = t + q


# Driver Code
if __name__ == '__main__':
    patternFile = input("Enter the path of the pattern file: ")
    textFile = input("Enter the path of the text file: ")

    try:
        with open(patternFile, 'r') as f:
            pat = f.read().strip()

        with open(textFile, 'r') as f:
            txt = f.read().strip()

        # A prime number
        q = 101

        # Function Call
        search(pat, txt, q)

    except FileNotFoundError:
        print("Error: Unable to open file(s).")
