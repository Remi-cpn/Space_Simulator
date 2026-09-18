
# Solar system at real astronomical scale (positions/velocities/masses
# match the true bodies). Distances use the same 0.0001 AU (~14 960 km)
# unit G_CONST is actually calibrated for -- see note below, do not
# rescale these to plain AU. Not to be confused with solar_system_visual.ss,
# which compresses distances for a single readable frame instead.

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
# Mass == 0.0 disables physics for that body (decorative/static instead
# of N-body simulated).
# A ri must directly follow the sphere it belongs to.
#
# Planet/ring diameters below are x10 real scale for visibility (position
# stays real, only the visual size is cheated). The Sun keeps its real
# diameter -- x10 would put its radius past Mercury's orbit. Moons are
# left out for now : their real orbital offset from their parent is
# smaller than the parent's x10 radius, which would bury them inside it.
# ————————————————————————————————————————————————————————————————————————

A 0.2 255,255,255
C 0,0,-2000 0,0,1 70

# Sun
so Sun 0,0,0 930 255,240,200 32 1.0 1.0 0,0,0 assets/textures/sun/sun.png NULL

# Mercury (i=7°)
sp Mercury 3870,0,0 200 180,180,180 1 0.001072 1.65e-7 0,33.7,274.4 assets/textures/mercury/mercury.png NULL

# Venus (i=3.4°, retrograde rotation)
sp Venus 7230,0,0 350 255,200,100 1 -0.000259 2.45e-6 0,12.0,201.9 assets/textures/venus/venus_surface.png NULL

# Earth (i=0°)
sp Earth 10000,0,0 200 100,150,255 1 0.06283 3.003e-6 0,0,172.1 assets/textures/earth/earthmap2k.png assets/textures/earth/earthbump2k.png

# Mars (i=1.85°)
sp Mars 15240,0,0 100 220,100,70 1 0.06100 3.21e-7 0,4.50,139.2 assets/textures/mars/mars.png NULL

# Jupiter (i=1.3°)
sp Jupiter 52030,0,0 500 255,200,150 1 0.15324 9.543e-4 0,1.710,75.39 assets/textures/jupiter/jupiter.png NULL

# Saturn (i=2.49°)
sp Saturn 95370,0,0 600 255,220,180 1 0.14280 2.857e-4 0,2.420,55.65 assets/textures/saturn/saturn.png NULL
ri SaturnRing 1.5,-3.894,0.449 360 660 200,180,140 1 assets/textures/saturn/saturn_ring.png NULL

# Uranus (i=0.77°)
sp Uranus 191910,0,0 400 180,220,255 1 0.0 4.37e-5 0,0.528,39.27 assets/textures/uranus/uranus.png NULL

# Neptune (i=1.77°)
sp Neptune 300700,0,0 380 100,150,255 1 0.0 5.15e-5 0,0.969,31.37 assets/textures/neptune/neptune.png NULL
