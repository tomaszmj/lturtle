from collections import Counter

keywords = ["forward",  "rotate",  "penup",  "pendown",  "pencolour",  "goto",
            "pensize", "scale",  "pushstate",  "popstate", "evaluate", 
            "execute", "redefine"]

def gethash(string, coeff0, coeff1, coeff2):
    retval = 0
    for c in string:
        retval = coeff0*retval ^ coeff1*ord(c)
    retval += coeff2*len(string)
    retval = retval % (len(keywords)+4)
    return retval

best_coeff = [0]*3
best_hash_quality = len(keywords) # the smaller, the better

for coeff0 in range(30):
    for coeff1 in range(30):
        for coeff2 in range(30):
            hashes = [gethash(kw, coeff0, coeff1, coeff2) for kw in keywords]
            hash_ocurrences = dict(Counter(hashes)).values()
            hash_quality = sum(hash_ocurrences) - len(hash_ocurrences)
            if hash_quality < best_hash_quality:
                best_hash_quality = hash_quality
                best_coeff[0], best_coeff[1], best_coeff[2] = coeff0, coeff1, coeff2

print("best hash quality:", best_hash_quality)
print("best coefficients:", best_coeff[0], best_coeff[1], best_coeff[2])
hashes = [gethash(kw, best_coeff[0], best_coeff[1], best_coeff[2]) for kw in keywords]
print(dict(Counter(hashes)).items())
print("hashes:", dict(zip(keywords, hashes)))
