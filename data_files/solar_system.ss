
# Systeme solaire stylise (pas a l'echelle astronomique reelle -- distances
# et tailles resserrees pour rester lisibles a l'ecran, meme esprit que le
# schema de reference). Le trou noir est obligatoire (uniforme bh_mass/
# bh_pos toujours lus), place tres loin avec une masse negligeable pour ne
# rien courber ni se voir.

# Obligatoire:
A 0 255,255,255
C 190,80,-350 0,-0.148,0.989 80

# SOLEIL
# <Itentifiant> <Nom> <Position> <Rayon> <Couleur> <Intencite> <Masse> <Velocity> <Texture> <Bumpmap>
so Soleil 0,0,0 40 255,230,140 1.0 1.0 0,0,0 assets/textures/sun/sun.png NULL

# Planetes 
# <Itentifiant> <Nom> <Position> <Rayon> <Couleur> <RotationSpeed> <Masse> <Velocity> <Texture> <Bumpmap>
sp Mercure 60,0,0 6 170,169,173 0 1.0e-7 0,0,0 assets/textures/mercury/mercury.png NULL
sp Venus 90,0,0 9 230,200,140 0 2.0e-7 0,0,0 assets/textures/venus/venus_surface.png NULL
sp Terre 120,0,0 10 100,150,255 0 3.003e-6 0,0,0 assets/textures/earth/earthmap2k.png NULL
sp Mars 150,0,0 8 210,110,70 0 3.2e-7 0,0,0 assets/textures/mars/mars.png NULL
sp Jupiter 230,0,0 24 230,190,140 0 9.5e-4 0,0,0 assets/textures/jupiter/jupiter.png NULL
sp Saturne 280,0,0 20 220,200,150 0 2.8e-4 0,0,0 assets/textures/saturn/saturn.png NULL

# ANNEAUX (Mettre sous sa planete)
# <Itentifiant> <Nom> <Normale> <Rayon Interrieur> <Rayon Exterieur> <Couleur> <Texture> <Bumpmap>
ri AnneauSaturne 0.1,1,0 13 24 200,180,140 assets/textures/saturn/saturn_ring.png NULL

sp Uranus 330,0,0 14 150,220,230 0 4.4e-5 0,0,0 assets/textures/uranus/uranus.png NULL
ri AnneauUranus 0.1,1,0 9 13 180,220,225 NULL NULL

sp Neptune 380,0,0 13 80,110,230 0 5.2e-5 0,0,0 assets/textures/neptune/neptune.png NULL
