
# Test scene for shadow sharpness. Here the sun is small and far
# away. Its angular radius, seen from the planet, is much closer
# to a realistic case. The moon's shadow on the planet should be
# much sharper.

# ————————————————————————————————————————————————————————————————————————
# Format .ss One line per entity, fields separated by a space.
#
# Mandatory:
# A  <Identifier> <Intensity> <Color>
# C  <Identifier> <Origin> <Direction> <Fov>
#
# L  <Identifier> <Name> <Position> <Intensity> <Color>
# so <Identifier> <Name> <Position> <Diameter> <Color> <Shininess> <Intensity> <Mass> <Velocity> <Texture> <Bumpmap>
# sp <Identifier> <Name> <Position> <Diameter> <Color> <Shininess> <RotationSpeed> <Mass> <Velocity> <Texture> <Bumpmap>
# ri <Identifier> <Name> <Normal> <InnerRadius> <OuterRadius> <Color> <Shininess> <Texture> <Bumpmap>
# bh <Identifier> <Name> <Position> <Mass>
#
# NULL (mandatory) -> if no value (name, texture, bumpmap).
# A ri must directly follow the sphere it belongs to.
# ————————————————————————————————————————————————————————————————————————

A 0 255,255,255
C 300,40,-150 0.508,-0.203,0.838 40

# SUN
so Soleil 0,0,0 10 255,240,200 32 1.0 1.0 0,0,0 NULL NULL

# Planets
sp Cible 400,0,0 30 100,150,255 32 0 1.0 0,0,0 NULL NULL
sp Lune 350,0,0 8 180,180,180 32 0 1.0e-3 0,0,0 NULL NULL
