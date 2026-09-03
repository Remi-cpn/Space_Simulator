
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
# <Mass>/<Velocity> on sp/so lines must be filled in (line format) but
# are not used yet (physics disabled).
# A ri must directly follow the sphere it belongs to.
# ————————————————————————————————————————————————————————————————————————

A 0.1 255,255,255
C 0,0,-20 0,0,1 70
L NULL 0,30,0 0.8 255,255,255

# SUN
so NULL -20,0,0 10 255,240,200 32 0.8 1.0 0,0,0 NULL NULL

# Planets
sp Terre 20,0,0 10 100,150,255 32 0 3.003e-6 0,158.0,0 NULL NULL

# Black hole
bh 1 0,0,0 1