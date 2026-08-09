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

---

## Stack technique

| Composant        | Choix                                    |
|------------------|------------------------------------------|
| Langage hôte     | C                                        |
| Fenêtre / input  | SDL2                                     |
| GPU              | OpenGL (core profile) + GLSL             |
| Rendu            | Fullscreen quad + fragment shader        |
| Physique lumière | Intégration RK4 **dans le fragment shader** (1 pixel = 1 géodésique) |
| Dynamique corps  | Moteur N-corps newtonien hérité du RT (réintégré en v3) |

Le CPU orchestre : fenêtre, événements, uniforms (caméra, scène, paramètres).
La physique de la lumière vit dans le shader.

---

## v1 — Le trou noir (validation du moteur)

### Phase 0 — Socle GPU
> Objectif : un pipeline de contrôle total.

- [x] Fenêtre SDL2 + contexte OpenGL.
- [ ] Compilation de shaders avec **affichage des logs d'erreur**.
- [ ] Fullscreen quad + fragment shader affichant un dégradé UV.
- [ ] Boucle de rendu, gestion du resize, uniform `time` animé.

**Validation :** dégradé fluide, 60 fps, aucun warning de compilation shader.

### Phase 1 — Ciel étoilé, rayons droits
> Objectif : reconstruire l'« univers témoin » du RT, dans le shader.

- [ ] Texture panoramique équirectangulaire (fonds NASA libres de droits :
      *Deep Star Maps*).
- [ ] Caméra en uniforms : position, orientation, FOV — mêmes maths que le RT.
- [ ] Par pixel : direction du rayon → (longitude, latitude) → échantillonnage.
- [ ] Contrôles caméra basiques (souris = orientation).

**Validation :** ciel identique au fond du RT, navigation fluide.
Référence visuelle : toute déformation future se lit par rapport à elle.

### Phase 2 — Théorie (papier, pas de code)
> Objectif : comprendre chaque terme avant de l'intégrer.

- [ ] Métrique de Schwarzschild, rayon `rs = 2GM/c²`, unités du simulateur
      (poser `G = c = 1`, distances en multiples de `rs`).
- [ ] Équation d'orbite d'un photon (forme de Binet relativiste) :
      trajectoire 2D `u(φ)` avec `u = 1/r` dans le plan du rayon.
- [ ] Construction du plan de chaque rayon + passage 3D → 2D → 3D.
- [ ] Conditions initiales : paramètre d'impact `b`, direction de départ.

**Validation :** savoir expliquer l'équation terme par terme, et prédire :
sphère de photons à `1.5 rs`, capture si `b < b_crit ≈ 2.6 rs`.

### Phase 3 — Intégration des géodésiques
> Objectif : la courbure entre dans le shader.

- [ ] RK4 sur l'équation d'orbite, pas fixe pour commencer.
- [ ] Les trois sorties : horizon (`r < rs`), évasion (`r > r_max`,
      direction finale → skybox), budget de pas épuisé.
- [ ] Uniforms : masse, position du trou noir, nombre de pas, taille du pas.
- [ ] Précision : `highp` partout ; surveiller les artefacts près de
      l'horizon (pas adaptatif si besoin).

**Validation :** la silhouette noire apparaît, entourée de déformations.
Aucun disque n'a été modélisé — si tu le vois, la physique est juste.

### Phase 4 — Validation quantitative
> Objectif : prouver que c'est correct, pas juste joli.

- [ ] Diamètre de la silhouette ≈ `5.2 rs` — mesurable en pixels via le FOV.
- [ ] Sphère émissive lointaine derrière le trou noir → **anneau d'Einstein**
      à l'alignement parfait caméra–trou noir–source.
- [ ] Rayons lointains : déflexion ≈ formule analytique `4GM/(c²b)` —
      vérifiable en repassant quelques rayons de référence sur CPU.
- [ ] Anneau de photons fin et brillant au bord de la silhouette.

**Validation :** les chiffres collent à la théorie à quelques % près.

### Phase 5 — Confort
- [ ] Supersampling (N rayons par pixel, moyennés) — mélange *intra*-pixel
      uniquement.
- [ ] Masse ajustable en direct, zoom, capture d'écran.
- [ ] Exposition / gamma.

---

## v2 — Intégration du RT : les objets entrent en scène

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

## v3 — Dynamique : l'espace s'anime

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

## v4 — Disque d'accrétion et effets relativistes

- [ ] Disque émissif dans le plan équatorial du trou noir.
- [ ] Redshift gravitationnel (la lumière s'extrait du puits → rougit).
- [ ] Beaming relativiste (asymétrie de brillance type M87 / Interstellar).

## v5 — Kerr : le trou noir en rotation

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

## Références à consulter

- Textures : NASA SVS *Deep Star Maps* (domaine public) ; textures
  planétaires libres (mots-clés *planet texture equirectangular*).
- Théorie : chapitres « orbites de photons / métrique de Schwarzschild »
  d'un cours introductif de relativité générale ; mots-clés
  *photon geodesics Schwarzschild ray tracing*.
- Pour se situer : l'article technique de l'équipe d'*Interstellar*
  (Double Negative / Kip Thorne) sur leur moteur de rendu gravitationnel.
