from build import Zenith

mat = Zenith.Matrix(3, 3)
print(mat.get(0, 0))
mat.set(0, 0, 1.0)
print(mat.get(0, 0))