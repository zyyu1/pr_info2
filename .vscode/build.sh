#!/usr/bin/env bash
# Inkrementeller Build fuer macOS/Linux (nur g++).
# $1 = Boost-Include-Pfad (optional, leer = kein -I)
set -e

BOOST="$1"
INC=""
[ -n "$BOOST" ] && INC="-I$BOOST"
OUT="build/Debug/outDebug"

mkdir -p build/Debug

# Zeitstempel plattformuebergreifend (Linux: stat -c, macOS: stat -f)
mtime() { stat -c %Y "$1" 2>/dev/null || stat -f %m "$1"; }

# Neuester Header im aktuellen Ordner (ohne Unterordner)
newest_h=0
for h in *.h *.hpp; do
  [ -e "$h" ] || continue
  t=$(mtime "$h")
  [ "$t" -gt "$newest_h" ] && newest_h=$t
done

objs=()
for f in *.cpp; do
  [ -e "$f" ] || continue
  o="build/Debug/${f%.cpp}.o"
  objs+=("$o")

  rebuild=0
  if [ ! -f "$o" ]; then
    rebuild=1
  else
    ot=$(mtime "$o")
    ft=$(mtime "$f")
    if [ "$ft" -gt "$ot" ]; then rebuild=1; fi
    if [ "$newest_h" -gt "$ot" ]; then rebuild=1; fi
  fi

  if [ "$rebuild" -eq 1 ]; then
    echo "Kompiliere $f"
    g++ -std=c++17 -g -Wall -DBOOST_ALL_NO_LIB $INC -c "$f" -o "$o"
  fi
done

echo "Linke $OUT"
g++ -std=c++17 -g -o "$OUT" "${objs[@]}"
