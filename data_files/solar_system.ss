
# Systeme solaire stylise (pas a l'echelle astronomique reelle -- distances
# et tailles resserrees pour rester lisibles a l'ecran, meme esprit que le
# schema de reference).

# Obligatoire:
A 0 255,255,255
C -25.74,128.82,-300.21 -0.05,-0.41,0.91 80

# SOLEIL
# <Itentifiant> <Nom> <Position> <Diametre> <Couleur> <Shininess> <Intencite> <Masse> <Velocity> <Texture> <Bumpmap>
so Soleil 0,0,0 40 255,230,140 32 1.0 1.0 0,0,0 assets/textures/sun/sun.png NULL

# Planetes
# <Itentifiant> <Nom> <Position> <Diametre> <Couleur> <Shininess> <RotationSpeed> <Masse> <Velocity> <Texture> <Bumpmap>
sp Mercure 50,0,22 12 170,169,173 1 0 1.0e-7 0,0,0 assets/textures/mercury/mercury.png NULL
sp Venus -90,0,0 16 230,200,140 1 0 2.0e-7 0,0,0 assets/textures/venus/venus_surface.png NULL
sp Terre 88,0,-30 18 100,150,255 1 0 3.003e-6 0,0,0 assets/textures/earth/earthmap2k.png NULL
sp Mars -108,0,-72 16 210,110,70 1 0 3.2e-7 0,0,0 assets/textures/mars/mars.png NULL
sp Jupiter 206,0,118 40 230,190,140 1 0 9.5e-4 0,0,0 assets/textures/jupiter/jupiter.png NULL
sp Saturne -250,0,52 34 220,200,150 1 0 2.8e-4 0,0,0 assets/textures/saturn/saturn.png NULL

# ANNEAUX (Mettre sous sa planete)
# <Itentifiant> <Nom> <Normale> <Rayon Interrieur> <Rayon Exterieur> <Couleur> <Shininess> <Texture> <Bumpmap>
ri AnneauSaturne 0.1,1,0 27 38 200,180,140 1 NULL NULL

sp Uranus 226,0,-74 16 150,220,230 1 0 4.4e-5 0,0,0 assets/textures/uranus/uranus.png NULL
ri AnneauUranus 0.1,1,0 11 12 180,220,225 1 NULL NULL

sp Neptune -380,0,0 16 80,110,230 1 0 5.2e-5 0,0,0 assets/textures/neptune/neptune.png NULL
