
# Stylized solar system (not to real astronomical scale -- distances
# and sizes compressed to stay readable on screen, same spirit as the
# reference diagram).

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
C -74.30,132.17,-300.29 0,-0.38,0.93 80

# SUN
so Soleil 0,0,0 40 255,230,140 32 1.0 1.0 0,0,0 assets/textures/sun/sun.png NULL

# Planets
sp Mercure 50,0,22 12 170,169,173 1 0 1.0e-7 0,0,0 assets/textures/mercury/mercury.png NULL
sp Venus -90,0,0 16 230,200,140 1 0 2.0e-7 0,0,0 assets/textures/venus/venus_surface.png NULL
sp Terre 88,0,-30 18 100,150,255 1 0 3.003e-6 0,0,0 assets/textures/earth/earthmap2k.png NULL
sp Mars -108,0,-72 16 210,110,70 1 0 3.2e-7 0,0,0 assets/textures/mars/mars.png NULL
sp Jupiter 206,0,118 40 230,190,140 1 0 9.5e-4 0,0,0 assets/textures/jupiter/jupiter.png NULL
sp Saturne -250,0,52 34 220,200,150 1 0 2.8e-4 0,0,0 assets/textures/saturn/saturn.png NULL
ri AnneauSaturne 0.45,0.89,0 27 38 200,180,140 1 NULL NULL
sp Uranus 208.20,0,-90.60 16 150,220,230 1 0 4.4e-5 0,0,0 assets/textures/uranus/uranus.png NULL
ri AnneauUranus 0.99,-0.13,0 11 12 180,220,225 1 NULL NULL
sp Neptune -380,0,-78 16 80,110,230 1 0 5.2e-5 0,0,0 assets/textures/neptune/neptune.png NULL
