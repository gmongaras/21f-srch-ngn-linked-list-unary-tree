f2 = open(".\\stopWords2.txt", 'w')

with open(".\\stopWords.txt", 'r') as f:
    for a in f:
        a = a.strip()
        print(a)
        f2.write(a + ",")


f2.close()
