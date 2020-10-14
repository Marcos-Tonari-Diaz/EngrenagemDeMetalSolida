import sys

fname = sys.argv[1];
height = int(sys.argv[2]);
width = int(sys.argv[3]);

map = [[0 for i in range(width)] for j in range(width)]

out = open(fname+".txt", "w")
for i in map:
    out.write("\n")
    for j in i:
        out.write(str(j))
