import random

ceil = 8388608

data = [i for i in range(ceil)]
random.shuffle(data)

out = open("inp.txt", 'w')
out.write(" ".join(map(str, data)))
out.close()
