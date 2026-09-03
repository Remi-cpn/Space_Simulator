
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

# Black hole
bh 1 0,0,0 1