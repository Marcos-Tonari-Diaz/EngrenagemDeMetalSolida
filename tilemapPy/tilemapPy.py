import sys

fname = sys.argv[1];
width = int(sys.argv[2]);
height = int(sys.argv[3]);

map = [[0 for i in range(width)] for j in range(height)]

out = open(fname+".map", "w")
for i in map:
    for j in i:
        out.write(str(j))
    out.write("\n")
