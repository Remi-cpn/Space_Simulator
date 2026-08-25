# Simulation d'espace en rendu relativiste

Simulation d'espace en C/GLSL rendue par raytracing relativiste : la lumière
est intégrée le long des géodésiques de l'espace-temps. Trous noirs,
lentilles gravitationnelles et dynamique N-corps émergent des équations —
rien n'est dessiné, tout est calculé.

Le trou noir n'est que le point de départ : c'est le cas extrême qui valide
le moteur. L'objectif est une scène spatiale complète — corps célestes,
lumière courbée, dynamique gravitationnelle — héritière du projet RT
(École 42), dont le moteur passe de l'intersection géométrique à
l'intégration numérique de trajectoires.

---

![alt text](assets/readme/Blackholev1.png)
*trou noir V1*

---

## Sommaire

- [Patch Note](#patch-note)
- [Principe du moteur](#principe-du-moteur)
- [Stack technique](#stack-technique)
- [Contrôles](#contrôles)
- [Rendu par shaders](#rendu-par-shaders)
- [Théorie](#théorie)
- [Roadmap](#roadmap)
- [Pièges connus](#pièges-connus)
- [Dette technique](#dette-technique--à-retravailler-plus-tard)
- [Références à consulter](#références-à-consulter)

---

## Patch Note

### V1 — Ce qui est fait

Première version validée. Résumé, une ligne par fonctionnalité :

- Pipeline de rendu 100 % compute shader (aucun vertex/fragment).
- Caméra libre (déplacement + rotation).
- Ciel étoilé panoramique (skybox équirectangulaire) avec cache de textures.
- Théorie posée et documentée : métrique de Schwarzschild, équation de
  Binet relativiste, unités géométrisées.
- Intégration RK4 3D des géodésiques d'un photon (approche "starless"),
  pas adaptatif selon la distance au trou noir.
- Trois issues par rayon : horizon (noir), évasion (couleur du ciel),
  budget de pas épuisé.
- Silhouette du trou noir et lentille gravitationnelle visibles et
  physiquement cohérentes (pas de disque modélisé — v4).
- Supersampling (N rayons/pixel, séquence à ratio doré pour un
  échantillonnage régulier intra-pixel).
- HUD de debug terminal : arbre de valeurs par catégorie, navigation
  (`Tab` / `Entrée` / `Retour arrière`), cible surlignée.
- Édition à la molette de n'importe quelle valeur enregistrée dans
  l'arbre, avec coefficient de vitesse réglable (`Maj` + molette).
- Paramètres ajustables en direct sans recompilation (masse et position
  du trou noir, position/direction/fov caméra, nombre de rayons...).
- Exposition et gamma réglables (contrôle de la luminosité et du contraste
  perçu de l'image finale, avant affichage).

---

## Principe du moteur

1. La caméra émet un rayon par pixel (comme un raytracer classique).
2. Chaque rayon est **intégré pas à pas** le long de sa géodésique dans un
   espace-temps courbé par les masses de la scène.
3. À chaque pas, le rayon peut : franchir un horizon (**noir**), rencontrer
   un objet de la scène (**couleur de l'objet** — à partir de la v2),
   s'échapper (**fond étoilé**), ou épuiser son budget de pas.
4. Chaque rayon écrit uniquement dans **son** pixel. La déformation vient de
   *où il lit* dans la scène, jamais de *où il écrit* sur l'écran.

Simplification de la v1 : autour d'un trou noir de Schwarzschild (statique,
sans rotation), chaque rayon reste confiné dans un plan → l'intégration 3D
se réduit à une équation d'orbite 2D par rayon.

```mermaid
flowchart LR
    A[Caméra : un rayon par pixel] --> B[Intégration RK4 pas à pas]
    B --> C{Horizon ?}
    C -->|oui| D[Noir]
    C -->|non| E{Objet ? — v2}
    E -->|oui| F[Couleur objet]
    E -->|non| G{Évadé ?}
    G -->|oui| H[Ciel étoilé]
    G -->|non| I{Budget épuisé ?}
    I -->|non| B
    I -->|oui| D
```

---

## Stack technique

| Composant        | Choix                                    |
|------------------|------------------------------------------|
| Langage hôte     | C                                        |
| Fenêtre / input  | SDL2                                     |
| GPU              | OpenGL + GLSL                            |
| Rendu            | Compute shader (`image2D` + `imageStore`) + blit vers l'écran |
| Physique lumière | Intégration RK4 **dans le compute shader** (1 pixel = 1 géodésique) |
| Dynamique corps  | Moteur N-corps newtonien hérité du RT (réintégré en v3) |

Le CPU orchestre : fenêtre, événements, uniforms (caméra, scène, paramètres).
La physique de la lumière vit dans le shader.

---

## Contrôles

| Touche              | Action                                  |
|---------------------|------------------------------------------|
| `W` / `A` / `S` / `D` | Déplacement avant / gauche / arrière / droite |
| `Espace` / `Ctrl`   | Déplacement haut / bas                    |
| Flèches directionnelles | Rotation de la caméra (regard)       |
| `Page Up` / `Page Down` | Nombre de rayons par pixel (supersampling), min. 1 |
| `Tab`               | Navigue dans le HUD (catégorie suivante, ou valeur suivante une fois dans une catégorie) |
| `Entrée`            | Rentre dans la catégorie ciblée           |
| `Retour arrière`    | Ressort de la catégorie courante          |
| Molette souris      | Ajuste la valeur ciblée dans le HUD — le pas grandit avec le défilement continu (coefficient de vitesse `coef molette`, 1 à 5, lui-même visible/réglable dans le HUD) |
| `Échap`             | Quitter                                   |

### HUD de debug (terminal)

Pas de vrai HUD à l'écran pour l'instant : un widget dessiné (type ImGui) passerait
par le pipeline vertex/fragment classique, hors de portée tant qu'on reste dans les
clous du sujet RT (fragment shaders interdits) — remis à plus tard.

En attendant, un HUD texte tourne dans le terminal (redessiné sur place via des
séquences ANSI, pas de spam) : les valeurs de la simulation sont rangées dans un
arbre par catégorie (`Paramètres`, `Trou noir`, `Objets`, `Caméra`), chaque feuille
portant un pointeur direct vers la vraie variable (`bh.mass`, `cam.fov`, etc.) plutôt
qu'une copie. `Tab` déplace la cible affichée (`Target : ...`) à l'intérieur du
niveau courant en bouclant dessus (catégories au niveau racine, valeurs une fois
entré dans une catégorie via `Entrée`) ; la molette modifie directement la valeur
ciblée, avec un pas propre à son type (entier ou flottant) et un plancher à `0`
quand une valeur négative n'aurait pas de sens (masse, nombre de rayons).

![alt text](assets/readme/HUD.png)

---

## Rendu par shaders

Aucune boucle sur les pixels n'existe dans le code C : le calcul de
l'image est délégué au GPU. Le programme dispatch un compute shader écrit en GLSL
(compilé par le driver au lancement, d'où le module shader.c qui récupère les logs du
compilateur GPU) : une invocation par pixel, en parallèle, écrit directement dans une
texture via `imageStore`. Chaque invocation déduit son rayon, l'intègre le long de sa
géodésique, et écrit une couleur. L'image est ensuite présentée à l'écran par un blit
(`glBlitFramebuffer`), sans jamais passer par le pipeline vertex/fragment. Le code C
n'est que l'orchestrateur : fenêtre, événements, et envoi des uniforms (caméra, masse,
paramètres) qui alimentent le shader à chaque frame.

```mermaid
sequenceDiagram
    participant CPU as CPU (C)
    participant GPU as GPU (compute shader)
    participant Img as Texture (image2D)
    participant Ecran as Écran

    CPU->>GPU: uniforms (caméra, masse, paramètres)
    CPU->>GPU: glDispatchCompute
    loop une invocation par pixel
        GPU->>GPU: intègre la géodésique
        GPU->>Img: imageStore (couleur du pixel)
    end
    CPU->>CPU: glMemoryBarrier
    Img->>Ecran: glBlitFramebuffer
```

---

## Théorie

### Schwarzschild

`rs = 2GM/c²` — le rayon de Schwarzschild. C'est la limite en dessous de laquelle
il faudrait comprimer une masse pour qu'elle devienne un trou noir. Rien d'exotique
dans la formule en soi : n'importe quelle masse en a un, même la Terre (environ
9 mm) ou le Soleil (environ 3 km) — elles ne s'effondrent simplement jamais
jusque-là.

### Équation d'orbite d'un photon

Pour éviter de trimballer `G` et `c` partout, on choisit des unités où ils valent 1
(unités géométrisées) — ça ne change rien à la physique, juste à combien de
lettres on écrit. `rs = 2GM/c²` devient `rs = 2M`.

On part de la métrique de Schwarzschild complète :
`ds² = -(1 - rs/r) dt² + dr²/(1 - rs/r) + r²(dθ² + sin²θ dφ²)`.

Chaque terme raconte quelque chose : le premier dit que le temps s'écoule
différemment selon la distance au trou noir, le deuxième que l'espace radial se
contracte, les deux derniers décrivent la position angulaire classique en
coordonnées sphériques. Grâce à la symétrie sphérique, un rayon qui part dans un
plan y reste — le moment angulaire se conserve. On peut donc orienter les axes
pour que ce plan soit l'équateur (`θ = π/2`), ce qui tue le terme en `dθ` puisqu'il
ne bouge jamais. La métrique se simplifie tout de suite :
`ds² = -(1 - 2M/r) dt² + dr²/(1 - 2M/r) + r² dφ²`.

Un photon suit une géodésique nulle : `ds² = 0` tout au long de sa trajectoire
(contrairement à une particule massive, dont `ds²` mesure le temps propre — un
photon n'en a pas). Comme il n'a pas de temps propre pour paramétrer son chemin,
on utilise un paramètre affine `λ` quelconque : `dt = ṫ dλ`, `dr = ṙ dλ`,
`dφ = φ̇ dλ`. En remplaçant dans la métrique, chaque terme se retrouve avec un
`dλ²` en facteur qu'on peut sortir, et comme `ds² = 0` et `dλ² ≠ 0`, ce qui reste
doit valoir zéro :
`-(1-2M/r)ṫ² + ṙ²/(1-2M/r) + r²φ̇² = 0`.

C'est là qu'Euler-Lagrange devient utile : si une variable n'apparaît dans
l'équation que par sa dérivée (jamais elle-même), la quantité associée à cette
dérivée reste constante tout au long du trajet. Ni `t` ni `φ` n'apparaissent en
tant que tels — seulement `ṫ` et `φ̇` — donc on récupère deux quantités
conservées gratuitement : l'énergie du photon `E = (1-2M/r) ṫ`, et son moment
angulaire `L = r² φ̇`. En les réinjectant dans l'équation (et en éliminant `ṫ` au
passage), on arrive à :
`ṙ² = E² - (1-2M/r) × L²/r²`.

Reste à transformer ça en équation d'orbite, c'est-à-dire en `r(φ)` plutôt qu'en
fonction du temps. `ṙ/φ̇ = dr/dφ` fait disparaître `λ`, et comme `φ̇ = L/r²`, on
peut réécrire `ṙ` en fonction de `dr/dφ`. Après substitution et le changement de
variable classique en mécanique céleste (`u = 1/r`, qui simplifie beaucoup
l'algèbre), on obtient :
`(du/dφ)² = 1/b² - u² + 2Mu³`
où `b = L/E` est le paramètre d'impact — grosso modo, à quelle distance du trou
noir le rayon "viserait" s'il n'y avait pas de gravité.

Une dernière dérivation par rapport à `φ` donne la forme finale, l'équation de
Binet relativiste :
`d²u/dφ² + u = 3Mu²`

Le terme `3Mu²` à droite, c'est toute la relativité générale condensée en une
seule correction — sans lui, on retomberait sur l'équation d'une orbite
newtonienne classique.

---

## Roadmap

### v2 — Intégration du RT : les objets entrent en scène

> Le retour du raytracer classique, mais dans un espace courbé.

- [ ] Format de scène hérité du `.rt` : sphères / planètes avec position,
      rayon, texture ou couleur.
- [ ] Intersection le long de la géodésique : chaque pas d'intégration est
      un petit segment quasi-droit → test d'intersection classique
      segment/objet, réutilisant les maths du RT.
- [ ] Objets émissifs (soleils : couleur directe, sans éclairage) et objets
      éclairés (planètes : Phong adapté — la source vue depuis le point
      d'impact).
- [ ] Textures planétaires (mapping sphérique, déjà connu du RT).
- [ ] Cas spectaculaire à valider : une planète *derrière* le trou noir,
      visible déformée en arc.

**Validation :** une scène mixte — trou noir + planètes texturées + soleil —
où les objets proches de l'horizon apparaissent distordus.

### v3 — Dynamique : l'espace s'anime

- [ ] Réintégration du moteur N-corps newtonien du RT (mis de côté, pas
      supprimé) : les corps massifs s'attirent et orbitent.
- [ ] Couplage simulation → rendu : à chaque frame, le N-corps fournit les
      positions, les uniforms les poussent au shader, le shader photographie
      l'instant.
- [ ] Intégrateur symplectique (leapfrog/Verlet) pour la stabilité des
      orbites à long terme — remplace Euler/RK4 côté dynamique.
- [ ] Scènes : système planétaire autour du trou noir, lentille
      gravitationnelle balayant le fond au passage d'un corps.

**Validation :** orbites stables sur de longues durées (énergie conservée),
animation fluide temps réel.

### v4 — Disque d'accrétion et effets relativistes

- [ ] Disque émissif dans le plan équatorial du trou noir.
- [ ] Redshift gravitationnel (la lumière s'extrait du puits → rougit).
- [ ] Beaming relativiste (asymétrie de brillance type M87 / Interstellar).

### v5 — Kerr : le trou noir en rotation

- [ ] Métrique de Kerr → la simplification « un plan par rayon » tombe :
      intégration 3D complète des géodésiques.
- [ ] Ergosphère, entraînement de l'espace-temps (frame dragging).

---

## Pièges connus

- **Debug shader :** pas de printf. Stratégie : encoder les valeurs
  suspectes dans la couleur de sortie et lire l'image.
- **Précision float :** les géodésiques proches de `b_crit` sont
  hyper-sensibles — c'est physique (instabilité de la sphère de photons),
  mais ça amplifie les erreurs numériques.
- **Pas d'intégration :** trop grand → silhouette fausse ; trop petit → GPU
  à genoux. Se règle en phase 4 contre les chiffres théoriques.
- **v2 — intersections manquées :** un pas trop grand peut « sauter »
  par-dessus un objet fin ; borner la taille du pas par la taille du plus
  petit objet proche.
- **Performance :** si le temps réel décroche, réduire la résolution interne
  et upscaler avant de toucher au pas d'intégration.

## Dette technique — à retravailler plus tard

Compromis acceptés consciemment pour avancer, à revisiter quand le besoin
deviendra bloquant (pas des bugs à corriger dans l'immédiat).

- **Caméra libre — dérive de roulis vs boucle complète verticale :**
  `calcul_viewport` reconstruit `hor_n` à partir de sa propre valeur
  précédente plutôt que de se recaler sur `up` — choix délibéré pour
  permettre une boucle complète (regarder droit vers le haut et continuer)
  sans singularité de type gimbal lock. Coût : une légère dérive de roulis
  s'accumule sur des rotations combinées prolongées (haut/bas + gauche/droite
  enchaînés). Vraie solution : orientation par quaternion (ni dérive, ni
  singularité aux pôles) — demande d'ajouter la multiplication de quaternions
  et la rotation d'un vecteur par quaternion à la `librt`, pas encore fait.

- **Scintillement près de l'anneau de photons :** les pixels dont le rayon
  passe très proche de `b_crit` scintillent d'une frame à l'autre — un rayon
  peut faire un tour de plus ou de moins autour du trou noir pour un
  déplacement infime de la caméra ou une infime différence de précision
  flottante, renvoyant une couleur de ciel complètement différente. C'est
  physique (instabilité de la sphère de photons, déjà notée dans "Pièges
  connus"), amplifié par l'absence de supersampling (un seul rayon par
  pixel, alors que c'est justement la zone la plus "magnifiée" par la
  lentille). Vraie solution : supersampling (Phase 5) — moyenner plusieurs
  rayons par pixel lissera cette instabilité locale.

- **Résolution interne réglable (perf sous charge) :** pour l'instant la
  seule protection contre une charge GPU excessive est le supersampling
  (`nbr_ray`, borné à 1 minimum) — pas de garde-fou dans l'autre sens. Le
  besoin viendra avec la v3 (N-corps) : si la caméra doit rester fluide
  pendant que le GPU est aussi sollicité par la dynamique, il faudra pouvoir
  descendre sous 1 rayon par pixel. Piste envisagée puis écartée pour
  l'instant : partager un rayon entre plusieurs pixels voisins (ex. 1 pour 4)
  directement dans la grille pleine résolution — rejetée à cause de la
  divergence de warp (les invocations "meneuses" et "suiveuses" mélangées
  dans le même warp/wavefront font attendre tout le paquet, donc gain quasi
  nul en pratique). Vraie solution : rendre dans une texture plus petite
  (dispatch réduit, ex. `taille/2` dans chaque dimension) puis upscaler au
  `glBlitFramebuffer` (qui scale nativement src→dst de tailles différentes,
  `GL_NEAREST` pour rester cohérent avec l'esthétique pixelisée) — un vrai
  quart des invocations, sans divergence. Orthogonal au supersampling : les
  deux réglages (résolution interne, `nbr_ray`) pourront cohabiter et se
  piloter indépendamment selon la charge du moment.

## Références à consulter

- Textures : NASA SVS *Deep Star Maps* (domaine public) ; textures
  planétaires libres (mots-clés *planet texture equirectangular*).
- Théorie : chapitres « orbites de photons / métrique de Schwarzschild »
  d'un cours introductif de relativité générale ; mots-clés
  *photon geodesics Schwarzschild ray tracing*.
- Pour se situer : l'article technique de l'équipe d'*Interstellar*
  (Double Negative / Kip Thorne) sur leur moteur de rendu gravitationnel.
