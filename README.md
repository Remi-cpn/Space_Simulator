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

Premier visuel du trou noir
![alt text](image.png)

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
| GPU              | OpenGL + GLSL                            |
| Rendu            | Compute shader (`image2D` + `imageStore`) + blit vers l'écran |
| Physique lumière | Intégration RK4 **dans le compute shader** (1 pixel = 1 géodésique) |
| Dynamique corps  | Moteur N-corps newtonien hérité du RT (réintégré en v3) |

Le CPU orchestre : fenêtre, événements, uniforms (caméra, scène, paramètres).
La physique de la lumière vit dans le shader.

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

---

## Théorie

### Schwarzschild

`rs = 2GM/c²`
Toute masse a un rayon de Schwarzschild. C'est le rayon en dessous duquel il faudrait
comprimer une masse donnée pour qu'elle devienne un trou noir.
La Terre a un `rs` d'environ 9 mm, le Soleil environ 3 km.

### Équation d'orbite d'un photon

En choisissant des unités de longueur/masse/temps adaptées (unités géométrisées),
on peut poser `G = 1` et `c = 1` — pas parce que ces constantes valent réellement 1,
mais parce que leur valeur numérique dépend entièrement du système d'unités choisi.
Ce choix les élimine de toutes les équations : `rs = 2GM/c²` devient `rs = 2M`.

Se restreindre au plan du rayon:
> On part de l'équation de l'intervalle spatio-temporel:
>`ds² = -(1 - rs/r) dt² + dr²/(1 - rs/r) + r²(dθ² + sin²θ dφ²)`
>- `-(1 - rs/r) dt²` — dilatation du temps
>- `dr²/(1 - rs/r)` — contraction radiale
>- `r² dθ²` — partie angulaire polaire
>- `r² sin²θ dφ²` — partie angulaire azimutale
>
> Grâce à la symétrie sphérique, le moment angulaire est conservé → la trajectoire
> reste dans un plan fixe. L'axe polaire des coordonnées sphériques étant un choix
> arbitraire, on l'oriente perpendiculairement à ce plan : il coïncide alors avec
> l'équateur, `θ = π/2`.
> `dθ = 0` vu que `θ` ne change jamais le long du trajet, sa dérivée est nulle.
> On obtient donc après simplification : `ds² = -(1 - 2M/r) dt² + dr²/(1 - 2M/r) + r² dφ²`

Condition de photon:
> La lumière suit une géodésique nulle : `ds² = 0` tout le long de sa trajectoire
> (contrairement à une particule massive, où `ds²` mesure le temps propre).

> Un photon n'ayant pas de temps propre (`ds` est toujours nul pour lui), on
> paramètre sa trajectoire par un paramètre affine `λ` quelconque. La règle de la
> chaîne donne :
`dt = ṫ dλ`, `dr = ṙ dλ`, `dφ = φ̇ dλ`.

> En replaçant ça dans l'équation :
> `ds² = -(1-2M/r)(ṫ dλ)² + (ṙ dλ)²/(1-2M/r) + r²(φ̇ dλ)²`

>Chaque terme a un `dλ²` en facteur commun — on peut le sortir :
>`ds² = [ -(1-2M/r)ṫ² + ṙ²/(1-2M/r) + r²φ̇² ] × dλ²`

> Et comme `ds² = 0` (condition de photon) et que `dλ² ≠ 0` on a :
`-(1-2M/r)ṫ² + ṙ²/(1-2M/r) + r²φ̇² = 0`

Quantités conservées:

> Selon Euler-Lagrange, si une variable n'apparaît que par sa dérivée (jamais
> elle-même) dans l'expression ci-dessus, la quantité associée à cette dérivée
> reste constante le long du trajet. Ni `t` ni `φ` n'apparaissent explicitement
> (seulement `ṫ` et `φ̇`) → deux quantités conservées :

> L'énergie du photon : `E = (1-2M/r) ṫ`

> Son moment angulaire : `L = r² φ̇`

> Après substitution dans notre équation on a : `-E²/(1-2M/r) + ṙ²/(1-2M/r) + L²/r² = 0` — on a donc éliminé `ṫ`.

> On simplifie : `-E² + ṙ² + (1-2M/r) × L²/r² = 0`

> On isole : `ṙ² = E² - (1-2M/r) × L²/r²`

L'équation de Binet relativiste pour l'orbite d'un photon

> On a `ṙ = dr/dλ` et `φ̇ = dφ/dλ`. Diviser l'un par l'autre élimine `λ` : `dr/dφ = ṙ/φ̇`

> Et on connaît `φ̇ = L/r²` donc : `ṙ = φ̇ × (dr/dφ) = (L/r²) × (dr/dφ)`

> On obtient : `(L/r²)² × (dr/dφ)² = E² - (1-2M/r)L²/r²`

> On isole `(dr/dφ)²` : `(dr/dφ)² = (E²/L²)r⁴ - (1-2M/r)r²`

> On pose `u = 1/r` (donc `r = 1/u` et `dr/dφ = -(1/u²)(du/dφ)`), on substitue et
> on simplifie : `(du/dφ)² = E²/L² - u² + 2Mu³`

> On introduit le paramètre d'impact `b = L/E` : `(du/dφ)² = 1/b² - u² + 2Mu³`

> Et après dérivation par rapport à `φ` on obtient : `d²u/dφ² + u = 3Mu²`


# Roadmap

## v1 — Le trou noir (validation du moteur)

### Phase 0 — Socle GPU
> Objectif : un pipeline de contrôle total.

- [x] Fenêtre SDL2 + contexte OpenGL.
- [x] Compilation de shaders avec **affichage des logs d'erreur**.
- [x] Compute shader écrivant un dégradé UV dans une texture (`imageStore`) + présentation par blit (`glBlitFramebuffer`).
- [x] Boucle de rendu, gestion du resize.


### Phase 1 — Ciel étoilé, rayons droits
> Objectif : reconstruire l'« univers témoin » du RT, dans le shader.

- [x] Texture panoramique équirectangulaire.
- [x] Caméra en uniforms : position, orientation, FOV — mêmes maths que le RT.
- [x] Par pixel : direction du rayon → (longitude, latitude) → échantillonnage.
- [x] Contrôles caméra basiques.

**Validation :** ciel identique au fond du RT, navigation fluide.

### Phase 2 — Théorie
> Objectif : comprendre chaque terme avant de l'intégrer.

- [x] Métrique de Schwarzschild, rayon `rs = 2GM/c²`, unités du simulateur
      (poser `G = c = 1`, distances en multiples de `rs`).
- [x] Équation d'orbite d'un photon (forme de Binet relativiste) :
      trajectoire 2D `u(φ)` avec `u = 1/r` dans le plan du rayon.
- [x] Construction du plan de chaque rayon + passage 3D → 2D → 3D.
- [x] Conditions initiales : paramètre d'impact `b`, direction de départ.

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

## Références à consulter

- Textures : NASA SVS *Deep Star Maps* (domaine public) ; textures
  planétaires libres (mots-clés *planet texture equirectangular*).
- Théorie : chapitres « orbites de photons / métrique de Schwarzschild »
  d'un cours introductif de relativité générale ; mots-clés
  *photon geodesics Schwarzschild ray tracing*.
- Pour se situer : l'article technique de l'équipe d'*Interstellar*
  (Double Negative / Kip Thorne) sur leur moteur de rendu gravitationnel.
