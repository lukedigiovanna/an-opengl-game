import math

vertices = [0, 0]

N = 20
for i in range(N):
    angle = i / N * 2 * math.pi
    vertices.append(math.cos(angle) * 0.5)
    vertices.append(math.sin(angle) * 0.5)

indices = []
for i in range(N):
    indices.append(0)
    indices.append(i + 1)
    indices.append(i + 2)

indices.append(0)
indices.append(N - 1)
indices.append(1)

print(", ".join(map(lambda v: str(v) + 'f', vertices)))
print(", ".join(map(str, indices)))