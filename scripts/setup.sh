#!/bin/sh
# **************************************************************************** #
#   Space_Simulator — setup.sh                                                 #
#   Installe les dépendances système nécessaires à la compilation.             #
#   Usage : ./setup.sh                                                         #
# **************************************************************************** #

# Arrête le script à la première erreur (pas d'installation à moitié faite)
set -e

# ——— Dépendances requises ——————————————————————————————————————————————————— #
# libsdl2-dev      : fenêtre, événements, contexte OpenGL
# libgl1-mesa-dev  : headers OpenGL
DEPENDENCIES="libsdl2-dev libgl1-mesa-dev"


# ——— Couleurs ——————————————————————————————————————————————————————————————— #
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

info()  { printf "%b[Space_Simulator]%b %s\n"  "$GREEN"  "$RESET" "$1"; }
warn()  { printf "%b[Space_Simulator]%b %s\n"  "$YELLOW" "$RESET" "$1"; }
fail()  { printf "%b[Space_Simulator]%b %s\n"  "$RED"    "$RESET" "$1"; exit 1; }


# ——— Vérification ——————————————————————————————————————————————————————————— #
# Vérifie si sdl2-config, il est installé par libsdl2-dev
if command -v sdl2-config >/dev/null 2>&1 && [ -f /usr/include/GL/gl.h ]; then
	info "Dependencies already present (SDL2 $(sdl2-config --version)). Nothing to do."
	exit 0
fi


# ——— Installation ——————————————————————————————————————————————————————————— #
# Possible Debian / Ubuntu uniquement
if ! command -v apt-get >/dev/null 2>&1; then
	fail "apt-get not found. Manually install the equivalent of: $DEPENDENCIES"
fi

info "Missing dependencies, installation of: $DEPENDENCIES"
warn "Sudo will ask for your password."

sudo apt-get update
sudo apt-get install -y $DEPENDENCIES


# ——— Vérification finale ———————————————————————————————————————————————————— #
command -v sdl2-config >/dev/null 2>&1 || fail "SDL2 still not found after installation."
[ -f /usr/include/GL/gl.h ]            || fail "OpenGL headers still not found."

info "Installation complete (SDL2 $(sdl2-config --version)). You can run: make"