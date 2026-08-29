
# Scene de test pour la nettete de l'ombre (comparer avec solar_system.ss,
# ou le soleil est enorme et proche -> penombre demesuree). Ici le soleil
# est petit et loin -> son rayon angulaire, vu depuis la planete, est
# beaucoup plus proche d'un cas realiste -> l'ombre de la lune sur la
# planete devrait etre bien plus nette. Pas de trou noir -> classic_trajectory.

# Obligatoire:
A 0 255,255,255
C 300,40,-150 0.508,-0.203,0.838 40

# SOLEIL
# <Itentifiant> <Nom> <Position> <Rayon> <Couleur> <Intencite> <Masse> <Velocity> <Texture> <Bumpmap>
so Soleil 0,0,0 10 255,240,200 1.0 1.0 0,0,0 NULL NULL

# Planetes
# <Itentifiant> <Nom> <Position> <Rayon> <Couleur> <RotationSpeed> <Masse> <Velocity> <Texture> <Bumpmap>
sp Cible 400,0,0 30 100,150,255 0 1.0 0,0,0 NULL NULL
sp Lune 350,0,0 8 180,180,180 0 1.0e-3 0,0,0 NULL NULL
