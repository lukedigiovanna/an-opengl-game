import math

vertices = [0, 0, 0, 0.5, 0.5]

N = 20
for i in range(N):
    angle = i / N * 2 * math.pi
    x = math.cos(angle) * 0.5
    y = math.sin(angle) * 0.5
    vertices.append(x)
    vertices.append(y)
    vertices.append(0.0)
    vertices.append(x + 0.5)
    vertices.append(y + 0.5)

indices = []
for i in range(N):
    indices.append(0)
    indices.append(i + 1)
    indices.append(i + 2)

indices.append(0)
indices.append(N - 1)
indices.append(1)

print(", ".join(map(lambda v: "{:.4f}f".format(v), vertices)))
print(", ".join(map(str, indices)))